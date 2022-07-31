#include "ECSAccess.hpp"

#include "Controller/LuaManager.hpp"

#include "ECS.hpp"
#include "Entity.hpp"
#include "Model/Components/Transform.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Md2Animation.hpp"
#include "Model/Components/Terrain.hpp"
#include "Model/Components/Statemachine.hpp"
#include "Model/Components/Remove.hpp"

#include "Controller/AI/statemachineComponentHelper.hpp"

using namespace Component;
using namespace Reflex;

void ECSAccess::register_ecs() {
	register_registry();
	register_entity();
	register_transform_component();
	register_model_component();
	register_script_component();
	register_directional_light_component();
	register_point_light_component();
	register_spot_light_component();
	register_mesh_component();
	register_md2_component();
	register_terrain_component();
	register_statemachine_component();
}

void ECSAccess::register_registry() {
	auto& lua = LuaManager::get_instance().get_state();

	lua.new_usertype<ECS>("ECS");

	auto ecs_table = lua["ECS"].get_or_create<sol::table>();

	ecs_table["create_entity"] = [](ECS& ecs, const std::string& name) {
		return ecs.create_entity(name);
	};

	ecs_table["get_entity"] = [](ECS& ecs, entt::entity entity_id) {
		return ecs.get_entity(entity_id);
	};

	ecs_table["remove_entity"] = [](ECS& ecs, entt::entity entity_id) {
		ecs.get_entity(entity_id).add_component<Remove>();
	};

	ecs_table["each_transform"] = [](ECS& ecs, const sol::function& callback) {
		auto view = ecs.get_registry().view<Transform>();
		for (auto entity_id : view) callback(ecs.get_entity(entity_id));
	};

	ecs_table["each_model"] = [](ECS& ecs, const sol::function& callback) {
		auto view = ecs.get_registry().view<Model>();
		for (auto entity_id : view) callback(ecs.get_entity(entity_id));
	};

	ecs_table["each_script"] = [](ECS& ecs, const sol::function& callback) {
		auto view = ecs.get_registry().view<Script>();
		for (auto entity_id : view) callback(ecs.get_entity(entity_id));
	};

	ecs_table["each_directional_light"] = [](ECS& ecs,
	                                         const sol::function& callback) {
		auto view = ecs.get_registry().view<DirectionalLight>();
		for (auto entity_id : view) callback(ecs.get_entity(entity_id));
	};

	ecs_table["each_point_light"] = [](ECS& ecs,
	                                   const sol::function& callback) {
		auto view = ecs.get_registry().view<PointLight>();
		for (auto entity_id : view) callback(ecs.get_entity(entity_id));
	};

	ecs_table["each_spot_light"] = [](ECS& ecs, const sol::function& callback) {
		auto view = ecs.get_registry().view<SpotLight>();
		for (auto entity_id : view) callback(ecs.get_entity(entity_id));
	};

	ecs_table["each_mesh"] = [](ECS& ecs, const sol::function& callback) {
		auto view = ecs.get_registry().view<Mesh>();
		for (auto entity_id : view) callback(ecs.get_entity(entity_id));
	};

	ecs_table["each_terrain"] = [](ECS& ecs, const sol::function& callback) {
		auto view = ecs.get_registry().view<Terrain>();
		for (auto entity_id : view) callback(ecs.get_entity(entity_id));
	};
}

