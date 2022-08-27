#include "CollisionEvent.hpp"
#include "PhysicBody.hpp"
#include <iostream>

void CollisionEventListener::onContact(const CallbackData& collision_data) {

	for (size_t i = 0; i < collision_data.getNbContactPairs(); ++i) {
		ContactPair contact_pair = collision_data.getContactPair(i);

		PhysicsBody::collision(contact_pair.getCollider1(),
		                       contact_pair.getCollider2());

		 ContactPair::EventType event_type = contact_pair.getEventType();

		 if (event_type == ContactPair::EventType::ContactStart) {
		 	std::cout << "Contact start\n";
		 } else if (event_type == ContactPair::EventType::ContactStay) {
		 	std::cout << "Contact stay\n";
		 } else if (event_type == ContactPair::EventType::ContactExit) {
		 	std::cout << "Contact end\n";
		 }

		for (size_t j = 0; j < contact_pair.getNbContactPoints(); ++j) {
			ContactPoint contact_point = contact_pair.getContactPoint(j);
		}
	}
}
