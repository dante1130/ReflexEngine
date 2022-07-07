#include "PhysicResolution.hpp"

const int PhysicResolution::colliderSize() { 
	return colliders.size();
}

void PhysicResolution::removeAllColliders()
{
	m_box.clear();
	m_sphere.clear();;
	m_capsule.clear();

	colliders.clear();
}

const glm::vec3 PhysicResolution::getColliderPosition(int index, Apply type)
{
	Vector3 temp;
	switch (type)
	{
		case Apply::LOCAL :
			temp = colliders[index]->getLocalToBodyTransform().getPosition();
			break;
		case Apply::WORLD :
			temp = colliders[index]->getLocalToWorldTransform().getPosition();
			break;
		default:
			break;
	}
	return glm::vec3(temp.x, temp.y, temp.z);
}

const glm::vec4 PhysicResolution::getColliderOrientation(int index, Apply type)
{
	Quaternion temp;
	switch (type)
	{
	case Apply::LOCAL:
		temp = colliders[index]->getLocalToBodyTransform().getOrientation();
		break;
	case Apply::WORLD:
		temp = colliders[index]->getLocalToWorldTransform().getOrientation();
		break;
	default:
		break;
	}
	return glm::vec4(temp.w, temp.x, temp.y, temp.z);
}

const float PhysicResolution::getColliderBounce(int index){
	return colliders[index]->getMaterial().getBounciness();
}
const float PhysicResolution::getColliderFriction(int index){
	return colliders[index]->getMaterial().getFrictionCoefficient();
}
const float PhysicResolution::getColliderMassDesity(int index) {
	return colliders[index]->getMaterial().getMassDensity();
}

const int PhysicResolution::getColliderType(int index)
{
	switch (colliders[index]->getCollisionShape()->getName())
	{
		case CollisionShapeName::BOX : 
			return 1;
		case CollisionShapeName::SPHERE :
			return 2;
		case CollisionShapeName::CAPSULE :
			return 3;
		default:
			return 0;
	}
}

void PhysicResolution::addMaterialToCollider(int index, float bounce,
	float mass_density, float friction)
{
	Material& material = colliders[index]->getMaterial();
	material.setBounciness(bounce);
	material.setMassDensity(mass_density);
	material.setFrictionCoefficient(friction);
}


const BoxShape* PhysicResolution::getColliderBox(int index){
	try {
		if (getColliderType(index) == 1)
			return m_box.find(index)->second;
		else
			throw("Could not convert box type!");
	}
	catch(std::string err)
	{
		std::cout << "ERROR: " << err << std::endl;
	}
}
const SphereShape* PhysicResolution::getColliderSphere(int index) {
	try {
		if (getColliderType(index) == 2)
			return m_sphere.find(index)->second;
		else
			throw("Could not convert sphere type!");
	}
	catch (std::string err)
	{
		std::cout << "ERROR: " << err << std::endl;
	}
}
const CapsuleShape* PhysicResolution::getColliderCapsule(int index) {
	try {
		if (getColliderType(index) == 3)
			return m_capsule.find(index)->second;
		else
			throw("Could not convert capsule type!");
	}
	catch (std::string err)
	{
		std::cout << "ERROR: " << err << std::endl;
	}
}
