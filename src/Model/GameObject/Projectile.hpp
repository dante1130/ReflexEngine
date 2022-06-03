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
	 * @param delta_time The time since the last frame.
	 */
	void update(double delta_time);

	/**
	 * @brief Updates the game object with fixed delta time.
	 *
	 * @param delta_time The time since the last fixed tick.
	 */
	void fixed_update(double delta_time);

	/**
	 * @brief Adds a draw call to the renderer.
	 */
	void add_draw_call();

	/**
	 * @brief The draw call.
	 *
	 * @param shader The shader to use.
	 */
	void draw(const Shader& shader);

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

	/**
	 * @brief Freeze the projectile.
	 */
	void freeze_projectile();

	/**
	 * @brief Removes the colliders from the rigid body
	 */
	void remove_colliders();

	/**
	 * @brief Set the time alive left for the projectile.
	 *
	 * @param time The time alive left.
	 */
	void set_time_alive_left(float time);

	/**
	 * @brief Set the damage of the projectile.
	 *
	 * @param damage The damage.
	 */
	void set_damage(float damage);

	/**
	 * @brief Set the logic script.
	 *
	 * @param script The script.
	 */
	void set_logic_script(const std::string& script);

	/**
	 * @brief Set the floor contact flag.
	 *
	 * @param val
	 */
	void set_floor_contact(bool val);

	/**
	 * @brief Set to delete flag.
	 *
	 * @param val
	 */
	void set_to_delete(bool val);

private:
	/// The time alive left.
	bool to_be_deleted_ = false;
	/// Floor contact flag
	bool floor_contact_ = false;
	/// The time alive left.
	float time_alive_left_ = 20.0f;
	/// The damage.
	float damage_ = 1.0f;
	/// The collision detection flag.
	bool collision_detected_ = false;
	/// The logic script.
	std::string lua_script_;
};
