#include "EngineResolve.hpp"

using namespace rp3d;

EngineResolve::EngineResolve() {
	linear_.velocity = glm::vec3(0);
	linear_.acceleration = glm::vec3(0);

	angular_.velocity = glm::vec3(0);
	angular_.acceleration = glm::vec3(0);

	total_mass_ = 1;

	body_type_ = BodyType::DYNAMIC;
}

bool EngineResolve::usingReactResolve() { return false; }

void EngineResolve::resolve(glm::vec3 normal, CollisionEvent c_type) {}

void EngineResolve::update(float delta_time) {
	if (body_type_ == BodyType::STATIC) {
		return;
	}

	glm::vec3 pos = getPosition();
	float temp = 0.5 * pow(delta_time, 2);
	pos = pos + (linear_.velocity * delta_time) +
	      (linear_.acceleration.x * temp, linear_.acceleration.y * temp,
	       linear_.acceleration.z * temp);
	setPosition(pos);

	linear_.velocity = linear_.velocity + linear_.acceleration * delta_time;
	linear_.acceleration = glm::vec3(0);
	angular_.velocity = angular_.velocity + angular_.acceleration * delta_time;
	angular_.acceleration = glm::vec3(0);

	if (body_type_ == BodyType::KINEMATIC) {
		return;
	}
}

void EngineResolve::initialise_body(glm::vec3 pos, glm::vec3 rot, float angle) {
	initialise_body(pos, rot);
	setAngle(angle);
}

void EngineResolve::initialise_body(glm::vec3 pos, glm::vec3 rot) {
	Transform trans;
	trans.setPosition(Vector3(pos.x, pos.y, pos.z));
	trans.setOrientation(Quaternion::identity());

	collision_body_ = Physics::getPhysicsWorld()->createCollisionBody(trans);
	setRotation(rot);
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
}

void EngineResolve::addForceAtPoint(glm::vec3 force, glm::vec3 point,
                                    ApplyPoint type) {
	///
	///
	///
	///
}

void EngineResolve::addTorque(glm::vec3 torque, Apply type) {
	///
	///
	///
	angular_.acceleration =
	    angular_.acceleration + (torque / (total_mass_ * 1));
}

void EngineResolve::setMass(float mass) { total_mass_ = mass; }

float EngineResolve::getMass() { return total_mass_; }

void EngineResolve::setCenterOfMass(glm::vec3 cOFmass) {
	///
	///
	///
	///
}

void EngineResolve::setVelocity(glm::vec3 vel) { linear_.velocity = vel; }

glm::vec3 EngineResolve::getVelocity() { return linear_.velocity; }

void EngineResolve::setAngVelocity(glm::vec3 ang_vel) {
	angular_.velocity = ang_vel;
}

glm::vec3 EngineResolve::getAngVelocity() { return angular_.velocity; }

void EngineResolve::setDragForce(float drag) {
	///
	///
	///
	///
}

void EngineResolve::addDragForce(float drag) {
	///
	///
	///
	///
}

float EngineResolve::getDragForce() {
	///
	///
	///
	return 0.0;
}

void EngineResolve::setDragTorque(float ang_drag) {
	///
	///
	///
	///
}

void EngineResolve::addDragTorque(float ang_drag) {
	///
	///
	///
	///
}

float EngineResolve::getDragTorque() {
	///
	///
	///
	return 0.0;
}

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

void EngineResolve::enableGravity(bool ean) {
	///
	///
	///
	///
}

bool EngineResolve::getIsGravityEnabled() {
	///
	///
	///
	return false;
}

void EngineResolve::setCanSleep(bool ean) {
	///
	///
	///
	///
}

bool EngineResolve::getCanSleep() {
	///
	///
	///
	return false;
}

uint32_t EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size) {
	BoxShape* collider = Physics::getPhysicsCommon().createBoxShape(
	    rp3d::Vector3(size.x / 2, size.y / 2, size.z / 2));

	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());

	colliders.push_back(collision_body_->addCollider(collider, center));
	m_box.emplace(colliders[colliders.size() - 1], collider);

	return colliders.size() - 1;
}

uint32_t EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size,
                                       float bounce, float friction) {
	uint32_t index = addBoxCollider(pos, size);

	Material& mat = colliders[index]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);

	return index;
}

uint32_t EngineResolve::addBoxCollider(PhysicsBody* rb, glm::vec3 pos,
                                       glm::vec3 size, float bounce,
                                       float friction) {
	uint32_t index = addBoxCollider(pos, size, bounce, friction);
	colliders[index]->setUserData(rb);

	return index;
}

uint32_t EngineResolve::addSphereCollider(glm::vec3 pos, float radius) {
	SphereShape* collider =
	    Physics::getPhysicsCommon().createSphereShape(radius);

	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());

	colliders.push_back(collision_body_->addCollider(collider, center));
	m_sphere.emplace(colliders[colliders.size() - 1], collider);

	return colliders.size() - 1;
}

uint32_t EngineResolve::addSphereCollider(glm::vec3 pos, float radius,
                                          float bounce, float friction) {
	uint32_t index = addSphereCollider(pos, radius);

	Material& mat = colliders[index]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);

	return index;
}

uint32_t EngineResolve::addSphereCollider(PhysicsBody* rb, glm::vec3 pos,
                                          float radius, float bounce,
                                          float friction) {
	uint32_t index = addSphereCollider(pos, radius, bounce, friction);
	colliders[index]->setUserData(rb);

	return index;
}

uint32_t EngineResolve::addCapsuleCollider(glm::vec3 pos, float radius,
                                           float height) {
	CapsuleShape* collider =
	    Physics::getPhysicsCommon().createCapsuleShape(radius, height);

	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());

	colliders.push_back(collision_body_->addCollider(collider, center));
	m_capsule.emplace(colliders[colliders.size() - 1], collider);

	return colliders.size() - 1;
}

uint32_t EngineResolve::addCapsuleCollider(glm::vec3 pos, float radius,
                                           float height, float bounce,
                                           float friction) {
	uint32_t index = addCapsuleCollider(pos, radius, height);

	Material& mat = colliders[index]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);

	return index;
}

uint32_t EngineResolve::addCapsuleCollider(PhysicsBody* rb, glm::vec3 pos,
                                           float radius, float height,
                                           float bounce, float friction) {
	uint32_t index = addCapsuleCollider(pos, radius, height, bounce, friction);
	colliders[index]->setUserData(rb);

	return index;
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
	return glm::quat(quat.x, quat.y, quat.z, quat.w);
}

void EngineResolve::setEulerRotation(glm::vec3 rot) {
	///
	///
	///
}

void EngineResolve::setRotation(glm::vec3 rot) {
	///
	///
	///
}

glm::vec3 EngineResolve::getRotation() {
	///
	///
	///
	Quaternion quat = collision_body_->getTransform().getOrientation();
	return glm::degrees(
	    glm::eulerAngles(glm::quat(quat.x, quat.y, quat.z, quat.w)));
}

void EngineResolve::setAngle(float ang) {
	///
	///
	///
	Transform trans = collision_body_->getTransform();
	Quaternion quat = trans.getOrientation();
	quat.w = ang;
	trans.setOrientation(quat);
	collision_body_->setTransform(trans);
}

float EngineResolve::getAngle() {
	///
	///
	///
	return collision_body_->getTransform().getOrientation().w;
}