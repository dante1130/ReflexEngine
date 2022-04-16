#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include "Physics.hpp"

using namespace reactphysics3d;

namespace Physics {
/**
 * @brief	Creates the world for the physic objects
 * @param	No param
 * @return	Void
 *
 * @pre		Nothing
 * @post	World is created & ready to use
 */
void createWorld();

/**
 * @brief	Updates the world for the physic objects
 * @param	delta_time	- Time since the last update
 * @return	Void
 *
 * @pre		World has been created
 * @post	World has been updated
 */
void updateWorld(float delta_time);

/**
 * @brief	Sets which debugger to active
 * @param	val	- true if you want it activated
 * @return	Void
 *
 * @pre		World has been created
 * @post	Debugger activated/deactivated
 */
void setDebuggerToActive(bool val);

/**
 * Collider AABB = 1
 * Collider Broadphase AABB = 2
 * Collision Shape = 4
 * Contact Normal = 16
 * Contact Point = 8
 *
 * @brief	Can set different debug values to be returned
 * @param	type	- The type of debugger to add
 * @param	val		- true if you want to add it / use it
 * @return	Void
 *
 * @pre		Nothing
 * @post	Debugger will use/not use the value
 */
void setDebuggerValues(int type, bool val);

/**
 * @brief	Creates the world for the physic objects
 * @param	No param
 * @return	Void
 *
 * @pre		World is created
 * @post	World is destoryed
 */
void destoryWorld();

/**
 * @brief	Returns physics common game object
 * @param	No param
 * @return	&PhysicsCommon	- The physics common object
 *
 * @pre		Nothing
 * @post	Nothing
 */
PhysicsCommon& getPhysicsCommon();

/**
 * @brief	Returns physics world game object
 * @param	No param
 * @return	*PhysicsWorld	- The physics world
 *
 * @pre		Nothing
 * @post	Nothing
 */
PhysicsWorld* getPhysicsWorld();

/**
 * @brief	Returns if the physics world is created or not
 * @param	No param
 * @return	bool	- If the physics world exsists
 *
 * @pre		Nothing
 * @post	Nothing
 */
bool WorldExsists();
}  // namespace Physics
