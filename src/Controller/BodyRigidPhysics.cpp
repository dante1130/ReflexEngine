#include "BodyRigidPhysics.hpp"

BodyRigidPhysics::BodyRigidPhysics() {}

void BodyRigidPhysics::init(glm::vec3 pos, glm::vec3 rotation, float angle) {
	Vector3 position(pos.x, pos.y, pos.z);
	Quaternion o = Quaternion::identity();

	angle = angle / (180 / PI_RP3D);

	float x = rotation.x * sin(angle / 2);
	float y = rotation.y * sin(angle / 2);
	float z = rotation.z * sin(angle / 2);
	float w = cos(angle / 2);

	float normal = sqrt(pow(cos(angle / 2), 2) +
	                    pow(rotation.x, 2) * pow(sin(angle / 2), 2) +
	                    pow(rotation.y, 2) * pow(sin(angle / 2), 2) +
	                    pow(rotation.z, 2) * pow(sin(angle / 2), 2));

	o.setAllValues(x / normal, y / normal, z / normal, w / normal);
	Transform t(position, o);
	rb = Physics::getPhysicsWorld()->createRigidBody(t);
	setType(2);

	created = true;
}

void BodyRigidPhysics::set_position(glm::vec3 pos) {
	Transform transform = rb->getTransform();

	transform.setPosition(Vector3(pos.x, pos.y, pos.z));

	rb->setTransform(transform);
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

void BodyRigidPhysics::setLinearVelocity(glm::vec3 velocity) {
	Vector3 vel(velocity.x, velocity.y, velocity.z);
	rb->setLinearVelocity(vel);
}

void BodyRigidPhysics::addTorque(glm::vec3 torque) {
	Vector3 t(torque.x, torque.y, torque.z);
	rb->applyLocalTorque(t);
}

void BodyRigidPhysics::setAngularVelocity(glm::vec3 velocity) {
	Vector3 vel(velocity.x, velocity.y, velocity.z);
	rb->setAngularVelocity(vel);
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

glm::vec3 BodyRigidPhysics::getLinearVelocity() {
	Vector3 v3 = rb->getLinearVelocity();
	return glm::vec3(v3.x, v3.y, v3.z);
}

glm::vec3 BodyRigidPhysics::getAngularVelocity() {
	Vector3 v3 = rb->getAngularVelocity();
	return glm::vec3(v3.x, v3.y, v3.z);
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
	if (bounciness < 0) {
		bounciness = 0;
	} else if (bounciness > 1) {
		bounciness = 1;
	}

	if (friction < 0) {
		friction = 0;
	} else if (friction > 1) {
		friction = 1;
	}

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
	if (bounciness < 0) {
		bounciness = 0;
	} else if (bounciness > 1) {
		bounciness = 1;
	}

	if (friction < 0) {
		friction = 0;
	} else if (friction > 1) {
		friction = 1;
	}

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
	if (bounciness < 0) {
		bounciness = 0;
	} else if (bounciness > 1) {
		bounciness = 1;
	}

	if (friction < 0) {
		friction = 0;
	} else if (friction > 1) {
		friction = 1;
	}

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

void BodyRigidPhysics::addHeightFieldShape(glm::vec3 pos, float bounciness,
                                           float friction, int nColumns,
                                           int nRows, int minHeight,
                                           int maxHeight,
                                           unsigned char* heightValues) {
	/*
	if (bounciness < 0) {
	    bounciness = 0;
	} else if (bounciness > 1) {
	    bounciness = 1;
	}

	if (friction < 0) {
	    friction = 0;
	} else if (friction > 1) {
	    friction = 1;
	}

	int* values = new int[nColumns * nRows];
	for (int x = 0; x < nColumns; x++) {
	    for (int y = 0; y < nRows; y++) {
	        values[y * nColumns + x] = (int)heightValues[y * nColumns + x];
	    }
	}

	HeightFieldShape* heightFieldShape =
	    Physics::getPhysicsCommon().createHeightFieldShape(
	        nColumns, nRows, minHeight, maxHeight, values,
	        HeightFieldShape::HeightDataType::HEIGHT_INT_TYPE);

	Transform t = Transform::identity();
	t.setPosition(Vector3(pos.x, pos.y, pos.z));

	Collider* collider;
	collider = rb->addCollider(heightFieldShape, t);

	Material& mat = collider->getMaterial();

	mat.setBounciness(bounciness);
	mat.setFrictionCoefficient(friction);
	*/
}

bool BodyRigidPhysics::getIfGravityActive() { return rb->isGravityEnabled(); }

int BodyRigidPhysics::getRBType() { return (int)rb->getType(); }

int BodyRigidPhysics::getNumberOfColliders() { return rb->getNbColliders(); }

float BodyRigidPhysics::getLinearDamping() { return rb->getLinearDamping(); }

float BodyRigidPhysics::getAngularDamping() { return rb->getAngularDamping(); }

bool BodyRigidPhysics::getIfAllowedSleep() { return rb->isSleeping(); }

int BodyRigidPhysics::getColliderType(int index) {
	Collider* c = rb->getCollider(index);
	return (int)c->getCollisionShape()->getName();
}

float BodyRigidPhysics::getBounciness(int index) {
	Collider* c = rb->getCollider(index);
	return c->getMaterial().getBounciness();
}

float BodyRigidPhysics::getFriction(int index) {
	Collider* c = rb->getCollider(index);
	return c->getMaterial().getBounciness();
}

glm::vec3 BodyRigidPhysics::getLocalColliderPos(int index) {
	Collider* c = rb->getCollider(index);
	Transform t = c->getLocalToBodyTransform();
	return glm::vec3(t.getPosition().x, t.getPosition().y, t.getPosition().z);
}
