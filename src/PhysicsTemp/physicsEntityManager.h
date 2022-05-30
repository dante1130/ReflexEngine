#pragma once

#include <vector>
#include <string>
#include "Model/GameObject/BodyRigid.hpp"

class physicsEntityManager {
private:
	/// to facilitate quick lookup the entities are stored in a std::map, in
	/// which pointers to entities are cross referenced by their identifying
	/// number
	std::vector<BodyRigid*>* entityMap = new std::vector<BodyRigid*>;

public:
	~physicsEntityManager();

	/**
	 * @brief	Registers a new entity to the entity manager
	 * @param	*NewEntity	- the entity to store
	 */
	void registerEntity(BodyRigid* NewEntity);

	/**
	 * @brief	Get sthe entity based on its index (NOT ID)
	 * @param	index	- the index of the entity
	 * @return	NPC	- retrieved NPC
	 */
	BodyRigid* getEntityByIndex(int index) const;

	/**
	 * @brief	Gets the number of entites stored
	 * @return	int	- the number of entities
	 */
	int numberOfEntities();

	/**
	 * @brief	Removes all entitites
	 */
	void killEntities();

	/**
	 * @brief	Kills the manager
	 */
	void killManager();
};
