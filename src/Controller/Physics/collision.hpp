#pragma once

#include "AI/singletons.h"
#include "Model/GameObject/BodyRigid.hpp"
#include "glm/glm.hpp"

namespace collisionResolution {
/**
 * @brief	Checks if a rigid body is colliding with another rigid body
 * @param	*rb	- The rigid body to test everything else against
 * @return	True if it collides with an object else false
 */
bool collides(BodyRigid *rb, glm::vec3 new_pos);

}  // namespace collisionResolution
