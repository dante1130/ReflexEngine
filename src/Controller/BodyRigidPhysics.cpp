#include "BodyRigidPhysics.hpp"

BodyRigidPhysics::BodyRigidPhysics() {}

void BodyRigidPhysics::init(glm::vec3 pos) {
	Vector3 position(pos.x, pos.y, pos.z);
	Quaternion o = Quaternion::identity();
	o.setAllValues(0, 1, 0, 0);
	Transform t(position, o);
	rb = Physics::getPhysicsWorld()->createRigidBody(t);

	setType(2);

	created = true;
}

void BodyRigidPhysics::setType(int type) {
	switch (type) {
		case 0:
			rb->setType(BodyType::STATIC);
			break;
		case 1:
			rb->setType(BodyType::KINEMATIC);
			break;
		case 2:
			rb->setType(BodyType::DYNAMIC);
			break;
	}
}

void BodyRigidPhysics::enableGravity(bool val) { rb->enableGravity(val); }

void BodyRigidPhysics::setLinearVelocityDamping(float val) {
	rb->setLinearDamping(val);
}

void BodyRigidPhysics::setAngularVelocityDamping(float val) {
	rb->setAngularDamping(val);
}

void BodyRigidPhysics::setIfBodyCanSleep(bool val) {
	rb->setIsAllowedToSleep(val);
}

void BodyRigidPhysics::addForce(glm::vec3 force) {
	Vector3 f(force.x, force.y, force.z);
	rb->applyLocalForceAtCenterOfMass(f);
}

void BodyRigidPhysics::addTorque(glm::vec3 torque) {
	Vector3 t(torque.x, torque.y, torque.z);
	rb->applyLocalTorque(t);
}

glm::vec3 BodyRigidPhysics::getPosition() {
	Transform t = rb->getTransform();
	Vector3 v = t.getPosition();
	glm::vec3 pos(v.x, v.y, v.z);
	return pos;
}

glm::vec3 BodyRigidPhysics::getRotation() {
	Transform t = rb->getTransform();
	Quaternion q = t.getOrientation();
	Vector3 v;
	float angle;
	q.getRotationAngleAxis(angle, v);
	glm::vec3 rot(v.x, v.y, v.z);
	return rot;
}

float BodyRigidPhysics::getAngle() {
	Transform t = rb->getTransform();
	Quaternion q = t.getOrientation();
	Vector3 v;
	float angle;
	q.getRotationAngleAxis(angle, v);
	angle = angle * 180 / PI_RP3D;
	return angle;
}

BodyRigidPhysics::~BodyRigidPhysics() {
	if (created == false || Physics::WorldExsists() == false) {
		return;
	}
	Physics::getPhysicsWorld()->destroyRigidBody(rb);
	created = false;
}

void BodyRigidPhysics::addBoxCollider(glm::vec3 pos, glm::vec3 halfSize,
                                      float bounciness, float friction) {
	BoxShape* boxShape = Physics::getPhysicsCommon().createBoxShape(
	    Vector3(halfSize.x, halfSize.y, halfSize.z));

	Transform t = Transform::identity();
	t.setPosition(Vector3(pos.x, pos.y, pos.z));

	Collider* collider;
	collider = rb->addCollider(boxShape, t);

	Material& mat = collider->getMaterial();

	mat.setBounciness(bounciness);
	mat.setFrictionCoefficient(friction);
}

void BodyRigidPhysics::addSphereCollider(glm::vec3 pos, float radius,
                                         float bounciness, float friction) {
	SphereShape* sphereShape =
	    Physics::getPhysicsCommon().createSphereShape(radius);

	Transform t = Transform::identity();
	t.setPosition(Vector3(pos.x, pos.y, pos.z));

	Collider* collider;
	collider = rb->addCollider(sphereShape, t);

	Material& mat = collider->getMaterial();

	mat.setBounciness(bounciness);
	mat.setFrictionCoefficient(friction);
}

void BodyRigidPhysics::addCapsuleCollider(glm::vec3 pos, float radius,
                                          float height, float bounciness,
                                          float friction) {
	CapsuleShape* capsuleShape =
	    Physics::getPhysicsCommon().createCapsuleShape(radius, height);

	Transform t = Transform::identity();
	t.setPosition(Vector3(pos.x, pos.y, pos.z));

	Collider* collider;
	collider = rb->addCollider(capsuleShape, t);

	Material& mat = collider->getMaterial();

	mat.setBounciness(bounciness);
	mat.setFrictionCoefficient(friction);
}
