#include "EngineResolve.hpp"

using namespace rp3d;

bool EngineResolve::usingReactResolve() 
{ 
	return false; 
}

EngineResolve::EngineResolve() 
{ 
	//something
}

void EngineResolve::initialise_body(glm::vec3 pos, glm::vec3 rot, float angle) {
	Vector3 position(pos.x, pos.y, pos.z);
	Quaternion orientation = Quaternion::identity();

	angle = angle / (180 / PI_RP3D);

	float x = rot.x * sin(angle / 2);
	float y = rot.y * sin(angle / 2);
	float z = rot.z * sin(angle / 2);
	float w = cos(angle / 2);

	float normal = sqrt(pow(cos(angle / 2), 2) +
		pow(rot.x, 2) * pow(sin(angle / 2), 2) +
		pow(rot.y, 2) * pow(sin(angle / 2), 2) +
		pow(rot.z, 2) * pow(sin(angle / 2), 2));

	orientation.setAllValues(x / normal, y / normal, z / normal, w / normal);

	cb = Physics::getPhysicsWorld()->createRigidBody(Transform(position, orientation));
}

void EngineResolve::initialise_body(glm::vec3 pos, glm::vec3 rot)
{
	Vector3 position(pos.x, pos.y, pos.z);
	Quaternion orientation = rp3d::Quaternion::identity();
	glm::vec3 rot_radians = glm::radians(rot);

	double cy = glm::cos(rot_radians.z * 0.5); // cosine applied on yaw
	double sy = glm::sin(rot_radians.z * 0.5); // sine applied on yaw
	double cp = glm::cos(rot_radians.y * 0.5); // cosine applied on pitch
	double sp = glm::sin(rot_radians.y * 0.5); // sine applied on pitch
	double cr = glm::cos(rot_radians.x * 0.5); // cosine applied on roll
	double sr = glm::sin(rot_radians.x * 0.5); // sine applied on roll

	orientation.w = cr * cp * cy + sr * sp * sy;
	orientation.x = sr * cp * cy - cr * sp * sy;
	orientation.y = cr * sp * cy + sr * cp * sy;
	orientation.z = cr * cp * sy - sr * sp * cy;

	cb = Physics::getPhysicsWorld()->createRigidBody(Transform(position, orientation));

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
void EngineResolve::setDragForce(float drag)
{

}

void EngineResolve::setDragTorque(float ang_drag)
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

float EngineResolve::getMass()
{
	return 0.0f;
}
glm::vec3 EngineResolve::getVelocity()
{
	return glm::vec3(0.0f);
}
glm::vec3 EngineResolve::getAngVelocity()
{
	return glm::vec3(0.0f);
}
float EngineResolve::getDragForce()
{
	return 0.0f;
}
float EngineResolve::getDragTorque()
{
	return 0.0f;
}

BodyType EngineResolve::getType()
{
	return BodyType::STATIC;
}
bool EngineResolve::getIsGravityEnabled()
{
	return false;
}
bool EngineResolve::getCanSleep()
{
	return false;
}

uint32_t EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size)
{
	return 0;
}
uint32_t EngineResolve::addSphereCollider(glm::vec3 pos, float radius)
{
	return 0;
}
uint32_t EngineResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height)
{
	return 0;
}

uint32_t EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction)
{
	return 0;
}
uint32_t EngineResolve::addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
{
	return 0;
}
uint32_t EngineResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
{
	return 0;
}

void EngineResolve::deleteCollider(Collider* collider) {
	cb->removeCollider(collider);
}




glm::vec3 EngineResolve::getPosition() {
	return glm::vec3(0);
}

glm::vec3 EngineResolve::getRotation() {
	return glm::vec3(0);
}

glm::quat EngineResolve::getOrientation() {
	return glm::quat(0, glm::vec3(0));
}

void EngineResolve::setPosition(glm::vec3 pos)
{
	
}

void EngineResolve::setQuaternion(glm::quat quat)
{

}

void EngineResolve::setEulerRotation(glm::vec3 rot)
{

}


//Physics object needed, can delete later
float EngineResolve::getAngle()
{
	return 0.0f;
}
void EngineResolve::setRotation(glm::vec3 rot)
{

}
void EngineResolve::setAngle(float ang)
{

}