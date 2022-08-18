#include "Rigidbody.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"


void Rigidbody_::init(bool usingReact, glm::vec3 pos, glm::vec3 rot)
{
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->init(pos, rot);
}

Rigidbody_::Rigidbody_(bool usingReact, glm::vec3 pos, glm::vec3 rot)
{
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->init(pos, rot);
}


//Encapsulation


int Rigidbody_::colliderSize() { return pb->colliderSize(); }

glm::vec3 Rigidbody_::getColliderPosition(int index, Apply type) { return pb->getColliderPosition(index, type); }

//glm::vec4 Rigidbody::getColliderOrientation(int index, Apply type);

float Rigidbody_::getColliderBounce(int index) { return pb->getColliderBounce(index); }

float Rigidbody_::getColliderFriction(int index) { return pb->getColliderFriction(index); }

float Rigidbody_::getColliderMassDesity(int index) { return pb->getColliderMassDesity(index); }

int Rigidbody_::getColliderType(int index) { return pb->getColliderType(index); }

const BoxShape* Rigidbody_::getColliderBox(int index) { return pb->getColliderBox(index); }

const SphereShape* Rigidbody_::getColliderSphere(int index) { return pb->getColliderSphere(index); }

const CapsuleShape* Rigidbody_::getColliderCapsule(int index) { return pb->getColliderCapsule(index); }

void Rigidbody_::addMaterialToCollider(int index, float bounce, float mass_density, float friction)
{
	return pb->addMaterialToCollider(index, bounce, mass_density, friction);
}

void Rigidbody_::removeAllColliders() { pb->removeAllColliders(); }

void Rigidbody_::setObjectTrigger(bool ean) { pb->setObjectTrigger(ean); }

bool Rigidbody_::usingReactResolve() { return pb->usingReactResolve(); }

void Rigidbody_::addForce(glm::vec3 force, Apply type) { pb->addForce(force, type); }

void Rigidbody_::addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type)
{
	pb->addForceAtPoint(force, point, type);
}

void Rigidbody_::addTorque(glm::vec3 torque, Apply type) { pb->addTorque(torque, type); }

void Rigidbody_::addDragForce(float drag) { pb->addDragForce(drag); }

void Rigidbody_::addDragTorque(float ang_drag) { pb->addDragTorque(ang_drag); }

void Rigidbody_::setMass(float mass) { pb->setMass(mass); }

void Rigidbody_::setCenterOfMass(glm::vec3 p) { pb->setCenterOfMass(p); }

void Rigidbody_::setVelocity(glm::vec3 vel) {
	pb->setVelocity(vel);
}

void Rigidbody_::setAngVelocity(glm::vec3 ang_vel) { pb->setAngVelocity(ang_vel); }

void Rigidbody_::setDragForce(float drag){ pb->setDragForce(drag); }

void Rigidbody_::setDragTorque(float ang_drag) { pb->setDragTorque(ang_drag); }

void Rigidbody_::setType(BodyType type) { pb->setType(type); }

void Rigidbody_::setType(int type) { pb->setType(type); }

void Rigidbody_::enableGravity(bool ean) { pb->enableGravity(ean); }

void Rigidbody_::setCanSleep(bool ean) { pb->setCanSleep(ean); }

float Rigidbody_::getMass() { return pb->getMass(); }

glm::vec3 Rigidbody_::getVelocity() { return pb->getVelocity(); }

glm::vec3 Rigidbody_::getAngVelocity() { return pb->getAngVelocity(); }

float Rigidbody_::getDragForce() { return pb->getDragForce(); }

float Rigidbody_::getDragTorque() { return pb->getDragTorque(); }

BodyType Rigidbody_::getType() { return pb->getType(); }

bool Rigidbody_::getIsGravityEnabled() { return pb->getIsGravityEnabled(); }

bool Rigidbody_::getCanSleep() { return pb->getCanSleep(); }

bool Rigidbody_::getIsTrigger() { return pb->getIsTrigger(); }

void Rigidbody_::addBoxCollider(glm::vec3 pos, glm::vec3 size) { pb->addBoxCollider(pos, size); }

void Rigidbody_::addSphereCollider(glm::vec3 pos, float radius) { pb->addSphereCollider(pos, radius); }

void Rigidbody_::addCapsuleCollider(glm::vec3 pos, float radius, float height) { pb->addCapsuleCollider(pos, radius, height); }

void Rigidbody_::addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) {
	pb->addBoxCollider(pos, size, bounce, friction);
}
void Rigidbody_::addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
{
	pb->addSphereCollider(pos, radius, bounce, friction);
}
void Rigidbody_::addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
{
	pb->addCapsuleCollider(pos, radius, height, bounce, friction);
}

glm::vec3 Rigidbody_::getPosition() { return pb->getPosition(); }

glm::vec3 Rigidbody_::getRotation() { return pb->getRotation(); }

glm::quat Rigidbody_::getOrientation() { return pb->getOrientation(); }

void Rigidbody_::setPosition(glm::vec3 pos) { pb->setPosition(pos); }

void Rigidbody_::setQuanternion(glm::quat quat) { pb->setQuanternion(quat); }

void Rigidbody_::setEulerRotation(glm::vec3 rot) { pb->setEulerRotation(rot); }
