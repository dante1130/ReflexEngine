#include <string>
#include "Controller/ECS/Entity.hpp"

/**
 * @author Daniel Rodic
 * @brief Enables the loading in of colliders through an OBJ file
 */
namespace loadOBJColliderData {
/**
 * @brief Provides lua access to relavent namespace functions
 */
void lua_access();

/**
 * @brief Adds collider data found in an OBJ file to a rigidbody
 *
 * @param entity the entity to add the collider data too
 * @param file  The OBJ file which includes the collider data
 */
void load_obj_collider_data(Reflex::Entity &entity, const std::string &file);

}  // namespace loadOBJColliderData
