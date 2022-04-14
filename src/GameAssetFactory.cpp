#include "GameAssetFactory.hpp"

GameObject* GameAssetFactory::create(std::string fileName) {
	if (fileName.length() == 0 || isLuaScript(fileName) == false) {
		return NULL;
	}
	// GetType(fileName);
	std::string type = getObjectType(fileName);

	if (type == "Item") {
		//
		// return loadItem(fileName);
	} else if (type == "Water") {
		//
		// return GameObjectLoader::water(fileName);
	} else if (type == "Player") {
		//
		// return GameObjectLoader::player(fileName);
	} else if (type == "NPC") {
		//
		// return GameObjectLoader::npc(fileName);
	} else {
		return NULL;
	}
}

bool GameAssetFactory::isLuaScript(std::string luaScript) {
	int pos = luaScript.find_last_of(".");

	std::string ext = "n/a";
	if (pos != -1 && (luaScript.length() > pos + (int)1)) {
		ext = luaScript.substr(pos + (int)1, luaScript.length());
	}

	if (ext._Equal("lua")) {
		return true;
	} else {
		return false;
	}
}

std::string GameAssetFactory::getObjectType(std::string luaScript) {
	// sol::state lua;
	return "N/A";
}
