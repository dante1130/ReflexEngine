#pragma once

#include <glm/glm.hpp>
#include <iostream>

/*********************************************************************************************
 * Moves an object located at curpos and travelling at curVelocity towards
 *targetPos. This    * function changes the curPos and curVelocity to steer it
 *towards targetPos over time. The   * time factor is specified by timeElasped
 *which should be the current time in the game loop  * timer. 20ms is a
 *reasonable update time.                                                   *
 * Pre: all vars are assigned values. * Post: curPos and curVelocity are updated
 *to incrementally move towards targetPos. curPos   * will be equal to targetPos
 *if the object has reached the target.                     * Returns: true if
 *target has reached targetPos, otherwise false.                            *
 *********************************************************************************************/
namespace ai_movement {
/**
 * @brief    Moves to targets position
 * @param    curPos      - current position
 * @param    targetPos   - target position
 * @param    curVelocity - current veloctiy
 * @param    timeElapsed - time elapsed to calculate movement
 * @param    offset      - offset (how close to get to the target)
 * @return   bool        - true if at target
 */
bool moveTo(glm::vec2& curPos, const glm::vec2& targetPos,
            glm::vec2 curVelocity, double timeElapsed, double offset = 0);

/**
 * @brief    Moves away from a persuer position
 * @param    curPos      - current position
 * @param    pursuerPos  - persuers position
 * @param    curVelocity - current veloctiy
 * @param    timeElapsed - time elapsed to calculate movement
 * @param    flee speed  - How fast to flee
 * @return   bool        - true if in panic range
 */
bool flee(glm::vec2& curPos, const glm::vec2& pursuerPos,
          glm::vec2& curVelocity, double fleeSpeed, double timeElapsed);

/**
 * @brief    Persues a target
 * @param    evaderPos          - evader position
 * @param    pursuerPos         - pursuer pos
 * @param    evaderVelocity     - evader velocity
 * @param    pursuerVelocity    - persuer velocity
 * @param    timeElapsed        - time elapsed
 * @param    offset
 * @return   bool
 */
void pursue(const glm::vec2& evaderPos, glm::vec2& pursuerPos,
            const glm::vec2& evaderVelocity, glm::vec2& pursuerVelocity,
            double timeElapsed, double offset);

/**
 * @brief    Moves away from a persuer position
 * @param    evaderPos          - evader position
 * @param    pursuerPos         - pursuer pos
 * @param    evaderVelocity     - evader velocity
 * @param    pursuerVelocity    - persuer velocity
 * @param    timeElapsed        - time elapsed
 * @return   bool               - true if within pursuer area
 */
bool evade(glm::vec2& evaderPos, const glm::vec2& pursuerPos,
           glm::vec2& evaderVelocity, const glm::vec2& pursuerVelocity,
           double timeElapsed);

/**
 * @brief    Moves away from a persuer position
 * @param    patroller          - patroller position
 * @param    target             - target position
 * @param    patrollerVel       - patroller veloctiy
 * @param    coneDistance       - view cone distance
 * @param    flee coneRadius    - cone radius
 * @return   bool               - true if can see the target
 */
bool seeTarget(const glm::vec2& patroller, const glm::vec2& target,
               const glm::vec2& patrollerVel, float coneDistance,
               float coneRadius);

}  // namespace ai_movement
