#pragma once
#include "PhysicsObject.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"

class Projectile : public PhysicsObject {
public:
	/**
	 * @brief Initializes the game object.
	 */
	void init();

	/**
	 * @brief Updates the game object with delta time.
	 *
	 * @param delta_time
	 */
	void update(float delta_time);

	/**
	 * @brief Updates the game object with fixed delta time.
	 *
	 * @param delta_time
	 */
	void fixed_update(float delta_time);

	/**
	 * @brief Adds a draw call to the renderer.
	 */
	void add_draw_call();

	/**
	 * @brief The draw call.
	 *
	 * @param shader
	 */
	void draw(std::shared_ptr<Shader> shader);

	/**
	 * @brief	Saves the object to lua file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object();

	/**
	 * @brief default destructor.
	 */
	~Projectile() = default;

	void freeze_projectile();

	/**
	 * @brief removes the colliders from the rigid body
	 */
	void remove_colliders();

	void set_time_alive_left(float time);
	void set_damage(float damage);
	void set_logic_script(std::string script);
	void set_floor_contact(bool val);
	void set_to_delete(bool val);

private:
	bool to_be_deleted_ = false;
	bool floor_contact_ = false;
	float time_alive_left_ = 20;
	float damage_ = 1;
	bool collision_detected_ = false;
	std::string lua_script_;
};
