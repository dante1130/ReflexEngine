#include "ECS.hpp"

#include "Entity.hpp"

#include "ComponentSystem/ComponentFunctions.hpp"

Entity& ECS::create_entity() {
	entt::entity entity_id = registry_.create();

	return *(entities_[entity_id] = std::make_unique<Entity>(entity_id, this));
}

void ECS::update(double delta_time) {
	component::script_update(registry_);
	component::directional_light_update(registry_);
	component::point_light_update(registry_);
	component::spot_light_update(registry_);
}

void ECS::fixed_update(double delta_time) {}

void ECS::draw() { component::model_draw(registry_); }

void ECS::destroy_entity(entt::entity entity_id) {
	entities_.erase(entity_id);
	registry_.destroy(entity_id);
}

Entity& ECS::get_entity(entt::entity entity_id) const {
	return *entities_.at(entity_id);
}

void ECS::clear_entities() {
	entities_.clear();
	registry_.clear();
}
