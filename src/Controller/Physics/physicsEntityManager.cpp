#include "physicsEntityManager.h"
#include "AI/singletons.h"

physicsEntityManager::~physicsEntityManager() {}

void physicsEntityManager::registerEntity(BodyRigid* newEntity) {
	entityMap.push_back(newEntity);
}

BodyRigid* physicsEntityManager::getEntityByIndex(int index) const {
	return entityMap.at(index);
}

int physicsEntityManager::numberOfEntities() { return entityMap.size(); }

void physicsEntityManager::killEntities() { entityMap.clear(); }

bool physicsEntityManager::collides(glm::vec3 old_pos, glm::vec3 new_pos,
                                    float radius) {
	int size = physicsEntityMgr.numberOfEntities();
	bool collisionOutcome = false;

	for (int count = 0; count < size; count++) {
		if (entityMap[count]->getCapsuleColliders().size() == 0) {
			continue;
		} else {
			collisionOutcome = sphereCollision(
			    new_pos, radius, entityMap[count]->position,
			    entityMap[count]->getCapsuleColliders().at(0).m_radius);
		}

		if (collisionOutcome) {
			if (!(old_pos.x == entityMap[count]->position.x &&
			      old_pos.z == entityMap[count]->position.z)) {
				return collisionOutcome;
			}
		}
	}

	return collisionOutcome;

	// return false;
}

bool physicsEntityManager::sphereCollision(glm::vec3 posOne, float radOne,
                                           glm::vec3 posTwo, float radTwo) {
	glm::vec3 dist = posOne - posTwo;
	float distance = glm::length(dist);

	if (distance < (radOne + radTwo)) {
		return true;
	}

	return false;
}

void physicsEntityManager::garbage_collection() {
	int size = numberOfEntities();
	for (int count = 0; count < numberOfEntities(); count++) {
		if (entityMap[count]->position.y < -5000 ||
		    entityMap[count]->remove == true) {
			entityMap.erase(entityMap.begin() + count);
			count--;
		}
	}
}
