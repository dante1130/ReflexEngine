#include "QuaternionHelper.hpp"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <iostream>

glm::quat QuaternionHelper::EulerToQuat(glm::vec3 euler) {
	glm::quat quaternion = glm::quat(0, 0, 0, 0);

	glm::vec3 rot_radians = glm::radians(euler);

	double cy = glm::cos(rot_radians.z * 0.5);  // cosine applied on yaw
	double sy = glm::sin(rot_radians.z * 0.5);  // sine applied on yaw
	double cp = glm::cos(rot_radians.y * 0.5);  // cosine applied on pitch
	double sp = glm::sin(rot_radians.y * 0.5);  // sine applied on pitch
	double cr = glm::cos(rot_radians.x * 0.5);  // cosine applied on roll
	double sr = glm::sin(rot_radians.x * 0.5);  // sine applied on roll

	quaternion.w = cr * cp * cy + sr * sp * sy;
	quaternion.x = sr * cp * cy - cr * sp * sy;
	quaternion.y = cr * sp * cy + sr * cp * sy;
	quaternion.z = cr * cp * sy - sr * sp * cy;

	return quaternion;
}

glm::vec3 QuaternionHelper::QuatToEuler(glm::quat quat) {
	return glm::degrees(glm::eulerAngles(quat));
}

glm::mat3x3 QuaternionHelper::RotateMat3x3WithQuat(glm::mat3x3 matrix,
                                                   glm::quat quat) {
	glm::quat result = glm::toQuat(matrix);
	result = result * quat;
	return glm::toMat3(result);
}

glm::mat3x3 QuaternionHelper::QuatToRotationMatrix(glm::quat quat) {
	return glm::toMat3(quat);
}

glm::quat QuaternionHelper::Matrix3x3ToQuat(glm::mat3x3 matrix) {
	return glm::toQuat(matrix);
}

glm::vec3 QuaternionHelper::RotateVectorWithQuat(glm::vec3 vec,
                                                 glm::quat quat) {
	glm::quat vec_q = glm::quat(0, vec.x, vec.y, vec.z);
	glm::quat quat_m = glm::quat(quat.w, -quat.x, -quat.y, -quat.z);

	glm::quat result = quat * vec_q;
	result = result * quat_m;

	return glm::vec3(result.x, result.y, result.z);
}