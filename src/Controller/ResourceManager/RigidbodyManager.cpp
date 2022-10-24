#include "RigidbodyManager.hpp"
#include "Controller/ReflexEngine/EngineTime.hpp"

float RigidbodyManager::accumulator_ = 0.0f;

auto RigidbodyManager::accumulator(float time_increase) -> bool {
	accumulator_ += time_increase;

	if (accumulator_ < EngineTime::get_time_step() / 2) {
		return false;
	}

	accumulator_ -= EngineTime::get_time_step() / 2;
	return true;
}

void RigidbodyManager::add_rigidbody(Component::Rigidbody& rb,
                                     const Component::Transform& tf) {
	if (!rb.intialised()) rb.init(false, tf.position, tf.rotation);
	rb.setPreviousPosition(tf.position);
}

void RigidbodyManager::update_rigidbody(Component::Rigidbody& rb,
                                        Component::Transform& tf) {
	/// Calculates new position (if using engine calculation)
	if (!rb.usingReactResolve()) rb.update(EngineTime::get_time_step() / 2);

	/// Sets transform position if the same as the previous cycle
	/// Else it must have been manually moved (the transform) therefore
	/// The rigidbodies internal position must be updated
	if (rb.getPreviousPosition() != tf.position) {
		rb.setPosition(tf.position);
		rb.setEulerRotation(tf.rotation);
		rb.setVelocity(glm::vec3(0));
	} else {
		tf.position = rb.getPosition();
		tf.rotation = rb.getRotation();
	}

	/// Update the properties of the rigidbody based of changes made to
	/// the component from the gui or lua
	if (rb.getIsGravityEnabled() != rb.gravity_on)
		rb.enableGravity(rb.gravity_on);

	// if (rb.getIsTrigger() != rb.is_trigger)
	// rb.setObjectTrigger(rb.is_trigger);
	if (rb.getCanSleep() != rb.can_sleep) rb.setCanSleep(rb.can_sleep);

	if (rb.getDragForce() != rb.lin_drag) rb.setDragForce(rb.lin_drag);
	if (rb.getDragTorque() != rb.ang_drag) rb.setDragTorque(rb.ang_drag);

	/// Sets previous position
	rb.setPreviousPosition(tf.position);
}

void RigidbodyManager::delete_rigidbody(Component::Rigidbody& rb) {
	rb.removeAllColliders();
	rb.deleteBody();
	rb = Component::Rigidbody();
	std::cout << "Rigidbody has been deleted!\n";
}