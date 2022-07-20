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
 * @param entity_id The entity ID to initialize the script component.
 *
 * @pre The script component members must be set.
 */
void script_init(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Initializes the directional light component of an entity.
 *
 * @param registry The ECS registry.
 * @param entity_id The entity ID to initialize the directional light component.
 */
void directional_light_init(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Initializes the point light component of an entity.
 *
 * @param registry The ECS registry.
 * @param entity_id The entity ID to initialize the point light component.
 */
void point_light_init(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Initializes the spot light component of an entity.
 *
 * @param registry The ECS registry.
 * @param entity_id The entity ID to initialize the spot light
 * component.
 */
void spot_light_init(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Update the script components.
 *
 * @param registry The ECS registry.
 *
 * @pre The script components must be initialized.
 */
void script_update(entt::registry& registry);

/**
 * @brief Update the directional light components.
 *
 * @param registry The ECS registry.
 */
void directional_light_update(entt::registry& registry);

/**
 * @brief Update the point light components.
 *
 * @param registry The ECS registry.
 */
void point_light_update(entt::registry& registry);

/**
 * @brief Update the spot light components.
 *
 * @param registry The ECS registry.
 */
void spot_light_update(entt::registry& registry);
};  // namespace component
