#include "EngineResolve.hpp"

using namespace rp3d;

bool EngineResolve::usingReactResolve() 
{ 
	return false; 
}

EngineResolve::EngineResolve() {
	lin_velocity_ = glm::vec3(0.0f);
	lin_accelaration_ = glm::vec3(0.0f);

	force_ = glm::vec3(0.0f);

	lin_drag = 0.0f;

	mass_ = 1.0f;

	type_ = BodyType::DYNAMIC;

	gravity_ = glm::vec3(0.0f, -9.8f, 0.0f);

	collision_axes = glm::vec3(0.0f, 0.0f, 0.0f);

	lock_axes_front = bool3(false, false, false);
	lock_axes_back = bool3(false, false, false);
}

void EngineResolve::update(float delta_time) {
	
	if (type_ == BodyType::STATIC || type_ == BodyType::KINEMATIC)
		return;

	// Previous position and orientation
	Vector3 old_position = cb->getTransform().getPosition();
	Quaternion old_orientation = cb->getTransform().getOrientation();

	glm::vec3 applied_gravity = glm::vec3(0.0f);
	glm::vec3 temp_acc = glm::vec3(0.0f);

	// Applies gravity if enabled
	if (use_gravity_) 
		applied_gravity = gravity_;

	// Applies force to acceleration
	if (force_ != glm::vec3(0.0f)) {
		temp_acc = force_ / mass_;
		lin_accelaration_ += temp_acc;
		force_ = glm::vec3(0.0f);
	}

	// Calcuating new linear velocity
	lin_velocity_ =
		    lin_velocity_ + (lin_accelaration_ + applied_gravity) * delta_time;

	lin_velocity_ = lin_velocity_ * (1 - delta_time * lin_drag);

	// Calculating new position
	Vector3 new_position = old_position +
	    Vector3(lin_velocity_.x, lin_velocity_.y, lin_velocity_.z) * delta_time;
	// Calculating new orientation
	Quaternion new_orientation = old_orientation;
	
	if (lock_axes_front.lock_x && new_position.x > collision_axes.x)
		new_position.x = collision_axes.x;
	if (lock_axes_front.lock_y && new_position.y > collision_axes.y)
		new_position.y = collision_axes.y;
	if (lock_axes_front.lock_z && new_position.z > collision_axes.z)
		new_position.z = collision_axes.z;

	if (lock_axes_back.lock_x && new_position.x < collision_axes.x)
		new_position.x = collision_axes.x;
	if (lock_axes_back.lock_y && new_position.y < collision_axes.y)
		new_position.y = collision_axes.y;
	if (lock_axes_back.lock_z && new_position.z < collision_axes.z)
		new_position.z = collision_axes.z;

	//Final linking
	cb->setTransform(Transform(new_position, new_orientation));

	lin_accelaration_ -= temp_acc;
}

void EngineResolve::stop(glm::vec3 normal, CollisionEvent c_type) {

	if (c_type == CollisionEvent::ContactStart) {
		collision_axes = getPosition();
	}

	if (c_type == CollisionEvent::ContactStay) {

		if (normal.x == 1 && !lock_axes_front.lock_x)
			lock_axes_front.lock_x = true;
		if (normal.y == 1 && !lock_axes_front.lock_y)
			lock_axes_front.lock_y = true;
		if (normal.z == 1 && !lock_axes_front.lock_z)
			lock_axes_front.lock_z = true;

		if (normal.x == -1 && !lock_axes_back.lock_x)
			lock_axes_back.lock_x = true;
		if (normal.y == -1 && !lock_axes_back.lock_y)
			lock_axes_back.lock_y = true;
		if (normal.z == -1 && !lock_axes_back.lock_z)
			lock_axes_back.lock_z = true;
	}

	if (c_type == CollisionEvent::ContactExit) {
		lock_axes_front = bool3(false, false, false);
		lock_axes_back = bool3(false, false, false);
	}
}

void EngineResolve::initialise_body(glm::vec3 pos, glm::vec3 rot, float angle) {
	Vector3 position(pos.x, pos.y, pos.z);
	Quaternion orientation = Quaternion::identity();

	angle = angle / (180 / PI_RP3D);

	float x = rot.x * sin(angle / 2);
	float y = rot.y * sin(angle / 2);
	float z = rot.z * sin(angle / 2);
	float w = cos(angle / 2);

	float normal = sqrt(pow(cos(angle / 2), 2) +
		pow(rot.x, 2) * pow(sin(angle / 2), 2) +
		pow(rot.y, 2) * pow(sin(angle / 2), 2) +
		pow(rot.z, 2) * pow(sin(angle / 2), 2));

	orientation.setAllValues(x / normal, y / normal, z / normal, w / normal);

	cb = Physics::getPhysicsWorld()->createCollisionBody(Transform(position, orientation));
}

