#include "CollisionEvent.hpp"
#include "PhysicBody.hpp"

void CollisionEventListener::onContact(const CallbackData& collision_data) {
	size_t size = collision_data.getNbContactPairs();
	for (size_t count = 0; count < size; ++count) {
		ContactPair contact_pair = collision_data.getContactPair(count);
	}
}