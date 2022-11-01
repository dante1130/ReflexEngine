#include "EngineResolve.hpp"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Controller/Physics/QuaternionHelper.hpp"
#include "Controller/ReflexEngine/EngineTime.hpp"
#include "Controller/GUI/DebugLogger.hpp"

#include <string>
#include <ReflexAssertion.hpp>

const constexpr glm::vec3 GRAVITY_CONSTANT = glm::vec3(0.0f, -9.807f, 0.0f);
const constexpr float SLEEP_TIME_THRESHOLD = 1.0f; //in seconds

using namespace rp3d;

EngineResolve::EngineResolve() {
	linear_.velocity = glm::vec3(0);
	linear_.acceleration = glm::vec3(0);

	angular_.velocity = glm::vec3(0);
	angular_.acceleration = glm::vec3(0);

	sleep_.ang_velocity = 5.0f;
	sleep_.lin_velocity = glm::vec3(0.02f, 0.8f, 0.02f); 

	total_mass_ = 0;
	epsilon_value_ = 0;

	body_type_ = BodyType::DYNAMIC;
}

bool EngineResolve::usingReactResolve() { return false; }

void EngineResolve::resolve(float lambda, glm::vec3 vector_to_collision,
                            glm::vec3 contact_normal, int collision_number) {
	float mult = 1.0f;
	if (collision_number == 2) {
		mult = -1.0f;
	}

	// Linear velocity change
	linear_.change = (lambda * contact_normal) / total_mass_ * mult;

	//  Angular velocity change
	angular_.change = (lambda * inverse_rotated_inertia_tensor_) *
	                  glm::cross(vector_to_collision, contact_normal) * mult;

	++number_of_collisions_; 

	if (!can_sleep_) return;

	bool vel_check = sleep_.ang_velocity > glm::length(angular_.velocity) &&
	                 sleep_.lin_velocity.x > std::abs(linear_.velocity.x) &&
	                 sleep_.lin_velocity.y > std::abs(linear_.velocity.y) &&
	                 sleep_.lin_velocity.z > std::abs(linear_.velocity.z);

	/*if (test) {
		std::cout << "Vel check: " << vel_check << std::endl;
		std::cout << "Velocity: " << linear_.velocity.x << " "
		          << linear_.velocity.y << " " << linear_.velocity.z
		          << std::endl;

		test = false;
	}*/

	if (glm::length(linear_.change) > 0.4f) {
		vel_check = false;
	}

	if (vel_check)
		sleep_.time += EngineTime::get_fixed_delta_time();
	else if (sleep_.time > 0.0f) {
		sleep_.time = 0.0f;
		asleep_ = false;
	} 

	if (asleep_) return;

	if (sleep_.time > SLEEP_TIME_THRESHOLD) {
		asleep_ = true;

		linear_.velocity = glm::vec3(0);
		linear_.acceleration = glm::vec3(0);

		angular_.velocity = glm::vec3(0);
		angular_.acceleration = glm::vec3(0);
	}
}

void EngineResolve::update(float delta_time) {
	if (body_type_ == BodyType::STATIC) {
		return;
	}

	if (asleep_) return;


	if (body_type_ == BodyType::KINEMATIC) {
		linear_.acceleration = glm::vec3(0);
		angular_.acceleration = glm::vec3(0);
	}

	// Gets velocity changes due to collisions
	if (number_of_collisions_ != 0) {
		linear_.velocity =
		    linear_.velocity +
		    linear_.change / static_cast<float>(number_of_collisions_);
		angular_.velocity =
		    angular_.velocity +
		    angular_.change / static_cast<float>(number_of_collisions_);
		number_of_collisions_ = 0;
	}

	// Position update
	glm::vec3 pos = getPosition();
	pos =
	    pos + (linear_.velocity * delta_time) +
	    (linear_.acceleration * static_cast<float>(pow(delta_time, 2)) * 0.5f);
	setPosition(pos);

	// Rotation update
	glm::quat orientation = getOrientation();
	orientation = orientation + glm::quat(0, angular_.velocity) * orientation *
	                                0.5f * delta_time;
	setQuaternion(glm::normalize(orientation));

	// Apply gravity
	if (use_gravity_) {
		linear_.acceleration += GRAVITY_CONSTANT;
	}

	// Set new velocity and angular velocity based on acceleration and delta
	// time
	prev_vel_acceleration_ = linear_.acceleration * delta_time;
	linear_.velocity = linear_.velocity + prev_vel_acceleration_;
	linear_.acceleration = glm::vec3(0);
	prev_ang_vel_acceleration_ = angular_.acceleration * delta_time;
	angular_.velocity = angular_.velocity + prev_ang_vel_acceleration_;
	angular_.acceleration = glm::vec3(0);

	// Apply damping (drag)
	linear_.velocity = linear_.velocity * (1 - delta_time * linear_.drag);
	angular_.velocity = angular_.velocity * (1 - delta_time * angular_.drag);
}

