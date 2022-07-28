#include "Entity.hpp"

#include <string>

using namespace Reflex;

Entity::Entity(const std::string& name, entt::entity entity_id, ECS* ecs)
    : name_(name), entity_id_(entity_id), ecs_(ecs) {
	if (name.empty()) {
		name_ = "Entity_" + std::to_string(static_cast<uint32_t>(entity_id));
	}
}

entt::entity Entity::get_entity_id() const { return entity_id_; }

entt::registry& Entity::get_registry() { return ecs_->get_registry(); }

const std::string& Entity::get_name() const { return name_; }
