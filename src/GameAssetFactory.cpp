#include "GameAssetFactory.hpp"

GameObject* GameAssetFactory::create(std::string fileName) {
	if (fileName.length() == 0 || isLuaScript(fileName) == false) {
		return NULL;
	}
	// GetType(fileName);
	std::string type = getObjectType(fileName);

	if (type == "Item") {
		return loadItem(fileName);
	} else if (type == "Water") {
		return loadWater(fileName);
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
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string type = "N/A";
	type = lua["type"];

	return type;
}

glm::vec3 GameAssetFactory::loadBasePos(sol::state& lua) {
	glm::vec3 pos;

	pos.x = lua["xPos"];
	pos.y = lua["yPos"];
	pos.z = lua["zPos"];

	return pos;
}

glm::vec3 GameAssetFactory::loadBaseRotation(sol::state& lua) {
	glm::vec3 rotation;

	rotation.x = lua["xRotation"];
	rotation.y = lua["yRotation"];
	rotation.z = lua["zRotation"];

	return rotation;
}

float GameAssetFactory::loadBaseAngle(sol::state& lua) {
	float angle = lua["angle"];

	return angle;
}

glm::vec3 GameAssetFactory::loadBaseScale(sol::state& lua) {
	glm::vec3 scale;

	scale.x = lua["xScale"];
	scale.y = lua["yScale"];
	scale.z = lua["zScale"];

	return scale;
}

Item* GameAssetFactory::loadItem(std::string luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string model_path = lua["model_path"];
	float shininess = lua["shininess"];
	float spec_intensity = lua["spec_intensity"];

	Item* item = new Item(model_path, shininess, spec_intensity);

	glm::vec3 pos, rotation, scale;
	float angle;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);

	item->position = pos;
	item->scale = scale;
	item->rotation = rotation;
	item->angle = angle;

	return item;
}

Water* GameAssetFactory::loadWater(std::string luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string filePath = lua["texturePath"];
	Water* water = new Water(filePath);

	glm::vec3 pos, rotation, scale, offMult, intensity;
	float angle;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);

	water->position = pos;
	water->scale = scale;
	water->rotation = rotation;
	water->angle = angle;

	offMult.x = lua["xMult"];
	offMult.y = lua["yMult"];
	offMult.z = lua["zMult"];
	water->setOffsetMult(offMult);

	intensity.x = lua["xIntensity"];
	intensity.y = lua["yIntensity"];
	intensity.z = lua["zIntensity"];
	water->setIntensity(intensity);

	return water;
}
