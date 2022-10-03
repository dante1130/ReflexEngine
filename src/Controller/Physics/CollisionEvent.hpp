#pragma once

#include <reactphysics3d/reactphysics3d.h>

/**
 * @brief Observers collision events from react physics
 */
class CollisionEventListener : public rp3d::EventListener {
	/**
	 * @brief Observer for if collision occurs. This method is called and sent
	 * collision data
	 *
	 * @param collision_data All the collision data for the contact points and
	 * objects involved
	 */
	virtual void onContact(const CallbackData& collision_data) override;
};