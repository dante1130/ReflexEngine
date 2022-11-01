#pragma once

namespace ECSAccess {
/**
 * @brief Register the Entity class and all the componenents to Lua.
 */
void register_ecs();

/**
 * @brief Register the ECS class to Lua.
 */
void register_registry();

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
 * @brief Register the md2 animation component to Lua.
 */
void register_md2_component();

/**
 * @brief Register the terrain component to Lua.
 */
void register_terrain_component();

/**
 * @brief Register the statemachine component to Lua.
 */
void register_statemachine_component();

/**
 * @brief Register the rigidbody component to Lua.
 */
void register_rigidbody_component();

/**
 * @brief Register the affordance agent component to Lua.
 */
auto register_affordance_agent_component() -> void;

};  // namespace ECSAccess
