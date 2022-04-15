#include "BodyRigid.hpp"

void BodyRigid::init() {}

void BodyRigid::createBR(float x, float y, float z) {
	rb.init(glm::vec3(x, y, z));
}

void BodyRigid::setType(int type) { rb.setType(type); }

void BodyRigid::enableGravity(bool val) { rb.enableGravity(val); }

void BodyRigid::setLinearVelocityDamping(float val) {
	rb.setLinearVelocityDamping(val);
}

void BodyRigid::setAngularVelocityDamping(float val) {
	rb.setAngularVelocityDamping(val);
}

void BodyRigid::setIfBodyCanSleep(bool val) { rb.setIfBodyCanSleep(val); }

void BodyRigid::addForce(glm::vec3 force) { rb.addForce(force); }

void BodyRigid::addTorque(glm::vec3 torque) { rb.addTorque(torque); }

void BodyRigid::update(float delta_time) {
	position = rb.getPosition();
	rotation = rb.getRotation();
	angle = rb.getAngle();
}

glm::vec3 BodyRigid::getPosition() { return rb.getPosition(); }

glm::vec3 BodyRigid::getRotation() { return rb.getRotation(); }

float BodyRigid::getAngle() { return rb.getAngle(); }

BodyRigid::~BodyRigid() { rb.~BodyRigidPhysics(); }

void BodyRigid::addBoxCollider(glm::vec3 pos, glm::vec3 halfSize,
                               float bounciness, float friction) {
	rb.addBoxCollider(pos, halfSize, bounciness, friction);
}

void BodyRigid::addSphereCollider(glm::vec3 pos, float radius, float bounciness,
                                  float friction) {
	rb.addSphereCollider(pos, radius, bounciness, friction);
}

void BodyRigid::addCapsuleCollider(glm::vec3 pos, float radius, float height,
                                   float bounciness, float friction) {
	rb.addCapsuleCollider(pos, radius, height, bounciness, friction);
}
