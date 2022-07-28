#pragma once

#include "Controller/ECS/Entity.hpp"

#include <string>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

namespace statemachineComponentHelper {
/**
 * @brief   Changes the state of the statemachine. Calls relevant entry & exit
 * methods
 *
 * @param &ecs          - The ecs
 * @param &entity       - The entity
 * @param new_state     - The state you want to change too
 */
void change_state(ECS& ecs, Reflex::Entity& entity, std::string new_state);

/**
 * @brief   Sends a message to a directed target (entity) with a statemachine
 *
 * @param &ecs          - The ecs
 * @param &entity       - The entity
 * @param reciever      - The id of the recieve (id of statemachine)
 * @param msg           - The message you want to send
 * @param extraInfo     - sol table of extra info to send
 */
void send_message(ECS& ecs, Reflex::Entity& entity, int reciever, int msg,
                  sol::table extraInfo);

/**
 * @brief   Same as send_message except sends an area message to any entity in
 * the designated area
 *
 * @param &ecs          - The ecs
 * @param &entity       - The entity
 * @param range         - How close another entity should be to recieve a
 * message
 * @param msg           - The message you want to send
 * @param extraInfo     - sol table of extra info to send
 */
void send_area_message(ECS& ecs, Reflex::Entity& entity, float range, int msg,
                       sol::table extraInfo);

/**
 * @brief Looks for an enemy within arc & range, will add to the sol table
 * variables, such as info about the target if it spots one (e.g., target_id)
 *
 * @param &ecs          - The ecs
 * @param &entity       - The entity
 * @param arc           - The arc of the view
 * @param distance      - How far infront from transfrom it can see
 */
void look_for_enemy(ECS& ecs, Reflex::Entity& entity, float arc,
                    float distance);

/**
 * @brief Uses pathfinding technique (aStar) to generate waypoints. These are
 * stored in the statemachines sol table. (TOO BE COMPLETED)
 *
 * @param &ecs                  - The ecs
 * @param &entity               - The entity
 * @param currentPos            - Current position to generate the waypoints
 * from
 * @param targetPos             - Target position which is the destination
 * @param terrain_to_pathfind   - The name of the terrain which you want to
 * pathfind across
 */
void generate_waypoints(ECS& ecs, Reflex::Entity& entity, glm::vec3 currentPos,
                        glm::vec3 targetPos, std::string terrain_to_pathfind);

/**
 * @brief Follows a generated waypoint from a pathfinding algorithm (UNTESTED)
 *
 * @param &entity               - The entity
 * @param use_physics_movement  - If it should add velocity compared to just
 * setting the position
 * @param speed         - The speed of movement
 * @param terrain_name  - The name of the terrain (if you want to set height
 * (not available with physics movement (implement yourself)))
 */
void follow_generated_waypoints(Reflex::Entity& entity,
                                bool use_physics_movement, float speed,
                                std::string terrain_name);

/**
 * @brief   Follows a waypoint by setting the transform
 *
 * @param &entity       - The entity
 * @param targetPos     - The target position you are heading too
 * @param speed         - The speed of movement
 * @param terrain_name  - The name of the terrain (if you want to set height)
 * position to terrain (can leave empty)
 */
void follow_waypoint(Reflex::Entity& entity, glm::vec3 targetPos, float speed,
                     std::string terrain_name);

/**
 * @brief   Follows a waypoint by setting the transform. Only sets velocity of
 * physics component (NEEDS TO BE IMPLEMENTED WHEN PHYSICS COMPONENT COMPLETED)
 *
 * @param &entity       - The entity
 * @param targetPos     - The target position you are heading too
 * @param speed         - The speed of movement
 */
void follow_waypoint_physics(Reflex::Entity& entity, glm::vec3 targetPos,
                             float speed);

}  // namespace statemachineComponentHelper
