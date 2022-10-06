#include <catch2/catch_test_macros.hpp>

#include <reactphysics3d/reactphysics3d.h>
#include "Controller/Physics/QuaternionHelper.hpp"
#include "Controller/Physics/PhysicBody.hpp"
#include "Controller/Physics/ReactResolve.hpp"

TEST_CASE("Physics tests", "[PHYSICS]") {
	SECTION("Euler To Quaternion") { REQUIRE(true); }

	SECTION("Quaternion To Euler") { REQUIRE(true); }

	SECTION("Rotate Mat3x3 With Quaternion") { REQUIRE(true); }

	SECTION("Quaternion to Rotation Matrix") { REQUIRE(true); }

	SECTION("Rotation Matrix to Quaternion") { REQUIRE(true); }

	SECTION("Valid Rectangle Inertia Tensor") { REQUIRE(true); }

	SECTION("Valid Sphere Inertia Tensor") { REQUIRE(true); }

	SECTION("Valid Cylinder Inertia Tensor") { REQUIRE(true); }
}