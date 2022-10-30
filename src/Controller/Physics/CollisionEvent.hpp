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

private:
	auto convert_local_point(rp3d::Vector3 local_point,
	                         rp3d::CollisionBody* collision_body,
	                         rp3d::Collider* collider, float num)
	    -> rp3d::Vector3;
};