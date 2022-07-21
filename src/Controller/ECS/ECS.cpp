#include "ECS.hpp"

#include "Entity.hpp"

#include "ComponentSystem/ComponentFunctions.hpp"

Entity& ECS::create_entity() {
	entt::entity entity_id = registry_.create();

	return *(entities_[entity_id] = std::make_unique<Entity>(entity_id, this));
}

void ECS::update(double delta_time) {
	component::update_script(registry_);
	component::update_directional_light(registry_);
	component::update_point_light(registry_);
	component::update_spot_light(registry_);
}

void ECS::fixed_update(double delta_time) {}

void ECS::draw() { component::draw_model(registry_); }

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
