#include "PhysicBody.hpp"

const int PhysicsBody::colliderSize() { 
	return colliders.size();
}

void PhysicsBody::removeAllColliders()
{
	m_box.clear();
	m_sphere.clear();;
	m_capsule.clear();

	colliders.clear();
}

void PhysicsBody::setObjectTrigger(bool ean)
{
	for (Collider* c : colliders)
		c->setIsTrigger(ean);

}
const glm::vec3 PhysicsBody::getColliderPosition(int index, Apply type)
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

const glm::vec4 PhysicsBody::getColliderOrientation(int index, Apply type)
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

const float PhysicsBody::getColliderBounce(int index){
	return colliders[index]->getMaterial().getBounciness();
}
const float PhysicsBody::getColliderFriction(int index){
	return colliders[index]->getMaterial().getFrictionCoefficient();
}
const float PhysicsBody::getColliderMassDesity(int index) {
	return colliders[index]->getMaterial().getMassDensity();
}

const int PhysicsBody::getColliderType(int index)
{
	switch (colliders[index]->getCollisionShape()->getName())
	{
		case CollisionShapeName::SPHERE: 
			return 1;
		case CollisionShapeName::CAPSULE :
			return 2;
		case CollisionShapeName::BOX :
			return 3;
		default:
			return 0;
	}
}

void PhysicsBody::addMaterialToCollider(int index, float bounce,
	float mass_density, float friction)
{
	Material& material = colliders[index]->getMaterial();
	material.setBounciness(bounce);
	material.setMassDensity(mass_density);
	material.setFrictionCoefficient(friction);
}


const BoxShape* PhysicsBody::getColliderBox(int index){
	try {
		if (getColliderType(index) == 3)
			return m_box.find(index)->second;
		else
			throw("Could not convert box type!");
	}
	catch(std::string err)
	{
		std::cout << "ERROR: " << err << std::endl;
	}
}
const SphereShape* PhysicsBody::getColliderSphere(int index) {
	try {
		if (getColliderType(index) == 1)
			return m_sphere.find(index)->second;
		else
			throw("Could not convert sphere type!");
	}
	catch (std::string err)
	{
		std::cout << "ERROR: " << err << std::endl;
	}
}
const CapsuleShape* PhysicsBody::getColliderCapsule(int index) {
	try {
		if (getColliderType(index) == 2)
			return m_capsule.find(index)->second;
		else
			throw("Could not convert capsule type!");
	}
	catch (std::string err)
	{
		std::cout << "ERROR: " << err << std::endl;
	}
}
