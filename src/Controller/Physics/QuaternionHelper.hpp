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

/**
 * @brief Rotates a 3 by 3 matrix with a quaternion
 *
 * @param matrix The matrix to rotate
 * @param quat The quaternion to rotate
 * @return glm::mat3x3
 */
glm::mat3x3 RotateMat3x3WithQuat(glm::mat3x3 matrix, glm::quat quat);

/**
 * @brief Specifically for rotating the inertia tensor in the opposite direction
 * of a quaternion
 *
 * @param matrix the inertia tensor you wish to rotate
 * @param quat the quaternion you want to rotate the inertia tensor
 * @return glm::mat3x3
 */
glm::mat3x3 RotateInertiaTensorOppositeQuat(glm::mat3x3 matrix, glm::quat quat);

/**
 * @brief Converts a quaternion to a rotation matrix
 *
 * @param quat the quaternion to convert
 * @return glm::mat3x3
 */
glm::mat3x3 QuatToRotationMatrix(glm::quat quat);

/**
 * @brief Converts a matrix 3x3 to a quaternion
 *
 * @param matrix the matrix to convert
 * @return glm::quat
 */
glm::quat Matrix3x3ToQuat(glm::mat3x3 matrix);

/**
 * @brief Rotates a vector in the direction of the quaternion
 *
 * @param vec the vector you want to rotate
 * @param quat the quaternion you want to rotate the vector with
 * @return glm::vec3
 */
glm::vec3 RotateVectorWithQuat(glm::vec3 vec, glm::quat quat);

/**
 * @brief Rotates a vector in the opposite direction of the quaternion
 *
 * @param vec the vector you want to rotate
 * @param quat the quaternion you want to rotate the vector with
 * @return glm::vec3
 */
glm::vec3 RotateVectorWithOppositeQuat(glm::vec3 vec, glm::quat quat);

}  // namespace QuaternionHelper