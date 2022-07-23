#include "GameAssetFactory.hpp"

GameObject* GameAssetFactory::create(const std::string& fileName) {
	if (fileName.length() == 0 || isLuaScript(fileName) == false) {
		assert("Not a valid lua script file!" && 0);
	}

	std::string type = getObjectType(fileName);
	if (type == "Item") {
		return loadItem(fileName);
	} else if (type == "Water") {
		return loadWater(fileName);
	} else if (type == "Player") {
		return load_player(fileName);
	} else if (type == "SimpleTerrainObject") {
		return load_simple_terrain_object(fileName);
	} else if (type == "TerrainObject") {
		return loadTerrainObject(fileName);
	} else if (type == "PhysicsObject") {
		return loadPhysicsObject(fileName);
	} else if (type == "ScriptableObject") {
		return loadScriptableObject(fileName);
	} else if (type == "Skybox") {
		return load_skybox(fileName);
	} else if (type == "Projectile") {
		return loadProjectileObject(fileName);
	} else if (type == "NetworkedItem") {
		return loadNetworkedItem(fileName);
	} else if (type == "NPC") {
		return loadNPCObject(fileName);
	} else if (type == "DirectionalLight") {
		return load_directional_light(fileName);
	} else if (type == "PointLight") {
		return load_point_light(fileName);
	} else if (type == "SpotLight") {
		return load_spot_light(fileName);
	} else {
		assert("Object type not found" && 0);
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

bool GameAssetFactory::loadBaseSavable(sol::state& lua) {
	auto valid = lua["baseObject"]["savable"];
	bool savable = false;
	if (valid.valid()) {
		savable = lua["baseObject"]["savable"];
	}

	return savable;
}

Item* GameAssetFactory::loadItem(const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string model_name = lua["item"]["modelName"];
	std::string material_name = lua["item"]["material_name"];

	Item* item = new Item(model_name, material_name);

	glm::vec3 pos, rotation, scale;
	float angle;
	bool savable;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);
	savable = loadBaseSavable(lua);

	item->position = pos;
	item->scale = scale;
	item->rotation = rotation;
	item->angle = angle;
	item->savable = savable;

	return item;
}

Water* GameAssetFactory::loadWater(const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string filePath = lua["water"]["textureName"];
	Water* water = new Water(filePath);

	glm::vec3 pos, rotation, scale, offMult, intensity;
	float angle;
	bool savable;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);
	savable = loadBaseSavable(lua);

	water->position = pos;
	water->scale = scale;
	water->rotation = rotation;
	water->angle = angle;
	water->savable = savable;

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

Player* GameAssetFactory::load_player(const std::string& lua_script) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(lua_script);

	Player* player = new Player();

	glm::vec3 pos, rotation, scale;
	float angle;
	bool savable;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);
	savable = loadBaseSavable(lua);

	player->position = pos;
	player->scale = scale;
	player->rotation = rotation;
	player->angle = angle;
	player->savable = savable;

	player->initRB(player->position, player->rotation, player->angle);

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
	po->savable = loadBaseSavable(lua);

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

	if (po->getType() != BodyType::STATIC) {
		gameWorld.create_box_obstruction(po->position.x, po->position.z,
		                                 boxV.x * 2, boxV.z * 2);
	}
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
	if (po->getType() != BodyType::STATIC) {
		gameWorld.create_sphere_obstruction(po->position.x, po->position.z,
		                                    radius);
	}
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
	if (po->getType() != BodyType::STATIC) {
		gameWorld.create_sphere_obstruction(po->position.x, po->position.z,
		                                    radius);
	}
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
	po->setVelocity(force);

	torque.x = lua["baseObject"]["xTorque"];
	torque.y = lua["baseObject"]["yTorque"];
	torque.z = lua["baseObject"]["zTorque"];
	po->setAngVelocity(torque);

	float linDamp = lua["baseObject"]["linearDamping"];
	po->addDragForce(linDamp);
	float angDamp = lua["baseObject"]["angularDamping"];
	po->addDragTorque(angDamp);

	int sleep = lua["baseObject"]["sleep"];
	if (sleep == 0) {
		po->setCanSleep(false);
	}
}

ScriptableObject* GameAssetFactory::loadScriptableObject(
    const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	glm::vec3 pos, scale, rotation;
	float angle;
	bool savable;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);
	savable = loadBaseSavable(lua);

	std::string script;
	script = lua["script"];

	ScriptableObject* so = new ScriptableObject(script);

	so->position = pos;
	so->scale = scale;
	so->rotation = rotation;
	so->angle = angle;
	so->savable = savable;

	return so;
}

