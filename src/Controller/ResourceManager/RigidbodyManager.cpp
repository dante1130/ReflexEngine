#include "RigidbodyManager.hpp"
#include "Controller/ReflexEngine/EngineTime.hpp"
    //#include "glm/vec3.hpp"

// RigidbodyManager::RigidbodyManager()
//{
//	Physics::createWorld();
// }
//
// RigidbodyManager::~RigidbodyManager()
//{
//	Physics::destroyWorld();
// }

void RigidbodyManager::add_rigidbody(Component::Rigidbody& rb,
                                     const Component::Transform& tf) {
	if (!rb.intialised())
		rb.init(true, tf.position, tf.rotation);
	rb.setPreviousPosition(tf.position);
}

void RigidbodyManager::update_rigidbody(Component::Rigidbody& rb,
                                        Component::Transform& tf) {
	if (!rb.usingReactResolve()) 
		rb.update(EngineTime::get_fixed_delta_time());

	if (rb.getPreviousPosition() != tf.position) {
		rb.setPosition(tf.position);
		rb.setEulerRotation(tf.rotation);
		rb.setVelocity(glm::vec3(0));
	} else {
		tf.position = rb.getPosition();
		tf.rotation = rb.getRotation();
	}

	if (rb.getIsGravityEnabled() != rb.gravity_on)
		rb.enableGravity(rb.gravity_on);

	if (rb.getIsTrigger() != rb.is_trigger) rb.setObjectTrigger(rb.is_trigger);
	if (rb.getCanSleep() != rb.can_sleep) rb.setCanSleep(rb.can_sleep);

	if (rb.getDragForce() != rb.lin_drag) rb.setDragForce(rb.lin_drag);
	if (rb.getDragTorque() != rb.ang_drag) rb.setDragTorque(rb.ang_drag);

	rb.setPreviousPosition(tf.position);
}

void RigidbodyManager::delete_rigidbody(Component::Rigidbody& rb) {
	rb.removeAllColliders();
	rb.deleteBody();
	rb = Component::Rigidbody();
	std::cout << "Rigidbody has been deleted!\n";
}