#pragma once

#include <unordered_map>

#include "Affordance.hpp"

namespace Affordance {
using AffordanceMap = std::unordered_map<std::string, AffordancePtr>;

/**
 * @author Andrew Ho
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
	 * @brief Set an object to an affordance composite in the system.
	 *
	 * @param object The name of the object to associate the affordances to
	 * @param affordance The affordances
	 */
	auto set_affordance(std::string object, AffordancePtr affordance) -> void;

	/**
	 * @brief Get the affordance composite associated with the object.
	 *
	 * @param object
	 * @return AffordancePtr The affordance composite
	 */
	auto get_affordance(const std::string& object) -> AffordancePtr;

	/**
	 * @brief Breadth first search through the affordance tree and returns the
	 * affordance that has the given properties.
	 *
	 * @param properties
	 * @return std::vector<AffordancePtr>
	 */
	auto find_objects(const Properties& properties)
	    -> std::vector<AffordancePtr>;

	/**
	 * @brief Clear the affordance system. Used when the simulation is exited.
	 */
	auto clear_affordances() -> void;

private:
	AffordanceSystem() = default;

	/// The map of affordances, associating between an object and its
	/// affordances
	AffordanceMap affordance_map_;
};
}  // namespace Affordance
