#pragma once

#include <string>
#include <unordered_set>

#include <sol/sol.hpp>

#include "Pattern/Composite.hpp"

namespace Affordance {
using Properties = std::unordered_set<std::string>;

class Affordance : public Pattern::Composite::Component {
private:
	std::string name_;
	Properties properties_;
};

class AffordanceComposite : Affordance {
private:
	std::vector<std::shared_ptr<Affordance>> affordances_;
};

class AffordanceLeaf : Affordance {
private:
	sol::function function_;
};

};  // namespace Affordance