void EngineResolve::initialise_body(glm::vec3 pos, glm::vec3 rot, float angle) {
	//
	//
	//
	initialise_body(pos, rot);
	// setAngle(angle);
}

void EngineResolve::initialise_body(glm::vec3 pos, glm::vec3 rot) {
	Transform trans;
	trans.setPosition(Vector3(pos.x, pos.y, pos.z));
	trans.setOrientation(Quaternion::identity());

	collision_body_ = Physics::getPhysicsWorld()->createCollisionBody(trans);
	setEulerRotation(rot);
}

void EngineResolve::delete_body() { collision_body_->~CollisionBody(); }

void EngineResolve::deleteCollider(rp3d::Collider* collider) {
	collision_body_->removeCollider(collider);
}

void EngineResolve::addForce(glm::vec3 force, Apply type) {
	///
	///
	///
	linear_.acceleration = linear_.acceleration + (force / total_mass_);
	asleep_ = false;
}

void EngineResolve::addForceAtPoint(glm::vec3 force, glm::vec3 point,
                                    ApplyPoint type) {
	///
	///
	///
	///
	DebugLogger::log("EngineResolve - addForceAtPoint called",
	                 "NOT IMPLEMENTED");
}

void EngineResolve::addTorque(glm::vec3 torque, Apply type) {
	///
	///
	///
	angular_.acceleration =
	    angular_.acceleration + (torque / (total_mass_ * 1));
	asleep_ = false; 
}

void EngineResolve::setMass(float mass) { total_mass_ = mass; }

float EngineResolve::getMass() { return total_mass_; }

void EngineResolve::setCenterOfMass(glm::vec3 cOFmass) {
	///
	///
	///
	///
	DebugLogger::log("EngineResolve - setCenterOfMass called",
	                 "NOT IMPLEMENTED");
}

void EngineResolve::setVelocity(glm::vec3 vel) {
	linear_.velocity = vel;
	asleep_ = false;
	test = true;
}

glm::vec3 EngineResolve::getVelocity() { return linear_.velocity; }

void EngineResolve::setAngVelocity(glm::vec3 ang_vel) {
	angular_.velocity = ang_vel;
	asleep_ = false;
}

glm::vec3 EngineResolve::getAngVelocity() { return angular_.velocity; }

glm::vec3 EngineResolve::getLinearAcceleration() {
	return linear_.acceleration;
}

void EngineResolve::setDragForce(float drag) { linear_.drag = drag; }

void EngineResolve::addDragForce(float drag) { linear_.drag += drag; }

float EngineResolve::getDragForce() { return linear_.drag; }

void EngineResolve::setDragTorque(float ang_drag) { angular_.drag = ang_drag; }

void EngineResolve::addDragTorque(float ang_drag) { angular_.drag += ang_drag; }

float EngineResolve::getDragTorque() { return angular_.drag; }

void EngineResolve::setType(rp3d::BodyType type) { body_type_ = type; }

void EngineResolve::setType(int type) {
	switch (type) {
		case 0:
			body_type_ = rp3d::BodyType::STATIC;
			break;
		case 1:
			body_type_ = rp3d::BodyType::KINEMATIC;
			break;
		case 2:
			body_type_ = rp3d::BodyType::DYNAMIC;
			break;
		default:
			break;
	}
}

