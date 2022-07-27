#include "ECS.hpp"

#include "Entity.hpp"
#include "System.hpp"

#include "Model/Components/Script.hpp"
#include "Model/Components/Light.hpp"

using namespace Reflex;

ECS::ECS() {
	registry_.on_construct<Component::Script>().connect<&System::init_script>();
	registry_.on_construct<Component::DirectionalLight>()
	    .connect<&System::init_directional_light>();
	registry_.on_construct<Component::PointLight>()
	    .connect<&System::init_point_light>();
	registry_.on_construct<Component::SpotLight>()
	    .connect<&System::init_spot_light>();
}

Entity& ECS::create_entity(const std::string& name) {
	entt::entity entity_id = registry_.create();

	return *(entities_[entity_id] =
	             std::make_shared<Entity>(name, entity_id, this));
}

void ECS::update(double delta_time) {
	System::update_script(registry_);
	System::update_directional_light(registry_);
	System::update_point_light(registry_);
	System::update_spot_light(registry_);
}

void ECS::fixed_update(double delta_time) {}

void ECS::draw() {
	System::draw_terrain(registry_);
	System::draw_model(registry_);
	System::draw_mesh(registry_);
}

void ECS::destroy_entity(entt::entity entity_id) {
	entities_.erase(entity_id);
	registry_.destroy(entity_id);
}

Entity& ECS::get_entity(entt::entity entity_id) {
	return *entities_.at(entity_id);
}

entt::registry& ECS::get_registry() { return registry_; }

void ECS::clear_entities() {
	entities_.clear();
	registry_.clear();
}
