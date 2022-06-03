#include "Projectile.hpp"

void Projectile::init() {}

void Projectile::update(double delta_time) {
	sol::state& lua = LuaManager::get_instance().get_state();

	if (position.y - 0.1 <=
	    GenericFunctions::getHeight(position.x, position.z)) {
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
	position = rb.getPosition();
	rotation = rb.getRotation();
	angle = rb.getAngle();
}

void Projectile::add_draw_call() { PhysicsObject::add_draw_call(); }

void Projectile::draw(const Shader& shader) { PhysicsObject::draw(shader); }

void Projectile::save_object() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle + 0.01,
	                             "Projectile");
	ObjectSaving::addComma();
	ObjectSaving::addValue("modelName", model_name_, false);
	ObjectSaving::addValue("material_name", material_name_, false);
	ObjectSaving::addValue("rbType", rb.getRBType(), false);
	ObjectSaving::addValue("gravity", (int)rb.getIfGravityActive(), false);
	ObjectSaving::addValue("xForce", rb.getLinearVelocity().x, false);
	ObjectSaving::addValue("yForce", rb.getLinearVelocity().y, false);
	ObjectSaving::addValue("zForce", rb.getLinearVelocity().z, false);
	ObjectSaving::addValue("xTorque", rb.getAngularVelocity().x, false);
	ObjectSaving::addValue("yTorque", rb.getAngularVelocity().y, false);
	ObjectSaving::addValue("zTorque", rb.getAngularVelocity().z, false);
	ObjectSaving::addValue("linearDamping", rb.getLinearDamping(), false);
	ObjectSaving::addValue("angularDamping", rb.getAngularDamping(), false);
	ObjectSaving::addValue("sleep", (int)rb.getIfAllowedSleep(), false);
	ObjectSaving::addValue("numOfColliders", rb.getNumberOfColliders(), false);
	ObjectSaving::addValue("timeAliveLeft", time_alive_left_, false);
	ObjectSaving::addValue("damage", damage_, false);
	ObjectSaving::addValue("logic", lua_script_, false);
	ObjectSaving::addValue("toDelete", to_be_deleted_, false);
	ObjectSaving::addValue("floorContact", floor_contact_, true);
	ObjectSaving::closeStruct();

	for (int count = 0; count < rb.getNumberOfColliders(); count++) {
		int type = rb.getColliderType(count);
		ObjectSaving::createStruct("collider" + std::to_string(count + 1));
		saveCollider(count, type);
		ObjectSaving::closeStruct();
	}

	ObjectSaving::closeFile();
}

void Projectile::freeze_projectile() {
	rb.setAngularAxisFactor(glm::vec3(0));
	rb.setLinearAxisFactor(glm::vec3(0));
	rb.setLinearVelocity(glm::vec3(0));
	rb.setAngularVelocity(glm::vec3(0));
	position.y = GenericFunctions::getHeight(position.x, position.z) + 0.1;
}

void Projectile::remove_colliders() { rb.removeColliders(); }

void Projectile::set_time_alive_left(float time) { time_alive_left_ = time; }

void Projectile::set_damage(float damage) { damage_ = damage; }

void Projectile::set_logic_script(const std::string& script) {
	lua_script_ = script;
}

void Projectile::set_floor_contact(bool val) { floor_contact_ = val; }

void Projectile::set_to_delete(bool val) { to_be_deleted_ = val; }
