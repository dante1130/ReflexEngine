#include "ECSGameAssetFactory.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Terrain.hpp"

#include "Controller/ECS/System.hpp"

#include "Controller/LuaManager.hpp"

void ECSGameAssetFactory::create(ECS& ecs, const std::string& lua_script) {
	if (!is_lua_script(lua_script)) return;

	auto& lua = LuaManager::get_instance().get_state();

	lua.script_file(lua_script);

	auto entity_table = lua["entity"];

	if (entity_table.valid()) {
		load_components(ecs, ecs.create_entity(), entity_table);
	}
}

void ECSGameAssetFactory::load_components(ECS& ecs, Reflex::Entity& entity,
                                          const sol::table& entity_table) {
	if (entity_table["transform"].valid()) {
		load_transform(entity, entity_table["transform"]);
	} else {
		// Load a default transform component if the entity has no transform.
		entity.add_component<Component::Transform>();
	}

	if (entity_table["model"].valid()) {
		load_model(entity, entity_table["model"]);
	}

	if (entity_table["script"].valid()) {
		load_script(ecs, entity, entity_table["script"]);
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

	if (entity_table["terrain"].valid()) {
		load_terrain(entity, entity_table["terrain"]);
	}
}

void ECSGameAssetFactory::load_transform(Reflex::Entity& entity,
                                         const sol::table& transform_table) {
	glm::vec3 position = {transform_table["position"]["x"],
	                      transform_table["position"]["y"],
	                      transform_table["position"]["z"]};
	glm::quat rotation = {
	    transform_table["rotation"]["w"], transform_table["rotation"]["x"],
	    transform_table["rotation"]["y"], transform_table["rotation"]["z"]};
	glm::vec3 scale = {transform_table["scale"]["x"],
	                   transform_table["scale"]["y"],
	                   transform_table["scale"]["z"]};

	entity.add_component<Component::Transform>(position, rotation, scale);
}

void ECSGameAssetFactory::load_script(ECS& ecs, Reflex::Entity& entity,
                                      const sol::table& script_table) {
	entity.add_component<Component::Script>(script_table["lua_script"], ecs,
	                                        entity);
}

void ECSGameAssetFactory::load_mesh(Reflex::Entity& entity,
                                    const sol::table& mesh_table) {
	entity.add_component<Component::Mesh>(mesh_table["mesh_name"],
	                                      mesh_table["texture_name"],
	                                      mesh_table["material_name"]);
}

void ECSGameAssetFactory::load_model(Reflex::Entity& entity,
                                     const sol::table& model_table) {
	entity.add_component<Component::Model>(model_table["model_name"],
	                                       model_table["material_name"]);
}

void ECSGameAssetFactory::load_terrain(Reflex::Entity& entity,
                                       const sol::table& terrain_table) {
	entity.add_component<Component::Terrain>(
	    terrain_table["terrain_name"], terrain_table["texture_name"],
	    terrain_table["material_name"], terrain_table["detailmap_name"]);
}

void ECSGameAssetFactory::load_directional_light(
    Reflex::Entity& entity, const sol::table& light_table) {
	glm::vec3 color = {light_table["color"]["r"], light_table["color"]["g"],
	                   light_table["color"]["b"]};
	glm::vec3 direction = {light_table["direction"]["x"],
	                       light_table["direction"]["y"],
	                       light_table["direction"]["z"]};

	auto& light_component = entity.add_component<Component::DirectionalLight>(
	    color, light_table["ambient_intensity"],
	    light_table["diffuse_intensity"], direction);
}

void ECSGameAssetFactory::load_point_light(Reflex::Entity& entity,
                                           const sol::table& light_table) {
	glm::vec3 color = {light_table["color"]["r"], light_table["color"]["g"],
	                   light_table["color"]["b"]};

	glm::vec3 position = {light_table["position"]["x"],
	                      light_table["position"]["y"],
	                      light_table["position"]["z"]};

	entity.add_component<Component::PointLight>(
	    color, light_table["ambient_intensity"],
	    light_table["diffuse_intensity"], position, light_table["constant"],
	    light_table["linear"], light_table["quadratic"]);
}

void ECSGameAssetFactory::load_spot_light(Reflex::Entity& entity,
                                          const sol::table& light_table) {
	glm::vec3 color = {light_table["color"]["r"], light_table["color"]["g"],
	                   light_table["color"]["b"]};

	glm::vec3 position = {light_table["position"]["x"],
	                      light_table["position"]["y"],
	                      light_table["position"]["z"]};

	glm::vec3 direction = {light_table["direction"]["x"],
	                       light_table["direction"]["y"],
	                       light_table["direction"]["z"]};

	entity.add_component<Component::SpotLight>(
	    color, light_table["ambient_intensity"],
	    light_table["diffuse_intensity"], position, light_table["constant"],
	    light_table["linear"], light_table["quadratic"], direction,
	    light_table["cutoff"]);
}

bool ECSGameAssetFactory::is_lua_script(const std::string& lua_script) {
	return lua_script.substr(lua_script.find_last_of('.') + 1) == "lua";
}