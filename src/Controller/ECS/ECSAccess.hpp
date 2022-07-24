#pragma once

namespace ECSAccess {
/**
 * @brief Register the Entity class and all the componenents to Lua.
 */
void register_ecs();

/**
 * @brief Register the Entity class to Lua.
 */
void register_entity();

/**
 * @brief Register the Transform component to Lua.
 */
void register_transform_component();

/**
 * @brief Register the Model component to Lua.
 */
void register_model_component();

/**
 * @brief Register the Script component to Lua.
 */
void register_script_component();

/**
 * @brief Register the directional light component to Lua.
 */
void register_directional_light_component();

/**
 * @brief Register the point light component to Lua.
 */
void register_point_light_component();

/**
 * @brief Register the spot light component to Lua.
 */
void register_spot_light_component();

/**
 * @brief Register the mesh component to Lua.
 */
void register_mesh_component();

/**
 * @brief Register the terrain component to Lua.
 */
void register_terrain_component();
};  // namespace ECSAccess