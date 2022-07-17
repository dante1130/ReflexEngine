#include "Physics.hpp"

bool Physics::isCreated = false;
PhysicsCommon Physics::physicsCommon;
PhysicsWorld* Physics::world = nullptr;
CollisionEventListener Physics::collisionEvent;

void Physics::createWorld() {
	if (!isCreated) {
		world = physicsCommon.createPhysicsWorld();
		world->setEventListener(&collisionEvent);
		isCreated = true;
	}
}

void Physics::updateWorld(double delta_time) {
	if (!isCreated) return;

	world->update(delta_time);
}

void Physics::setDebuggerToActive(bool val) {
	if (!isCreated) return;

	world->setIsDebugRenderingEnabled(val);
}

void Physics::setDebuggerValues(int type, bool val) {
	if (!isCreated) return;
	DebugRenderer& debugRenderer = world->getDebugRenderer();
	debugRenderer.setIsDebugItemDisplayed(
	    static_cast<DebugRenderer::DebugItem>(type), val);
}

void Physics::destroyWorld() {
	if (isCreated) {
		physicsCommon.destroyPhysicsWorld(world);
		isCreated = false;
	}
}

PhysicsCommon& Physics::getPhysicsCommon() { return physicsCommon; }

PhysicsWorld* Physics::getPhysicsWorld() { return world; }

bool Physics::WorldExists() { return isCreated; }
