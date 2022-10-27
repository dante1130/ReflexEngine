#pragma once

#include "Controller/Affordance/Affordance.hpp"

using Affordance::Properties;
using Affordance::PropertiesWeight;

namespace Component {
struct AffordanceAgent {
	Properties properties;
	PropertiesWeight property_weights;
};
}  // namespace Component