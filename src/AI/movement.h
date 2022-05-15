#ifndef __MOVEMENT_H
#define __MOVEMENT_H

#include <glm/glm.hpp>

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
bool moveTo(glm::vec2& curPos, const glm::vec2& targetPos,
            glm::vec2& curVelocity, double timeElapsed, double offset = 0);

bool flee(glm::vec2& curPos, const glm::vec2& pursuerPos,
          glm::vec2& curVelocity, double fleeSpeed, double timeElapsed);

void pursue(const glm::vec2& evaderPos, glm::vec2& pursuerPos,
            const glm::vec2& evaderVelocity, glm::vec2& pursuerVelocity,
            double timeElapsed, double offset);

bool evade(glm::vec2& evaderPos, const glm::vec2& pursuerPos,
           glm::vec2& evaderVelocity, const glm::vec2& pursuerVelocity,
           double timeElapsed);

bool seeTarget(const glm::vec2& patroller, const glm::vec2& target,
               const glm::vec2& patrollerVel, float coneDistance,
               float coneRadius);

#endif
