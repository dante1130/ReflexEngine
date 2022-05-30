#include "Player.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "AI/singletons.h"

void Player::init() { position.y = 10.0f; }

void Player::update(double delta_time) {
	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file(lua_script_);

	/*
	position = rb.getPosition();
	position.y = GenericFunctions::getHeight(position.x, position.z) + height_;
	rb.set_position(position);
	*/
	glm::vec3 velocity = rb.getLinearVelocity();
	glm::vec3 newPos = position;
	newPos.x = position.x + velocity.x * delta_time;
	newPos.y = position.y + velocity.z * delta_time;
	newPos.z = position.z + velocity.z * delta_time;

	// position = rb.getPosition();
	newPos.y = GenericFunctions::getHeight(newPos.x, newPos.z) + 1;
	// rb.set_position(glm::vec3(position.x, position.y + 1,
	// position.z));
	rb.set_position(glm::vec3(-999, 9999, position.z));

	bool collides =
	    physicsEntityMgr.collides(position, newPos, m_capsule[0].m_radius);
	if (!collides) {
		position = newPos;
	} else {
		std::cout << "collision" << std::endl;
	}

	auto& camera = ReflexEngine::get_instance().camera_;

	camera.set_position(position);
}

void Player::fixed_update(double delta_time) {
	auto& camera = ReflexEngine::get_instance().camera_;

	glm::vec3 direction = camera.get_move_direction();

	glm::vec3 move = direction * move_speed_;
	rb.setLinearVelocity(move);
}

void Player::set_lua_script(const std::string& script) { lua_script_ = script; }

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
