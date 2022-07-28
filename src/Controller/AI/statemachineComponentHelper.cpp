#include "statemachineComponentHelper.hpp"

#include <Controller/LuaManager.hpp>

#include "Model/Components/Statemachine.hpp"
#include "Model/Components/Transform.hpp"
#include "Model/Components/Terrain.hpp"
#include "Model/singletons.h"

#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/AI/telegram.h"
#include "Controller/ReflexEngine/EngineTime.hpp"

#include <math.h>

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
                                                 float arc, float distance) {
	auto& registry = ecs.get_registry();

	auto view = registry.view<Component::Statemachine, Component::Transform>();

	Component::Statemachine& own_statemachine =
	    entity.get_component<Component::Statemachine>();
	glm::vec3 own_pos = entity.get_component<Component::Transform>().position;
	glm::vec3 look_at;

	look_at = entity.get_component<Component::Transform>().rotation *
	          glm::vec3(0, 0, -1);

	glm::vec3 target_pos;
	float arc_angle = 0;
	int target_id = 0;

	std::vector<int> possible_enemy_ids;

	for (auto& entityTwo : view) {
		target_pos = view.get<Component::Transform>(entityTwo).position;

		if (glm::length(target_pos - own_pos) > distance) {
			continue;
		}

		target_pos = target_pos - own_pos;
		// dot product / (mag of both)
		arc_angle = (look_at.x * target_pos.x + look_at.z * target_pos.z) /
		            (glm::length(glm::vec2(look_at.x, look_at.z)) *
		             glm::length(glm::vec2(target_pos.x, target_pos.z)));
		arc_angle = acos(arc_angle) * (180 / 3.141);
		if (arc_angle > (arc / 2)) {
			continue;
		}

		target_id = view.get<Component::Statemachine>(entityTwo)
		                .unique_statemachine_identifier;

		if (target_id == own_statemachine.unique_statemachine_identifier) {
			continue;
		}

		possible_enemy_ids.push_back(target_id);
	}

	own_statemachine.lua_variables["possible_enemy_ids"] = possible_enemy_ids;
	own_statemachine.lua_variables["number_of_enemy_ids"] =
	    possible_enemy_ids.size();
}

void statemachineComponentHelper::generate_waypoints(
    ECS& ecs, Reflex::Entity& entity, glm::vec3 currentPos, glm::vec3 targetPos,
    std::string terrain_to_pathfind) {
	/*
	glm::vec2 start = glm::vec2(currentPos.x, currentPos.z);
	glm::vec2 end = glm::vec2(targetPos.x, targetPos.z);

	// Convert points to be in relation to terrain
	auto& view =
	    ecs.get_registry().view<Component::Transform, Component::Terrain>();
	Component::Terrain terrain_component;
	bool found = false;
	Component::Transform& transform_component =
	    entity.get_component<Component::Transform>();

	for (auto& entityTwo : view) {
	    terrain_component = view.get<Component::Terrain>(entityTwo);

	    if (terrain_to_pathfind._Equal(terrain_component.terrain_name)) {
	        found = true;
	        transform_component = view.get<Component::Transform>(entityTwo);
	        break;
	    }
	}

	if (!found) {
	    return;
	}

	TexturedTerrain& tt =
	    ResourceManager::get_instance().get_terrain_manager().get_terrain(
	        terrain_to_pathfind);

	glm::vec3 terrain_offset = transform_component.position;
	terrain_offset.x = terrain_offset.x - (tt.get_length() / 2 - 1);
	terrain_offset.z = terrain_offset.z - (tt.get_length() / 2 - 1);

	// terrain_offset.x = terrain_offset.x * transform_component.scale.x;
	// terrain_offset.z = terrain_offset.z * transform_component.scale.z;

	std::cout << terrain_offset.x << " : " << terrain_offset.y << " : "
	          << terrain_offset.z << std::endl;

	start = start - glm::vec2(terrain_offset.x, terrain_offset.z);
	end = end - glm::vec2(terrain_offset.x, terrain_offset.z);

	std::cout << start.x << " : " << start.y << " vs " << end.x << " : "
	          << end.y << std::endl;
	// Pathfind
	std::queue<glm::vec2> points =
	    gameWorlds.at(terrain_to_pathfind)
	        .pathFinding(start.x, start.y, end.x, end.y);

	std::vector<glm::vec3> vec_points;
	glm::vec2 point;
	while (!points.empty()) {
	    point = points.front();
	    points.pop();

	    vec_points.push_back(glm::vec3(point.x + terrain_offset.x, 0,
	                                   point.y + terrain_offset.z));
	}

	// Provide results to lua
	Component::Statemachine& own_statemachine =
	    entity.get_component<Component::Statemachine>();

	own_statemachine.lua_variables["waypoints"] = vec_points;
	own_statemachine.lua_variables["number_of_waypoints"] = vec_points.size();
	own_statemachine.lua_variables["current_number"] = 1;
	*/
}

void statemachineComponentHelper::follow_generated_waypoints(
    Reflex::Entity& entity, bool use_physics_movement, float speed,
    std::string terrain_name) {
	if (use_physics_movement) {
		use_physics_movement =
		    false;  // entity.any_component<Component::Physics>();
	}

	Component::Statemachine& states =
	    entity.get_component<Component::Statemachine>();
	glm::vec3 target = glm::vec3(0, 0, 0);

	int current_number = states.lua_variables["current_number"];
	target = states.lua_variables["waypoints"][current_number];

	if (use_physics_movement) {
		follow_waypoint(entity, target, speed, terrain_name);
	} else {
		follow_waypoint_physics(entity, target, speed);
	}

	int num = states.lua_variables["number_of_waypoints"];
	if (current_number < num) {
		states.lua_variables["current_number"] = (++current_number);
	}
}

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
