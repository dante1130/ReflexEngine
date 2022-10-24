#pragma once

#include "Affordance.hpp"

namespace Affordance {
/**
 * @brief Find the best affordance from a list of affordances.
 * Determines the best affordance by comparing the properties of the affordances
 * with the given properties. The properties are weighted by the given weight,
 * if it is not given, the weight is 1.
 *
 * @param affordances The list of affordances to search.
 * @param properties The properties to search for.
 * @param properties_weight The weight of each property.
 * @return AffordancePtr The best affordance
 */
auto find_affordance(const AffordancePtr& affordances,
                     const Properties& properties,
                     const PropertiesWeight& properties_weight)
    -> AffordancePtr;
};  // namespace Affordance