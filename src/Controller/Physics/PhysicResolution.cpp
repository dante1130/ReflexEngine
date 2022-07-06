#include "PhysicResolution.hpp"


void PhysicResolution::addBoxCollider(glm::vec3 pos, glm::vec3 size) 
{
	BoxShape* bs = Physics::getPhysicsCommon().createBoxShape(
	    Vector3(size.x / 2, size.y / 2, size.z / 2));
	//identity only for now maybe idk
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	
	colliders.push_back(cb->addCollider(bs, center));

}

void PhysicResolution::addSphereCollider(glm::vec3 pos, float radius) 
{
	SphereShape* ss = Physics::getPhysicsCommon().createSphereShape(radius);
	// identity only for now maybe idk
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());

	colliders.push_back(cb->addCollider(ss, center));
}

void PhysicResolution::addCapsuleCollider(glm::vec3 pos, float radius,float height) 
{
	CapsuleShape* cs = Physics::getPhysicsCommon().createCapsuleShape(radius, height);
	// identity only for now maybe idk
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());

	colliders.push_back(cb->addCollider(cs, center));
}


glm::vec3 PhysicResolution::getPosition() 
{
	Vector3 p = cb->getTransform().getPosition();
	return glm::vec3(p.x, p.y, p.z);
}

glm::vec3 PhysicResolution::getRotation() 
{
	Quaternion r = cb->getTransform().getOrientation();
	return glm::vec3(r.x, r.y, r.z);
}

float PhysicResolution::getAngle() 
{
	return cb->getTransform().getOrientation().w;
}

