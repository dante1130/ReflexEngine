#include "Physics.hpp"

bool Physics::created = false;
PhysicsCommon Physics::physicsCommon;
PhysicsWorld* Physics::world = nullptr;

void Physics::createWorld() {
	if (!created) {
		world = physicsCommon.createPhysicsWorld();
		created = true;
	}
}

void Physics::updateWorld(double delta_time) {
	if (!created) {
		return;
	}
	world->update(delta_time);
}

void Physics::setDebuggerToActive(bool val) {
	if (!created) {
		return;
	}
	world->setIsDebugRenderingEnabled(val);
}

void Physics::setDebuggerValues(int type, bool val) {
	if (!created) {
		return;
	}
	DebugRenderer& debugRenderer = world->getDebugRenderer();
	debugRenderer.setIsDebugItemDisplayed(
	    static_cast<DebugRenderer::DebugItem>(type), val);
}

void Physics::destroyWorld() {
	if (created) {
		physicsCommon.destroyPhysicsWorld(world);
		created = false;
	}
}

PhysicsCommon& Physics::getPhysicsCommon() { return physicsCommon; }

PhysicsWorld* Physics::getPhysicsWorld() { return world; }

bool Physics::WorldExists() { return created; }
