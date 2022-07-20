#pragma once

#include <entt/entt.hpp>

namespace component {
/**
 * @brief Passes the draw call of the model component to the renderer.
 *
 * @param registry The ECS registry.
 *
 * @pre Both the transform and the model component must be present in an entity.
 */
void model_draw(entt::registry& registry);

/**
 * @brief Initializes the script component of an entity.
 *
 * @param registry The ECS registry.
 * @param entity_id The entity ID of the entity to initialize the script
 * component on.
 *
 * @pre The script component members must be set.
 */
void script_init(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Updates all the script components.
 *
 * @param registry The ECS registry.
 *
 * @pre The script components must be initialized.
 */
void script_update(entt::registry& registry);
};  // namespace component