void EngineResolve::initialise_body(glm::vec3 pos, glm::vec3 rot)
{
	Vector3 position(pos.x, pos.y, pos.z);
	Quaternion orientation = rp3d::Quaternion::identity();
	glm::vec3 rot_radians = glm::radians(rot);

	double cy = glm::cos(rot_radians.z * 0.5); // cosine applied on yaw
	double sy = glm::sin(rot_radians.z * 0.5); // sine applied on yaw
	double cp = glm::cos(rot_radians.y * 0.5); // cosine applied on pitch
	double sp = glm::sin(rot_radians.y * 0.5); // sine applied on pitch
	double cr = glm::cos(rot_radians.x * 0.5); // cosine applied on roll
	double sr = glm::sin(rot_radians.x * 0.5); // sine applied on roll

	orientation.w = cr * cp * cy + sr * sp * sy;
	orientation.x = sr * cp * cy - cr * sp * sy;
	orientation.y = cr * sp * cy + sr * cp * sy;
	orientation.z = cr * cp * sy - sr * sp * cy;

	cb = Physics::getPhysicsWorld()->createCollisionBody(Transform(position, orientation));
}

void EngineResolve::delete_body() { cb->~CollisionBody(); }

void EngineResolve::addForce(glm::vec3 force, Apply type) {
	if (type != Apply::LOCAL) 
		return;
	force_ = force;
}

void EngineResolve::addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type)
{
	return;
}

void EngineResolve::addTorque(glm::vec3 torque, Apply type)
{ return; }

void EngineResolve::addDragForce(float drag)
{ lin_drag += drag; }

void EngineResolve::addDragTorque(float ang_drag)
{ return; }

void EngineResolve::setMass(float mass)
{ 
	mass_ = mass; 
}

void EngineResolve::setCenterOfMass(glm::vec3 p)
{ return; }

void EngineResolve::setVelocity(glm::vec3 vel)
{ 
	lin_velocity_ = vel; 
}
void EngineResolve::setAngVelocity(glm::vec3 ang_vel)
{ return; }
void EngineResolve::setDragForce(float drag)
{ lin_drag = drag; }

void EngineResolve::setDragTorque(float ang_drag)
{ return; }

void EngineResolve::setType(BodyType type)
{ 
	type_ = type; 
}
void EngineResolve::setType(int type)
{
	switch (type) {
		case 0:
			type_ = BodyType::STATIC;
			break;
		case 1:
			type_ = BodyType::KINEMATIC;
			break;
		case 2:
			type_ = BodyType::DYNAMIC;
			break;
		default:
			break;
	}
}
void EngineResolve::enableGravity(bool ean)
{ 
	use_gravity_ = ean; 
}

void EngineResolve::setCanSleep(bool ean)
{ 
	can_sleep_ = ean; 
}

float EngineResolve::getMass()
{
	return mass_;
}
glm::vec3 EngineResolve::getVelocity()
{
	return lin_velocity_;
}
glm::vec3 EngineResolve::getAngVelocity()
{
	return glm::vec3(0.0f);
}
float EngineResolve::getDragForce()
{
	return 0.0f;
}
float EngineResolve::getDragTorque()
{
	return 0.0f;
}

BodyType EngineResolve::getType()
{
	return type_;
}
bool EngineResolve::getIsGravityEnabled()
{
	return use_gravity_;
}
bool EngineResolve::getCanSleep()
{
	return can_sleep_;
}

uint32_t EngineResolve::addBoxCollider(glm::vec3 pos, glm::vec3 size)
{
	BoxShape* bs = Physics::getPhysicsCommon().createBoxShape(
	    Vector3(size.x / 2, size.y / 2, size.z / 2));
	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(cb->addCollider(bs, center));
	m_box.emplace(colliders[colliders.size() - 1], bs);
	return colliders.size() - 1;
}

uint32_t EngineResolve::addSphereCollider(glm::vec3 pos, float radius)
{
	SphereShape* ss = Physics::getPhysicsCommon().createSphereShape(radius);
	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(cb->addCollider(ss, center));
	m_sphere.emplace(colliders[colliders.size() - 1], ss);
	return colliders.size() - 1;
}

