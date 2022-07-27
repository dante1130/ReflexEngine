#pragma once

#include <entt/entt.hpp>

#include <Controller/ECS/ECS.hpp>

namespace System {
/**
 * @brief Passes the draw call of the model component to the renderer.
 *
 * @param registry The ECS registry.
 *
 * @pre Both the transform and the model component must be present in an entity.
 */
void draw_model(entt::registry& registry);

/**
 * @brief Passes the draw call of the mesh component to the renderer.
 *
 * @param registry The ECS registry.
 */
void draw_mesh(entt::registry& registry);

/**
 * @brief Passes the draw call of the terrain component to the renderer.
 *
 * @param registry The ECS registry.
 */
void draw_terrain(entt::registry& registry);

/**
 * @brief Initializes the script component of an entity.
 *
 * @param ecs The ECS class.
 * @param entity_id The entity ID to initialize the script component.
 *
 * @pre The script component members must be set.
 */
void init_script(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Initializes the directional light component of an entity.
 *
 * @param registry The ECS registry.
 * @param entity_id The entity ID to initialize the directional light component.
 */
void init_directional_light(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Initializes the point light component of an entity.
 *
 * @param registry The ECS registry.
 * @param entity_id The entity ID to initialize the point light component.
 */
void init_point_light(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Initializes the spot light component of an entity.
 *
 * @param registry The ECS registry.
 * @param entity_id The entity ID to initialize the spot light
 * component.
 */
void init_spot_light(entt::registry& registry, entt::entity entity_id);

/**
 * @brief Update the script components.
 *
 * @param ecs The ECS class.
 *
 * @pre The script components must be initialized.
 */
void update_script(entt::registry& registry);

/**
 * @brief Update the directional light components.
 *
 * @param registry The ECS registry.
 */
void update_directional_light(entt::registry& registry);

/**
 * @brief Update the point light components.
 *
 * @param registry The ECS registry.
 */
void update_point_light(entt::registry& registry);

/**
 * @brief Update the spot light components.
 *
 * @param registry The ECS registry.
 */
void update_spot_light(entt::registry& registry);

/**
 * @brief Deletes any entities that has a Remove component.
 *
 * @param ecs The ECS class.
 */
void update_remove(ECS& ecs);
};  // namespace System
