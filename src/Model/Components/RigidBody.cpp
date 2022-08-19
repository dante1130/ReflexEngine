#include "RigidBody.hpp"

Component::Rigidbody::Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot)
{
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->initialise_body(pos, rot);

}

Component::Rigidbody::Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot, bool gravity_on, bool can_sleep,
	bool is_trigger, float linear_drag, float angular_drag) {

	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->initialise_body(pos, rot);

	pb->enableGravity(gravity_on);
	pb->setCanSleep(can_sleep);
	pb->setObjectTrigger(is_trigger);
	pb->setDragForce(linear_drag);
	pb->setDragTorque(angular_drag);

}

void Component::Rigidbody::init(bool usingReact, glm::vec3 pos, glm::vec3 rot)
{
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->initialise_body(pos, rot);
}

void Component::Rigidbody::setTransform(glm::vec3 pos, glm::vec3 rot)
{
	pb->setPosition(pos);
	pb->setEulerRotation(rot);
}

void Component::Rigidbody::setViewables(bool gravity_on, bool can_sleep,
	bool is_trigger, float linear_drag, float angular_drag)
{
	pb->enableGravity(gravity_on);
	pb->setCanSleep(can_sleep);
	pb->setObjectTrigger(is_trigger);
	pb->setDragForce(linear_drag);
	pb->setDragTorque(angular_drag);
}

// Using react
bool Component::Rigidbody::usingReactResolve() { return pb->usingReactResolve(); }


// Colliders

size_t Component::Rigidbody::colliderSize() { return pb->colliderSize(); }

glm::vec3 Component::Rigidbody::getColliderPosition(size_t index, Apply type) { return pb->getColliderPosition(index, type); }

float Component::Rigidbody::getColliderBounce(size_t index) { return pb->getColliderBounce(index); }

float Component::Rigidbody::getColliderFriction(size_t index) { return pb->getColliderFriction(index); }

float Component::Rigidbody::getColliderMassDesity(size_t index) { return pb->getColliderMassDesity(index); }

int Component::Rigidbody::getColliderType(size_t index) { return pb->getColliderType(index); }

const rp3d::BoxShape* Component::Rigidbody::getColliderBox(size_t index) { return pb->getColliderBox(index); }

const rp3d::SphereShape* Component::Rigidbody::getColliderSphere(size_t index) { return pb->getColliderSphere(index); }

const rp3d::CapsuleShape* Component::Rigidbody::getColliderCapsule(size_t index) { return pb->getColliderCapsule(index); }

void Component::Rigidbody::addMaterialToCollider(size_t index, float bounce, float mass_density, float friction)
{
	return pb->addMaterialToCollider(index, bounce, mass_density, friction);
}

void Component::Rigidbody::removeAllColliders() { pb->removeAllColliders(); }

void Component::Rigidbody::removeCollider(size_t index) { pb->removeCollider(index); }


// Gui viewable variables methods

void Component::Rigidbody::setObjectTrigger(bool ean) {
	pb->setObjectTrigger(ean);
	is_trigger = ean;
}

void Component::Rigidbody::enableGravity(bool ean) {
	pb->enableGravity(ean);
	gravity_on = ean;
}

void Component::Rigidbody::setCanSleep(bool ean) {
	pb->setCanSleep(ean);
	can_sleep = ean;
}

bool Component::Rigidbody::getIsGravityEnabled() { return pb->getIsGravityEnabled(); }

bool Component::Rigidbody::getCanSleep() { return pb->getCanSleep(); }

bool Component::Rigidbody::getIsTrigger() { return pb->getIsTrigger(); }


// Applying interaction methods

void Component::Rigidbody::addForce(glm::vec3 force, Apply type) {
	pb->addForce(force, type);
}

void Component::Rigidbody::addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type)
{
	pb->addForceAtPoint(force, point, type);
}

void Component::Rigidbody::addTorque(glm::vec3 torque, Apply type) { pb->addTorque(torque, type); }

void Component::Rigidbody::addDragForce(float drag) {
	pb->addDragForce(drag);
	lin_drag = pb->getDragForce();
}

void Component::Rigidbody::addDragTorque(float ang_drag) {
	pb->addDragTorque(ang_drag);
	ang_drag = pb->getDragTorque();
}


// Set methods

void Component::Rigidbody::setMass(float mass) { pb->setMass(mass); }

void Component::Rigidbody::setCenterOfMass(glm::vec3 p) { pb->setCenterOfMass(p); }

void Component::Rigidbody::setVelocity(glm::vec3 vel) {
	pb->setVelocity(vel);
}

void Component::Rigidbody::setAngVelocity(glm::vec3 ang_vel) { pb->setAngVelocity(ang_vel); }

void Component::Rigidbody::setDragForce(float drag) {
	pb->setDragForce(drag);
	lin_drag = drag;
}

void Component::Rigidbody::setDragTorque(float angular_drag) {
	pb->setDragTorque(angular_drag);
	ang_drag = angular_drag;
}

void Component::Rigidbody::setType(rp3d::BodyType type) { pb->setType(type); }

void Component::Rigidbody::setType(int type) { pb->setType(type); }


// Get methods

float Component::Rigidbody::getMass() { return pb->getMass(); }

glm::vec3 Component::Rigidbody::getVelocity() { return pb->getVelocity(); }

glm::vec3 Component::Rigidbody::getAngVelocity() { return pb->getAngVelocity(); }

float Component::Rigidbody::getDragForce() { return pb->getDragForce(); }

float Component::Rigidbody::getDragTorque() { return pb->getDragTorque(); }

rp3d::BodyType Component::Rigidbody::getType() { return pb->getType(); }


// Collider methods

//void addBoxCollider(glm::vec3 pos, glm::vec3 size) { pb->addBoxCollider(pos, size); }

//void addSphereCollider(glm::vec3 pos, float radius) { pb->addSphereCollider(pos, radius); }

//void addCapsuleCollider(glm::vec3 pos, float radius, float height) { pb->addCapsuleCollider(pos, radius, height); }

uint32_t Component::Rigidbody::addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) {
	return pb->addBoxCollider(pos, size, bounce, friction);
}
uint32_t Component::Rigidbody::addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
{
	return pb->addSphereCollider(pos, radius, bounce, friction);
}
uint32_t Component::Rigidbody::addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
{
	return pb->addCapsuleCollider(pos, radius, height, bounce, friction);
}


// Methods used for transform

glm::vec3 Component::Rigidbody::getPosition() { return pb->getPosition(); }

glm::vec3 Component::Rigidbody::getRotation() { return pb->getRotation(); }

glm::quat Component::Rigidbody::getOrientation() { return pb->getOrientation(); }

void Component::Rigidbody::setPosition(glm::vec3 pos) { pb->setPosition(pos); }

void Component::Rigidbody::setQuanternion(glm::quat quat) { pb->setQuaternion(quat); }

void Component::Rigidbody::setEulerRotation(glm::vec3 rot) { pb->setEulerRotation(rot); }


