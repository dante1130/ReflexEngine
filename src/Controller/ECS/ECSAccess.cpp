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
#include "Model/Components/RigidBody.hpp"
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
	register_rigidbody_component();
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

	ecs_table["each_rigidbody"] = [](ECS& ecs, const sol::function& callback) {
		auto view = ecs.get_registry().view<Rigidbody>();
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
	entity_type["add_rigidbody_component"] =
		&Entity::add_component<Rigidbody>;

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
	entity_type["remove_rigidbody_component"] =
		&Entity::remove_component<Rigidbody>;

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
	entity_type["get_rigidbody_component"] =
		&Entity::get_component<Rigidbody>;

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
	entity_type["any_rigidbody_component"] = &Entity::any_component<Rigidbody>;

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

	auto animation_types = md2_table.new_enum(
	    "AnimationType", "STAND", md2::animation_type::STAND, "RUN",
	    md2::animation_type::RUN, "ATTACK", md2::animation_type::ATTACK,
	    "PAIN_A", md2::animation_type::PAIN_A, "PAIN_B",
	    md2::animation_type::PAIN_B, "PAIN_C", md2::animation_type::PAIN_C,
	    "JUMP", md2::animation_type::JUMP, "FLIP", md2::animation_type::FLIP,
	    "SALUTE", md2::animation_type::SALUTE, "SALUTE",
	    md2::animation_type::SALUTE, "FALLBACK", md2::animation_type::SALUTE,
	    "WAVE", md2::animation_type::WAVE, "POINT", md2::animation_type::POINT,
	    "CROUCH_STAND", md2::animation_type::CROUCH_STAND, "CROUCH_WALK",
	    md2::animation_type::CROUCH_WALK, "CROUCH_ATTACK",
	    md2::animation_type::CROUCH_ATTACK, "CROUCH_DEATH",
	    md2::animation_type::CROUCH_DEATH, "DEATH_FALLBACK",
	    md2::animation_type::DEATH_FALLBACK, "DEATH_FALLFORWARD",
	    md2::animation_type::DEATH_FALLFORWARD, "DEATH_FALLBACKSLOW",
	    md2::animation_type::DEATH_FALLBACKSLOW, "BOOM",
	    md2::animation_type::BOOM);

	auto md2_type = lua.new_usertype<Md2Animation>("Md2");

	md2_type["md2_name"] = &Md2Animation::md2_name;
	md2_type["texture_name"] = &Md2Animation::texture_name;
	md2_type["material_name"] = &Md2Animation::material_name;
	md2_type["animation_state"] = &Md2Animation::animstate;
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

	auto animstate_type =
	    md2_table.new_usertype<md2::animstate_t>("AnimationState");

	animstate_type["start_frame"] = &md2::animstate_t::start_frame;
	animstate_type["end_frame"] = &md2::animstate_t::end_frame;
	animstate_type["fps"] = &md2::animstate_t::fps;

	animstate_type["curr_time"] = &md2::animstate_t::curr_time;
	animstate_type["prev_time"] = &md2::animstate_t::prev_time;
	animstate_type["interpolation"] = &md2::animstate_t::interpol;

	animstate_type["animation_type"] = &md2::animstate_t::type;

	animstate_type["curr_frame"] = &md2::animstate_t::curr_frame;
	animstate_type["next_frame"] = &md2::animstate_t::next_frame;
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

void ECSAccess::register_rigidbody_component() {
	auto& lua = LuaManager::get_instance().get_state();

	lua["Apply"] = lua.create_table_with(
		"LOCAL", Apply::LOCAL,
		"WORLD", Apply::WORLD
	);

	lua["ApplyPoint"] = lua.create_table_with(
		"LOCAL_LOCAL", ApplyPoint::LOCAL_LOCAL,
		"LOCAL_WORLD", ApplyPoint::LOCAL_WORLD,
		"WORLD_LOCAL", ApplyPoint::WORLD_LOCAL,
		"WORLD_WORLD", ApplyPoint::WORLD_WORLD
	);

	auto rigidbody_type = lua.new_usertype<Rigidbody>("Rigidbody");

	rigidbody_type["using_react"] = &Rigidbody::usingReactResolve;
	rigidbody_type["get_position"] = &Rigidbody::getPosition;
	rigidbody_type["get_rotation"] = &Rigidbody::getRotation;

	rigidbody_type["can_sleep"] = sol::property(&Rigidbody::getCanSleep, &Rigidbody::setCanSleep);
	rigidbody_type["is_trigger"] = sol::property(&Rigidbody::getIsTrigger, &Rigidbody::setObjectTrigger);
	rigidbody_type["gravity_on"] = sol::property(&Rigidbody::getIsGravityEnabled, &Rigidbody::enableGravity);
	rigidbody_type["linear_drag"] = sol::property(&Rigidbody::getDragForce, &Rigidbody::setDragForce);
	rigidbody_type["angular_drag"] = sol::property(&Rigidbody::getDragTorque, &Rigidbody::setDragTorque);

	rigidbody_type["add_force"] = &Rigidbody::addForce;
	rigidbody_type["add_torque"] = &Rigidbody::addTorque;
	rigidbody_type["add_force_at_point"] = &Rigidbody::addForceAtPoint;

	rigidbody_type["add_sphere_collider"] = &Rigidbody::addSphereCollider;
	rigidbody_type["add_box_collider"] = &Rigidbody::addBoxCollider;
	rigidbody_type["add_capsule_collider"] = &Rigidbody::addCapsuleCollider;

	rigidbody_type["remove_all_colliders"] = &Rigidbody::removeAllColliders;
	rigidbody_type["remove_collider"] = &Rigidbody::removeCollider;
}