#include "ReactResolve.hpp"

bool ReactResolve::usingReactResolve() { 
	return true; 
}

void ReactResolve::init(glm::vec3 rot, glm::vec3 pos, float angle) 
{
	Vector3 p = Vector3(pos.x, pos.y, pos.z);
	Quaternion qt = Quaternion(Vector3(rot.x, rot.y, rot.z), angle);

	cb = Physics::getPhysicsWorld()->createRigidBody(Transform(p, qt));
	((RigidBody*)cb)->setMass(1.0f);
}

void ReactResolve::addForce(glm::vec3 force, Apply type) 
{ 
	try {
		Vector3 temp_force = Vector3(force.x, force.y, force.z);
		switch(type)
		{ 
			case Apply::LOCAL :
				((RigidBody*)cb)->applyLocalForceAtCenterOfMass(temp_force);
				break;
			case Apply::WORLD :
				((RigidBody*)cb)->applyWorldForceAtCenterOfMass(temp_force);
				break;
			default:
				break;
		}
	}
	catch(const std::exception& e) 
	{
		std::cout << "Error: " << e.what() << '\n';
	}
}

void ReactResolve::addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type) {
	try {
		Vector3 temp_force = Vector3(force.x, force.y, force.z);
		Vector3 temp_point = Vector3(point.x, point.y, point.z);
		switch (type) {
			case ApplyPoint::LOCAL_LOCAL :
				((RigidBody*)cb)->applyLocalForceAtLocalPosition(temp_force, temp_point); 
				break;
			case ApplyPoint::LOCAL_WORLD :
				((RigidBody*)cb)->applyLocalForceAtWorldPosition(temp_force, temp_point); 
				break;
			case ApplyPoint::WORLD_LOCAL :
				((RigidBody*)cb)->applyWorldForceAtLocalPosition(temp_force, temp_point);
				break;
			case ApplyPoint::WORLD_WORLD :
				((RigidBody*)cb)->applyWorldForceAtWorldPosition(temp_force, temp_point);
				break;
			default:
				break;
		}
	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << '\n';
	}
}

void ReactResolve::addTorque(glm::vec3 torque, Apply type) 
{
	try {
		Vector3 temp_torque = Vector3(torque.x, torque.y, torque.z);
		switch (type) {
			case Apply::LOCAL :
				((RigidBody*)cb)->applyLocalTorque(temp_torque);
				break;
			case Apply::WORLD :
				((RigidBody*)cb)->applyWorldTorque(temp_torque);
				break;
			default:
				break;
		}
	}catch(const std::exception& e) {
		std::cout << "Error: " << e.what() << '\n';
	}
}

void ReactResolve::addDragForce(float drag) {
	((RigidBody*)cb)->setLinearDamping(drag);
}

void ReactResolve::addDragTorque(float ang_drag) {
	((RigidBody*)cb)->setAngularDamping(ang_drag);
}


void ReactResolve::setMass(float mass) { 
	((RigidBody*)cb)->setMass(mass);
}
void ReactResolve::setCenterOfMass(glm::vec3 p) { 
	((RigidBody*)cb)->setLocalCenterOfMass(Vector3(p.x, p.y, p.z));
}
void ReactResolve::setVelocity(glm::vec3 vel) {
	((RigidBody*)cb)->setLinearVelocity(Vector3(vel.x, vel.y, vel.z));
}
void ReactResolve::setAngVelocity(glm::vec3 ang_vel) {
	((RigidBody*)cb)->setLinearVelocity(Vector3(ang_vel.x, ang_vel.y, ang_vel.z));
}

void ReactResolve::setIsTrigger(bool ean) {
	for (Collider* c : colliders) 
		c->setIsTrigger(ean);
}




