#include "RigidBody.hpp"

Component::Rigidbody::Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot) {
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->initialise_body(pos, rot);

	gravity_on = false;
	can_sleep = true;
	is_trigger = false;
	lin_drag = 0.0f;
	ang_drag = 0.0f;

	using_react_start = usingReact;
}

Component::Rigidbody::Rigidbody(bool usingReact, glm::vec3 pos, glm::vec3 rot,
                                bool gravity_on_, bool can_sleep_,
                                bool is_trigger_, float linear_drag_,
                                float angular_drag_) {
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->initialise_body(pos, rot);

	pb->enableGravity(gravity_on_);
	pb->setCanSleep(can_sleep_);
	pb->setObjectTrigger(is_trigger_);
	pb->setDragForce(linear_drag_);
	pb->setDragTorque(angular_drag_);

	gravity_on = gravity_on_;
	can_sleep = can_sleep_;
	is_trigger = is_trigger_;
	lin_drag = linear_drag_;
	ang_drag = angular_drag_;

	using_react_start = usingReact;
}

void Component::Rigidbody::init(bool usingReact, glm::vec3 pos, glm::vec3 rot) {
	if (usingReact)
		pb = new ReactResolve();
	else
		pb = new EngineResolve();

	pb->initialise_body(pos, rot);

	gravity_on = false;
	can_sleep = true;
	is_trigger = false;
	lin_drag = 0.0f;
	ang_drag = 0.0f;

	using_react_start = usingReact;
}

bool Component::Rigidbody::intialised() { return pb != nullptr; }

void Component::Rigidbody::setTransform(glm::vec3 pos, glm::vec3 rot) {
	pb->setPosition(pos);
	pb->setEulerRotation(rot);
}

void Component::Rigidbody::setViewables(bool gravity_on, bool can_sleep,
                                        bool is_trigger, float linear_drag,
                                        float angular_drag) {
	pb->enableGravity(gravity_on);
	pb->setCanSleep(can_sleep);
	pb->setObjectTrigger(is_trigger);
	pb->setDragForce(linear_drag);
	pb->setDragTorque(angular_drag);
}

// Using react
bool Component::Rigidbody::usingReactResolve() {
	return pb->usingReactResolve();
}

// update

void Component::Rigidbody::update(float delta_time) { pb->update(delta_time); }

void Component::Rigidbody::deleteBody() { pb->delete_body(); }

// Colliders

size_t Component::Rigidbody::colliderSize() { return pb->colliderSize(); }

glm::vec3 Component::Rigidbody::getColliderPosition(size_t index, Apply type) {
	return pb->getColliderPosition(index, type);
}

float Component::Rigidbody::getColliderBounce(size_t index) {
	return pb->getColliderBounce(index);
}

float Component::Rigidbody::getColliderFriction(size_t index) {
	return pb->getColliderFriction(index);
}

float Component::Rigidbody::getColliderMassDesity(size_t index) {
	return pb->getColliderMassDesity(index);
}

int Component::Rigidbody::getColliderType(size_t index) {
	return pb->getColliderType(index);
}

rp3d::BoxShape* Component::Rigidbody::getColliderBox(size_t index) {
	return pb->getColliderBox(index);
}

rp3d::SphereShape* Component::Rigidbody::getColliderSphere(size_t index) {
	return pb->getColliderSphere(index);
}

rp3d::CapsuleShape* Component::Rigidbody::getColliderCapsule(size_t index) {
	return pb->getColliderCapsule(index);
}

void Component::Rigidbody::addMaterialToCollider(size_t index, float bounce,
                                                 float mass_density,
                                                 float friction) {
	return pb->addMaterialToCollider(index, bounce, mass_density, friction);
}

void Component::Rigidbody::removeAllColliders() { pb->removeAllColliders(); }

void Component::Rigidbody::removeCollider(size_t index) {
	pb->removeCollider(index);
}

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

bool Component::Rigidbody::getIsGravityEnabled() {
	return pb->getIsGravityEnabled();
}

bool Component::Rigidbody::getCanSleep() { return pb->getCanSleep(); }