void ECSAccess::register_entity() {
	auto& lua = LuaManager::get_instance().get_state();

	auto entity_type = lua.new_usertype<Reflex::Entity>("Entity");

	entity_type["get_id"] = &Entity::get_entity_id;

	entity_type["add_transform_component"] = &Entity::add_component<Transform>;
	entity_type["add_model_component"] = &Entity::add_component<Model>;
	entity_type["add_script_component"] = &Entity::add_component<Script>;
	entity_type["add_directional_light_component"] =
	    &Entity::add_component<DirectionalLight>;
	entity_type["add_point_light_component"] =
	    &Entity::add_component<PointLight>;
	entity_type["add_spot_light_component"] = &Entity::add_component<SpotLight>;
	entity_type["add_mesh_component"] = &Entity::add_component<Mesh>;
	entity_type["add_stateMachine_component"] =
	    &Entity::add_component<Statemachine>;

	entity_type["remove_transform_component"] =
	    &Entity::remove_component<Transform>;
	entity_type["remove_model_component"] = &Entity::remove_component<Model>;
	entity_type["remove_script_component"] = &Entity::remove_component<Script>;
	entity_type["remove_directional_light_component"] =
	    &Entity::remove_component<DirectionalLight>;
	entity_type["remove_point_light_component"] =
	    &Entity::remove_component<PointLight>;
	entity_type["remove_spot_light_component"] =
	    &Entity::remove_component<SpotLight>;
	entity_type["remove_mesh_component"] = &Entity::remove_component<Mesh>;
	entity_type["remove_statemachine_component"] =
	    &Entity::remove_component<Statemachine>;

	entity_type["get_transform_component"] = &Entity::get_component<Transform>;
	entity_type["get_model_component"] = &Entity::get_component<Model>;
	entity_type["get_script_component"] = &Entity::get_component<Script>;
	entity_type["get_directional_light_component"] =
	    &Entity::get_component<DirectionalLight>;
	entity_type["get_point_light_component"] =
	    &Entity::get_component<PointLight>;
	entity_type["get_spot_light_component"] = &Entity::get_component<SpotLight>;
	entity_type["get_mesh_component"] = &Entity::get_component<Mesh>;
	entity_type["get_statemachine_component"] =
	    &Entity::get_component<Statemachine>;

	entity_type["any_transform_component"] = &Entity::any_component<Transform>;
	entity_type["any_model_component"] = &Entity::any_component<Model>;
	entity_type["any_script_component"] = &Entity::any_component<Script>;
	entity_type["any_directional_light_component"] =
	    &Entity::any_component<DirectionalLight>;
	entity_type["any_point_light_component"] =
	    &Entity::any_component<PointLight>;
	entity_type["any_spot_light_component"] = &Entity::any_component<SpotLight>;
	entity_type["any_mesh_component"] = &Entity::any_component<Mesh>;
	entity_type["any_mesh_statemachine"] = &Entity::any_component<Statemachine>;
}

void ECSAccess::register_transform_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto transform_type = lua.new_usertype<Transform>("Transform");

	transform_type["position"] = &Transform::position;
	transform_type["rotation"] = &Transform::rotation;
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

	directional_light_type["color"] = &DirectionalLight::color;
	directional_light_type["ambient_intensity"] =
	    &DirectionalLight::ambient_intensity;
	directional_light_type["diffuse_intensity"] =
	    &DirectionalLight::diffuse_intensity;
	directional_light_type["direction"] = &DirectionalLight::direction;
}

void ECSAccess::register_point_light_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto point_light_type = lua.new_usertype<PointLight>("PointLight");

	point_light_type["color"] = &PointLight::color;
	point_light_type["ambient_intensity"] = &PointLight::ambient_intensity;
	point_light_type["diffuse_intensity"] = &PointLight::diffuse_intensity;
	point_light_type["position"] = &PointLight::position;
	point_light_type["constant"] = &PointLight::constant;
	point_light_type["linear"] = &PointLight::linear;
	point_light_type["quadratic"] = &PointLight::quadratic;
}

void ECSAccess::register_spot_light_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto spot_light_type = lua.new_usertype<SpotLight>("SpotLight");

	spot_light_type["color"] = &SpotLight::color;
	spot_light_type["ambient_intensity"] = &SpotLight::ambient_intensity;
	spot_light_type["diffuse_intensity"] = &SpotLight::diffuse_intensity;
	spot_light_type["position"] = &SpotLight::position;
	spot_light_type["constant"] = &SpotLight::constant;
	spot_light_type["linear"] = &SpotLight::linear;
	spot_light_type["quadratic"] = &SpotLight::quadratic;
	spot_light_type["direction"] = &SpotLight::direction;
	spot_light_type["edge"] = &SpotLight::edge;
}

void ECSAccess::register_mesh_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto mesh_type = lua.new_usertype<Mesh>("Mesh");

	mesh_type["mesh_name"] = &Mesh::mesh_name;
	mesh_type["texture_name"] = &Mesh::texture_name;
	mesh_type["material_name"] = &Mesh::material_name;
}

