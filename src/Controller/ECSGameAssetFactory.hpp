#pragma once

#include <string>

#include <sol/sol.hpp>

#include "ECS/ECS.hpp"
#include "ECS/Entity.hpp"

class ECSGameAssetFactory {
public:
	static void create(ECS& ecs, const std::string& lua_script);

private:
	static void load_components(Reflex::Entity& entity,
	                            const sol::table& entity_table);

	static void load_transform(Reflex::Entity& entity,
	                           const sol::table& transform_table);

	static void load_script(Reflex::Entity& entity,
	                        const sol::table& script_table);

	static void load_model(Reflex::Entity& entity,
	                       const sol::table& model_table);

	static void load_directional_light(Reflex::Entity& entity,
	                                   const sol::table& light_table);

	static bool is_lua_script(const std::string& lua_script);
};