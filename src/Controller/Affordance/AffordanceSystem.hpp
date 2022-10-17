#pragma once

#include <unordered_map>

#include "Affordance.hpp"

namespace Affordance {
using AffordanceMap = std::unordered_map<std::string, AffordancePtr>;

/**
 * @class AffordanceSystem
 * @brief The AffordanceSystem class is a singleton class that contains all the
 * affordances that can be applied onto an object.
 */
class AffordanceSystem {
public:
	/**
	 * @brief Get the instance of the AffordanceSystem.
	 *
	 * @return AffordanceSystem&
	 */
	static auto get_instance() -> AffordanceSystem&;

	/**
	 * @brief Expose the AffordanceSystem and the Affordance classes to Lua.
	 */
	auto lua_access() -> void;

	/**
	 * @brief Add an affordance to the system.
	 *
	 * @param object The name of the object to associate the affordances to
	 * @param affordance The affordances
	 */
	auto add_affordance(std::string object, AffordancePtr affordance) -> void;

	/**
	 * @brief Get the affordance composite associated with the object.
	 *
	 * @param object
	 * @return AffordancePtr The affordance composite
	 */
	auto get_affordance(const std::string& object) -> AffordancePtr;

private:
	AffordanceSystem() = default;

	AffordanceMap affordance_map_;
};
}  // namespace Affordance