rp3d::BodyType EngineResolve::getType() { return body_type_; }

void EngineResolve::enableGravity(bool enable) { use_gravity_ = enable; }

bool EngineResolve::getIsGravityEnabled() { return use_gravity_; }

void EngineResolve::setCanSleep(bool enable) { can_sleep_ = enable; }

bool EngineResolve::getCanSleep() { return can_sleep_; }

uint32_t EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 rot,
                                       glm::vec3 size, float mass,
                                       float epsilon) {
	BoxShape* collider = Physics::getPhysicsCommon().createBoxShape(
	    rp3d::Vector3(size.x / 2, size.y / 2, size.z / 2));

	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	glm::quat quat = QuaternionHelper::EulerToQuat(rot);
	center.setOrientation(rp3d::Quaternion(quat.x, quat.y, quat.z, quat.w));

	colliders.push_back(collision_body_->addCollider(collider, center));
	m_box.emplace(colliders[colliders.size() - 1], collider);

	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(epsilon);
	mat.setMassDensity(mass);
	total_mass_ += mass;
	calculate_center_of_mass(pos, mass);

	calculate_inertia_tensor();

	return colliders.size() - 1;
}

uint32_t EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 rot,
                                       glm::vec3 size, float friction,
                                       float mass, float epsilon) {
	uint32_t index = addBoxCollider(pos, rot, size, mass, epsilon);

	Material& mat = colliders[index]->getMaterial();
	mat.setFrictionCoefficient(friction);

	return index;
}

uint32_t EngineResolve::addBoxCollider(PhysicsBody* rb, glm::vec3 pos,
                                       glm::vec3 rot, glm::vec3 size,
                                       float friction, float mass,
                                       float epsilon) {
	uint32_t index = addBoxCollider(pos, rot, size, friction, mass, epsilon);
	colliders[index]->setUserData(rb);

	return index;
}

uint32_t EngineResolve::addSphereCollider(glm::vec3 pos, glm::vec3 rot,
                                          float radius, float mass,
                                          float epsilon) {
	SphereShape* collider =
	    Physics::getPhysicsCommon().createSphereShape(radius);

	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	glm::quat quat = QuaternionHelper::EulerToQuat(rot);
	center.setOrientation(rp3d::Quaternion(quat.x, quat.y, quat.z, quat.w));

	colliders.push_back(collision_body_->addCollider(collider, center));
	m_sphere.emplace(colliders[colliders.size() - 1], collider);

	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(epsilon);
	mat.setMassDensity(mass);
	total_mass_ += mass;
	calculate_center_of_mass(pos, mass);

	calculate_inertia_tensor();

	return colliders.size() - 1;
}

uint32_t EngineResolve::addSphereCollider(glm::vec3 pos, glm::vec3 rot,
                                          float radius, float friction,
                                          float mass, float epsilon) {
	uint32_t index = addSphereCollider(pos, rot, radius, mass, epsilon);

	Material& mat = colliders[index]->getMaterial();
	mat.setFrictionCoefficient(friction);

	return index;
}

uint32_t EngineResolve::addSphereCollider(PhysicsBody* rb, glm::vec3 pos,
                                          glm::vec3 rot, float radius,
                                          float friction, float mass,
                                          float epsilon) {
	uint32_t index =
	    addSphereCollider(pos, rot, radius, friction, mass, epsilon);
	colliders[index]->setUserData(rb);

	return index;
}

uint32_t EngineResolve::addCapsuleCollider(glm::vec3 pos, glm::vec3 rot,
                                           float radius, float height,
                                           float mass, float epsilon) {
	CapsuleShape* collider =
	    Physics::getPhysicsCommon().createCapsuleShape(radius, height);

	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	glm::quat quat = QuaternionHelper::EulerToQuat(rot);
	center.setOrientation(rp3d::Quaternion(quat.x, quat.y, quat.z, quat.w));

	colliders.push_back(collision_body_->addCollider(collider, center));
	m_capsule.emplace(colliders[colliders.size() - 1], collider);

	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(epsilon);
	mat.setMassDensity(mass);
	total_mass_ += mass;
	calculate_center_of_mass(pos, mass);

	calculate_inertia_tensor();

	return colliders.size() - 1;
}