SimpleTerrainObject* GameAssetFactory::load_simple_terrain_object(
    const std::string& lua_script) {
	auto& lua = LuaManager::get_instance().get_state();
	lua.script_file(lua_script);

	SimpleTerrainObject* simple_terrain_object = new SimpleTerrainObject();

	simple_terrain_object->position = loadBasePos(lua);
	simple_terrain_object->scale = loadBaseScale(lua);
	simple_terrain_object->rotation = loadBaseRotation(lua);
	simple_terrain_object->angle = loadBaseAngle(lua);

	simple_terrain_object->set_heightmap_name(lua["terrain"]["heightmap"]);
	simple_terrain_object->set_texture_name(lua["terrain"]["texture"]);
	simple_terrain_object->set_detailmap_name(lua["terrain"]["detailmap"]);

	simple_terrain_object->init();

	return simple_terrain_object;
}

TerrainObject* GameAssetFactory::loadTerrainObject(
    const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	glm::vec3 pos, scale, rotation;
	float angle;
	bool savable;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);
	savable = loadBaseSavable(lua);

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

	TerrainManager::set_terrain(tt, scale.y, height_size);

	float min = lua["terrain"]["min"];
	float max = lua["terrain"]["max"];
	gameWorld.setMinMaxHeight(min, max);
	gameWorld.setWorld();

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

DirectionalLightObject* GameAssetFactory::load_directional_light(
    const std::string& lua_script) {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(lua_script);

	DirectionalLightData light_data;

	light_data.color.x = lua["light"]["color"]["r"];
	light_data.color.y = lua["light"]["color"]["g"];
	light_data.color.z = lua["light"]["color"]["b"];
	light_data.ambient_intensity = lua["light"]["ambient_intensity"];
	light_data.diffuse_intensity = lua["light"]["diffuse_intensity"];
	light_data.direction.x = lua["light"]["direction"]["x"];
	light_data.direction.y = lua["light"]["direction"]["y"];
	light_data.direction.z = lua["light"]["direction"]["z"];

	DirectionalLightObject* d_light = new DirectionalLightObject(light_data);

	d_light->savable = loadBaseSavable(lua);

	d_light->init();

	return d_light;
}

PointLightObject* GameAssetFactory::load_point_light(
    const std::string& lua_script) {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(lua_script);

	PointLightData light_data;

	light_data.color.x = lua["light"]["color"]["r"];
	light_data.color.y = lua["light"]["color"]["g"];
	light_data.color.z = lua["light"]["color"]["b"];
	light_data.ambient_intensity = lua["light"]["ambient_intensity"];
	light_data.diffuse_intensity = lua["light"]["diffuse_intensity"];
	light_data.position.x = lua["light"]["position"]["x"];
	light_data.position.y = lua["light"]["position"]["y"];
	light_data.position.z = lua["light"]["position"]["z"];
	light_data.constant = lua["light"]["constant"];
	light_data.linear = lua["light"]["linear"];
	light_data.quadratic = lua["light"]["quadratic"];

	PointLightObject* p_light = new PointLightObject(light_data);

	p_light->savable = loadBaseSavable(lua);

	p_light->init();

	return p_light;
}

SpotLightObject* GameAssetFactory::load_spot_light(
    const std::string& lua_script) {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(lua_script);

	SpotLightData light_data;

	light_data.color.x = lua["light"]["color"]["r"];
	light_data.color.y = lua["light"]["color"]["g"];
	light_data.color.z = lua["light"]["color"]["b"];
	light_data.ambient_intensity = lua["light"]["ambient_intensity"];
	light_data.diffuse_intensity = lua["light"]["diffuse_intensity"];
	light_data.position.x = lua["light"]["position"]["x"];
	light_data.position.y = lua["light"]["position"]["y"];
	light_data.position.z = lua["light"]["position"]["z"];
	light_data.constant = lua["light"]["constant"];
	light_data.linear = lua["light"]["linear"];
	light_data.quadratic = lua["light"]["quadratic"];
	light_data.direction.x = lua["light"]["direction"]["x"];
	light_data.direction.y = lua["light"]["direction"]["y"];
	light_data.direction.z = lua["light"]["direction"]["z"];
	light_data.edge = lua["light"]["edge"];

	SpotLightObject* s_light = new SpotLightObject(light_data);

	s_light->savable = loadBaseSavable(lua);

	s_light->init();

	return s_light;
}

