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
	} else if (type == "Body") {
		return loadBody(fileName);
	} else if (type == "PhysicsObject") {
		return loadPhysicsObject(fileName);
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

Body* GameAssetFactory::loadBody(std::string luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	Body* body = new Body();

	int val = lua["creator"];
	if (val == 0) {
		body->setCreator(false);
	}

	body->init();

	return body;
}

PhysicsObject* GameAssetFactory::loadPhysicsObject(std::string luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	PhysicsObject* po = new PhysicsObject();

	glm::vec3 pos, rotation, scale, offMult, intensity;
	float angle;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);

	po->position = pos;
	po->scale = scale;
	po->rotation = rotation;
	po->angle = angle;

	std::string model_path = lua["model_path"];
	float shininess = lua["shininess"];
	float spec_intensity = lua["spec_intensity"];

	po->initModel(model_path, shininess, spec_intensity);
	po->initRB(pos, rotation, angle);
	po->addSphereCollider(glm::vec3(0, 0, 0), 2, 0.5, 0.5);

	loadExtraPhysicObjectSettings(po, lua);

	int size = lua["numOfColliders"];
	std::string colliderType = "Box";

	for (int count = 1; count <= size; count++) {
		colliderType = lua["colliderType" + std::to_string(count)];

		if (colliderType == "Box") {
			loadBoxCollider(count, po, lua);
		} else if (colliderType == "Sphere") {
			loadSphereCollider(count, po, lua);
		} else if (colliderType == "Capsule") {
			loadCapsuleCollider(count, po, lua);
		}
	}

	return po;
}

void GameAssetFactory::loadBoxCollider(int count, PhysicsObject* po,
                                       sol::state& lua) {
	std::string pos = "Pos" + std::to_string(count);
	glm::vec3 posV;
	posV.x = lua['x' + pos];
	posV.y = lua['y' + pos];
	posV.z = lua['z' + pos];

	std::string box = "Box" + std::to_string(count);
	glm::vec3 boxV;
	boxV.x = lua['x' + box];
	boxV.y = lua['y' + box];
	boxV.z = lua['z' + box];

	float bounciness = lua["bounciness" + std::to_string(count)];
	float friction = lua["friction" + std::to_string(count)];

	po->addBoxCollider(posV, boxV, bounciness, friction);
}

void GameAssetFactory::loadSphereCollider(int count, PhysicsObject* po,
                                          sol::state& lua) {
	std::string pos = "Pos" + std::to_string(count);
	glm::vec3 posV;
	posV.x = lua['x' + pos];
	posV.y = lua['y' + pos];
	posV.z = lua['z' + pos];

	float radius = lua["radius" + std::to_string(count)];

	float bounciness = lua["bounciness" + std::to_string(count)];
	float friction = lua["friction" + std::to_string(count)];

	po->addSphereCollider(posV, radius, bounciness, friction);
}

void GameAssetFactory::loadCapsuleCollider(int count, PhysicsObject* po,
                                           sol::state& lua) {
	std::string pos = "Pos" + std::to_string(count);
	glm::vec3 posV;
	posV.x = lua['x' + pos];
	posV.y = lua['y' + pos];
	posV.z = lua['z' + pos];

	float radius = lua["radius" + std::to_string(count)];
	float height = lua["height" + std::to_string(count)];

	float bounciness = lua["bounciness" + std::to_string(count)];
	float friction = lua["friction" + std::to_string(count)];

	po->addCapsuleCollider(posV, radius, height, bounciness, friction);
}

void GameAssetFactory::loadExtraPhysicObjectSettings(PhysicsObject* po,
                                                     sol::state& lua) {
	int type = lua["rbType"];
	po->setType(type);
	int grav = lua["gravity"];
	if (grav == 0) {
		po->enableGravity(false);
	}

	glm::vec3 force, torque;
	force.x = lua["xForce"];
	force.y = lua["yForce"];
	force.z = lua["zForce"];
	po->setLinearVelocity(force);

	torque.x = lua["xTorque"];
	torque.y = lua["yTorque"];
	torque.z = lua["zTorque"];
	po->setAngularVelocity(torque);

	float linDamp = lua["linearDamping"];
	po->setLinearVelocityDamping(linDamp);
	float angDamp = lua["angularDamping"];
	po->setAngularVelocityDamping(angDamp);

	int sleep = lua["sleep"];
	if (sleep == 0) {
		po->setIfBodyCanSleep(false);
	}
}
