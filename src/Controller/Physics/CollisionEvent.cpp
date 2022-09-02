#include "CollisionEvent.hpp"
#include "PhysicBody.hpp"
#include <iostream>

void CollisionEventListener::onContact(const CallbackData& collision_data) {

	for (size_t i = 0; i < collision_data.getNbContactPairs(); ++i) {
		ContactPair contact_pair = collision_data.getContactPair(i);

		rp3d::Vector3 total_normal = rp3d::Vector3(0.0f, 0.0f, 0.0f);
		for (size_t j = 0; j < contact_pair.getNbContactPoints(); ++j) {
			ContactPoint contact_point = contact_pair.getContactPoint(j);
			total_normal += contact_point.getWorldNormal();
		}

		total_normal.x = total_normal.x / contact_pair.getNbContactPoints();
		total_normal.y = total_normal.y / contact_pair.getNbContactPoints();
		total_normal.z = total_normal.z / contact_pair.getNbContactPoints();

		ContactPair::EventType event_type = contact_pair.getEventType();

		
		PhysicsBody::collision(contact_pair.getCollider1(),
		                       contact_pair.getCollider2(), total_normal, event_type);


		/* if (event_type == ContactPair::EventType::ContactStart) {
		 	std::cout << "Contact start\n";
		 } else if (event_type == ContactPair::EventType::ContactStay) {
		 	std::cout << "Contact stay\n";
		 } else if (event_type == ContactPair::EventType::ContactExit) {
		 	std::cout << "Contact end\n";
		 }*/

	}
}
