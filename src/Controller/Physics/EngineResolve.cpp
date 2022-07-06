#include "EngineResolve.hpp"

bool EngineResolve::usingReactResolve() 
{ 
	return false; 
}

void EngineResolve::init(glm::vec3 rot, glm::vec3 pos, float angle) {
	Vector3 p = Vector3(pos.x, pos.y, pos.z);
	Quaternion qt = Quaternion(Vector3(rot.x, rot.y, rot.z), angle);

	cb = Physics::getPhysicsWorld()->createCollisionBody(Transform(p, qt));
}
