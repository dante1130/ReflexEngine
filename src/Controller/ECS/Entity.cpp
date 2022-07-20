#include "Entity.hpp"

Entity::Entity(entt::entity entity_id, ECS* ecs)
    : entity_id_(entity_id), ecs_(ecs) {}

entt::entity Entity::get_entity_id() const { return entity_id_; }
