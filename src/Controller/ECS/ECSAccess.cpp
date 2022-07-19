#include "ECSAccess.hpp"

#include "Controller/LuaManager.hpp"

#include "Entity.hpp"
#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"

using namespace component;

void ECSAccess::register_ecs() {
	register_entity();
	register_transform_component();
	register_model_component();
	register_script_component();
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