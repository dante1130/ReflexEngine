#ifndef __ENTITYMANAGER_H
#define __ENTITYMANAGER_H

#include <map>
#include <string>
#include <map>
#include "NPC.hpp"

class entityManager {
private:
	// to facilitate quick lookup the entities are stored in a std::map, in
	// which pointers to entities are cross referenced by their identifying
	// number
	map<int, NPC*> entityMap;

public:
	// this method stores a pointer to the entity in the std::vector
	// at the index position indicated by the entity's ID
	//(makes for faster access)
	void registerEntity(NPC* NewEntity);
	// returns a pointer to the entity with the ID given as a parameter
	NPC* getEntityFromID(int id) const;
	// this method removes the entity from the list
	void removeEntity(NPC* pEntity);
};
#endif
