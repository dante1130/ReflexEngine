#include "CollisionEvent.hpp"
#include "PhysicBody.hpp"

#include "Controller/GUI/DebugLogger.hpp"
#include "Controller/ReflexEngine/EngineTime.hpp"

void CollisionEventListener::onContact(const CallbackData& collision_data) {
	if (EngineTime::is_paused()) {
		return;
	}
	static bool first_done = false;
	if (first_done == true) {
		// return;
	}

	size_t size = collision_data.getNbContactPairs();
	for (size_t count = 0; count < size; ++count) {
		first_done = true;
		ContactPair contact_pair = collision_data.getContactPair(count);
		if (contact_pair.getEventType() ==
		    ContactPair::EventType::ContactExit) {
			continue;
		}

		int num_of_contacts = contact_pair.getNbContactPoints();
		DebugLogger::log("Physics num of contacts",
		                 std::to_string(num_of_contacts));
		/*
		rp3d::Vector3 contact_normal, local_point_c1, local_point_c2;

		for (size_t countTwo = 0; countTwo < num_of_contacts; ++countTwo) {
		    ContactPoint contact_point = contact_pair.getContactPoint(countTwo);

		    local_point_c1 = contact_point.getLocalPointOnCollider1();
		    local_point_c2 = contact_point.getLocalPointOnCollider2();
		    contact_normal = contact_point.getWorldNormal();

		    PhysicsBody::collision(
		        contact_pair.getCollider1(), contact_pair.getCollider2(),
		        glm::vec3(local_point_c1.x, local_point_c1.y, local_point_c1.z),
		        glm::vec3(local_point_c2.x, local_point_c2.y, local_point_c2.z),
		        glm::vec3(contact_normal.x, contact_normal.y, contact_normal.z),
		        contact_point.getPenetrationDepth(),
		        contact_pair.getEventType());
		}
		*/

		rp3d::Vector3 contact_normal = rp3d::Vector3(0, 0, 0);
		rp3d::Vector3 local_point_c1 = rp3d::Vector3(0, 0, 0);
		rp3d::Vector3 local_point_c2 = rp3d::Vector3(0, 0, 0);
		float penetration_depth = 0;

		for (size_t countTwo = 0; countTwo < num_of_contacts; ++countTwo) {
			ContactPoint contact_point = contact_pair.getContactPoint(countTwo);
			contact_normal += contact_point.getWorldNormal();
			local_point_c1 += contact_point.getLocalPointOnCollider1();
			local_point_c2 += contact_point.getLocalPointOnCollider2();
			penetration_depth += contact_point.getPenetrationDepth();
		}

		float num = static_cast<float>(num_of_contacts);
		local_point_c1 /= num;
		local_point_c2 /= num;
		contact_normal /= num;
		penetration_depth /= num;

		if (num_of_contacts != 0) {
			PhysicsBody::collision(
			    contact_pair.getCollider1(), contact_pair.getCollider2(),
			    glm::vec3(local_point_c1.x, local_point_c1.y, local_point_c1.z),
			    glm::vec3(local_point_c2.x, local_point_c2.y, local_point_c2.z),
			    glm::vec3(contact_normal.x, contact_normal.y, contact_normal.z),
			    penetration_depth, contact_pair.getEventType());
		}
	}
}