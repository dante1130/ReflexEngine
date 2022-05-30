#include "movement.h"
#include <cmath>
/*********************************************************************************************
 * Moves an object located at curpos and travelling at curVelocity towards
 *targetPos. This    * function changes the curPos and curVelocity to steer it
 *towards targetPos over time. The   * time factor is specified by timeElasped
 *which should be the current time in the game loop  * timer. 20ms is a
 *reasonable update time.                                                   *
 * Pre: all vars are assigned values. * Post: curPos and curVelocity are updated
 *to incrementally move towards targetPos. curPos   * will be equal to targetPos
 *if the object has reached the target.                     * Variables: curPos
 *is the position vector of the current agent.                             *
 *            targetPos is the vector of the target position. * curVelocity is
 *the current velocity of the agent.                               *
 *            timeElaspsed is the time elaspsed since last logic update. *
 *            offset is the distance to stop prior to reaching the target. *
 *********************************************************************************************/
bool ai_movement::moveTo(glm::vec2& curPos, const glm::vec2& targetPos,
                         glm::vec2 curVelocity, double timeElapsed,
                         double offset) {
	bool xdone = false, zdone = false;
	glm::vec2 newPos;

	glm::vec2 toTarget =
	    targetPos - curPos;  // vector between current position and target
	toTarget = glm::normalize(toTarget);  // get heading
	glm::vec2 pos = targetPos;
	if (!(toTarget.x == 0 && toTarget.y == 0)) {
		pos += -(toTarget * (float)offset);
	}
	if (curPos == pos) {
		return true;
	}
	curVelocity = toTarget * (float)glm::length(curVelocity);  // new velocity
	newPos = curVelocity * (float)timeElapsed;                 // pos = vt
	// test if we have arrived at location.
	if (curPos.x == pos.x) {
		xdone = true;
	} else if (curPos.x < pos.x) {
		if (curPos.x + newPos.x >= pos.x) xdone = true;
	} else if (curPos.x > pos.x) {
		if (curPos.x + newPos.x <= pos.x) xdone = true;
	}
	if (curPos.y == pos.y) {
		zdone = true;
	} else if (curPos.y < pos.y) {
		if (curPos.y + newPos.y >= pos.y) zdone = true;
	} else if (curPos.y > pos.y) {
		if (curPos.y + newPos.y <= pos.y) zdone = true;
	}
	if (xdone && zdone) {
		curPos = pos;
		return true;
	} else
		curPos += newPos;

	if (glm::length(targetPos - curPos) < offset) {
		return true;
	}

	return false;
}

bool ai_movement::flee(glm::vec2& curPos, const glm::vec2& pursuerPos,
                       glm::vec2& curVelocity, double fleeSpeed,
                       double timeElapsed) {
	glm::vec2 fromPursuer;
	double panicDistSq = 100.0 * 100.0;

	fromPursuer = curPos - pursuerPos;
	if (pow(glm::length(fromPursuer), 2) > panicDistSq)
		return false;  // pursuer not in panic range

	fromPursuer = glm::normalize(fromPursuer);     // get heading
	curVelocity = fromPursuer * (float)fleeSpeed;  // new velocity
	curPos += curVelocity * (float)timeElapsed;    // pos = vt
	return true;
}

void ai_movement::pursue(const glm::vec2& evaderPos, glm::vec2& pursuerPos,
                         const glm::vec2& evaderVelocity,
                         glm::vec2& pursuerVelocity, double timeElapsed,
                         double offset) {
	double lookAheadTime;
	// distance between evader and pursuer
	glm::vec2 toEvader = evaderPos - pursuerPos;
	// compute agent headings
	glm::vec2 pursuerHeading = pursuerVelocity;
	pursuerHeading = glm::normalize(pursuerHeading);
	glm::vec2 evaderHeading = evaderVelocity;
	evaderHeading = glm::normalize(evaderHeading);
	// compute angle between agents
	double relativeHeading = glm::dot(pursuerHeading, evaderHeading);
	// determine if evader is facing pursuer - note .95 radians =18 degrees
	if (((glm::dot(toEvader, pursuerHeading) > 0) && relativeHeading < -0.95) ||
	    glm::length(evaderVelocity) == 1) {
		moveTo(pursuerPos, evaderPos, pursuerVelocity, timeElapsed, offset);
	} else {
		lookAheadTime =
		    (glm::length(toEvader)) /
		    (glm::length(evaderVelocity) + glm::length(pursuerVelocity));
		moveTo(pursuerPos, evaderPos + evaderVelocity * (float)lookAheadTime,
		       pursuerVelocity, timeElapsed, offset);
	}
}

bool ai_movement::evade(glm::vec2& evaderPos, const glm::vec2& pursuerPos,
                        glm::vec2& evaderVelocity,
                        const glm::vec2& pursuerVelocity, double timeElapsed) {
	// distance between pursuer and evader
	glm::vec2 toPursuer = pursuerPos - evaderPos;
	double lookaheadTime =
	    glm::length(toPursuer) /
	    (glm::length(evaderVelocity) + glm::length(pursuerVelocity));
	return (flee(evaderPos, pursuerPos + pursuerVelocity * (float)lookaheadTime,
	             evaderVelocity, glm::length(evaderVelocity), timeElapsed));
}

// fov in degrees not radians
bool ai_movement::seeTarget(const glm::vec2& patroller, const glm::vec2& target,
                            const glm::vec2& patrollerVel, float coneDistance,
                            float fov) {
	// vector between patroller and target
	glm::vec2 toTarget = target - patroller;
	// distance between patroller and target
	float dist = glm::length(toTarget);
	if (dist > coneDistance) return false;
	// get heading to target
	toTarget = glm::normalize(toTarget);
	glm::vec2 patrollerHeading = patrollerVel;
	// get patrollers current heading
	patrollerHeading = glm::normalize(patrollerHeading);
	// compute angle between patroller and target
	double angle = (double)glm::dot(patrollerHeading, toTarget);
	// getting some precision problem ensure cos angle is in -1.0 to 1.0
	if (angle > 1.0)
		angle = 1.0;
	else if (angle < -1.0)
		angle = -1.0;
	angle = acos(angle) * 180 / 3.141592653f;  // get heading in degrees
	// determine if target is in fov
	if (angle <= (fov / 2)) return true;
	return false;
}
