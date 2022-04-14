#pragma once

#include "Model/GameObject/GameObject.hpp"
#include "Model/GameObject/Item.hpp"
#include "Model/GameObject/Water.hpp"

class GameAssetFactory {
public:
	/**
	 * @brief	Parameterised factory method pattern for created game objects
	 * @param	type		- The type of object to be created
	 * @param	fileName	- The name of the lua file for object creation
	 * @return	*GameObject - A child game object
	 *
	 * @pre	type/file exists
	 * @post	Game object created
	 */
	GameObject* create(std::string fileName);

private:
	bool isLuaScript(std::string luaScript);
	std::string getObjectType(std::string luaScript);

	Item* loadItem();
	Water* loadWater();
};
