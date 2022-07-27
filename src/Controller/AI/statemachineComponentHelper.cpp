#include "statemachineComponentHelper.hpp"

#include <Controller/LuaManager.hpp>

#include "Model/Components/Statemachine.hpp"
#include "Model/Components/Transform.hpp"

#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/AI/telegram.h"
#include "Controller/ReflexEngine/EngineTime.hpp"

void statemachineComponentHelper::change_state(ECS& ecs, Reflex::Entity& entity,
                                               std::string new_state) {
	auto& lua = LuaManager::get_instance().get_state();
	sol::function exe;

	Component::Statemachine& stateMachine =
	    entity.get_component<Component::Statemachine>();
	stateMachine.previous_state = stateMachine.current_state;
	stateMachine.current_state = new_state;

	exe = lua[stateMachine.previous_state]["exit"];
	exe(ecs, entity);

	exe = lua[stateMachine.current_state]["enter"];
	exe(ecs, entity);
}

void statemachineComponentHelper::send_message(ECS& ecs, Reflex::Entity& entity,
                                               int reciever, int msg,
                                               sol::table extraInfo) {
	auto view = ecs.get_registry().view<Component::Statemachine>();

	for (auto entityTwo : view) {
		Component::Statemachine& statemachine =
		    view.get<Component::Statemachine>(entityTwo);

		if (statemachine.unique_statemachine_identifier != reciever) {
			continue;
		}

		auto& lua = LuaManager::get_instance().get_state();
		sol::function exe;

		telegram message(0,
		                 entity.get_component<Component::Statemachine>()
		                     .unique_statemachine_identifier,
		                 reciever, msg, extraInfo);
		statemachine.current_state;

		exe = lua[statemachine.current_state]["onMessage"];
		exe(ecs, statemachine.entity, message);

		break;
	}
}

void statemachineComponentHelper::send_area_message(ECS& ecs,
                                                    Reflex::Entity& entity,
                                                    float range, int msg,
                                                    sol::table extraInfo) {
	auto view = ecs.get_registry()
	                .view<Component::Statemachine, Component::Transform>();

	Component::Transform& transSender =
	    entity.get_component<Component::Transform>();
	Component::Statemachine& statemachineSender =
	    entity.get_component<Component::Statemachine>();

	for (auto entityTwo : view) {
		Component::Transform transTarget =
		    view.get<Component::Transform>(entityTwo);

		float distance =
		    glm::length(transTarget.position - transSender.position);

		// Needs to be in range
		if (distance > range) {
			continue;
		}

		Component::Statemachine& statemachine =
		    view.get<Component::Statemachine>(entityTwo);

		// So doesn't send message to itself
		if (statemachineSender.unique_statemachine_identifier ==
		    statemachine.unique_statemachine_identifier) {
			continue;
		}

		// Sends the message
		auto& lua = LuaManager::get_instance().get_state();
		sol::function exe;

		telegram message(0,
		                 entity.get_component<Component::Statemachine>()
		                     .unique_statemachine_identifier,
		                 statemachine.unique_statemachine_identifier, msg,
		                 extraInfo);
		statemachine.current_state;

		exe = lua[statemachine.current_state]["onMessage"];
		exe(ecs, statemachine.entity, message);
	}
}

void statemachineComponentHelper::look_for_enemy(ECS& ecs,
                                                 Reflex::Entity& entity,
                                                 float arc, float distance) {}

void statemachineComponentHelper::generate_waypoints(Reflex::Entity& entity,
                                                     glm::vec3 currentPos,
                                                     glm::vec3 targetPos) {}

void statemachineComponentHelper::follow_waypoint(Reflex::Entity& entity,
                                                  glm::vec3 targetPos,
                                                  float speed,
                                                  std::string terrain_name) {
	Component::Transform& trans = entity.get_component<Component::Transform>();
	glm::vec3 currentPos = trans.position;

	glm::vec3 directionalVector = targetPos - currentPos;
	float directionalMagnitude = glm::length(directionalVector);

	float movement = (speed * EngineTime::get_delta_time());
	if (directionalMagnitude < movement) {
		trans.position = targetPos;
	} else {
		trans.position = trans.position +
		                 (directionalVector / directionalMagnitude) * movement;
	}

	if (!terrain_name.empty()) {
		trans.position.y =
		    ResourceManager::get_instance()
		        .get_terrain_manager()
		        .get_terrain(terrain_name)
		        .get_height_world(trans.position.x, trans.position.z);
	}
}

void statemachineComponentHelper::follow_waypoint_physics(
    Reflex::Entity& entity, glm::vec3 targetPos, float speed) {
	// Needs to be implemented when physics is implemented
}