void ECSAccess::register_md2_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto md2_table = lua["Md2"].get_or_create<sol::table>();

	auto animation_types = md2_table.new_enum("Animation");

	animation_types["STAND"] = md2::animation_type::STAND;
	animation_types["RUN"] = md2::animation_type::RUN;
	animation_types["ATTACK"] = md2::animation_type::ATTACK;
	animation_types["PAIN_A"] = md2::animation_type::PAIN_A;
	animation_types["PAIN_B"] = md2::animation_type::PAIN_B;
	animation_types["PAIN_C"] = md2::animation_type::PAIN_C;
	animation_types["JUMP"] = md2::animation_type::JUMP;
	animation_types["FLIP"] = md2::animation_type::FLIP;
	animation_types["SALUTE"] = md2::animation_type::SALUTE;
	animation_types["FALLBACK"] = md2::animation_type::FALLBACK;
	animation_types["WAVE"] = md2::animation_type::WAVE;
	animation_types["POINT"] = md2::animation_type::POINT;
	animation_types["CROUCH_STAND"] = md2::animation_type::CROUCH_STAND;
	animation_types["CROUCH_WALK"] = md2::animation_type::CROUCH_WALK;
	animation_types["CROUCH_ATTACK"] = md2::animation_type::CROUCH_ATTACK;
	animation_types["CROUCH_PAIN"] = md2::animation_type::CROUCH_PAIN;
	animation_types["CROUCH_DEATH"] = md2::animation_type::CROUCH_DEATH;
	animation_types["DEATH_FALLBACK"] = md2::animation_type::DEATH_FALLBACK;
	animation_types["DEATH_FALLFORWARD"] =
	    md2::animation_type::DEATH_FALLFORWARD;
	animation_types["DEATH_FALLBACKSLOW"] =
	    md2::animation_type::DEATH_FALLBACKSLOW;
	animation_types["BOOM"] = md2::animation_type::BOOM;

	auto md2_type = lua.new_usertype<Md2Animation>("Md2");

	md2_type["md2_name"] = &Md2Animation::md2_name;
	md2_type["texture_name"] = &Md2Animation::texture_name;
	md2_type["material_name"] = &Md2Animation::material_name;
	md2_type["is_loop"] = &Md2Animation::is_loop;
	md2_type["is_interpolated"] = &Md2Animation::is_interpolated;
	md2_type["is_animation_done"] =
	    sol::readonly(&Md2Animation::is_animation_done);

	md2_table["change_animation"] = [](Md2Animation& md2,
	                                   md2::animation_type animation_type) {
		md2.animstate.type = animation_type;

		md2::anim_t anim = md2::animations_[static_cast<int>(animation_type)];

		md2.animstate.start_frame = anim.first_frame;
		md2.animstate.end_frame = anim.last_frame;
		md2.animstate.next_frame = anim.first_frame + 1;
		md2.animstate.fps = anim.fps;

		md2.is_animation_done = false;
	};
}

void ECSAccess::register_terrain_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto terrain_type = lua.new_usertype<Terrain>("Terrain");

	terrain_type["terrain_name"] = &Terrain::terrain_name;
	terrain_type["texture_name"] = &Terrain::texture_name;
	terrain_type["material_name"] = &Terrain::material_name;
	terrain_type["detailmap_name"] = &Terrain::detailmap_name;
}

void ECSAccess::register_statemachine_component() {
	auto& lua = LuaManager::get_instance().get_state();

	auto statemachine_type = lua.new_usertype<Statemachine>("Statemachine");

	statemachine_type["global_state"] = &Statemachine::global_state;
	statemachine_type["current_state"] = &Statemachine::current_state;
	statemachine_type["previous_state"] = &Statemachine::previous_state;

	sol::table statemachine = lua.create_named_table("statemachine_helper");
	statemachine["change_state"] = &statemachineComponentHelper::change_state;
	statemachine["send_message"] = &statemachineComponentHelper::send_message;
	statemachine["send_area_message"] =
	    &statemachineComponentHelper::send_area_message;
	statemachine["look_for_enemy"] =
	    &statemachineComponentHelper::look_for_enemy;
	statemachine["generate_waypoints"] =
	    &statemachineComponentHelper::generate_waypoints;
	statemachine["follow_generated_waypoints"] =
	    &statemachineComponentHelper::follow_generated_waypoints;
	statemachine["follow_waypoint"] =
	    &statemachineComponentHelper::follow_waypoint;
	statemachine["follow_waypoint_physics"] =
	    &statemachineComponentHelper::follow_waypoint_physics;
}
