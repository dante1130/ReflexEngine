#include "ECSGameAssetFactory.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Mesh.hpp"

#include "Controller/ECS/ComponentSystem/ComponentFunctions.hpp"

#include "Controller/LuaManager.hpp"

void ECSGameAssetFactory::create(ECS& ecs, const std::string& lua_script) {
	if (!is_lua_script(lua_script)) return;

	auto& lua = LuaManager::get_instance().get_state();

	lua.script_file(lua_script);

	auto entity_table = lua["entity"];

	if (entity_table.valid()) {
		load_components(ecs.create_entity(), entity_table);
	}
}

void ECSGameAssetFactory::load_components(Reflex::Entity& entity,
                                          const sol::table& entity_table) {
	if (entity_table["transform"].valid()) {
		load_transform(entity, entity_table["transform"]);
	} else {
		// Load a default transform component if the entity has no transform.
		entity.add_component<component::Transform>();
	}

	if (entity_table["model"].valid()) {
		load_model(entity, entity_table["model"]);
	}

	if (entity_table["script"].valid()) {
		load_script(entity, entity_table["script"]);
	}

	if (entity_table["directional_light"].valid()) {
		load_directional_light(entity, entity_table["directional_light"]);
	}

	if (entity_table["point_light"].valid()) {
		load_point_light(entity, entity_table["point_light"]);
	}

	if (entity_table["spot_light"].valid()) {
		load_spot_light(entity, entity_table["spot_light"]);
	}

	if (entity_table["mesh"].valid()) {
		load_mesh(entity, entity_table["mesh"]);
	}
}

void ECSGameAssetFactory::load_transform(Reflex::Entity& entity,
                                         const sol::table& transform_table) {
	auto& transform_component = entity.add_component<component::Transform>();

	transform_component.position.x = transform_table["position"]["x"];
	transform_component.position.y = transform_table["position"]["y"];
	transform_component.position.z = transform_table["position"]["z"];

	transform_component.rotation.x = transform_table["rotation"]["x"];
	transform_component.rotation.y = transform_table["rotation"]["y"];
	transform_component.rotation.z = transform_table["rotation"]["z"];
	transform_component.rotation.w = transform_table["rotation"]["w"];

	transform_component.scale.x = transform_table["scale"]["x"];
	transform_component.scale.y = transform_table["scale"]["y"];
	transform_component.scale.z = transform_table["scale"]["z"];
}

void ECSGameAssetFactory::load_script(Reflex::Entity& entity,
                                      const sol::table& script_table) {
	auto& script_component = entity.add_component<component::Script>();

	script_component.lua_script = script_table["lua_script"];
	script_component.entity = &entity;

	component::init_script(entity.get_registry(), entity.get_entity_id());
}

void ECSGameAssetFactory::load_model(Reflex::Entity& entity,
                                     const sol::table& model_table) {
	auto& model_component = entity.add_component<component::Model>();

	model_component.model_name = model_table["model_name"];
	model_component.material_name = model_table["material_name"];
}

void ECSGameAssetFactory::load_directional_light(
    Reflex::Entity& entity, const sol::table& light_table) {
	auto& light_component = entity.add_component<component::DirectionalLight>();

	light_component.color.x = light_table["color"]["r"];
	light_component.color.y = light_table["color"]["g"];
	light_component.color.z = light_table["color"]["b"];

	light_component.ambient_intensity = light_table["ambient_intensity"];
	light_component.diffuse_intensity = light_table["diffuse_intensity"];

	light_component.direction.x = light_table["direction"]["x"];
	light_component.direction.y = light_table["direction"]["y"];
	light_component.direction.z = light_table["direction"]["z"];

	component::init_directional_light(entity.get_registry(),
	                                  entity.get_entity_id());
}

void ECSGameAssetFactory::load_point_light(Reflex::Entity& entity,
                                           const sol::table& light_table) {
	auto& light_component = entity.add_component<component::PointLight>();

	light_component.color.x = light_table["color"]["r"];
	light_component.color.y = light_table["color"]["g"];
	light_component.color.z = light_table["color"]["b"];

	light_component.ambient_intensity = light_table["ambient_intensity"];
	light_component.diffuse_intensity = light_table["diffuse_intensity"];

	light_component.position.x = light_table["position"]["x"];
	light_component.position.y = light_table["position"]["y"];
	light_component.position.z = light_table["position"]["z"];

	light_component.constant = light_table["constant"];
	light_component.linear = light_table["linear"];
	light_component.quadratic = light_table["quadratic"];

	component::init_point_light(entity.get_registry(), entity.get_entity_id());
}

void ECSGameAssetFactory::load_spot_light(Reflex::Entity& entity,
                                          const sol::table& light_table) {
	auto& light_component = entity.add_component<component::SpotLight>();

	light_component.color.x = light_table["color"]["r"];
	light_component.color.y = light_table["color"]["g"];
	light_component.color.z = light_table["color"]["b"];

	light_component.ambient_intensity = light_table["ambient_intensity"];
	light_component.diffuse_intensity = light_table["diffuse_intensity"];

	light_component.position.x = light_table["position"]["x"];
	light_component.position.y = light_table["position"]["y"];
	light_component.position.z = light_table["position"]["z"];

	light_component.direction.x = light_table["direction"]["x"];
	light_component.direction.y = light_table["direction"]["y"];
	light_component.direction.z = light_table["direction"]["z"];

	light_component.constant = light_table["constant"];
	light_component.linear = light_table["linear"];
	light_component.quadratic = light_table["quadratic"];

	light_component.edge = light_table["edge"];

	component::init_spot_light(entity.get_registry(), entity.get_entity_id());
}

void ECSGameAssetFactory::load_mesh(Reflex::Entity& entity,
                                    const sol::table& mesh_table) {
	auto& mesh_component = entity.add_component<component::Mesh>();

	mesh_component.mesh_name = mesh_table["mesh_name"];
	mesh_component.material_name = mesh_table["material_name"];
	mesh_component.texture_name = mesh_table["texture_name"];
}

bool ECSGameAssetFactory::is_lua_script(const std::string& lua_script) {
	return lua_script.substr(lua_script.find_last_of('.') + 1) == "lua";
}