uint32_t EngineResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height)
{
	CapsuleShape* cs =
	    Physics::getPhysicsCommon().createCapsuleShape(radius, height);
	Transform center =
	    Transform(Vector3(pos.x, pos.y, pos.z), Quaternion::identity());
	colliders.push_back(cb->addCollider(cs, center));
	m_capsule.emplace(colliders[colliders.size() - 1], cs);
	return colliders.size() - 1;
}

uint32_t EngineResolve::addBoxCollider(PhysicsBody* rb, glm::vec3 pos,
                                       glm::vec3 size, float bounce,
                                       float friction) {
	unsigned int index = addBoxCollider(pos, size);
	colliders[colliders.size() - 1]->setUserData(rb);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

uint32_t EngineResolve::addSphereCollider(PhysicsBody* rb, glm::vec3 pos,
                                         float radius, float bounce,
                                         float friction) {
	unsigned int index = addSphereCollider(pos, radius);
	colliders[colliders.size() - 1]->setUserData(rb);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

uint32_t EngineResolve::addCapsuleCollider(PhysicsBody* rb, glm::vec3 pos,
                                          float radius, float height,
                                          float bounce, float friction) {
	unsigned int index = addCapsuleCollider(pos, radius, height);
	colliders[colliders.size() - 1]->setUserData(rb);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

uint32_t EngineResolve::addBoxCollider(glm::vec3 pos,
                                       glm::vec3 size, float bounce,
                                       float friction) {
	unsigned int index = addBoxCollider(pos, size);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

uint32_t EngineResolve::addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
{
	unsigned int index = addSphereCollider(pos, radius);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

uint32_t EngineResolve::addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
{
	unsigned int index = addCapsuleCollider(pos, radius, height);
	Material& mat = colliders[colliders.size() - 1]->getMaterial();
	mat.setBounciness(bounce);
	mat.setFrictionCoefficient(friction);
	return index;
}

void EngineResolve::deleteCollider(Collider* collider) {
	cb->removeCollider(collider);
}




glm::vec3 EngineResolve::getPosition() {
	Vector3 p = cb->getTransform().getPosition();
	return glm::vec3(p.x, p.y, p.z);
}

glm::vec3 EngineResolve::getRotation() {
	Quaternion r = cb->getTransform().getOrientation();
	return glm::degrees(glm::eulerAngles(glm::quat(r.w, r.x, r.y, r.z)));
}

glm::quat EngineResolve::getOrientation() {
	Quaternion r = cb->getTransform().getOrientation();
	return glm::quat(r.w, r.x, r.y, r.z);
}

void EngineResolve::setPosition(glm::vec3 pos)
{
	Transform transform = cb->getTransform();
	transform.setPosition(Vector3(pos.x, pos.y, pos.z));
	cb->setTransform(transform);
}

void EngineResolve::setQuaternion(glm::quat quat)
{
	Transform transform = cb->getTransform();
	transform.setOrientation(Quaternion(quat.x, quat.y, quat.z, quat.w));
	cb->setTransform(transform);
}

void EngineResolve::setEulerRotation(glm::vec3 rot)
{
	Transform transform = cb->getTransform();
	Quaternion orientation = Quaternion::identity();
	glm::vec3 rot_radians = glm::radians(rot);

	double cy = glm::cos(rot_radians.z * 0.5);  // cosine applied on yaw
	double sy = glm::sin(rot_radians.z * 0.5);  // sine applied on yaw
	double cp = glm::cos(rot_radians.y * 0.5);  // cosine applied on pitch
	double sp = glm::sin(rot_radians.y * 0.5);  // sine applied on pitch
	double cr = glm::cos(rot_radians.x * 0.5);  // cosine applied on roll
	double sr = glm::sin(rot_radians.x * 0.5);  // sine applied on roll

	orientation.w = cr * cp * cy + sr * sp * sy;
	orientation.x = sr * cp * cy - cr * sp * sy;
	orientation.y = cr * sp * cy + sr * cp * sy;
	orientation.z = cr * cp * sy - sr * sp * cy;

	transform.setOrientation(orientation);
	cb->setTransform(transform);
}


//Physics object needed, can delete later
float EngineResolve::getAngle()
{
	return cb->getTransform().getOrientation().w;
}
void EngineResolve::setRotation(glm::vec3 rot)
{
	Transform transform = cb->getTransform();
	transform.setOrientation(
	    Quaternion(rot.x, rot.y, rot.z, transform.getOrientation().w));
	cb->setTransform(transform);
}
void EngineResolve::setAngle(float ang)
{
	Transform transform = cb->getTransform();
	Quaternion orientation = cb->getTransform().getOrientation();
	orientation.w = ang;
	transform.setOrientation(orientation);
	cb->setTransform(transform);
}