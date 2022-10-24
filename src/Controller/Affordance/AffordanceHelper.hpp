#pragma once

#include "Affordance.hpp"

namespace Affordance {
auto find_affordance(AffordancePtr affordances, const Properties& properties,
                     const PropertiesWeight& properties_weight)
    -> AffordancePtr;
};  // namespace Affordance