#include "Physics.hpp"
bool created = false;
PhysicsCommon physicsCommon;
PhysicsWorld* world;

void Physics::createWorld() {
	if (created == false) {
		world = physicsCommon.createPhysicsWorld();
		created = true;
	}
}

void Physics::updateWorld(float delta_time) {
	if (created == false) {
		return;
	}
	world->update(delta_time);
}

void Physics::setDebuggerToActive(bool val) {
	if (created == false) {
		return;
	}
	world->setIsDebugRenderingEnabled(true);
}

void Physics::setDebuggerValues(int type, bool val) {
	if (created == false) {
		return;
	}
	DebugRenderer& debugRenderer = world->getDebugRenderer();
	debugRenderer.setIsDebugItemDisplayed((DebugRenderer::DebugItem)type, val);
}

void Physics::destoryWorld() {
	if (created == true) {
		physicsCommon.destroyPhysicsWorld(world);
		created = false;
	}
}

PhysicsCommon& Physics::getPhysicsCommon() { return physicsCommon; }

PhysicsWorld* Physics::getPhysicsWorld() { return world; }

bool Physics::WorldExsists() { return created; }
