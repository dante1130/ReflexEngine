#include "Projectile.hpp"
#include "Controller/Terrain/TerrainManager.hpp"

void Projectile::init() {}

void Projectile::update(double delta_time) {
	sol::state& lua = LuaManager::get_instance().get_state();

	if (position.y - 0.1 <= TerrainManager::getHeight(position.x, position.z)) {
		floor_contact_ = true;
	}

	lua["remove_obj"] = remove;
	lua["to_be_deleted"] = to_be_deleted_;
	lua["floor_contact"] = floor_contact_;
	lua["time_alive_left"] = time_alive_left_;
	lua["damage"] = damage_;
	lua["delta_time"] = delta_time;
	lua["collision"] = collision_detected_;
	lua["xPos"] = position.x;
	lua["zPos"] = position.z;

	lua.set_function("remove_colliders", &Projectile::remove_colliders, this);
	lua.set_function("freeze_projectile", &Projectile::freeze_projectile, this);

	lua.script_file(lua_script_);

	remove = lua["remove_obj"];
	to_be_deleted_ = lua["to_be_deleted"];
	time_alive_left_ = lua["time_alive_left"];
	damage_ = lua["damage"];
	position.x = lua["xPos"];
	position.z = lua["zPos"];
}

void Projectile::fixed_update(double delta_time) {
	position = rb->getPosition();
	rotation = rb->getRotation();
	angle = rb->getAngle();
}

void Projectile::add_draw_call() { PhysicsObject::add_draw_call(); }

void Projectile::draw(const Shader& shader) { PhysicsObject::draw(shader); }

void Projectile::save_object() {
	glm::vec3 temp_velocity = rb->getVelocity();
	glm::vec3 temp_ang_velocity = rb->getAngVelocity();
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle + 0.01,
	                             "Projectile");
	ObjectSaving::addComma();
	ObjectSaving::addValue("modelName", model_name_, false);
	ObjectSaving::addValue("material_name", material_name_, false);
	ObjectSaving::addValue("rbType", (int)rb->getType(), false);
	ObjectSaving::addValue("gravity", (int)rb->getIsGravityEnabled(), false);
	ObjectSaving::addValue("xForce", temp_velocity.x, false);
	ObjectSaving::addValue("yForce", temp_velocity.y, false);
	ObjectSaving::addValue("zForce", temp_velocity.z, false);
	ObjectSaving::addValue("xTorque", temp_ang_velocity.x, false);
	ObjectSaving::addValue("yTorque", temp_ang_velocity.y, false);
	ObjectSaving::addValue("zTorque", temp_ang_velocity.z, false);
	ObjectSaving::addValue("linearDamping", rb->getDragForce(), false);
	ObjectSaving::addValue("angularDamping", rb->getDragTorque(), false);
	ObjectSaving::addValue("sleep", (int)rb->getCanSleep(), false);
	ObjectSaving::addValue("numOfColliders", rb->colliderSize(), false);
	ObjectSaving::addValue("timeAliveLeft", time_alive_left_, false);
	ObjectSaving::addValue("damage", damage_, false);
	ObjectSaving::addValue("logic", lua_script_, false);
	ObjectSaving::addValue("toDelete", to_be_deleted_, false);
	ObjectSaving::addValue("floorContact", floor_contact_, true);
	ObjectSaving::closeStruct();

	for (int count = 0; count < rb->colliderSize(); count++) {
		int type = rb->getColliderType(count);
		ObjectSaving::createStruct("collider" + std::to_string(count + 1));
		saveCollider(count, type);
		ObjectSaving::closeStruct();
	}

	ObjectSaving::closeFile();
}

void Projectile::freeze_projectile() {

	rb->setVelocity(glm::vec3(0));
	rb->setAngVelocity(glm::vec3(0));
	rb->setType(BodyType::STATIC);
	position.y = TerrainManager::getHeight(position.x, position.z) + 0.1;
}

void Projectile::remove_colliders() { rb->removeAllColliders(); }

void Projectile::set_time_alive_left(float time) { time_alive_left_ = time; }

void Projectile::set_damage(float damage) { damage_ = damage; }

void Projectile::set_logic_script(const std::string& script) {
	lua_script_ = script;
}

void Projectile::set_floor_contact(bool val) { floor_contact_ = val; }

void Projectile::set_to_delete(bool val) { to_be_deleted_ = val; }
