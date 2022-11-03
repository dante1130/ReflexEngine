#pragma once

#include "Affordance.hpp"
#include "Controller/ECS/Entity.hpp"

namespace Affordance {
/**
 * @brief Find the best affordance from a list of affordances.
 * Determines the best affordance by comparing the properties of the
 * affordances with the given properties. The properties are weighted by the
 * given weight, if it is not given, the weight is 1.
 *
 * @param affordances The list of affordances to search.
 * @param properties The properties to search for.
 * @param properties_weight The weight of each property.
 * @return AffordancePtr The best affordance
 */
auto find_affordance(const AffordancePtr& affordances,
                     const Properties& properties,
                     const PropertiesWeight& properties_weight = {})
    -> AffordancePtr;

/**
 * @brief Breadth first search for an affordance with the given properties.
 *
 * @param affordances The affordances to search.
 * @param properties The properties to search for.
 * @return bool
 */
auto has_affordance(const AffordancePtr& affordances,
                    const Properties& properties) -> bool;

/**
 * @brief Evaluates the best utility state for the affordance agent.
 *
 * @param entity The affordance agent entity.
 */
auto evaluate_utility(const Reflex::Entity& entity) -> void;
};  // namespace Affordance