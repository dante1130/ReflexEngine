#include "luaAccessScriptedFSM.hpp"

#include "sol/sol.hpp"
#include "AI/NPC.hpp"
#include "AI/stateMachine.h"
#include "AI/messageDispatcher.h"
#include "AI/telegram.h"
#include "Model/ModelData.hpp"
#include "AI/vector2D.hpp"
#include "AI/singletons.h"
#include "View/Renderer/OpenGL/Objects/Md2.hpp"

void luaAccessScriptedFSM::registerAllAI() {
	registerScriptedStateMachine();
	registerGameObject();
	registerPlayer();
	registerVector2D();
	registerMessage();
	registerWorld();
	registerTelegram();
	registerAnimation::registerModelData();
}

void luaAccessScriptedFSM::registerScriptedStateMachine() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::usertype<stateMachine<NPC>> player_type =
	    lua.new_usertype<stateMachine<NPC>>("stateMachine");

	// State variables
	player_type["getPreviousState"] = &stateMachine<NPC>::getPreviousState;
	player_type["setPreviousState"] = &stateMachine<NPC>::setPreviousState;

	player_type["getCurrentState"] = &stateMachine<NPC>::getCurrentState;
	player_type["setCurrentState"] = &stateMachine<NPC>::setCurrentState;

	player_type["getGlobalState"] = &stateMachine<NPC>::getGlobalState;
	player_type["setGlobalState"] = &stateMachine<NPC>::setGlobalState;

	// Functions
	player_type["changeState"] = &stateMachine<NPC>::changeState;
	player_type["revertStateBack"] = &stateMachine<NPC>::revertToPreviousState;
}

void luaAccessScriptedFSM::registerGameObject() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::usertype<entityManager> player_type =
	    lua.new_usertype<entityManager>("entityManager");

	// player_type["getEntity"] = &entityManager::getEntityFromID;
	player_type.set_function("getEntity", &entityManager::getEntityFromID,
	                         entityMgr);
}

void luaAccessScriptedFSM::registerPlayer() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::usertype<NPC> player_type = lua.new_usertype<NPC>("player");

	// Variables
	player_type["id"] = sol::property(&NPC::get_id, &NPC::set_id);
	player_type["health"] = sol::property(&NPC::get_health, &NPC::set_health);
	player_type["power"] = sol::property(&NPC::get_power, &NPC::set_power);
	player_type["dead"] = sol::property(&NPC::is_dead, &NPC::kill_npc);
	player_type["target_id"] =
	    sol::property(&NPC::get_target_id, &NPC::set_target_id);
	player_type["moveSpeed"] =
	    sol::property(&NPC::get_move_speed, &NPC::set_move_speed);

	player_type["set_target_position"] = &NPC::set_enemy_target;
	player_type["get_target_position"] = &NPC::get_enemy_target;
	player_type["faction"] =
	    sol::property(&NPC::get_faction, &NPC::set_faction);

	player_type["setPos"] = &NPC::set_pos;
	player_type["getX"] = &NPC::get_pos_x;
	player_type["getY"] = &NPC::get_pos_y;
	player_type["getZ"] = &NPC::get_pos_z;

	// Waypoints setting & getting
	player_type["numberOfWaypoints"] = &NPC::get_waypoint_count;
	player_type["add_waypoint"] =
	    sol::overload(&NPC::add_waypoint, &NPC::add_waypointGLM);
	player_type["add_waypoints"] = &NPC::add_waypoints;
	player_type["remove_waypoints"] = &NPC::remove_waypoints;

	// FSM & states
	player_type["newState"] = &NPC::new_state;
	player_type["getFSM"] = &NPC::get_FSM;

	// Processing
	player_type["followWaypoint"] = &NPC::waypoint_follow;
	player_type["moveNPC"] = &NPC::move_NPC;
	player_type["watchForEnemy"] =
	    sol::overload(&NPC::watch_for_enemy, &NPC::watch_for_enemyVal);
	player_type["moveToEnemy"] = &NPC::move_to_enemy;
	player_type["pathfindToPoint"] = &NPC::use_pathfinding;

	player_type["sendMessage"] = &NPC::send_message;
	player_type["sendGroupMessage"] = &NPC::send_group_message;

	player_type["stopMovement"] = &NPC::freezeNPC;

	player_type["getAnimation"] = &NPC::get_animation;
}

void luaAccessScriptedFSM::registerVector2D() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::usertype<vector2D> player_type =
	    lua.new_usertype<vector2D>("vector2D");
	player_type["set"] = &vector2D::set;
	player_type["x"] = sol::property(&vector2D::getX, &vector2D::setX);
	player_type["y"] = sol::property(&vector2D::getY, &vector2D::setY);

	player_type["normalise"] = &vector2D::normalise;
	player_type["length"] = &vector2D::length;
}

void luaAccessScriptedFSM::registerMessage() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::usertype<messageDispatcher> player_type =
	    lua.new_usertype<messageDispatcher>("messageDispatcher");

	player_type["dispatchMsg"] = &messageDispatcher::dispatchMsg;
}

void luaAccessScriptedFSM::registerWorld() {}

void luaAccessScriptedFSM::registerTelegram() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::usertype<telegram> player_type =
	    lua.new_usertype<telegram>("telegram");

	player_type["sender"] = &telegram::sender;
	player_type["reciever"] = &telegram::receiver;
	player_type["msg"] = &telegram::msg;
	player_type["disptachTime"] = &telegram::dispatchTime;
	player_type["extraInfo"] = &telegram::extraInfo;
}

void registerAnimation::registerModelData() {
	sol::state& lua = LuaManager::get_instance().get_state();

	sol::usertype<ModelData> player_type =
	    lua.new_usertype<ModelData>("animation");

	player_type["isRunning"] = &ModelData::get_is_running;
	player_type["setFPS"] = &ModelData::set_fps;
	player_type["setAnimation"] = &ModelData::set_animation;
	player_type["shouldLoop"] = &ModelData::set_loop;
	player_type["shouldAnimate"] = &ModelData::set_is_animated;

	lua.new_enum("animation_types", "run", md2::animation_type::CROUCH_STAND,
	             "attack", md2::animation_type::FALLBACK, "stand",
	             md2::animation_type::STAND, "death",
	             md2::animation_type::DEATH_FALLBACK, "pain",
	             md2::animation_type::PAIN_A);
}
