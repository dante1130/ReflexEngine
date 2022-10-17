#include "PhysicBody.hpp"

#include "Controller/Physics/QuaternionHelper.hpp"
#include "Controller/GUI/DebugLogger.hpp"
#include "Controller/Physics/ResolutionOutput.hpp"
#include <string>
#include "Controller/ReflexEngine/EngineTime.hpp"
#include <iostream>

using namespace rp3d;

void PhysicsBody::collision(Collider* collider1, Collider* collider2,
                            glm::vec3 lpoint_c1, glm::vec3 lpoint_c2,
                            glm::vec3 collision_normal, double collision_depth,
                            CollisionEvent c_type) {
	PhysicsBody* pb1 = static_cast<PhysicsBody*>(collider1->getUserData());
	PhysicsBody* pb2 = static_cast<PhysicsBody*>(collider2->getUserData());

	// Get the epsilon value (stored as a bounciness)
	float epsilon = collider1->getMaterial().getBounciness();
	if (epsilon > collider2->getMaterial().getBounciness()) {
		epsilon = collider2->getMaterial().getBounciness();
	}

	// Convert from center of collision body to center of mass
	lpoint_c1 += pb1->center_of_mass_;
	lpoint_c2 += pb2->center_of_mass_;

	if (pb1->getType() == rp3d::BodyType::STATIC &&
	    pb2->getType() == rp3d::BodyType::STATIC) {
		return;
	} else if (pb1->getType() == rp3d::BodyType::STATIC) {
		static_collision(collider2, lpoint_c2, -collision_normal, epsilon,
		                 collision_depth);
		return;
	} else if (pb2->getType() == rp3d::BodyType::STATIC) {
		static_collision(collider1, lpoint_c1, collision_normal, epsilon,
		                 collision_depth);
		return;
	}

	DePenetrate(pb1, pb2, collision_normal, collision_depth);

	// J1^-1
	pb1->inverse_rotated_inertia_tensor_ =
	    QuaternionHelper::RotateInertiaTensorOppositeQuat(
	        glm::inverse(pb1->inertia_tensor_), pb1->getOrientation());
	// J2^-1
	pb2->inverse_rotated_inertia_tensor_ =
	    QuaternionHelper::RotateInertiaTensorOppositeQuat(
	        glm::inverse(pb2->inertia_tensor_), pb2->getOrientation());

	// (r1 x n)
	glm::vec3 r1xn = glm::cross(lpoint_c1, collision_normal);
	// (r2 x n)
	glm::vec3 r2xn = glm::cross(lpoint_c2, collision_normal);

	// Rotates angular velocity to world coordaintes from local coordinates
	glm::vec3 ang_vel_b1 =
	    pb1->getAngVelocity() - pb1->prev_ang_vel_acceleration_;
	glm::vec3 ang_vel_b2 =
	    pb2->getAngVelocity() - pb2->prev_ang_vel_acceleration_;

	// num_eqn = numerator section of equation
	// div_eqn = divisor section of equation

	// (1 + E)
	float epsilon_num_eqn = 1.0f + epsilon;

	// n . (v1 - v2)
	float vel_num_eqn = glm::dot(
	    collision_normal, ((pb1->getVelocity() - pb1->prev_vel_acceleration_) -
	                       (pb2->getVelocity() - pb2->prev_vel_acceleration_)));
	// w1 . (r1 x n)
	float w1_num_eqn = glm::dot(ang_vel_b1, r1xn);
	// w2 . (r2 x n)
	float w2_num_eqn = glm::dot(ang_vel_b2, r2xn);
	// b (baumgarte term)
	float b_num_eqn =
	    (0.2f / EngineTime::get_fixed_delta_time()) * collision_depth;

	// b - (1 + E)(n . (v1 - v2) + w1 . (r1 x n) - w2 . (r2 x n))
	float num_eqn =
	    b_num_eqn - epsilon_num_eqn * (vel_num_eqn + w1_num_eqn - w2_num_eqn);

	//  1      1
	// ____ + ____
	//  m1     m1
	float mass_div_eqn = (1.0 / pb1->getMass()) + (1.0 / pb2->getMass());

	// (r1 x n)^T * J1^-1 * (r1 x n)
	// OR (r1 x n) . J1^-1 * (r1 x n)
	float j1_div_eqn =
	    glm::dot(r1xn, pb1->inverse_rotated_inertia_tensor_ * r1xn);
	// (r2 x n)^T * J2^-1 * (r2 x n)
	// OR (r2 x n) . J2^-1 * (r2xn)
	float j2_div_eqn =
	    glm::dot(r2xn, pb2->inverse_rotated_inertia_tensor_ * r2xn);

	// 1/m1 + 1/m2 + ((r1xn)^T * J1^-1 * (r1xn) + (r2xn)^T * J2^-1 * (r2xn))
	float div_eqn = mass_div_eqn + (j1_div_eqn + j2_div_eqn);

	// Entire equation
	float lambda = (num_eqn / div_eqn);
	glm::vec3 linear_impluse = lambda * collision_normal;

	ResolutionOutput::output_resolution_data(
	    epsilon, lambda, collision_normal,
	    glm::vec3(vel_num_eqn, w1_num_eqn, w2_num_eqn),
	    glm::vec3(mass_div_eqn, j1_div_eqn, j2_div_eqn));
	ResolutionOutput::output_before_resolution_b1(
	    pb1->getMass(), pb1->getVelocity(), ang_vel_b1, lpoint_c1,
	    pb1->inverse_rotated_inertia_tensor_, pb1->inertia_tensor_,
	    pb1->getOrientation());
	ResolutionOutput::output_before_resolution_b2(
	    pb2->getMass(), pb2->getVelocity(), ang_vel_b2, lpoint_c2,
	    pb2->inverse_rotated_inertia_tensor_, pb2->inertia_tensor_,
	    pb2->getOrientation());

	// Set new velocity and angular velocity
	pb1->resolve(lambda, lpoint_c1, collision_normal, 1);
	pb2->resolve(lambda, lpoint_c2, collision_normal, 2);

	ResolutionOutput::output_after_resolution(
	    pb1->getVelocity(), pb1->getAngVelocity(), pb2->getVelocity(),
	    pb2->getAngVelocity());
}

