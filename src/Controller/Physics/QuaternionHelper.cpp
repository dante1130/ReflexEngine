#include "QuaternionHelper.hpp"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

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
	glm::quat result = Matrix3x3ToQuat(matrix);
	result = result * quat;
	return QuatToRotationMatrix(result);
}

glm::mat3x3 QuaternionHelper::QuatToRotationMatrix(glm::quat quat) {
	glm::mat3x3 matrix;

	matrix[0][0] = 2 * (pow(quat.w, 2) + pow(quat.x, 2)) - 1;
	matrix[0][1] = 2 * (quat.x * quat.y) - (quat.w * quat.z);
	matrix[0][2] = 2 * (quat.x * quat.z + quat.w * quat.y);

	matrix[1][0] = 2 * (quat.x * quat.y + quat.w * quat.z);
	matrix[1][1] = 2 * (pow(quat.w, 2) + pow(quat.y, 2)) - 1;
	matrix[1][2] = 2 * (quat.y * quat.z - quat.w * quat.x);

	matrix[2][0] = 2 * (quat.x * quat.z - quat.w * quat.y);
	matrix[2][1] = 2 * (quat.y * quat.z + quat.w * quat.x);
	matrix[2][2] = 2 * (pow(quat.w, 2) + pow(quat.z, 2)) - 1;

	return matrix;
}

glm::quat QuaternionHelper::Matrix3x3ToQuat(glm::mat3x3 a) {
	glm::quat q;

	float trace = a[0][0] + a[1][1] + a[2][2];
	if (trace > 0) {
		float s = 0.5f / sqrtf(trace + 1.0f);
		q.w = 0.25f / s;
		q.x = (a[2][1] - a[1][2]) * s;
		q.y = (a[0][2] - a[2][0]) * s;
		q.z = (a[1][0] - a[0][1]) * s;
	} else {
		if (a[0][0] > a[1][1] && a[0][0] > a[2][2]) {
			float s = 2.0f * sqrtf(1.0f + a[0][0] - a[1][1] - a[2][2]);
			q.w = (a[2][1] - a[1][2]) / s;
			q.x = 0.25f * s;
			q.y = (a[0][1] + a[1][0]) / s;
			q.z = (a[0][2] + a[2][0]) / s;
		} else if (a[1][1] > a[2][2]) {
			float s = 2.0f * sqrtf(1.0f + a[1][1] - a[0][0] - a[2][2]);
			q.w = (a[0][2] - a[2][0]) / s;
			q.x = (a[0][1] + a[1][0]) / s;
			q.y = 0.25f * s;
			q.z = (a[1][2] + a[2][1]) / s;
		} else {
			float s = 2.0f * sqrtf(1.0f + a[2][2] - a[0][0] - a[1][1]);
			q.w = (a[1][0] - a[0][1]) / s;
			q.x = (a[0][2] + a[2][0]) / s;
			q.y = (a[1][2] + a[2][1]) / s;
			q.z = 0.25f * s;
		}
	}

	return q;
}