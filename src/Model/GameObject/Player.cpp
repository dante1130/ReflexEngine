#include "Player.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

void Player::update(float delta_time) {
	auto& camera = ReflexEngine::get_instance().camera_;
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.script_file(lua_script_);

	glm::vec3 direction = camera.get_move_direction();

	glm::vec3 move = direction * move_speed_;
	rb.setLinearVelocity(move);

	position = rb.getPosition();
	camera.set_position(position);
}

void Player::set_lua_script(std::string script) { lua_script_ = script; }

void Player::save_object() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle, "Player");
	ObjectSaving::addComma();
	ObjectSaving::addValue("move_speed", move_speed_, true);
	ObjectSaving::closeStruct();
	ObjectSaving::addValue("script", lua_script_, true);
	ObjectSaving::createStruct("collider1");
	ObjectSaving::addValue("colliderType", "Capsule", false);
	ObjectSaving::addValue("xPos", rb.getLocalColliderPos(0).x, false);
	ObjectSaving::addValue("yPos", rb.getLocalColliderPos(0).y, false);
	ObjectSaving::addValue("zPos", rb.getLocalColliderPos(0).z, false);
	ObjectSaving::addValue("height", height_, false);
	ObjectSaving::addValue("radius", collider_radius_, false);
	ObjectSaving::addValue("bounciness", rb.getBounciness(0), false);
	ObjectSaving::addValue("friction", rb.getFriction(0), true);
	ObjectSaving::closeStruct();
	ObjectSaving::closeFile();
}

void Player::set_move_speed(float speed) { move_speed_ = speed; }

void Player::set_height(float height) { height_ = height; }

void Player::set_collider_radius(float radius) { collider_radius_ = radius; }