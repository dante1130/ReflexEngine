#include "Body.hpp"

void Body::init() {
	if (creator == true) {
		Physics::createWorld();
	}
}

void Body::update(float delta_time) {
	if (creator == true) {
		Physics::updateWorld(delta_time);
	}
}

void Body::physicsWorldDestroyer() {
	if (creator == false) {
		Physics::destoryWorld();
	}
}

void Body::physicsDebugger() {
	Physics::setDebuggerToActive(true);

	Physics::setDebuggerValues(1, true);
	Physics::setDebuggerValues(2, true);
	Physics::setDebuggerValues(4, true);
	Physics::setDebuggerValues(8, true);
	Physics::setDebuggerValues(16, true);
}

Body::~Body() { physicsWorldDestroyer(); }

void Body::setCreator(bool val) { creator = val; }
