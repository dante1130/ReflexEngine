#pragma once

#include <unordered_map>

#include "Affordance.hpp"

namespace Affordance {
using AffordanceMap = std::unordered_map<std::string, AffordancePtr>;

class AffordanceSystem {
public:
	AffordanceSystem() = default;

	void lua_access();

	auto add_affordance(std::string object, AffordancePtr affordance) -> void;
	auto get_affordance(std::string object) -> AffordancePtr;

private:
	AffordanceMap affordance_map_;
};
}  // namespace Affordance