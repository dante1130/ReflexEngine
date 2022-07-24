#include "Player.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Model/singletons.h"

void Player::init() { position.y = 10.0f; }

void Player::update(double delta_time) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(lua_script_);

	position = pb->getPosition();
	position.y = OldTerrainManager::getHeight(position.x, position.z) + height_;
	pb->setPosition(position);

	auto& camera = ReflexEngine::get_instance().camera_;

	camera.set_position(position);
}

void Player::fixed_update(double delta_time) {
	auto& camera = ReflexEngine::get_instance().camera_;

	glm::vec3 direction = camera.get_move_direction();

	glm::vec3 move = direction * move_speed_;

	pb->setVelocity(move);
}

void Player::set_lua_script(const std::string& script) { lua_script_ = script; }

void Player::save_object() {
	if (savable) {
		glm::vec3 pos = pb->getColliderPosition(0, Apply::LOCAL);

		ObjectSaving::openFile();
		ObjectSaving::saveGameObject(position, rotation, scale, angle, "Player",
		                             savable);
		ObjectSaving::addComma();
		ObjectSaving::addValue("move_speed", move_speed_, true);
		ObjectSaving::closeStruct();
		ObjectSaving::addValue("script", lua_script_, true);
		ObjectSaving::createStruct("collider1");
		ObjectSaving::addValue("colliderType", "Capsule", false);
		ObjectSaving::addValue("xPos", pos.x, false);
		ObjectSaving::addValue("yPos", pos.y, false);
		ObjectSaving::addValue("zPos", pos.z, false);
		ObjectSaving::addValue("height", height_, false);
		ObjectSaving::addValue("radius", collider_radius_, false);
		ObjectSaving::addValue("bounciness", pb->getColliderBounce(0), false);
		ObjectSaving::addValue("friction", pb->getColliderFriction(0), true);
		ObjectSaving::closeStruct();
		ObjectSaving::closeFile();
	}
}

void Player::set_move_speed(float speed) { move_speed_ = speed; }

void Player::set_height(float height) { height_ = height; }

void Player::set_collider_radius(float radius) { collider_radius_ = radius; }
