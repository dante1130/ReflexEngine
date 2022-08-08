#include "Rigidbody.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"


void Rigidbody::init(bool usingReact, glm::vec3 pos, glm::vec3 rot)
{
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->init(rot, pos);
}

Rigidbody::Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot)
{
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->init(rot, pos);
}


//Encapsulation


int Rigidbody::colliderSize() { return pb->colliderSize(); }

glm::vec3 Rigidbody::getColliderPosition(int index, Apply type) { return pb->getColliderPosition(index, type); }

//glm::vec4 Rigidbody::getColliderOrientation(int index, Apply type);

float Rigidbody::getColliderBounce(int index) { return pb->getColliderBounce(index); }

float Rigidbody::getColliderFriction(int index) { return pb->getColliderFriction(index); }

float Rigidbody::getColliderMassDesity(int index) { return pb->getColliderMassDesity(index); }

int Rigidbody::getColliderType(int index) { return pb->getColliderType(index); }

const BoxShape* Rigidbody::getColliderBox(int index) { return pb->getColliderBox(index); }

const SphereShape* Rigidbody::getColliderSphere(int index) { return pb->getColliderSphere(index); }

const CapsuleShape* Rigidbody::getColliderCapsule(int index) { return pb->getColliderCapsule(index); }

void Rigidbody::addMaterialToCollider(int index, float bounce, float mass_density, float friction)
{
	return pb->addMaterialToCollider(index, bounce, mass_density, friction);
}

void Rigidbody::removeAllColliders() { pb->removeAllColliders(); }

void Rigidbody::setObjectTrigger(bool ean) { pb->setObjectTrigger(ean); }

bool Rigidbody::usingReactResolve() { return pb->usingReactResolve(); }

void Rigidbody::addForce(glm::vec3 force, Apply type) { pb->addForce(force, type); }

void Rigidbody::addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type)
{
	pb->addForceAtPoint(force, point, type);
}

void Rigidbody::addTorque(glm::vec3 torque, Apply type) { pb->addTorque(torque, type); }

void Rigidbody::addDragForce(float drag) { pb->addDragForce(drag); }

void Rigidbody::addDragTorque(float ang_drag) { pb->addDragTorque(ang_drag); }

void Rigidbody::setMass(float mass) { pb->setMass(mass); }

void Rigidbody::setCenterOfMass(glm::vec3 p) { pb->setCenterOfMass(p); }

void Rigidbody::setVelocity(glm::vec3 vel) {
	pb->setVelocity(vel);
}

void Rigidbody::setAngVelocity(glm::vec3 ang_vel) { pb->setAngVelocity(ang_vel); }

void Rigidbody::setType(BodyType type) { pb->setType(type); }

void Rigidbody::setType(int type) { pb->setType(type); }

void Rigidbody::enableGravity(bool ean) { pb->enableGravity(ean); }

void Rigidbody::setCanSleep(bool ean) { pb->setCanSleep(ean); }

float Rigidbody::getMass() { return pb->getMass(); }

glm::vec3 Rigidbody::getVelocity() { return pb->getVelocity(); }

glm::vec3 Rigidbody::getAngVelocity() { return pb->getAngVelocity(); }

float Rigidbody::getDragForce() { return pb->getDragForce(); }

float Rigidbody::getDragTorque() { return pb->getDragTorque(); }

BodyType Rigidbody::getType() { return pb->getType(); }

bool Rigidbody::getIsGravityEnabled() { return pb->getIsGravityEnabled(); }

bool Rigidbody::getCanSleep() { return pb->getCanSleep(); }

void Rigidbody::addBoxCollider(glm::vec3 pos, glm::vec3 size) { pb->addBoxCollider(pos, size); }

void Rigidbody::addSphereCollider(glm::vec3 pos, float radius) { pb->addSphereCollider(pos, radius); }

void Rigidbody::addCapsuleCollider(glm::vec3 pos, float radius, float height) { pb->addCapsuleCollider(pos, radius, height); }

void Rigidbody::addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) {
	pb->addBoxCollider(pos, size, bounce, friction);
}
void Rigidbody::addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
{
	pb->addSphereCollider(pos, radius, bounce, friction);
}
void Rigidbody::addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
{
	pb->addCapsuleCollider(pos, radius, height, bounce, friction);
}

glm::vec3 Rigidbody::getPosition() { return pb->getPosition(); }

glm::vec3 Rigidbody::getRotation() { return pb->getRotation(); }

glm::quat Rigidbody::getOrientation() { return pb->getOrientation(); }

void Rigidbody::setPosition(glm::vec3 pos) { pb->setPosition(pos); }

void Rigidbody::setQuanternion(glm::quat quat) { pb->setQuanternion(quat); }

void Rigidbody::setEulerRotation(glm::vec3 rot) { pb->setEulerRotation(rot); }
