#pragma once

#include "Controller/ECS/Entity.hpp"

namespace statemachineComponentHelper {
void change_state(ECS& ecs, Reflex::Entity& entity, std::string new_state);
}
