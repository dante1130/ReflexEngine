#include "RigidbodyManager.hpp"

#include "Controller/LuaManager.hpp"
#include "glm/vec3.hpp"

//RigidbodyManager::RigidbodyManager()
//{
//	Physics::createWorld();
//}
//
//RigidbodyManager::~RigidbodyManager()
//{
//	Physics::destroyWorld();
//}

void RigidbodyManager::lua_access()
{
	auto& lua = LuaManager::get_instance().get_state();

	auto rigidbody_table = lua["Rigidbody"].get_or_create<sol::table>();

	rigidbody_table["func"] = [this](const int& num) {
		return num;
	};

	rigidbody_table["get_position"] = [this](const entt::entity& id)
	{	return rigidbodies_[id].getPosition(); };

	rigidbody_table["get_position_y"] = [this](const entt::entity& id)
	{	return rigidbodies_[id].getPosition().y; };

	rigidbody_table["set_position"] = [this](int id, glm::vec3 pos)
	{	rigidbodies_[(entt::entity)id].setPosition(pos); };

	rigidbody_table["get_orientation"] = [this](int id) {
		return rigidbodies_[(entt::entity)id].getOrientation();
	};

	rigidbody_table["get_orientation"] = [this](int id, glm::vec3 rot) {
		return rigidbodies_[(entt::entity)id].setEulerRotation(rot);
	};
	
	rigidbody_table["get_velocity"] = [this](int id)
	{	return rigidbodies_[(entt::entity)id].getVelocity(); };

	rigidbody_table["get_angular_velocity"] = [this](int id)
	{	return rigidbodies_[(entt::entity)id].getAngVelocity(); };

	rigidbody_table["set_velocity"] = [this](int id, glm::vec3 vel)
	{	return rigidbodies_[(entt::entity)id].setVelocity(vel); };

	rigidbody_table["set_angular_velocity"] = [this](int id, glm::vec3 ang_vel)
	{	return rigidbodies_[(entt::entity)id].setAngVelocity(ang_vel); };


	rigidbody_table["add_local_force"] = [this](int id, glm::vec3 force)
	{	rigidbodies_[(entt::entity)id].addForce(force, Apply::LOCAL); };

	rigidbody_table["add_local_torque"] = [this](int id, glm::vec3 torque)
	{	return rigidbodies_[(entt::entity)id].addTorque(torque, Apply::LOCAL); };

}

void RigidbodyManager::add_rigidbody(entt::entity id, const Component::Rigidbody& rb, const Component::Transform& tf)
{
	Rigidbody r_body;

	r_body.init(true, tf.position, tf.rotation);

	r_body.setCanSleep(rb.can_sleep);
	r_body.setObjectTrigger(rb.is_trigger);
	r_body.enableGravity(rb.gravity_on);
	r_body.addDragForce(rb.linear_drag);
	r_body.addDragTorque(rb.angular_drag);

	rigidbodies_.emplace(id, r_body);

	glm::vec3 pos = r_body.getPosition();
	std::cout << "Position: x: " << pos.x << " y: " << pos.y << " z: " << pos.z << std::endl;
}

void RigidbodyManager::update_rigidbody(entt::entity id, const Component::Rigidbody& rb, Component::Transform& tf)
{
	tf.position = rigidbodies_[id].getPosition();
	tf.rotation = rigidbodies_[id].getRotation();

	if (rigidbodies_[id].getIsGravityEnabled() != rb.gravity_on)
		rigidbodies_[id].enableGravity(rb.gravity_on);
	if (rigidbodies_[id].getCanSleep() != rb.can_sleep)
		rigidbodies_[id].setCanSleep(rb.gravity_on);
	if (rigidbodies_[id].getIsTrigger() != rb.is_trigger)
		rigidbodies_[id].setObjectTrigger(rb.is_trigger);

	if (rigidbodies_[id].getDragForce() != rb.linear_drag)
		rigidbodies_[id].setDragForce(rb.linear_drag);
	if (rigidbodies_[id].getDragTorque() != rb.angular_drag)
		rigidbodies_[id].setDragTorque(rb.angular_drag);

}

Rigidbody& RigidbodyManager::get_rigidbody(entt::entity id)
{
	return rigidbodies_[id];
}


void RigidbodyManager::delete_rigidbody(entt::entity id)
{
	rigidbodies_.erase(id);
}