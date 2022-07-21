#pragma once

#include <string>

#include <sol/sol.hpp>

#include "ECS/ECS.hpp"
#include "ECS/Entity.hpp"

class ECSGameAssetFactory {
public:
	static void create(ECS& ecs, const std::string& lua_script);

private:
	static void load_components(Entity& entity, const sol::table& entity_table);

	static void load_transform(Entity& entity,
	                           const sol::table& transform_table);

	static void load_model(Entity& entity, const sol::table& model_table);

	static void load_directional_light(Entity& entity,
	                                   const sol::table& light_table);

	static bool is_lua_script(const std::string& lua_script);
};