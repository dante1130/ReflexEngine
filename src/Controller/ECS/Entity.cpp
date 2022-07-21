#include "Entity.hpp"

using namespace Reflex;

Entity::Entity(entt::entity entity_id, ECS* ecs)
    : entity_id_(entity_id), ecs_(ecs) {}

entt::entity Entity::get_entity_id() const { return entity_id_; }

entt::registry& Entity::get_registry() { return ecs_->get_registry(); }
