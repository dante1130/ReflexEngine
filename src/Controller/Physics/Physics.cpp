#include "Physics.hpp"

bool Physics::isCreated = false;
reactphysics3d::PhysicsCommon Physics::physicsCommon;
reactphysics3d::PhysicsWorld* Physics::world = nullptr;
CollisionEventListener Physics::collisionEvent;

void Physics::createWorld() {
	if (!isCreated) {
		world = physicsCommon.createPhysicsWorld();
		world->setEventListener(&collisionEvent);
		isCreated = true;
	}
}

void Physics::updateWorld(double delta_time) {
	if (!isCreated) {
		return;
	}

	world->update(delta_time);
}

void Physics::setDebuggerToActive(bool val) {
	if (!isCreated) {
		return;
	}

	world->setIsDebugRenderingEnabled(val);
}

void Physics::setDebuggerValues(reactphysics3d::DebugRenderer::DebugItem type,
                                bool val) {
	if (!isCreated) {
		return;
	}
	world->getDebugRenderer().setIsDebugItemDisplayed(type, val);
}

void Physics::destroyWorld() {
	if (isCreated) {
		physicsCommon.destroyPhysicsWorld(world);
		isCreated = false;
	}
}

reactphysics3d::PhysicsCommon& Physics::getPhysicsCommon() {
	return physicsCommon;
}

reactphysics3d::PhysicsWorld* Physics::getPhysicsWorld() { return world; }

bool Physics::WorldExists() { return isCreated; }