uint32_t EngineResolve::addCapsuleCollider(glm::vec3 pos, glm::vec3 rot,
                                           float radius, float height,
                                           float friction, float mass,
                                           float epsilon) {
	uint32_t index =
	    addCapsuleCollider(pos, rot, radius, height, mass, epsilon);

	Material& mat = colliders[index]->getMaterial();
	mat.setFrictionCoefficient(friction);

	return index;
}

uint32_t EngineResolve::addCapsuleCollider(PhysicsBody* rb, glm::vec3 pos,
                                           glm::vec3 rot, float radius,
                                           float height, float friction,
                                           float mass, float epsilon) {
	uint32_t index =
	    addCapsuleCollider(pos, rot, radius, height, friction, mass, epsilon);
	colliders[index]->setUserData(rb);

	return index;
}

glm::mat3x3 EngineResolve::inertia_tensor_box(glm::vec3 size, float mass) {
	glm::mat3x3 inertia_tensor = glm::mat3x3(0);
	float temp_const = 1.0f / 12.0f;

	inertia_tensor[0][0] =
	    temp_const * mass * (pow(size.y, 2) + pow(size.z, 2));  // Ixx
	inertia_tensor[1][1] =
	    temp_const * mass * (pow(size.x, 2) + pow(size.z, 2));  // Iyy
	inertia_tensor[2][2] =
	    temp_const * mass * (pow(size.x, 2) + pow(size.y, 2));  // Izz

	return inertia_tensor;
}

glm::mat3x3 EngineResolve::inertia_tensor_sphere(float radius, float mass) {
	glm::mat3x3 inertia_tensor = glm::mat3x3(0);

	inertia_tensor[0][0] = (2.0f / 5.0f) * mass * pow(radius, 2);  // Ixx
	inertia_tensor[1][1] = inertia_tensor[0][0];                   // Iyy
	inertia_tensor[2][2] = inertia_tensor[0][0];                   // Izz

	return inertia_tensor;
}

glm::mat3x3 EngineResolve::inertia_tensor_capsule(float radius, float height,
                                                  float mass) {
	glm::mat3x3 inertia_tensor = glm::mat3x3(0);

	inertia_tensor[0][0] = (1.0f / 4.0f) * mass * pow(radius, 2) +
	                       (1.0f / 12.0f) * mass * pow(height, 2);  // Ixx
	inertia_tensor[1][1] =
	    (1.0f / 2.0f) * mass *
	    pow(radius,
	        2);  // Iyy //calculation of Iyy switched with Izz from the handout
	             // because of rotation (pointing up instead of to the side)
	inertia_tensor[2][2] = inertia_tensor[0][0];  // Izz

	return inertia_tensor;
}

auto EngineResolve::calculate_center_of_mass(glm::vec3 pos, float mass)
    -> void {
	auto old_mass_ratio = (total_mass_ - mass) / total_mass_;
	auto new_mass_ratio = mass / total_mass_;

	center_of_mass_ = center_of_mass_ * old_mass_ratio + pos * new_mass_ratio;
}