bool Component::Rigidbody::getIsTrigger() { return pb->getIsTrigger(); }

// Applying interaction methods

void Component::Rigidbody::addForce(glm::vec3 force, Apply type) {
	pb->addForce(force, type);
}

void Component::Rigidbody::addForceAtPoint(glm::vec3 force, glm::vec3 point,
                                           ApplyPoint type) {
	pb->addForceAtPoint(force, point, type);
}

void Component::Rigidbody::addTorque(glm::vec3 torque, Apply type) {
	pb->addTorque(torque, type);
}

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

void Component::Rigidbody::setCenterOfMass(glm::vec3 p) {
	pb->setCenterOfMass(p);
}

void Component::Rigidbody::setVelocity(glm::vec3 vel) { pb->setVelocity(vel); }

void Component::Rigidbody::setAngVelocity(glm::vec3 ang_vel) {
	pb->setAngVelocity(ang_vel);
}

void Component::Rigidbody::setDragForce(float drag) {
	pb->setDragForce(drag);
	lin_drag = drag;
}

void Component::Rigidbody::setDragTorque(float angular_drag) {
	pb->setDragTorque(angular_drag);
	ang_drag = angular_drag;
}

void Component::Rigidbody::setType(int type) { pb->setType(type); }

// Get methods

float Component::Rigidbody::getMass() { return pb->getMass(); }

glm::vec3 Component::Rigidbody::getVelocity() { return pb->getVelocity(); }

glm::vec3 Component::Rigidbody::getAngVelocity() {
	return pb->getAngVelocity();
}

float Component::Rigidbody::getDragForce() { return pb->getDragForce(); }

float Component::Rigidbody::getDragTorque() { return pb->getDragTorque(); }

int Component::Rigidbody::getType() { return (int)pb->getType(); }

// Collider methods

std::vector<rp3d::Collider*> Component::Rigidbody::getColliders() {
	return pb->getColliders();
}

std::string Component::Rigidbody::getColliderName(size_t index) {
	return pb->getColliderName(index);
}

uint32_t Component::Rigidbody::addBoxCollider(glm::vec3 pos, glm::vec3 rot,
                                              glm::vec3 size, float friction,
                                              float mass, float epsilon) {
	return pb->addBoxCollider(pb, pos, rot, size, friction, mass, epsilon);
}
uint32_t Component::Rigidbody::addSphereCollider(glm::vec3 pos, glm::vec3 rot,
                                                 float radius, float friction,
                                                 float mass, float epsilon) {
	return pb->addSphereCollider(pb, pos, rot, radius, friction, mass, epsilon);
}
uint32_t Component::Rigidbody::addCapsuleCollider(glm::vec3 pos, glm::vec3 rot,
                                                  float radius, float height,
                                                  float friction, float mass,
                                                  float epsilon) {
	return pb->addCapsuleCollider(pb, pos, rot, radius, height, friction, mass,
	                              epsilon);
}

// Methods used for transform

glm::vec3 Component::Rigidbody::getPosition() { return pb->getPosition(); }

glm::vec3 Component::Rigidbody::getRotation() { return pb->getRotation(); }

glm::quat Component::Rigidbody::getOrientation() {
	return pb->getOrientation();
}

void Component::Rigidbody::setPosition(glm::vec3 pos) { pb->setPosition(pos); }

void Component::Rigidbody::setQuanternion(glm::quat quat) {
	pb->setQuaternion(quat);
}

void Component::Rigidbody::setEulerRotation(glm::vec3 rot) {
	pb->setEulerRotation(rot);
}

glm::vec3 Component::Rigidbody::getPreviousPosition() {
	return pb->getPreviousPosition();
}

void Component::Rigidbody::setPreviousPosition(glm::vec3 prev_pos) {
	pb->setPreviousPosition(prev_pos);
}

bool Component::Rigidbody::isSleeping() {
	return pb->isSleeping();
}

void Component::Rigidbody::setIsSleeping(bool ean) {
	pb->setIsSleeping(ean);
}
