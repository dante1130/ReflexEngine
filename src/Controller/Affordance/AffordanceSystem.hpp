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
	auto get_instance() -> AffordanceSystem&;

	auto lua_access() -> void;

	auto add_affordance(std::string object, AffordancePtr affordance) -> void;
	auto get_affordance(const std::string& object) -> AffordancePtr;

private:
	AffordanceSystem() = default;

	AffordanceMap affordance_map_;
};
}  // namespace Affordance