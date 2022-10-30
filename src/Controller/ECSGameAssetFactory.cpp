#include "ECSGameAssetFactory.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Md2Animation.hpp"
#include "Model/Components/Terrain.hpp"
#include "Model/Components/Statemachine.hpp"
#include "Model/Components/RigidBody.hpp"

#include "Controller/GUI/CollectionsGUI.hpp"
#include "Controller/Physics/LoadOBJColliderData.hpp"

#include "Controller/ECS/System.hpp"

#include "Controller/LuaManager.hpp"

#include "Model/singletons.h"

void ECSGameAssetFactory::create(ECS& ecs, const std::string& lua_script) {
	if (!is_lua_script(lua_script)) return;

	auto& lua = LuaManager::get_instance().get_state();

	lua.script_file(lua_script);

	auto entity_table = lua["entity"];

	if (entity_table.valid()) {
		const std::string name = [&entity_table]() {
			if (entity_table["name"].valid()) {
				return entity_table["name"];
			}
		}();

		load_components(ecs, ecs.create_entity(name), entity_table);
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

	if (entity_table["md2_animation"].valid()) {
		load_md2_animation(entity, entity_table["md2_animation"]);
	}

	if (entity_table["terrain"].valid()) {
		load_terrain(entity, entity_table["terrain"]);
	}

	if (entity_table["statemachine"].valid()) {
		load_statemachine(entity, entity_table["statemachine"]);
	}

	if (entity_table["rigidbody"].valid()) {
		load_rigidbody(entity, entity_table["rigidbody"]);
	}

	// Put this last in case the script calls other components.
	if (entity_table["script"].valid()) {
		load_script(ecs, entity, entity_table["script"]);
	}

	if (entity_table["collection_id"].valid()) {
		CollectionsGUI::add_entity_to_collection(entity.get_entity_id(),
		                                         entity_table["collection_id"]);
	}
}

void ECSGameAssetFactory::load_transform(Reflex::Entity& entity,
                                         const sol::table& transform_table) {
	const glm::vec3 position = {transform_table["position"]["x"],
	                            transform_table["position"]["y"],
	                            transform_table["position"]["z"]};
	const glm::vec3 rotation = {transform_table["rotation"]["x"],
	                            transform_table["rotation"]["y"],
	                            transform_table["rotation"]["z"]};
	const glm::vec3 scale = {transform_table["scale"]["x"],
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

void ECSGameAssetFactory::load_md2_animation(Reflex::Entity& entity,
                                             const sol::table& md2_table) {
	auto& md2 = entity.add_component<Component::Md2Animation>(
	    md2_table["md2_name"], md2_table["texture_name"],
	    md2_table["material_name"]);

	if (md2_table["is_loop"].valid()) {
		md2.is_loop = md2_table["is_loop"];
	}

	if (md2_table["is_interpolated"].valid()) {
		md2.is_interpolated = md2_table["is_interpolated"];
	}
}

void ECSGameAssetFactory::load_terrain(Reflex::Entity& entity,
                                       const sol::table& terrain_table) {
	entity.add_component<Component::Terrain>(
	    terrain_table["terrain_name"], terrain_table["texture_name"],
	    terrain_table["material_name"], terrain_table["detailmap_name"]);

	world pathfinding_grid;
	float min = 0, max = 9999, max_dist = 100;
	if (terrain_table["pathfinding"].valid()) {
		min = terrain_table["pathfinding"]["min_value"];
		max = terrain_table["pathfinding"]["max_value"];
		max_dist = terrain_table["pathfinding"]["max_distance"];
	}
	pathfinding_grid.setMinMaxHeight(min, max);
	pathfinding_grid.setMaxDistance(max_dist);
	pathfinding_grid.setWorld(terrain_table["terrain_name"]);
	gameWorlds.insert({terrain_table["terrain_name"], pathfinding_grid});
}

void ECSGameAssetFactory::load_statemachine(
    Reflex::Entity& entity, const sol::table& statemachine_table) {
	auto& statemachine_component =
	    entity.add_component<Component::Statemachine>();

	statemachine_component.entity = &entity;

	statemachine_component.global_state = statemachine_table["global_state"];
	statemachine_component.current_state = statemachine_table["current_state"];
	statemachine_component.previous_state =
	    statemachine_table["previous_state"];

	System::init_statemachine(entity.get_registry(), entity.get_entity_id());
}

void ECSGameAssetFactory::load_directional_light(
    Reflex::Entity& entity, const sol::table& light_table) {
	const glm::vec3 color = {light_table["color"]["r"],
	                         light_table["color"]["g"],
	                         light_table["color"]["b"]};
	const glm::vec3 direction = {light_table["direction"]["x"],
	                             light_table["direction"]["y"],
	                             light_table["direction"]["z"]};

	entity.add_component<Component::DirectionalLight>(
	    light_table["shadow_width"], light_table["shadow_height"],
	    light_table["near_plane"], light_table["far_plane"],
	    light_table["ortho_left"], light_table["ortho_right"],
	    light_table["ortho_bottom"], light_table["ortho_top"], color,
	    light_table["ambient_intensity"], light_table["diffuse_intensity"],
	    direction);
}

void ECSGameAssetFactory::load_point_light(Reflex::Entity& entity,
                                           const sol::table& light_table) {
	const glm::vec3 color = {light_table["color"]["r"],
	                         light_table["color"]["g"],
	                         light_table["color"]["b"]};

	const glm::vec3 position = {light_table["position"]["x"],
	                            light_table["position"]["y"],
	                            light_table["position"]["z"]};

	entity.add_component<Component::PointLight>(
	    light_table["shadow_width"], light_table["shadow_height"],
	    light_table["near_plane"], light_table["far_plane"], color,
	    light_table["ambient_intensity"], light_table["diffuse_intensity"],
	    position, light_table["constant"], light_table["linear"],
	    light_table["quadratic"]);
}

void ECSGameAssetFactory::load_spot_light(Reflex::Entity& entity,
                                          const sol::table& light_table) {
	const glm::vec3 color = {light_table["color"]["r"],
	                         light_table["color"]["g"],
	                         light_table["color"]["b"]};

	const glm::vec3 position = {light_table["position"]["x"],
	                            light_table["position"]["y"],
	                            light_table["position"]["z"]};

	const glm::vec3 direction = {light_table["direction"]["x"],
	                             light_table["direction"]["y"],
	                             light_table["direction"]["z"]};

	entity.add_component<Component::SpotLight>(
	    light_table["shadow_width"], light_table["shadow_height"],
	    light_table["near_plane"], light_table["far_plane"], color,
	    light_table["ambient_intensity"], light_table["diffuse_intensity"],
	    position, light_table["constant"], light_table["linear"],
	    light_table["quadratic"], direction, light_table["edge"]);
}

bool ECSGameAssetFactory::is_lua_script(const std::string& lua_script) {
	return lua_script.substr(lua_script.find_last_of('.') + 1) == "lua";
}

void ECSGameAssetFactory::load_rigidbody(Reflex::Entity& entity,
                                         const sol::table& rigidbody_table) {
	Component::Transform trans = entity.get_component<Component::Transform>();
	Component::Rigidbody rb_comp = Component::Rigidbody(
	    rigidbody_table["using_react_start"], trans.position, trans.rotation,
	    rigidbody_table["gravity_on"], rigidbody_table["can_sleep"], false,
	    rigidbody_table["linear_drag"], rigidbody_table["angular_drag"]);

	rb_comp.setType(rigidbody_table["rb_type"]);

	if (rigidbody_table["collider_obj_data"].valid()) {
		rb_comp.collider_obj_data = rigidbody_table["collider_obj_data"];
		loadOBJColliderData::load_obj_collider_data(rb_comp,
		                                            rb_comp.collider_obj_data);
	}

	if (rigidbody_table["linear_velocity"].valid()) {
		auto linear_velocity = glm::vec3(0);
		linear_velocity.x = rigidbody_table["linear_velocity"]["x"];
		linear_velocity.y = rigidbody_table["linear_velocity"]["y"];
		linear_velocity.z = rigidbody_table["linear_velocity"]["z"];
		rb_comp.setVelocity(linear_velocity);
	}

	if (rigidbody_table["angular_velocity"].valid()) {
		auto angular_velocity = glm::vec3(0);
		angular_velocity.x = rigidbody_table["angular_velocity"]["x"];
		angular_velocity.y = rigidbody_table["angular_velocity"]["y"];
		angular_velocity.z = rigidbody_table["angular_velocity"]["z"];
		rb_comp.setAngVelocity(angular_velocity);
	}

	entity.add_component<Component::Rigidbody>(rb_comp);
}
