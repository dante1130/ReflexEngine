#include <catch2/catch_test_macros.hpp>

#include <reactphysics3d/reactphysics3d.h>
#include "Controller/Physics/QuaternionHelper.hpp"
#include "Controller/Physics/PhysicBody.hpp"
#include "Controller/Physics/ReactResolve.hpp"
#include "Model/Components/RigidBody.hpp"

#include <glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

TEST_CASE("Physics tests", "[PHYSICS]") {
	SECTION("Euler To Quaternion") {
		glm::quat quat = QuaternionHelper::EulerToQuat(glm::vec3(36.5, 42, 0));

		REQUIRE(quat.x < 0.29237);
		REQUIRE(quat.x > 0.29235);
		REQUIRE(quat.y < 0.34035);
		REQUIRE(quat.y > 0.34033);
		REQUIRE(quat.z < -0.11221);
		REQUIRE(quat.z > -0.11223);
		REQUIRE(quat.w < 0.88663);
		REQUIRE(quat.w > 0.88661);
	}

	SECTION("Quaternion To Euler") {
		glm::vec3 euler = QuaternionHelper::QuatToEuler(
		    glm::quat(0.7071068, 0, 0.7071068, 0));

		REQUIRE(euler.x < 0.001);
		REQUIRE(euler.x > -0.001);
		REQUIRE(euler.y < 90.001);
		REQUIRE(euler.y > 89.999);
		REQUIRE(euler.z < 0.001);
		REQUIRE(euler.z > -0.001);
	}

	SECTION("Rotate Mat3x3 With Quaternion - Simple") {
		glm::mat3x3 mat3x3;
		mat3x3[0][0] = -1;
		mat3x3[0][1] = 0;
		mat3x3[0][2] = 0;
		mat3x3[1][0] = 0;
		mat3x3[1][1] = 1;
		mat3x3[1][2] = 0;
		mat3x3[2][0] = 0;
		mat3x3[2][1] = 0;
		mat3x3[2][2] = -1;

		glm::quat quat = glm::quat(1, 0, 0, 0);

		glm::mat3x3 result3x3 =
		    QuaternionHelper::RotateMat3x3WithQuat(mat3x3, quat);

		REQUIRE(result3x3[0][0] == -1);
		REQUIRE(result3x3[0][1] == 0);
		REQUIRE(result3x3[0][2] == 0);
		REQUIRE(result3x3[1][0] == 0);
		REQUIRE(result3x3[1][1] == 1);
		REQUIRE(result3x3[1][2] == 0);
		REQUIRE(result3x3[2][0] == 0);
		REQUIRE(result3x3[2][1] == 0);
		REQUIRE(result3x3[2][2] == -1);
	}

	SECTION("Rotate Mat3x3 With Quaternion - Complex") {
		glm::mat3x3 mat3x3;
		mat3x3[0][0] = -1;
		mat3x3[0][1] = 0;
		mat3x3[0][2] = 0;
		mat3x3[1][0] = 0;
		mat3x3[1][1] = 1;
		mat3x3[1][2] = 0;
		mat3x3[2][0] = 0;
		mat3x3[2][1] = 0;
		mat3x3[2][2] = -1;

		glm::quat quat = glm::quat(0.7071068, 0, 0.7071068, 0);

		glm::mat3x3 result3x3 =
		    QuaternionHelper::RotateMat3x3WithQuat(mat3x3, quat);

		REQUIRE(result3x3[0][0] < 0.00001);
		REQUIRE(result3x3[0][0] > -0.00001);
		REQUIRE(result3x3[0][1] == 0);
		REQUIRE(result3x3[0][2] < 1.00001);
		REQUIRE(result3x3[0][2] > 0.99999);
		REQUIRE(result3x3[1][0] == 0);
		REQUIRE(result3x3[1][1] == 1);
		REQUIRE(result3x3[1][2] == 0);
		REQUIRE(result3x3[2][0] < -0.99999);
		REQUIRE(result3x3[2][0] > -1.00001);
		REQUIRE(result3x3[2][1] == 0);
		REQUIRE(result3x3[2][2] < 0.00001);
		REQUIRE(result3x3[2][2] > -0.00001);
	}

	SECTION("Rotate point With Quaternion - Complex") {
		glm::vec3 point = glm::vec3(1, 0, 0);
		glm::quat quat = glm::quat(0.7071068, 0.0, 0.7071068, 0.0);

		glm::vec3 result = QuaternionHelper::RotateVectorWithQuat(point, quat);

		REQUIRE(result.x == 0);
		REQUIRE(result.y == 0);
		REQUIRE(result.z > -1.0001);
		REQUIRE(result.z < -0.9999);
	}

	SECTION("Correct J calc result") {
		glm::vec3 point = glm::vec3(-0.5, 0.24, 2);
		glm::vec3 normal = glm::vec3(0.7071068, -0.7071068, 0);
		glm::mat3x3 mat3x3;
		mat3x3[0][0] = -1;
		mat3x3[0][1] = 0.9;
		mat3x3[0][2] = 0.56;
		mat3x3[1][0] = 0;
		mat3x3[1][1] = 1;
		mat3x3[1][2] = 1.5;
		mat3x3[2][0] = 0;
		mat3x3[2][1] = 0.345;
		mat3x3[2][2] = -1;

		float result = PhysicsBody::J_calc(point, normal, mat3x3);

		REQUIRE(result > 1.1879);
		REQUIRE(result < 1.1880);
	}

	SECTION("Valid Rectangle Inertia Tensor") {
		glm::mat3x3 inertia_tensor = glm::mat3x3(0);
		REQUIRE(inertia_tensor[0][0] == 0.5);
		REQUIRE(inertia_tensor[1][0] == 0);
		REQUIRE(inertia_tensor[2][0] == 0);
		REQUIRE(inertia_tensor[0][1] == 0);
		REQUIRE(inertia_tensor[1][1] == 0.5);
		REQUIRE(inertia_tensor[2][1] == 0);
		REQUIRE(inertia_tensor[0][2] == 0);
		REQUIRE(inertia_tensor[1][2] == 0);
		REQUIRE(inertia_tensor[2][2] == 0.5);
	}

	SECTION("Valid Sphere Inertia Tensor") { REQUIRE(true); }

	SECTION("Valid Cylinder Inertia Tensor") { REQUIRE(true); }
}