#include "ReactResolve.hpp"

using namespace rp3d;

bool ReactResolve::usingReactResolve() { 
	return true; 
}

ReactResolve::ReactResolve() 
{ 
	 //something
}


void ReactResolve::init(glm::vec3 pos, glm::vec3 rot, float angle) 
{
	Vector3 p(pos.x, pos.y, pos.z);
	Quaternion o = Quaternion::identity();

	angle = angle / (180 / PI_RP3D);

	float x = rot.x * sin(angle / 2);
	float y = rot.y * sin(angle / 2);
	float z = rot.z * sin(angle / 2);
	float w = cos(angle / 2);

	float normal = sqrt(pow(cos(angle / 2), 2) +
		pow(rot.x, 2) * pow(sin(angle / 2), 2) +
		pow(rot.y, 2) * pow(sin(angle / 2), 2) +
		pow(rot.z, 2) * pow(sin(angle / 2), 2));

	o.setAllValues(x / normal, y / normal, z / normal, w / normal);

	rb = Physics::getPhysicsWorld()->createRigidBody(Transform(p, o));

}

void ReactResolve::init(glm::vec3 pos, glm::vec3 rot)
{
	std::cout << "Rotation: x: " << rot.x << " y: " << rot.y << " z: " << rot.z << std::endl;
	Vector3 p(pos.x, pos.y, pos.z);
	Quaternion o = rp3d::Quaternion::identity();

	glm::vec3 rot_radians = glm::radians(rot);

	double cy = std::cos(rot_radians.z * 0.5);
    double sy = std::sin(rot_radians.z * 0.5);
    double cp = std::cos(rot_radians.y * 0.5);
    double sp = std::sin(rot_radians.y * 0.5);
    double cr = std::cos(rot_radians.x * 0.5);
    double sr = std::sin(rot_radians.x * 0.5);

    o.w = cr * cp * cy + sr * sp * sy;
    o.x = sr * cp * cy - cr * sp * sy;
    o.y = cr * sp * cy + sr * cp * sy;
    o.z = cr * cp * sy - sr * sp * cy;

	rb = Physics::getPhysicsWorld()->createRigidBody(Transform(p, o));
}

void ReactResolve::addForce(glm::vec3 force, Apply type) 
{ 
	try {
		Vector3 temp_force = Vector3(force.x , force.y , force.z );
		switch(type)
		{ 
			case Apply::LOCAL :
				rb->applyLocalForceAtCenterOfMass(temp_force);
				break;
			case Apply::WORLD :
				rb->applyWorldForceAtCenterOfMass(temp_force);
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
				rb->applyLocalForceAtLocalPosition(temp_force, temp_point); 
				break;
			case ApplyPoint::LOCAL_WORLD :
				rb->applyLocalForceAtWorldPosition(temp_force, temp_point); 
				break;
			case ApplyPoint::WORLD_LOCAL :
				rb->applyWorldForceAtLocalPosition(temp_force, temp_point);
				break;
			case ApplyPoint::WORLD_WORLD :
				rb->applyWorldForceAtWorldPosition(temp_force, temp_point);
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
				rb->applyLocalTorque(temp_torque);
				break;
			case Apply::WORLD :
				rb->applyWorldTorque(temp_torque);
				break;
			default:
				break;
		}
	}catch(const std::exception& e) {
		std::cout << "Error: " << e.what() << '\n';
	}
}

void ReactResolve::addDragForce(float drag) { 
	rb->setLinearDamping(drag); 
}

void ReactResolve::addDragTorque(float ang_drag) {
	rb->setAngularDamping(ang_drag);
}


void ReactResolve::setMass(float mass) { 
	rb->setMass(mass); 
}
void ReactResolve::setCenterOfMass(glm::vec3 p) { 
	rb->setLocalCenterOfMass(Vector3(p.x, p.y, p.z));
}
void ReactResolve::setVelocity(glm::vec3 vel) {
	rb->setLinearVelocity(Vector3(vel.x, vel.y, vel.z));
	
}
void ReactResolve::setAngVelocity(glm::vec3 ang_vel) {
	rb->setAngularVelocity(Vector3(ang_vel.x, ang_vel.y, ang_vel.z));
}
void ReactResolve::setType(BodyType type) { 
	rb->setType(type); 
}
void ReactResolve::setDragForce(float drag){
	rb->setLinearDamping(drag);
}
void ReactResolve::setDragTorque(float ang_drag){
	rb->setAngularDamping(ang_drag);
}

void ReactResolve::setType(int type)
{
	switch (type)
	{
		case 0:
			rb->setType(BodyType::STATIC);
			break;
		case 1:
			rb->setType(BodyType::KINEMATIC);
			break;
		case 2:
			rb->setType(BodyType::DYNAMIC);
			break;
		default:
			break;
	}
}
void ReactResolve::enableGravity(bool ean) {
	rb->enableGravity(ean);
}
void ReactResolve::setCanSleep(bool ean) {
	rb->setIsAllowedToSleep(ean);
}

