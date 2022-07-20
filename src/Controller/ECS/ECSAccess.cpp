#include "ECSAccess.hpp"

#include "Controller/LuaManager.hpp"

#include "Entity.hpp"
#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"

using namespace component;

void ECSAccess::register_ecs() {
	register_entity();
	register_transform_component();
	register_model_component();
	register_script_component();
	register_directional_light_component();
	register_point_light_component();
	register_spot_light_component();
}

void ECSAccess::register_entity() {
	auto& lua = LuaManager::get_instance().get_state();

	auto entity_type = lua.new_usertype<Entity>("Entity");

	entity_type["add_transform_component"] = &Entity::add_component<Transform>;
	entity_type["add_model_component"] = &Entity::add_component<Model>;
	entity_type["add_script_component"] = &Entity::add_component<Script>;

	entity_type["remove_transform_component"] =
	    &Entity::remove_component<Transform>;
	entity_type["remove_model_component"] = &Entity::remove_component<Model>;
	entity_type["remove_script_component"] = &Entity::remove_component<Script>;

	entity_type["get_transform_component"] = &Entity::get_component<Transform>;
	entity_type["get_model_component"] = &Entity::get_component<Model>;
	entity_type["get_script_component"] = &Entity::get_component<Script>;
}

void ECSAccess::register_transform_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto transform_type = lua.new_usertype<Transform>("Transform");

	// Probably need to register glm::vec3.

	transform_type["position"] = &Transform::position;
	transform_type["angle"] = &Transform::angle;
	transform_type["scale"] = &Transform::scale;
}

void ECSAccess::register_model_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto model_type = lua.new_usertype<Model>("Model");

	model_type["model_name"] = &Model::model_name;
	model_type["material_name"] = &Model::material_name;
}

void ECSAccess::register_script_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto script_type = lua.new_usertype<Script>("Script");

	script_type["lua_script"] = &Script::lua_script;
}

void ECSAccess::register_directional_light_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto directional_light_type =
	    lua.new_usertype<DirectionalLight>("DirectionalLight");

	// directional_light_type["color"] = &DirectionalLightData::color;
	// directional_light_type["ambient_intensity"] =
	//     &DirectionalLightData::ambient_intensity;
	// directional_light_type["diffuse_intensity"] =
	//     &DirectionalLightData::diffuse_intensity;
	// directional_light_type["direction"] = &DirectionalLightData::direction;
}

void ECSAccess::register_point_light_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto point_light_type = lua.new_usertype<PointLight>("PointLight");

	// point_light_type["color"] = &PointLightData::color;
	// point_light_type["ambient_intensity"] =
	// &PointLightData::ambient_intensity; point_light_type["diffuse_intensity"]
	// = &PointLightData::diffuse_intensity; point_light_type["position"] =
	// &PointLightData::position; point_light_type["constant"] =
	// &PointLightData::constant; point_light_type["linear"] =
	// &PointLightData::linear; point_light_type["quadratic"] =
	// &PointLightData::quadratic;
}

void ECSAccess::register_spot_light_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto spot_light_type = lua.new_usertype<SpotLight>("SpotLight");

	// spot_light_type["color"] = &SpotLightData::color;
	// spot_light_type["ambient_intensity"] = &SpotLightData::ambient_intensity;
	// spot_light_type["diffuse_intensity"] = &SpotLightData::diffuse_intensity;
	// spot_light_type["position"] = &SpotLightData::position;
	// spot_light_type["constant"] = &SpotLightData::constant;
	// spot_light_type["linear"] = &SpotLightData::linear;
	// spot_light_type["quadratic"] = &SpotLightData::quadratic;
	// spot_light_type["direction"] = &SpotLightData::direction;
	// spot_light_type["edge"] = &SpotLightData::edge;
}
