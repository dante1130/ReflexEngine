#pragma once

#include <map>
#include <string>
#include "NPC.hpp"

class entityManager {
private:
	/// to facilitate quick lookup the entities are stored in a std::map, in
	/// which pointers to entities are cross referenced by their identifying
	/// number
	std::map<int, NPC*>* entityMap = new std::map<int, NPC*>;

public:
	~entityManager();

	/**
	 * @brief	Registers a new entity to the entity manager
	 * @param	*NewEntity	- the entity to store
	 */
	void registerEntity(NPC* NewEntity);

	/**
	 * @brief	Returns the entity as given by the id
	 * @param	id	- entity identifier (id found in an NPC)
	 * @param	NPC	- retrieved NPC
	 */
	NPC* getEntityFromID(int id) const;
	/**
	 * @brief	Removes an entity from the list
	 * @param	pEntity	- the entity to remove
	 */
	void removeEntity(NPC* pEntity);

	/**
	 * @brief	Get sthe entity based on its index (NOT ID)
	 * @param	index	- the index of the entity
	 * @return	NPC	- retrieved NPC
	 */
	NPC* getEntityByIndex(int index) const;

	/**
	 * @brief	Gets the number of entites stored
	 * @return	int	- the number of entities
	 */
	int numberOfEntities();

	/**
	 * @brief	Removes all entitites
	 */
	void killEntities();

	void killManager();
};
