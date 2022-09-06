#include <catch2/catch_test_macros.hpp>

#include "Model/Components/RigidBody.hpp"
#include <glm/glm.hpp>
#include <string>

TEST_CASE("Rigidbody physics tests", "[Rigidbody]") {
	Component::Rigidbody rb_react, rb_engine;

	SECTION("Intialising rb through react resolution") {
		rb_react.init(true, glm::vec3(0.0f), glm::vec3(0.0f));
	}

	SECTION("Intialising pb through engine resolution") {
		rb_engine.init(false, glm::vec3(0.0f), glm::vec3(0.0f));
	}

	SECTION("Set/get velocity of rb_react") {
		glm::vec3 velocity = glm::vec3(1.0f);

		rb_react.setVelocity(velocity);

		REQUIRE(velocity == rb_react.getVelocity());
	}

	SECTION("Set/get velocity of rb_engine") {
		glm::vec3 velocity = glm::vec3(1.0f);

		rb_engine.setVelocity(velocity);

		REQUIRE(velocity == rb_engine.getVelocity());
	}

	SECTION("Set/get linear drag of rb_react") {
		float drag = 1.0f;

		rb_react.setDragForce(drag);

		REQUIRE(drag == rb_react.getDragForce());
	}

	SECTION("Set/get linear drag of rb_engine") {
		float drag = 1.0f;

		rb_engine.setDragForce(drag);

		REQUIRE(drag == rb_engine.getDragForce());
	}

	SECTION("Add a box collider to rb_react") {
		glm::vec3 position = glm::vec3(2.0f);
		glm::vec3 size = glm::vec3(1.0f);
		float bounciness = 1.0f;
		float friction = 1.0f;

		int index =
		    rb_react.addBoxCollider(position, size, bounciness, friction);

		// Collider* c = rb_react.getColliders()[index];
		reactphysics3d::BoxShape* bs = rb_react.getColliderBox(index);

		reactphysics3d::Transform tf = c->getLocalToBodyTransform();

		REQUIRE(position == glm::vec3(tf.x, tf.y, tf.z));
	}

	SECTION("Add a box collider to rb_engine") {
		float drag = 1.0f;

		rb_engine.setDragForce(drag);

		REQUIRE(drag == rb_engine.getDragForce());
	}
}
