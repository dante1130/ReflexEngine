#include "physicsEntityManager.h"
#include "AI/singletons.h"

physicsEntityManager::~physicsEntityManager() {}

void physicsEntityManager::registerEntity(BodyRigid* newEntity) {
	entityMap->push_back(newEntity);
}

BodyRigid* physicsEntityManager::getEntityByIndex(int index) const {
	return entityMap->at(index);
}

int physicsEntityManager::numberOfEntities() { return entityMap->size(); }

void physicsEntityManager::killEntities() { entityMap->clear(); }

void physicsEntityManager::killManager() { delete entityMap; }
