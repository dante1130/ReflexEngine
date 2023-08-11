#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include "CollisionEvent.hpp"

class Physics {
public:
	/**
	 * @brief	Creates the world for the physic objects
	 *
	 * @pre		Nothing
	 * @post	World is created & ready to use
	 */
	static void createWorld();

	/**
	 * @brief	Updates the world for the physic objects
	 * @param	delta_time	- Time since the last update
	 *
	 * @pre		World has been created
	 * @post	World has been updated
	 */
	static void updateWorld(double delta_time);

	/**
	 * @brief	Sets which debugger to active
	 * @param	val	- true if you want it activated
	 *
	 * @pre		World has been created
	 * @post	Debugger activated/deactivated
	 */
	static void setDebuggerToActive(bool val);

	/**
	 * @brief	Can set different debug values to be returned
	 * @param	type	- The type of debugger to add
	 * @param	val		- true if you want to add it / use it
	 *
	 * @pre		Nothing
	 * @post	Debugger will use/not use the value
	 */
	static void setDebuggerValues(reactphysics3d::DebugRenderer::DebugItem type,
	                              bool val);

	/**
	 * @brief	Creates the world for the physic objects
	 *
	 * @pre		World is created
	 * @post	World is destoryed
	 */
	static void destroyWorld();

	/**
	 * @brief	Returns physics common game object
	 * @return	&PhysicsCommon	- The physics common object
	 *
	 * @pre		Nothing
	 * @post	Nothing
	 */
	static reactphysics3d::PhysicsCommon& getPhysicsCommon();

	/**
	 * @brief	Returns physics world game object
	 * @return	*PhysicsWorld	- The physics world
	 *
	 * @pre		Nothing
	 * @post	Nothing
	 */
	static reactphysics3d::PhysicsWorld* getPhysicsWorld();

	/**
	 * @brief	Returns if the physics world is created or not
	 * @return	bool	- If the physics world exsists
	 *
	 * @pre		Nothing
	 * @post	Nothing
	 */
	static bool WorldExists();

private:
	/// A boolean determining if the world has been created or not.
	static bool isCreated;
	/// A class used to create and destroy the physics world and objects.
	static reactphysics3d::PhysicsCommon physicsCommon;
	/// The physics world.
	static reactphysics3d::PhysicsWorld* world;
	/// The collision event listener listening for any collision.
	static CollisionEventListener collisionEvent;
};