void PhysicsBody::static_collision(rp3d::Collider* collider, glm::vec3 r_point,
                                   glm::vec3 collision_normal, float epsilon,
                                   float collision_depth) {
	PhysicsBody* pb1 = static_cast<PhysicsBody*>(collider->getUserData());

	glm::vec3 pos = pb1->getPosition();
	pos -= collision_normal * collision_depth;
	pb1->setPosition(pos);

	// J1^-1
	pb1->inverse_rotated_inertia_tensor_ =
	    QuaternionHelper::RotateInertiaTensorOppositeQuat(
	        glm::inverse(pb1->inertia_tensor_), pb1->getOrientation());

	// (r1 x n)
	glm::vec3 rxn = glm::cross(r_point, collision_normal);

	// Rotates angular velocity to world coordaintes from local coordinates
	glm::vec3 ang_vel = pb1->getAngVelocity();

	// num_eqn = numerator section of equation
	// div_eqn = divisor section of equation

	// (1 + E)
	float epsilon_num_eqn = 1.0f + epsilon;

	// n . (v1 - v2)
	float vel_num_eqn = glm::dot(
	    collision_normal, pb1->getVelocity() - pb1->prev_vel_acceleration_);

	// w . (r x n)
	float w_num_eqn = glm::dot(ang_vel, rxn);

	// b (baumgarte term)
	float b_num_eqn =
	    (0.2f / EngineTime::get_fixed_delta_time()) * collision_depth;

	// b - (1 + E)(n . (v1 - v2) + w1 . (r1 x n) - w2 . (r2 x n))
	float num_eqn = b_num_eqn - epsilon_num_eqn * (vel_num_eqn + w_num_eqn);

	//  1      1
	// ____ + ____
	//  m1     m1
	float mass_div_eqn = (1.0 / pb1->getMass());

	// (r1 x n)^T * J1^-1 * (r1 x n)
	// OR (r1 x n) . J1^-1 * (r1 x n)
	float j_div_eqn = glm::dot(rxn, pb1->inverse_rotated_inertia_tensor_ * rxn);

	// 1/m1 + 1/m2 + ((r1xn)^T * J1^-1 * (r1xn) + (r2xn)^T * J2^-1 * (r2xn))
	float div_eqn = mass_div_eqn + (j_div_eqn);

	// Entire equation
	float lambda = (num_eqn / div_eqn);

	// Set new velocity and angular velocity
	pb1->resolve(lambda, r_point, collision_normal, 1);
}

glm::mat3x3 PhysicsBody::get_inertia_tensor() { return inertia_tensor_; }

void PhysicsBody::DePenetrate(PhysicsBody* pb1, PhysicsBody* pb2,
                              glm::vec3 normal, float penetration_depth) {
	glm::vec3 pos1 = pb1->getPosition();
	glm::vec3 pos2 = pb2->getPosition();

	if (glm::length(pb1->getVelocity()) == 0 ||
	    glm::length(pb2->getVelocity()) == 0) {
		if (glm::length(pb1->getVelocity()) == 0) {
			pos2 = pos2 + normal * penetration_depth;
		} else {
			pos1 = pos1 - normal * penetration_depth;
		}
	} else {
		float total_vel = glm::length(pb1->getVelocity() - pb2->getVelocity());
		pos1 = pos1 - (glm::length(pb1->getVelocity()) / total_vel) *
		                  (normal * penetration_depth);
		pos2 = pos2 + (glm::length(pb2->getVelocity()) / total_vel) *
		                  (normal * penetration_depth);
	}

	pb1->setPosition(pos1);
	pb2->setPosition(pos2);
}

