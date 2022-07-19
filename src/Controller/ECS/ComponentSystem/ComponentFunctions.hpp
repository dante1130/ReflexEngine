#pragma once

#include <entt/entt.hpp>

namespace component {
/**
 * @brief Passes the draw call of the model component to the renderer.
 *
 * @param registry The ECS registry.
 * @pre Both the transform and the model component must be present in an entity.
 */
void model_draw(entt::registry& registry);

void script_init(entt::registry& registry, entt::entity entity_id);
void script_update(entt::registry& registry);
};  // namespace component
