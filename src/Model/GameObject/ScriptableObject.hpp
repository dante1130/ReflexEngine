#pragma once

#include "GameObject.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"

class ScriptableObject : public GameObject {
public:
	/**
	 * @brief	Default constructor
	 * @param	script	- The script to run every update frame
	 *
	 * @pre		Nothing
	 * @post	Script added to run
	 */
	ScriptableObject(const std::string& script);

	/**
	 * @brief	initialisation of game object. Not needed
	 *
	 * @pre		object exists
	 * @post	Nothing
	 */
	void init() override {}

	/**
	 * @brief	Updates the object by running the lua script
	 * @param	delta_time	- The time between frames
	 *
	 * @pre		lua script stored
	 * @post	Script run
	 */
	void update(double delta_time) override;

	/**
	 * @brief Updates the body object with fixed delta time.
	 *
	 * @param delta_time The time since the last fixed tick.
	 */
	void fixed_update(double delta_time) override {}

	/**
	 * @brief	Adds a draw call. Not used
	 *
	 * @pre		object exists
	 * @post	Nothing
	 */
	void add_draw_call() override {}

	/**
	 * @brief	Draws the object. Not used
	 * @param	shader	- The shader
	 *
	 * @pre		Object exists
	 * @post	Nothing
	 */
	void draw(const Shader& shader) override {}

	/**
	 * @brief	Saves the object to lau file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override;

	/**
	 * @brief	Destructor
	 *
	 * @pre		Object exists
	 * @post	Object deleted
	 */
	~ScriptableObject(){};

private:
	/// <summary>
	/// Lua script to run every update frame
	/// </summary>
	std::string scriptPath;
};
