#include "entityManager.h"

//------------------------- GetEntityFromID -----------------------------------
//-----------------------------------------------------------------------------
NPC* entityManager::getEntityFromID(int id) const {
	// find the entity
	// entityMap::const_iterator ent = entityMap.find(id);
	map<int, NPC*>::const_iterator ent = entityMap.find(id);
	if (ent == entityMap.end()) {
		return NULL;
	}
	return ent->second;
}

//--------------------------- RemoveEntity ------------------------------------
//-----------------------------------------------------------------------------
void entityManager::removeEntity(NPC* pEntity) {
	entityMap.erase(entityMap.find(pEntity->get_id()));
}

//---------------------------- RegisterEntity ---------------------------------
//-----------------------------------------------------------------------------
void entityManager::registerEntity(NPC* newEntity) {
	entityMap.insert(std::make_pair(newEntity->get_id(), newEntity));
}

NPC* entityManager::getEntityByIndex(int index) const {
	return entityMap.at(index);
}

int entityManager::numberOfEntities() { return entityMap.size(); }

void entityManager::killEntities() { entityMap.clear(); }
