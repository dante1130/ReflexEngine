#include "Body.hpp"

void Body::init() {
	// if (creator == true) {
	//	Physics::createWorld();
	// }
}

void Body::update(float delta_time) {}

void Body::fixed_update(float delta_time) {
	// if (creator == true) {
	//	if (GenericFunctions::getIfPaused() == false) {
	//		Physics::updateWorld(delta_time);
	//	}
	// }
}

void Body::physicsWorldDestroyer() {
	// if (creator == false) {
	//	Physics::destoryWorld();
	// }
}

void Body::physicsDebugger() {
	// Physics::setDebuggerToActive(true);

	// Physics::setDebuggerValues(1, true);
	// Physics::setDebuggerValues(2, true);
	// Physics::setDebuggerValues(4, true);
	// Physics::setDebuggerValues(8, true);
	// Physics::setDebuggerValues(16, true);
}

void Body::setCreator(bool val) {  // creator = val;
}

void Body::save_object() {
	// ObjectSaving::openFile();
	// ObjectSaving::saveGameObject(position, rotation, scale, angle, "Body");
	// ObjectSaving::addComma();
	// ObjectSaving::addValue("creator", creator, true);
	// ObjectSaving::closeStruct();
	// ObjectSaving::closeFile();
}

Body::~Body() {  // physicsWorldDestroyer();
}
