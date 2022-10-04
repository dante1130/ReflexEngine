#include "PhysicBody.hpp"

using namespace rp3d;

void PhysicsBody::collision(Collider* c1, Collider* c2, Vector3 normal,
                            CollisionEvent c_type) {
	///
	///
	///
	///
}

size_t PhysicsBody::colliderSize() { return colliders.size(); }

void PhysicsBody::removeCollider(size_t index) {
	if (index < 0 || index >= colliders.size()) return;

	switch (this->getColliderType(index)) {
		case 1:
			m_sphere.erase(colliders[index]);
			break;
		case 2:
			m_capsule.erase(colliders[index]);
			break;
		case 3:
			m_box.erase(colliders[index]);
			break;
		default:
			return;
	}
	deleteCollider(colliders[index]);
	colliders.erase(colliders.begin() + index);
}

void PhysicsBody::removeAllColliders() {
	m_box.clear();
	m_sphere.clear();
	m_capsule.clear();

	for (Collider* c : colliders) deleteCollider(c);

	colliders.clear();
}

void PhysicsBody::setObjectTrigger(bool ean) {
	for (Collider* c : colliders) c->setIsTrigger(ean);

	is_trigger = ean;
}

bool PhysicsBody::getIsTrigger() { return is_trigger; }

glm::vec3 PhysicsBody::getColliderPosition(size_t index, Apply type) {
	Vector3 temp;
	switch (type) {
		case Apply::LOCAL:
			temp = colliders[index]->getLocalToBodyTransform().getPosition();
			break;
		case Apply::WORLD:
			temp = colliders[index]->getLocalToWorldTransform().getPosition();
			break;
		default:
			break;
	}
	return glm::vec3(temp.x, temp.y, temp.z);
}

glm::vec4 PhysicsBody::getColliderOrientation(size_t index, Apply type) {
	Quaternion temp;

	switch (type) {
		case Apply::LOCAL:
			temp = colliders[index]->getLocalToBodyTransform().getOrientation();
			break;
		case Apply::WORLD:
			temp =
			    colliders[index]->getLocalToWorldTransform().getOrientation();
			break;
		default:
			break;
	}
	return glm::vec4(temp.w, temp.x, temp.y, temp.z);
}

float PhysicsBody::getColliderBounce(size_t index) {
	return colliders[index]->getMaterial().getBounciness();
}
float PhysicsBody::getColliderFriction(size_t index) {
	return colliders[index]->getMaterial().getFrictionCoefficient();
}
float PhysicsBody::getColliderMassDesity(size_t index) {
	return colliders[index]->getMaterial().getMassDensity();
}

int PhysicsBody::getColliderType(size_t index) {
	switch (colliders[index]->getCollisionShape()->getName()) {
		case CollisionShapeName::SPHERE:
			return 1;
		case CollisionShapeName::CAPSULE:
			return 2;
		case CollisionShapeName::BOX:
			return 3;
		default:
			return 0;
	}
}

std::string PhysicsBody::getColliderName(size_t index) {
	switch (getColliderType(index)) {
		case 1:
			return "Sphere" + std::to_string(index);
		case 2:
			return "Capsule" + std::to_string(index);
		case 3:
			return "Box" + std::to_string(index);
	}
}

std::vector<rp3d::Collider*> PhysicsBody::getColliders() { return colliders; }

void PhysicsBody::addMaterialToCollider(size_t index, float bounce,
                                        float mass_density, float friction) {
	Material& material = colliders[index]->getMaterial();
	material.setBounciness(bounce);
	material.setMassDensity(mass_density);
	material.setFrictionCoefficient(friction);
}

BoxShape* PhysicsBody::getColliderBox(size_t index) {
	try {
		if (getColliderType(index) == 3)
			return m_box.find(colliders[index])->second;
		else
			throw("Could not convert box type!");
	} catch (std::string err) {
		std::cout << "ERROR: " << err << std::endl;
	}
}

SphereShape* PhysicsBody::getColliderSphere(size_t index) {
	try {
		if (getColliderType(index) == 1)
			return m_sphere.find(colliders[index])->second;
		else
			throw("Could not convert sphere type!");
	} catch (std::string err) {
		std::cout << "ERROR: " << err << std::endl;
	}
}

CapsuleShape* PhysicsBody::getColliderCapsule(size_t index) {
	try {
		if (getColliderType(index) == 2)
			return m_capsule.find(colliders[index])->second;
		else
			throw("Could not convert capsule type!");
	} catch (std::string err) {
		std::cout << "ERROR: " << err << std::endl;
	}
}

size_t PhysicsBody::getColliderIndex(rp3d::Collider* collider) {
	for (size_t i = 0; i < colliders.size(); ++i) {
		if (colliders[i] == collider) return i;
	}

	return colliders.size();
}

glm::vec3 PhysicsBody::getPreviousPosition() {
	return previous_transform_position;
}
void PhysicsBody::setPreviousPosition(glm::vec3 prev_pos) {
	previous_transform_position = prev_pos;
}