#pragma once

#include <reactphysics3d/reactphysics3d.h>

/**
 * @author Andrew Ho
 * @class CollisionEventListener
 * @brief An event listener for reactphysics3d collision events to retrieve the
 * collision and contact points data.
 */
class CollisionEventListener : public rp3d::EventListener {
	/**
	 * @brief The onContact method is called when a contact is detected.
	 *
	 * @param collision_data The collision data containing the contact points.
	 */
	virtual void onContact(const CallbackData& collision_data) override;
};