float ReactResolve::getMass(){
	return rb->getMass();
}
glm::vec3 ReactResolve::getVelocity() {
	Vector3 v = rb->getLinearVelocity();
	return glm::vec3(v.x, v.y, v.z);
}
glm::vec3 ReactResolve::getAngVelocity() {
	Vector3 av = rb->getAngularVelocity();
	return glm::vec3(av.x, av.y, av.z);
}
float ReactResolve::getDragForce() {
	return rb->getLinearDamping();
}
float ReactResolve::getDragTorque() {
	return rb->getAngularDamping();
}
BodyType ReactResolve::getType() {
	return rb->getType();
}
bool ReactResolve::getIsGravityEnabled() {
	return rb->isGravityEnabled();
}
bool ReactResolve::getCanSleep() {
	return rb->isAllowedToSleep();
}

unsigned int ReactResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size)
{
	BoxShape* bs = Physics::getPhysicsCommon().createBoxShape(
		Vector3(size.x / 2, size.y / 2, size.z / 2));
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(rb->addCollider(bs, center));
	m_box.emplace(colliders[colliders.size() - 1], bs);
	return colliders.size() - 1;
}

unsigned int ReactResolve::addSphereCollider(glm::vec3 pos, float radius)
{
	SphereShape* ss = Physics::getPhysicsCommon().createSphereShape(radius);
	// identity only for now maybe idk
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(rb->addCollider(ss, center));
	m_sphere.emplace(colliders[colliders.size() - 1], ss);
	return colliders.size() - 1;
}

unsigned int ReactResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height)
{
	CapsuleShape* cs = Physics::getPhysicsCommon().createCapsuleShape(radius, height);
	// identity only for now maybe idk
	Transform center = Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(rb->addCollider(cs, center));
	m_capsule.emplace(colliders[colliders.size() - 1], cs);
	return colliders.size() - 1;
}

unsigned int ReactResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction)
{
	unsigned int index = addBoxCollider(pos, size);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

unsigned int ReactResolve::addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
{
	unsigned int index = addSphereCollider(pos, radius);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

unsigned int ReactResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
{
	unsigned int index = addCapsuleCollider(pos, radius, height);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

glm::vec3 ReactResolve::getPosition() {
	Vector3 p = rb->getTransform().getPosition();
	return glm::vec3(p.x, p.y, p.z);
}

glm::vec3 ReactResolve::getRotation() {
	Quaternion r = rb->getTransform().getOrientation();
	return glm::degrees(glm::eulerAngles(glm::quat(r.w, r.x, r.y, r.z)));
}

glm::quat ReactResolve::getOrientation() {
	Quaternion r = rb->getTransform().getOrientation();
	return glm::quat(r.w, r.x, r.y, r.z);
}

void ReactResolve::setPosition(glm::vec3 pos)
{
	Transform transform = rb->getTransform();
	transform.setPosition(Vector3(pos.x, pos.y, pos.z));
	rb->setTransform(transform);
}

void ReactResolve::setQuanternion(glm::quat quat)
{
	Transform transform = rb->getTransform();
	transform.setOrientation(Quaternion(quat.x, quat.y, quat.z, quat.w));
	rb->setTransform(transform);
}

void ReactResolve::setEulerRotation(glm::vec3 rot)
{
	Transform transform = rb->getTransform();
	Quaternion o = Quaternion::identity();
	glm::vec3 rot_radians = glm::radians(rot);

	double cy = std::cos(rot_radians.z * 0.5);
	double sy = std::sin(rot_radians.z * 0.5);
	double cp = std::cos(rot_radians.y * 0.5);
	double sp = std::sin(rot_radians.y * 0.5);
	double cr = std::cos(rot_radians.x * 0.5);
	double sr = std::sin(rot_radians.x * 0.5);

	o.w = cr * cp * cy + sr * sp * sy;
	o.x = sr * cp * cy - cr * sp * sy;
	o.y = cr * sp * cy + sr * cp * sy;
	o.z = cr * cp * sy - sr * sp * cy;

	transform.setOrientation(o);
	rb->setTransform(transform);
}

//Physics object needed, can delete later
float ReactResolve::getAngle()
{
	return rb->getTransform().getOrientation().w;
}
void ReactResolve::setRotation(glm::vec3 rot)
{
	Transform transform = rb->getTransform();
	transform.setOrientation(Quaternion(rot.x, rot.y, rot.z, transform.getOrientation().w));
	rb->setTransform(transform);
}
void ReactResolve::setAngle(float ang)
{
	Transform transform = rb->getTransform();
	Quaternion orientation = rb->getTransform().getOrientation();
	orientation.w = ang;
	transform.setOrientation(orientation);
	rb->setTransform(transform);
}




