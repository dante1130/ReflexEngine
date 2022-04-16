#include "GameAssetFactory.hpp"

GameObject* GameAssetFactory::create(std::string fileName) {
	if (fileName.length() == 0 || isLuaScript(fileName) == false) {
		return NULL;
	}

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
	} else if (type == "Body") {
		return loadBody(fileName);
	} else if (type == "PhysicsObject") {
		return loadPhysicsObject(fileName);
	} else if (type == "ScriptableObject") {
		return loadScriptableObject(fileName);
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
	type = lua["baseObject"]["type"];

	return type;
}

glm::vec3 GameAssetFactory::loadBasePos(sol::state& lua) {
	glm::vec3 pos;

	pos.x = lua["baseObject"]["xPos"];
	pos.y = lua["baseObject"]["yPos"];
	pos.z = lua["baseObject"]["zPos"];

	return pos;
}

glm::vec3 GameAssetFactory::loadBaseRotation(sol::state& lua) {
	glm::vec3 rotation;

	rotation.x = lua["baseObject"]["xRotation"];
	rotation.y = lua["baseObject"]["yRotation"];
	rotation.z = lua["baseObject"]["zRotation"];

	return rotation;
}

float GameAssetFactory::loadBaseAngle(sol::state& lua) {
	float angle = lua["baseObject"]["angle"];

	return angle;
}

glm::vec3 GameAssetFactory::loadBaseScale(sol::state& lua) {
	glm::vec3 scale;

	scale.x = lua["baseObject"]["xScale"];
	scale.y = lua["baseObject"]["yScale"];
	scale.z = lua["baseObject"]["zScale"];

	return scale;
}

Item* GameAssetFactory::loadItem(std::string luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string model_path = lua["item"]["model_path"];
	float shininess = lua["item"]["shininess"];
	float spec_intensity = lua["item"]["spec_intensity"];

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

	std::string filePath = lua["water"]["texturePath"];
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

	offMult.x = lua["water"]["xMult"];
	offMult.y = lua["water"]["yMult"];
	offMult.z = lua["water"]["zMult"];
	water->setOffsetMult(offMult);

	intensity.x = lua["water"]["xIntensity"];
	intensity.y = lua["water"]["yIntensity"];
	intensity.z = lua["water"]["zIntensity"];
	water->setIntensity(intensity);

	return water;
}

Body* GameAssetFactory::loadBody(std::string luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	Body* body = new Body();

	int val = lua["baseObject"]["creator"];
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

	glm::vec3 offMult, intensity;

	po->position = loadBasePos(lua);
	po->scale = loadBaseScale(lua);
	po->rotation = loadBaseRotation(lua);
	po->angle = loadBaseAngle(lua);

	std::string model_path = lua["baseObject"]["model_path"];
	float shininess = lua["baseObject"]["shininess"];
	float spec_intensity = lua["baseObject"]["spec_intensity"];

	po->initModel(model_path, shininess, spec_intensity);
	po->initRB(po->position, po->rotation, po->angle);
	po->addSphereCollider(glm::vec3(0, 0, 0), 2, 0.5, 0.5);
	loadExtraPhysicObjectSettings(po, lua);

	int size = lua["baseObject"]["numOfColliders"];
	std::string colliderType = "Box";

	for (int count = 1; count <= size; count++) {
		colliderType = lua["collider" + std::to_string(count)]["colliderType"];
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
	std::string collider = "collider" + std::to_string(count);
	glm::vec3 posV;
	posV.x = lua[collider]["xPos"];
	posV.y = lua[collider]["yPos"];
	posV.z = lua[collider]["zPos"];

	glm::vec3 boxV;
	boxV.x = lua[collider]["xBox"];
	boxV.y = lua[collider]["yBox"];
	boxV.z = lua[collider]["zBox"];

	float bounciness = lua[collider]["bounciness"];
	float friction = lua[collider]["friction"];

	po->addBoxCollider(posV, boxV, bounciness, friction);
}

void GameAssetFactory::loadSphereCollider(int count, PhysicsObject* po,
                                          sol::state& lua) {
	std::string collider = "collider" + std::to_string(count);
	glm::vec3 posV;
	posV.x = lua[collider]["xPos"];
	posV.y = lua[collider]["yPos"];
	posV.z = lua[collider]["zPos"];

	float radius = lua[collider]["radius"];

	float bounciness = lua[collider]["bounciness"];
	float friction = lua[collider]["friction"];

	po->addSphereCollider(posV, radius, bounciness, friction);
}

void GameAssetFactory::loadCapsuleCollider(int count, PhysicsObject* po,
                                           sol::state& lua) {
	std::string collider = "collider" + std::to_string(count);
	glm::vec3 posV;
	posV.x = lua[collider]["xPos"];
	posV.y = lua[collider]["yPos"];
	posV.z = lua[collider]["zPos"];

	float radius = lua[collider]["radius"];
	float height = lua[collider]["height"];

	float bounciness = lua[collider]["bounciness"];
	float friction = lua[collider]["friction"];

	po->addCapsuleCollider(posV, radius, height, bounciness, friction);
}

void GameAssetFactory::loadExtraPhysicObjectSettings(PhysicsObject* po,
                                                     sol::state& lua) {
	int type = lua["baseObject"]["rbType"];
	po->setType(type);
	int grav = lua["baseObject"]["gravity"];
	if (grav == 0) {
		po->enableGravity(false);
	}

	glm::vec3 force, torque;
	force.x = lua["baseObject"]["xForce"];
	force.y = lua["baseObject"]["yForce"];
	force.z = lua["baseObject"]["zForce"];
	po->setLinearVelocity(force);

	torque.x = lua["baseObject"]["xTorque"];
	torque.y = lua["baseObject"]["yTorque"];
	torque.z = lua["baseObject"]["zTorque"];
	po->setAngularVelocity(torque);

	float linDamp = lua["baseObject"]["linearDamping"];
	po->setLinearVelocityDamping(linDamp);
	float angDamp = lua["baseObject"]["angularDamping"];
	po->setAngularVelocityDamping(angDamp);

	int sleep = lua["baseObject"]["sleep"];
	if (sleep == 0) {
		po->setIfBodyCanSleep(false);
	}
}

ScriptableObject* GameAssetFactory::loadScriptableObject(
    std::string luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	glm::vec3 pos, scale, rotation;
	float angle;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);

	std::string script;
	script = lua["script"];

	ScriptableObject* so = new ScriptableObject(script);

	so->position = pos;
	so->scale = scale;
	so->rotation = rotation;
	so->angle = angle;

	return so;
}