size_t PhysicsBody::colliderSize() { return colliders.size(); }

void PhysicsBody::removeCollider(size_t index) {
	if (index < 0 || index >= colliders.size()) return;

	switch (this->getColliderType(index)) {
		case 1:
			m_sphere.erase(colliders[index]);
			break;
		case 2:
			m_capsule.erase(colliders[index]);
			break;
		case 3:
			m_box.erase(colliders[index]);
			break;
		default:
			return;
	}
	deleteCollider(colliders[index]);
	colliders.erase(colliders.begin() + index);
}

void PhysicsBody::removeAllColliders() {
	m_box.clear();
	m_sphere.clear();
	m_capsule.clear();

	for (Collider* c : colliders) deleteCollider(c);

	colliders.clear();
}

void PhysicsBody::setObjectTrigger(bool ean) {
	for (Collider* c : colliders) c->setIsTrigger(ean);

	is_trigger = ean;
}

bool PhysicsBody::getIsTrigger() { return is_trigger; }

glm::vec3 PhysicsBody::getColliderPosition(size_t index, Apply type) {
	Vector3 temp;
	switch (type) {
		case Apply::LOCAL:
			temp = colliders[index]->getLocalToBodyTransform().getPosition();
			break;
		case Apply::WORLD:
			temp = colliders[index]->getLocalToWorldTransform().getPosition();
			break;
		default:
			break;
	}
	return glm::vec3(temp.x, temp.y, temp.z);
}

glm::vec4 PhysicsBody::getColliderOrientation(size_t index, Apply type) {
	Quaternion temp;

	switch (type) {
		case Apply::LOCAL:
			temp = colliders[index]->getLocalToBodyTransform().getOrientation();
			break;
		case Apply::WORLD:
			temp =
			    colliders[index]->getLocalToWorldTransform().getOrientation();
			break;
		default:
			break;
	}
	return glm::vec4(temp.w, temp.x, temp.y, temp.z);
}

float PhysicsBody::getColliderBounce(size_t index) {
	return colliders[index]->getMaterial().getBounciness();
}
float PhysicsBody::getColliderFriction(size_t index) {
	return colliders[index]->getMaterial().getFrictionCoefficient();
}
float PhysicsBody::getColliderMassDesity(size_t index) {
	return colliders[index]->getMaterial().getMassDensity();
}

int PhysicsBody::getColliderType(size_t index) {
	switch (colliders[index]->getCollisionShape()->getName()) {
		case CollisionShapeName::SPHERE:
			return 1;
		case CollisionShapeName::CAPSULE:
			return 2;
		case CollisionShapeName::BOX:
			return 3;
		default:
			return 0;
	}
}

std::string PhysicsBody::getColliderName(size_t index) {
	switch (getColliderType(index)) {
		case 1:
			return "Sphere" + std::to_string(index);
		case 2:
			return "Capsule" + std::to_string(index);
		case 3:
			return "Box" + std::to_string(index);
	}
}

std::vector<rp3d::Collider*> PhysicsBody::getColliders() { return colliders; }

void PhysicsBody::addMaterialToCollider(size_t index, float bounce,
                                        float mass_density, float friction) {
	Material& material = colliders[index]->getMaterial();
	material.setBounciness(bounce);
	material.setMassDensity(mass_density);
	material.setFrictionCoefficient(friction);
}

BoxShape* PhysicsBody::getColliderBox(size_t index) {
	try {
		if (getColliderType(index) == 3)
			return m_box.find(colliders[index])->second;
		else
			throw("Could not convert box type!");
	} catch (std::string err) {
		std::cout << "ERROR: " << err << std::endl;
	}
}

SphereShape* PhysicsBody::getColliderSphere(size_t index) {
	try {
		if (getColliderType(index) == 1)
			return m_sphere.find(colliders[index])->second;
		else
			throw("Could not convert sphere type!");
	} catch (std::string err) {
		std::cout << "ERROR: " << err << std::endl;
	}
}

CapsuleShape* PhysicsBody::getColliderCapsule(size_t index) {
	try {
		if (getColliderType(index) == 2)
			return m_capsule.find(colliders[index])->second;
		else
			throw("Could not convert capsule type!");
	} catch (std::string err) {
		std::cout << "ERROR: " << err << std::endl;
	}
}

size_t PhysicsBody::getColliderIndex(rp3d::Collider* collider) {
	for (size_t i = 0; i < colliders.size(); ++i) {
		if (colliders[i] == collider) return i;
	}

	return colliders.size();
}

glm::vec3 PhysicsBody::getPreviousPosition() {
	return previous_transform_position;
}
void PhysicsBody::setPreviousPosition(glm::vec3 prev_pos) {
	previous_transform_position = prev_pos;
}