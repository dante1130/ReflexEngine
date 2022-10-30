#pragma once

#include <string>

#include <sol/sol.hpp>

namespace Component {
/**
 * @author Andrew Ho
 * @struct Affordance
 * @brief The affordance component represents an object that has properties, the
 * context or state of the object is also included in the component.
 */
struct Affordance {
	/// The name of the object, referenced to the affordance system.
	std::string object_name;
	/// The lua script to initialize the affordance.
	std::string lua_script;
	/// The context variables of the object.
	sol::table context;

	Affordance() = default;

	Affordance(const Affordance&) = default;

	explicit Affordance(const std::string& object_name,
	                    const std::string& lua_script)
	    : object_name(object_name), lua_script(lua_script) {}
};
}  // namespace Component