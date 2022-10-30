#include "CollisionEvent.hpp"
#include "PhysicBody.hpp"

#include "Controller/GUI/DebugLogger.hpp"
#include "Controller/ReflexEngine/EngineTime.hpp"
#include "Controller/Physics/QuaternionHelper.hpp"

void CollisionEventListener::onContact(const CallbackData& collision_data) {
	if (EngineTime::is_paused()) {
		return;
	}

	size_t size = collision_data.getNbContactPairs();
	// Loop through all colliders-collider contacts
	for (size_t count = 0; count < size; ++count) {
		ContactPair contact_pair = collision_data.getContactPair(count);
		if (contact_pair.getEventType() ==
		    ContactPair::EventType::ContactExit) {
			continue;
		}

		int num_of_contacts = contact_pair.getNbContactPoints();
		rp3d::Vector3 contact_normal = rp3d::Vector3(0, 0, 0);
		rp3d::Vector3 local_point_c1 = rp3d::Vector3(0, 0, 0);
		rp3d::Vector3 local_point_c2 = rp3d::Vector3(0, 0, 0);
		float penetration_depth = 0;

		// Loop through all contacts against same collider
		for (size_t countTwo = 0; countTwo < num_of_contacts; ++countTwo) {
			ContactPoint contact_point = contact_pair.getContactPoint(countTwo);
			contact_normal += contact_point.getWorldNormal();
			local_point_c1 += contact_point.getLocalPointOnCollider1();
			local_point_c2 += contact_point.getLocalPointOnCollider2();
			penetration_depth += contact_point.getPenetrationDepth();
		}

		if (num_of_contacts != 0) {
			float num = static_cast<float>(num_of_contacts);

			// Converts the local point to body point
			local_point_c1 =
			    convert_local_point(local_point_c1, contact_pair.getBody1(),
			                        contact_pair.getCollider1(), num);
			local_point_c2 =
			    convert_local_point(local_point_c2, contact_pair.getBody2(),
			                        contact_pair.getCollider2(), num);

			contact_normal /= num;
			penetration_depth /= num;

			// Run collision method
			PhysicsBody::collision(
			    contact_pair.getCollider1(), contact_pair.getCollider2(),
			    glm::vec3(local_point_c1.x, local_point_c1.y, local_point_c1.z),
			    glm::vec3(local_point_c2.x, local_point_c2.y, local_point_c2.z),
			    glm::normalize(glm::vec3(contact_normal.x, contact_normal.y,
			                             contact_normal.z)),
			    penetration_depth, contact_pair.getEventType());
		}
	}
}

auto CollisionEventListener::convert_local_point(
    rp3d::Vector3 local_point, rp3d::CollisionBody* collision_body,
    rp3d::Collider* collider, float num) -> rp3d::Vector3 {
	auto com_vec = static_cast<PhysicsBody*>(collider->getUserData())
	                   ->get_center_of_mass();
	auto trans = collider->getLocalToBodyTransform();
	// Average collider contact point
	local_point /= num;

	// Rotate point based on collider orientation to body
	auto rp3d_quat = trans.getOrientation();
	auto lp_rot = QuaternionHelper::RotateVectorWithQuat(
	    glm::vec3(local_point.x, local_point.y, local_point.z),
	    glm::quat(rp3d_quat.w, rp3d_quat.x, rp3d_quat.y, rp3d_quat.z));

	// Get local point in terms of world coordinates
	local_point = collision_body->getWorldVector(
	    rp3d::Vector3(lp_rot.x, lp_rot.y, lp_rot.z) + trans.getPosition() -
	    rp3d::Vector3(com_vec.x, com_vec.y, com_vec.z));

	return local_point;
}