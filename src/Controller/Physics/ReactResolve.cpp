#include "ReactResolve.hpp"

bool ReactResolve::usingReactResolve() { 
	return true; 
}

ReactResolve::ReactResolve() 
{ 
	 //something
}


void ReactResolve::init(glm::vec3 rot, glm::vec3 pos, float angle) 
{
	Vector3 p = Vector3(pos.x, pos.y, pos.z);
	Quaternion qt = Quaternion(Vector3(rot.x, rot.y, rot.z), angle);

	rb = Physics::getPhysicsWorld()->createRigidBody(Transform(p, qt));
}

void ReactResolve::addForce(glm::vec3 force, Apply type) 
{ 
	try {
		Vector3 temp_force = Vector3(force.x, force.y, force.z);
		switch(type)
		{ 
			case Apply::LOCAL :
				rb->applyLocalForceAtCenterOfMass(temp_force);
				break;
			case Apply::WORLD :
				rb->applyWorldForceAtCenterOfMass(temp_force);
				break;
			default:
				break;
		}
	}
	catch(const std::exception& e) 
	{
		std::cout << "Error: " << e.what() << '\n';
	}
}

void ReactResolve::addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type) {
	try {
		Vector3 temp_force = Vector3(force.x, force.y, force.z);
		Vector3 temp_point = Vector3(point.x, point.y, point.z);
		switch (type) {
			case ApplyPoint::LOCAL_LOCAL :
				rb->applyLocalForceAtLocalPosition(temp_force, temp_point); 
				break;
			case ApplyPoint::LOCAL_WORLD :
				rb->applyLocalForceAtWorldPosition(temp_force, temp_point); 
				break;
			case ApplyPoint::WORLD_LOCAL :
				rb->applyWorldForceAtLocalPosition(temp_force, temp_point);
				break;
			case ApplyPoint::WORLD_WORLD :
				rb->applyWorldForceAtWorldPosition(temp_force, temp_point);
				break;
			default:
				break;
		}
	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << '\n';
	}
}

void ReactResolve::addTorque(glm::vec3 torque, Apply type) 
{
	try {
		Vector3 temp_torque = Vector3(torque.x, torque.y, torque.z);
		switch (type) {
			case Apply::LOCAL :
				rb->applyLocalTorque(temp_torque);
				break;
			case Apply::WORLD :
				rb->applyWorldTorque(temp_torque);
				break;
			default:
				break;
		}
	}catch(const std::exception& e) {
		std::cout << "Error: " << e.what() << '\n';
	}
}

void ReactResolve::addDragForce(float drag) { 
	rb->setLinearDamping(drag); 
}

void ReactResolve::addDragTorque(float ang_drag) {
	rb->setAngularDamping(ang_drag);
}


void ReactResolve::setMass(float mass) { 
	rb->setMass(mass); 
}
void ReactResolve::setCenterOfMass(glm::vec3 p) { 
	rb->setLocalCenterOfMass(Vector3(p.x, p.y, p.z));
}
void ReactResolve::setVelocity(glm::vec3 vel) {
	rb->setLinearVelocity(Vector3(vel.x, vel.y, vel.z));
}
void ReactResolve::setAngVelocity(glm::vec3 ang_vel) {
	rb->setLinearVelocity(Vector3(ang_vel.x, ang_vel.y, ang_vel.z));
}
void ReactResolve::setType(BodyType type) { 
	rb->setType(type); 
}
void ReactResolve::enableGravity(bool ean) {
	rb->enableGravity(ean);
}
void ReactResolve::setCanSleep(bool ean) {
	rb->setIsAllowedToSleep(ean);
}

const float ReactResolve::getMass(){
	return rb->getMass();
}
const glm::vec3 ReactResolve::getVelocity() {
	Vector3 v = rb->getLinearVelocity();
	return glm::vec3(v.x, v.y, v.z);
}
const glm::vec3 ReactResolve::getAngVelocity() {
	Vector3 av = rb->getAngularVelocity();
	return glm::vec3(av.x, av.y, av.z);
}
const float ReactResolve::getDragForce() {
	return rb->getLinearDamping();
}
const float ReactResolve::getDragTorque() {
	return rb->getAngularDamping();
}
const BodyType ReactResolve::getType() {
	return rb->getType();
}
const bool ReactResolve::getIsGravityEnabled() {
	return rb->isGravityEnabled();
}
const bool ReactResolve::getCanSleep() {
	return rb->isAllowedToSleep();
}

void ReactResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size)
{
	BoxShape* bs = Physics::getPhysicsCommon().createBoxShape(
		Vector3(size.x / 2, size.y / 2, size.z / 2));
	// identity only for now maybe idk
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(rb->addCollider(bs, center));
	m_box.emplace(colliders.size() - 1, bs);
}

void ReactResolve::addSphereCollider(glm::vec3 pos, float radius)
{
	SphereShape* ss = Physics::getPhysicsCommon().createSphereShape(radius);
	// identity only for now maybe idk
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(rb->addCollider(ss, center));
	m_sphere.emplace(colliders.size() - 1, ss);
}

void ReactResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height) 
{
	CapsuleShape* cs = Physics::getPhysicsCommon().createCapsuleShape(radius, height);
	// identity only for now maybe idk
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(rb->addCollider(cs, center));
	m_capsule.emplace(colliders.size() - 1, cs);
}

const glm::vec3 ReactResolve::getPosition() {
	Vector3 p = rb->getTransform().getPosition();
	return glm::vec3(p.x, p.y, p.z);
}

const glm::vec3 ReactResolve::getRotation() {
	Quaternion r = rb->getTransform().getOrientation();
	return glm::vec3(r.x, r.y, r.z);
}

const float ReactResolve::getAngle() {
	return rb->getTransform().getOrientation().w;
}

//void ReactResolve::setIsTrigger(bool ean) {
//	for (Collider* c : colliders) 
//		c->setIsTrigger(ean);
//}




