#include "EngineResolve.hpp"

bool EngineResolve::usingReactResolve() 
{ 
	return false; 
}

EngineResolve::EngineResolve() 
{ 
	//something
}

void EngineResolve::init(glm::vec3 rot, glm::vec3 pos, float angle) {
	Vector3 p = Vector3(pos.x, pos.y, pos.z);
	Quaternion qt = Quaternion(Vector3(rot.x, rot.y, rot.z), angle);

	cb = Physics::getPhysicsWorld()->createCollisionBody(Transform(p, qt));
}

void EngineResolve::addForce(glm::vec3 force, Apply type)
{

}

void EngineResolve::addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type)
{

}

void EngineResolve::addTorque(glm::vec3 torque, Apply type)
{

}

void EngineResolve::addDragForce(float drag)
{

}

void EngineResolve::addDragTorque(float ang_drag)
{

}

void EngineResolve::setMass(float mass)
{

}

void EngineResolve::setCenterOfMass(glm::vec3 p)
{

}

void EngineResolve::setVelocity(glm::vec3 vel)
{

}
void EngineResolve::setAngVelocity(glm::vec3 ang_vel)
{

}

void EngineResolve::setType(BodyType type)
{

}
void EngineResolve::setType(int type)
{

}
void EngineResolve::enableGravity(bool ean)
{

}
void EngineResolve::setCanSleep(bool ean)
{

}

const float EngineResolve::getMass()
{
	return 0.0f;
}
const glm::vec3 EngineResolve::getVelocity()
{
	return glm::vec3(0.0f);
}
const glm::vec3 EngineResolve::getAngVelocity()
{
	return glm::vec3(0.0f);
}
const float EngineResolve::getDragForce()
{
	return 0.0f;
}
const float EngineResolve::getDragTorque()
{
	return 0.0f;
}

const BodyType EngineResolve::getType()
{
	return BodyType::STATIC;
}
const bool EngineResolve::getIsGravityEnabled()
{
	return false;
}
const bool EngineResolve::getCanSleep()
{
	return false;
}

void EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size)
{

}
void EngineResolve::addSphereCollider(glm::vec3 pos, float radius)
{

}
void EngineResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height)
{

}

void EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction)
{

}
void EngineResolve::addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
{

}
void EngineResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
{

}

const glm::vec3 EngineResolve::getPosition()
{
	return glm::vec3(0.0f);
}
const glm::vec3 EngineResolve::getRotation()
{
	return glm::vec3(0.0f);
}
const float EngineResolve::getAngle()
{
	return 0.0f;
}

void EngineResolve::setPosition(glm::vec3 pos) {

}
void EngineResolve::setRotation(glm::vec3 rot)
{

}
void EngineResolve::setAngle(float ang) {

}