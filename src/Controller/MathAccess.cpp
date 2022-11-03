#include "MathAccess.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "LuaManager.hpp"

void MathAccess::lua_access() {
	register_vec3();
	register_quat();
	register_glm_functions();
}

void MathAccess::register_vec3() {
	auto& lua = LuaManager::get_instance().get_state();

	auto math_table = lua["Math"].get_or_create<sol::table>();

	auto vec3_type = math_table.new_usertype<glm::vec3>(
	    "vec3",
	    sol::constructors<glm::vec3(), glm::vec3(float, float, float)>());

	vec3_type["x"] = &glm::vec3::x;
	vec3_type["y"] = &glm::vec3::y;
	vec3_type["z"] = &glm::vec3::z;
}

void MathAccess::register_quat() {
	auto& lua = LuaManager::get_instance().get_state();

	auto math_table = lua["Math"].get_or_create<sol::table>();

	auto quat_type = math_table.new_usertype<glm::quat>(
	    "quat", sol::constructors<glm::quat(),
	                              glm::quat(float, float, float, float)>());

	quat_type["x"] = &glm::quat::x;
	quat_type["y"] = &glm::quat::y;
	quat_type["z"] = &glm::quat::z;
	quat_type["w"] = &glm::quat::w;
}

void MathAccess::register_glm_functions() {
	auto& lua = LuaManager::get_instance().get_state();

	auto math_table = lua["Math"].get_or_create<sol::table>();

	math_table["add"] = sol::overload(
	    [](const glm::vec3& a, const glm::vec3& b) { return a + b; },
	    [](const glm::quat& a, const glm::quat& b) { return a + b; });

	math_table["sub"] = sol::overload(
	    [](const glm::vec3& a, const glm::vec3& b) { return a - b; },
	    [](const glm::quat& a, const glm::quat& b) { return a - b; });

	math_table["mul"] = sol::overload(
	    [](const glm::vec3& a, const glm::vec3& b) { return a * b; },
	    [](const glm::quat& a, const glm::quat& b) { return a * b; },
	    [](const glm::vec3& a, const glm::quat& b) { return a * b; },
	    [](const glm::quat& a, const glm::vec3& b) { return a * b; },
	    [](const glm::vec3& a, float b) { return a * b; },
	    [](float a, const glm::vec3& b) { return a * b; });

	math_table["div"] = sol::overload(
	    [](const glm::vec3& a, const glm::vec3& b) { return a / b; },
	    [](const glm::vec3& a, float b) { return a / b; },
	    [](float a, const glm::vec3& b) { return a / b; });

	math_table["dot"] = sol::overload(
	    [](const glm::vec3& a, const glm::vec3& b) { return glm::dot(a, b); },
	    [](const glm::quat& a, const glm::quat& b) { return glm::dot(a, b); });

	math_table["cross"] = sol::overload(
	    [](const glm::vec3& a, const glm::vec3& b) { return glm::cross(a, b); },
	    [](const glm::quat& a, const glm::quat& b) {
		    return glm::cross(a, b);
	    });

	math_table["length"] =
	    sol::overload([](const glm::vec3& a) { return glm::length(a); },
	                  [](const glm::quat& a) { return glm::length(a); });

	math_table["distance"] =
	    sol::overload([](const glm::vec3& a, const glm::vec3& b) {
		    return glm::distance(a, b);
	    });

	math_table["normalize"] =
	    sol::overload([](const glm::vec3& a) { return glm::normalize(a); },
	                  [](const glm::quat& a) { return glm::normalize(a); });

	math_table["angle"] = [](const glm::vec3& a, const glm::vec3& b) {
		auto angle =
		    glm::degrees(glm::angle(glm::normalize(a), glm::normalize(b)));
		if (b.z > 0) {
			angle *= -1;
		}
		return angle;
	};

	math_table["sin"] =
	    sol::overload([](float a) { return glm::sin(a); },
	                  [](const glm::vec3& a) { return glm::sin(a); });

	math_table["cos"] =
	    sol::overload([](float a) { return glm::cos(a); },
	                  [](const glm::vec3& a) { return glm::cos(a); });

	math_table["tan"] =
	    sol::overload([](float a) { return glm::tan(a); },
	                  [](const glm::vec3& a) { return glm::tan(a); });

	math_table["euler_to_quat"] = [](const glm::vec3& euler) {
		return glm::quat(euler);
	};

	math_table["quat_to_euler"] = [](const glm::quat& quat) {
		return glm::eulerAngles(quat);
	};

	math_table["degrees"] = [](float radians) { return glm::degrees(radians); };

	math_table["radians"] = [](float degrees) { return glm::radians(degrees); };
}