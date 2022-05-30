#include "collision.hpp"

bool sphereCollision(glm::vec3 posOne, float radOne, glm::vec3 posTwo,
                     float radTwo);

bool collisionResolution::collides(BodyRigid* rb, glm::vec3 new_pos) {
	int size = physicsEntityMgr.numberOfEntities();
	bool collisionOutcome = false;
	BodyRigid* temp;

	if (rb->getCapsuleColliders().size() == 0) {
		return false;
	}

	for (int count = 0; count < size; count++) {
		temp = physicsEntityMgr.getEntityByIndex(count);
		if (temp->getCapsuleColliders().size() == 0) {
			continue;
		} else {
			collisionOutcome = sphereCollision(
			    new_pos, rb->getCapsuleColliders().at(0).m_radius,
			    temp->position, temp->getCapsuleColliders().at(0).m_radius);
		}

		if (collisionOutcome) {
			if (!(rb->position.x == temp->position.x &&
			      rb->position.z == temp->position.z)) {
				return collisionOutcome;
			}
		}
	}

	return collisionOutcome;
}

bool sphereCollision(glm::vec3 posOne, float radOne, glm::vec3 posTwo,
                     float radTwo) {
	glm::vec3 dist = posOne - posTwo;
	float distance = glm::length(dist);

	if (distance < (radOne + radTwo)) {
		return true;
	}

	return false;
}
