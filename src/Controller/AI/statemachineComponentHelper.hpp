#pragma once

#include "Controller/ECS/Entity.hpp"

#include <string>
#include <glm/glm.hpp>

namespace statemachineComponentHelper {
void change_state(ECS& ecs, Reflex::Entity& entity, std::string new_state);

// void send_message(entt::registry& registry, Reflex::Entity& entity, int
// sender,
//                   int reciever, int msg, double dispatchTime,
//                   sol::table extraInfo);

// void look_for_enemy(entt::registry& registry, Reflex::Entity& entity);

// void pathfind(Reflex::Entity& entity, glm::vec3 currentPos, glm::vec3
// targetPos)

}  // namespace statemachineComponentHelper
