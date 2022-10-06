#include "CollisionEvent.hpp"
#include "PhysicBody.hpp"

#include "Controller/GUI/DebugLogger.hpp"
#include "Controller/ReflexEngine/EngineTime.hpp"

void CollisionEventListener::onContact(const CallbackData& collision_data) {
	if (EngineTime::is_paused()) {
		return;
	}

	size_t size = collision_data.getNbContactPairs();

	for (size_t count = 0; count < size; ++count) {
		ContactPair contact_pair = collision_data.getContactPair(count);

		int num_of_contacts = contact_pair.getNbContactPoints();
		rp3d::Vector3 contact_normal, local_point_c1, local_point_c2;
		for (size_t countTwo = 0; countTwo < num_of_contacts; ++countTwo) {
			contact_normal =
			    contact_pair.getContactPoint(countTwo).getWorldNormal();
			local_point_c1 = contact_pair.getContactPoint(countTwo)
			                     .getLocalPointOnCollider1();
			local_point_c2 = contact_pair.getContactPoint(countTwo)
			                     .getLocalPointOnCollider2();

			PhysicsBody::collision(
			    contact_pair.getCollider1(), contact_pair.getCollider2(),
			    glm::vec3(local_point_c1.x, local_point_c1.y, local_point_c1.z),
			    glm::vec3(local_point_c2.x, local_point_c2.y, local_point_c2.z),
			    glm::vec3(contact_normal.x, contact_normal.y, contact_normal.z),
			    contact_pair.getContactPoint(countTwo).getPenetrationDepth(),
			    contact_pair.getEventType());
		}
	}
}