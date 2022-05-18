#include "GameAssetFactory.hpp"

GameObject* GameAssetFactory::create(const std::string& fileName) {
	if (fileName.length() == 0 || isLuaScript(fileName) == false) {
		return nullptr;
	}

	std::string type = getObjectType(fileName);

	if (type == "Item") {
		return loadItem(fileName);
	} else if (type == "Water") {
		return loadWater(fileName);
	} else if (type == "Player") {
		return load_player(fileName);
	} else if (type == "TerrainObject") {
		return loadTerrainObject(fileName);
	} else if (type == "Body") {
		return loadBody(fileName);
	} else if (type == "PhysicsObject") {
		return loadPhysicsObject(fileName);
	} else if (type == "ScriptableObject") {
		return loadScriptableObject(fileName);
	} else if (type == "Skybox") {
		return load_skybox(fileName);
	} else {
		return nullptr;
	}
}

bool GameAssetFactory::isLuaScript(const std::string& luaScript) {
	int pos = luaScript.find_last_of(".");

	std::string ext = "n/a";
	if (pos != -1 && (luaScript.length() > pos + (int)1)) {
		ext = luaScript.substr(pos + (int)1, luaScript.length());
	}

	return ext == "lua";
}

std::string GameAssetFactory::getObjectType(const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string type = lua["baseObject"]["type"];

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

Item* GameAssetFactory::loadItem(const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string model_name = lua["item"]["modelName"];
	std::string material_name = lua["item"]["material_name"];

	Item* item = new Item(model_name, material_name);

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

Water* GameAssetFactory::loadWater(const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string filePath = lua["water"]["textureName"];
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

	float time = lua["water"]["time"];
	water->setTotalTime(time);

	return water;
}

Body* GameAssetFactory::loadBody(const std::string& luaScript) {
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

Player* GameAssetFactory::load_player(const std::string& lua_script) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(lua_script);

	Player* player = new Player();

	glm::vec3 pos, rotation, scale;
	float angle;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);

	player->position = pos;
	player->scale = scale;
	player->rotation = rotation;
	player->angle = angle;

	player->createBR(player->position, player->rotation, player->angle);

	player->set_move_speed(lua["baseObject"]["move_speed"]);

	std::string collider = "collider1";
	glm::vec3 posV;
	posV.x = lua[collider]["xPos"];
	posV.y = lua[collider]["yPos"];
	posV.z = lua[collider]["zPos"];

	float radius = lua[collider]["radius"];
	float height = lua[collider]["height"];

	player->set_height(height);
	player->set_collider_radius(radius);

	float bounciness = lua[collider]["bounciness"];
	float friction = lua[collider]["friction"];

	player->setType(2);
	player->enableGravity(false);

	player->addCapsuleCollider(posV, radius, height, bounciness, friction);

	std::string script;
	script = lua["script"];
	player->set_lua_script(script);

	player->init();

	return player;
}

PhysicsObject* GameAssetFactory::loadPhysicsObject(
    const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	PhysicsObject* po = new PhysicsObject();

	glm::vec3 offMult, intensity;

	po->position = loadBasePos(lua);
	po->scale = loadBaseScale(lua);
	po->rotation = loadBaseRotation(lua);
	po->angle = loadBaseAngle(lua);

	std::string model_name = lua["baseObject"]["modelName"];
	std::string material_name = lua["baseObject"]["material_name"];

	po->initModel(model_name, material_name);
	po->initRB(po->position, po->rotation, po->angle);
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
    const std::string& luaScript) {
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

TerrainObject* GameAssetFactory::loadTerrainObject(
    const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	glm::vec3 pos, scale, rotation;
	float angle;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);

	std::string height_map = lua["terrain"]["heightMap"];

	TexturedTerrain* tt = new TexturedTerrain();
	tt->load_heightfield(height_map.c_str());

	TerrainObject* to = new TerrainObject();
	to->scale = scale;

	float height_size = lua["terrain"]["heightSize"];
	int make_island = lua["terrain"]["island"];

	to->add_texture(lua["terrain"]["text1"]);
	to->add_texture(lua["terrain"]["text2"]);
	to->add_texture(lua["terrain"]["text3"]);
	to->add_texture(lua["terrain"]["text4"]);
	to->add_detail_map(lua["terrain"]["detailMap"]);

	if (make_island == 1) {
		to->add_height_map(tt->get_height_map(), height_size, height_size,
		                   true);
	} else {
		to->add_height_map(tt->get_height_map(), height_size, height_size,
		                   false);
	}

	to->create_terrain(lua["terrain"]["chunkSize"],
	                   lua["terrain"]["chunkDetail"], lua["terrain"]["n"],
	                   height_size, glm::vec3(1.0f, scale.y, 1.0f));

	to->add_storage_text(lua["terrain"]["text1"], 0);
	to->add_storage_text(lua["terrain"]["text2"], 1);
	to->add_storage_text(lua["terrain"]["text3"], 2);
	to->add_storage_text(lua["terrain"]["text4"], 3);
	to->add_storage_text(lua["terrain"]["heightMap"], 4);
	to->add_storage_text(lua["terrain"]["detailMap"], 5);

	GenericFunctions::setPlayableArea(to->get_height_map(), tt, scale.y,
	                                  height_size);
	gameWorld.setWorld(tt);
	return to;
}

SkyboxObject* GameAssetFactory::load_skybox(const std::string& lua_script) {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(lua_script);

	SkyboxObject* skybox = new SkyboxObject();

	skybox->set_face(SkyboxFaces::RIGHT, lua["skybox_faces"]["right_face"]);
	skybox->set_face(SkyboxFaces::LEFT, lua["skybox_faces"]["left_face"]);
	skybox->set_face(SkyboxFaces::TOP, lua["skybox_faces"]["top_face"]);
	skybox->set_face(SkyboxFaces::BOTTOM, lua["skybox_faces"]["bottom_face"]);
	skybox->set_face(SkyboxFaces::BACK, lua["skybox_faces"]["back_face"]);
	skybox->set_face(SkyboxFaces::FRONT, lua["skybox_faces"]["front_face"]);

	skybox->init();

	return skybox;
}
