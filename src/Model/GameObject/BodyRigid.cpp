#include "BodyRigid.hpp"

void BodyRigid::init() {}

void BodyRigid::createBR(glm::vec3 pos, glm::vec3 rotation, float angle) {
	rb.init(pos, rotation, angle);
}

void BodyRigid::set_position(glm::vec3 pos) { rb.set_position(pos); }

void BodyRigid::setType(int type) { rb.setType(type); }

int BodyRigid::getType() { return rb.getRBType(); }

void BodyRigid::enableGravity(bool val) { rb.enableGravity(val); }

void BodyRigid::setLinearVelocityDamping(float val) {
	rb.setLinearVelocityDamping(val);
}

void BodyRigid::setAngularVelocityDamping(float val) {
	rb.setAngularVelocityDamping(val);
}

void BodyRigid::setIfBodyCanSleep(bool val) { rb.setIfBodyCanSleep(val); }

void BodyRigid::addForce(glm::vec3 force) { rb.addForce(force); }

void BodyRigid::setLinearVelocity(glm::vec3 velocity) {
	rb.setLinearVelocity(velocity);
}

void BodyRigid::addTorque(glm::vec3 torque) { rb.addTorque(torque); }

void BodyRigid::setAngularVelocity(glm::vec3 velocity) {
	rb.setAngularVelocity(velocity);
}

void BodyRigid::update(float delta_time) {}

void BodyRigid::fixed_update(float delta_time) {
	position = rb.getPosition();
	rotation = rb.getRotation();
	angle = rb.getAngle();
}

glm::vec3 BodyRigid::getPosition() { return rb.getPosition(); }

glm::vec3 BodyRigid::getRotation() { return rb.getRotation(); }

float BodyRigid::getAngle() { return rb.getAngle(); }

glm::vec3 BodyRigid::getLinearVelocity() { return rb.getLinearVelocity(); }

glm::vec3 BodyRigid::getAngularVelocity() { return rb.getAngularVelocity(); }

BodyRigid::~BodyRigid() { rb.~BodyRigidPhysics(); }

void BodyRigid::addBoxCollider(glm::vec3 pos, glm::vec3 halfSize,
                               float bounciness, float friction) {
	rb.addBoxCollider(pos, halfSize, bounciness, friction);
	colliderData_box cb(m_numOfColliders, halfSize.x, halfSize.y, halfSize.z);
	m_box.push_back(cb);
	m_numOfColliders++;
}

void BodyRigid::addSphereCollider(glm::vec3 pos, float radius, float bounciness,
                                  float friction) {
	rb.addSphereCollider(pos, radius, bounciness, friction);
	colliderData_sphere cb(m_numOfColliders, radius);
	m_sphere.push_back(cb);
	m_numOfColliders++;
}

void BodyRigid::addCapsuleCollider(glm::vec3 pos, float radius, float height,
                                   float bounciness, float friction) {
	rb.addCapsuleCollider(pos, radius, height, bounciness, friction);
	colliderData_capsule cb(m_numOfColliders, radius, height);
	m_capsule.push_back(cb);
	m_numOfColliders++;
}

void BodyRigid::setLinearAxisFactor(glm::vec3 factor) {
	rb.setLinearAxisFactor(factor);
}

void BodyRigid::setAngularAxisFactor(glm::vec3 factor) {
	rb.setAngularAxisFactor(factor);
}
