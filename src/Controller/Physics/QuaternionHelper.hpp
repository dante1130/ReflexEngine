#pragma once

#include <glm.hpp>

/**
 * @author Daniel Rodic
 *
 * @class QuaternionHelper
 *
 * @brief Assists in the processing of quaternions
 *
 */
namespace QuaternionHelper {
/**
 * @brief Converts an euler rotation (in degrees) to a quaternion
 *
 * @param euler the rotation to convert (in degrees)
 * @return glm::quat
 */
glm::quat EulerToQuat(glm::vec3 euler);

/**
 * @brief Converts a quaternion to an euler rotation (to degrees)
 *
 * @param quat the quaterion to convert to euler (in degrees)
 * @return glm::vec3
 */
glm::vec3 QuatToEuler(glm::quat quat);

}  // namespace QuaternionHelper