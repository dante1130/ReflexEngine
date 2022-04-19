#pragma once

#include "BodyRigid.hpp"
#include "Controller/LuaManager.hpp"

/**
 * @class Player
 * @brief The player game object.
 */
class Player : public BodyRigid {
public:
	/**
	 * @brief Initialize the game object.
	 */
	void init() override {}

	/**
	 * @brief Updates the game object.
	 *
	 * @param delta_time
	 */
	void update(float delta_time) override;

	/**
	 * @brief Adds the draw call to the renderer.
	 */
	void add_draw_call() override {}

	/**
	 * @brief The draw call function.
	 *
	 * @param shader
	 */
	void draw(std::shared_ptr<Shader> shader) override {}

	/**
	 * @brief Save the object to a lua script.
	 */
	void save_object() override;

	/**
	 * @brief Set the move speed.
	 *
	 * @param move_speed
	 */
	void set_move_speed(float move_speed);

	/**
	 * @brief Set the height.
	 *
	 * @param height
	 */
	void set_height(float height);

	/**
	 * @brief Set the collider radius.
	 *
	 * @param radius
	 */
	void set_collider_radius(float radius);

	/**
	 * @brief Sets the script for the player
	 *
	 * @param	script	- The lua script
	 */
	void set_lua_script(std::string script);

private:
	/// Player script
	std::string lua_script_;
	/// The move speed.
	float move_speed_ = 0.0f;
	/// The height.
	float height_ = 0.0f;
	/// The collider radius.
	float collider_radius_ = 0.0f;
};