auto EngineResolve::calculate_inertia_tensor() -> void {
	inertia_tensor_ = glm::mat3(0);
	for (auto collider : colliders) {
		float mass = collider->getMaterial()
		                 .getMassDensity();  // Mass is stored as mass density
		// Get basic inertia tensor
		rp3d::Vector3 rp3d_local_inertia_tensor =
		    collider->getCollisionShape()->getLocalInertiaTensor(mass);
		glm::mat3x3 inertia_tensor = glm::mat3x3(0);
		inertia_tensor[0][0] = rp3d_local_inertia_tensor.x;
		inertia_tensor[1][1] = rp3d_local_inertia_tensor.y;
		inertia_tensor[2][2] = rp3d_local_inertia_tensor.z;

		// Rotate inertia tensor
		rp3d::Quaternion quat =
		    collider->getLocalToBodyTransform().getOrientation();
		inertia_tensor = QuaternionHelper::RotateInertiaTensorOppositeQuat(
		    inertia_tensor, glm::quat(quat.w, quat.x, quat.y, quat.z));

		// Discard non diagonal values
		inertia_tensor[1][0] = 0;
		inertia_tensor[2][0] = 0;
		inertia_tensor[0][1] = 0;
		inertia_tensor[2][1] = 0;
		inertia_tensor[0][2] = 0;
		inertia_tensor[1][2] = 0;

		// Move inertia tensor to center of mass
		rp3d::Vector3 rp3d_distance =
		    collider->getLocalToBodyTransform().getPosition();
		rp3d_distance.x -= center_of_mass_.x;
		rp3d_distance.y -= center_of_mass_.y;
		rp3d_distance.z -= center_of_mass_.z;

		inertia_tensor[0][0] +=
		    mass *
		    static_cast<float>(pow(
		        sqrt(pow(rp3d_distance.y, 2) + pow(rp3d_distance.z, 2)), 2));
		inertia_tensor[1][1] +=
		    mass *
		    static_cast<float>(pow(
		        sqrt(pow(rp3d_distance.x, 2) + pow(rp3d_distance.z, 2)), 2));
		inertia_tensor[2][2] +=
		    mass *
		    static_cast<float>(pow(
		        sqrt(pow(rp3d_distance.x, 2) + pow(rp3d_distance.y, 2)), 2));

		// Add to bodies inertia tensor
		inertia_tensor_ += inertia_tensor;
	}
}

void EngineResolve::setPosition(glm::vec3 pos) {
	Transform trans = collision_body_->getTransform();
	trans.setPosition(Vector3(pos.x, pos.y, pos.z));
	collision_body_->setTransform(trans);
}

glm::vec3 EngineResolve::getPosition() {
	Transform trans = collision_body_->getTransform();
	Vector3 pos = trans.getPosition();
	return glm::vec3(pos.x, pos.y, pos.z);
}

void EngineResolve::setQuaternion(glm::quat quat) {
	Transform trans = collision_body_->getTransform();
	trans.setOrientation(Quaternion(quat.x, quat.y, quat.z, quat.w));
	collision_body_->setTransform(trans);
}

glm::quat EngineResolve::getOrientation() {
	Quaternion quat = collision_body_->getTransform().getOrientation();
	return glm::quat(quat.w, quat.x, quat.y, quat.z);
}

void EngineResolve::setEulerRotation(glm::vec3 rot) {
	Transform transform = collision_body_->getTransform();
	Quaternion orientation = Quaternion::identity();
	glm::quat quat = QuaternionHelper::EulerToQuat(rot);

	orientation = Quaternion(quat.x, quat.y, quat.z, quat.w);

	transform.setOrientation(orientation);
	collision_body_->setTransform(transform);
}

void EngineResolve::setRotation(glm::vec3 rot) {
	///
	///
	///
	///
	DebugLogger::log("EngineResolve - setRotation called", "NOT IMPLEMENTED");
}

glm::vec3 EngineResolve::getRotation() {
	///
	///
	///
	Quaternion quat = collision_body_->getTransform().getOrientation();
	return glm::degrees(
	    glm::eulerAngles(glm::quat(quat.w, quat.x, quat.y, quat.z)));
}

void EngineResolve::setAngle(float ang) {
	///
	///
	///
	///
	DebugLogger::log("EngineResolve - setAngle called", "NOT IMPLEMENTED");
}

float EngineResolve::getAngle() {
	///
	///
	///
	///
	DebugLogger::log("EngineResolve - getAngle called", "NOT IMPLEMENTED");
}

bool EngineResolve::isSleeping() {
	return asleep_;
}

void EngineResolve::setIsSleeping(bool ean) {
	asleep_ = ean;
}