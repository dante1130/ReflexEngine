#pragma once

namespace MathAccess {
/**
 * @brief Register the glm types and functions to Lua.
 */
void lua_access();

/**
 * @brief Register the glm::vec3 type to Lua.
 */
void register_vec3();

/**
 * @brief Register the glm::quat type to Lua.
 */
void register_quat();

/**
 * @brief Register the glm::vec3 and glm::quat types to Lua.
 */
void register_glm_functions();
};  // namespace MathAccess