Projectile* GameAssetFactory::loadProjectileObject(
    const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	Projectile* proj = new Projectile();

	proj->position = loadBasePos(lua);
	proj->scale = loadBaseScale(lua);
	proj->rotation = loadBaseRotation(lua);
	proj->angle = loadBaseAngle(lua);
	proj->savable = loadBaseSavable(lua);

	std::string model_name = lua["baseObject"]["modelName"];
	std::string material_name = lua["baseObject"]["material_name"];

	proj->initModel(model_name, material_name);
	proj->initRB(proj->position, proj->rotation, proj->angle);

	loadExtraPhysicObjectSettings(proj, lua);

	int size = lua["baseObject"]["numOfColliders"];
	std::string colliderType = "Box";

	for (int count = 1; count <= size; count++) {
		colliderType = lua["collider" + std::to_string(count)]["colliderType"];
		if (colliderType == "Box") {
			loadBoxCollider(count, proj, lua);
		} else if (colliderType == "Sphere") {
			loadSphereCollider(count, proj, lua);
		} else if (colliderType == "Capsule") {
			loadCapsuleCollider(count, proj, lua);
		}
	}

	proj->set_time_alive_left(lua["baseObject"]["timeAliveLeft"]);
	proj->set_damage(lua["baseObject"]["damage"]);
	proj->set_logic_script(lua["baseObject"]["logic"]);
	int tempNum = lua["baseObject"]["floorContact"];
	proj->set_floor_contact(tempNum);
	tempNum = lua["baseObject"]["toDelete"];
	proj->set_to_delete(tempNum);

	return proj;
}

NetworkedItem* GameAssetFactory::loadNetworkedItem(
    const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	std::string model_name = lua["NetworkedItem"]["modelName"];
	std::string material_name = lua["NetworkedItem"]["material_name"];

	NetworkedItem* networkedItem = new NetworkedItem(model_name, material_name);

	glm::vec3 pos, rotation, scale;

	float angle;
	bool savable;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);
	savable = loadBaseSavable(lua);

	networkedItem->position = pos;
	networkedItem->scale = scale;
	networkedItem->rotation = rotation;
	networkedItem->angle = angle;
	networkedItem->savable = savable;

	return networkedItem;
}

NPC* GameAssetFactory::loadNPCObject(const std::string& luaScript) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(luaScript);

	glm::vec3 pos, scale, rotation;

	float angle;
	bool savable;

	pos = loadBasePos(lua);
	scale = loadBaseScale(lua);
	rotation = loadBaseRotation(lua);
	angle = loadBaseAngle(lua);
	savable = loadBaseSavable(lua);

	std::string model = lua["baseObject"]["modelName"];
	std::string mat = lua["baseObject"]["material_name"];
	std::string model_texture = lua["baseObject"]["model_texture"];
	int animate = lua["baseObject"]["animate"];
	int loopAnimation = lua["baseObject"]["loopAnimation"];
	NPC* npc = new NPC(model, model_texture, animate, loopAnimation);
	npc->initModel(model, mat);
	npc->position = pos;
	npc->scale = scale;
	npc->rotation = rotation;
	npc->angle = angle;
	npc->savable = savable;

	npc->initRB(npc->position, npc->rotation, npc->angle);
	loadExtraPhysicObjectSettings(npc, lua);

	int size = lua["baseObject"]["numOfColliders"];
	std::string colliderType = "Box";

	for (int count = 1; count <= size; count++) {
		colliderType = lua["collider" + std::to_string(count)]["colliderType"];
		if (colliderType == "Box") {
			loadBoxCollider(count, npc, lua);
		} else if (colliderType == "Sphere") {
			loadSphereCollider(count, npc, lua);
		} else if (colliderType == "Capsule") {
			loadCapsuleCollider(count, npc, lua);
		}
	}

	int faction = lua["AI"]["faction"];
	float health = lua["AI"]["health"];
	float power = lua["AI"]["power"];

	npc->set_faction(faction);
	npc->set_health(health);
	npc->set_power(power);
	npc->set_move_speed(lua["AI"]["moveSpeed"]);

	// Sets up Finite State Machine
	std::string script = lua["AI"]["setUpFSM"];
	npc->setSetup(script);

	sol::function exe = lua[script];
	exe(npc);

	entityMgr.registerEntity(npc);
	return npc;
}
