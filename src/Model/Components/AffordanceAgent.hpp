#pragma once

#include <string>

#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"
#include "Controller/Affordance/AffordanceUtility.hpp"
#include "Controller/ECS/Entity.hpp"

namespace Component {
struct AffordanceAgent {
	Affordance::Properties properties;
	Affordance::PropertiesWeight property_weights;
	Affordance::AffordanceUtility utility;
};
}  // namespace Component