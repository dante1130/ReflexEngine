#include "ECS.hpp"

#include "Entity.hpp"
#include "System.hpp"

#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"
#include "Model/Components/Md2Animation.hpp"
#include "Model/Components/RigidBody.hpp"
#include "Controller/ReflexEngine/PerformanceLogger.hpp"

using namespace Reflex;

ECS::ECS() {
	registry_.on_construct<Component::Script>().connect<&System::init_script>();
	registry_.on_construct<Component::DirectionalLight>()
	    .connect<&System::init_directional_light>();
	registry_.on_construct<Component::PointLight>()
	    .connect<&System::init_point_light>();
	registry_.on_construct<Component::SpotLight>()
	    .connect<&System::init_spot_light>();
	registry_.on_construct<Component::Md2Animation>()
	    .connect<&System::init_md2_animation>();
	registry_.on_construct<Component::Rigidbody>()
	    .connect<&System::init_rigidbody>();

	registry_.on_update<Component::Script>().connect<&System::init_script>();
	registry_.on_update<Component::Md2Animation>()
	    .connect<&System::init_md2_animation>();
	registry_.on_update<Component::Rigidbody>()
	    .connect<&System::update_rigidbody>();

	registry_.on_destroy<Component::DirectionalLight>()
	    .connect<&System::delete_directional_light>();
	registry_.on_destroy<Component::PointLight>()
	    .connect<&System::delete_point_light>();
	registry_.on_destroy<Component::SpotLight>()
	    .connect<&System::delete_spot_light>();
}

Entity& ECS::create_entity(const std::string& name) {
	entt::entity entity_id = registry_.create();

	return *(entities_[entity_id] =
	             std::make_shared<Entity>(name, entity_id, this));
}

void ECS::update(double delta_time) {
	PERFORMANCE_LOGGER_PUSH("Script");
	System::update_script(registry_);
	PERFORMANCE_LOGGER_POP();
	PERFORMANCE_LOGGER_PUSH("Directional light");
	System::update_directional_light(registry_);
	PERFORMANCE_LOGGER_POP();
	PERFORMANCE_LOGGER_PUSH("Point light");
	System::update_point_light(registry_);
	PERFORMANCE_LOGGER_POP();
	PERFORMANCE_LOGGER_PUSH("Spot light");
	System::update_spot_light(registry_);
	PERFORMANCE_LOGGER_POP();
	PERFORMANCE_LOGGER_PUSH("md2");
	System::update_md2(registry_);
	PERFORMANCE_LOGGER_POP();
	PERFORMANCE_LOGGER_PUSH("Statemachine");
	System::update_statemachine(*this);
	PERFORMANCE_LOGGER_POP();
}

void ECS::fixed_update(double delta_time) {
	System::update_rigidbody(registry_);
}

void ECS::draw() {
	System::draw_terrain(registry_);
	System::draw_model(registry_);
	System::draw_mesh(registry_);
	System::draw_md2(registry_);
}

void ECS::destroy_entity(entt::entity entity_id) {
	entities_.erase(entity_id);
	registry_.destroy(entity_id);
}

Entity& ECS::get_entity(entt::entity entity_id) {
	return *entities_.at(entity_id);
}

entt::registry& ECS::get_registry() { return registry_; }

const EntityMap& ECS::get_entity_map() const { return entities_; }

void ECS::clear_entities() {
	entities_.clear();
	registry_.clear();
}
