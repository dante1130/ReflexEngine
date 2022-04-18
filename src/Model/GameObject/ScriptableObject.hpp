#pragma once

#include "GameObject.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"

class ScriptableObject : public GameObject {
public:
	/**
	 * @brief	Default constructor
	 * @param	script	- The script to run every update frame
	 * @return	Nothing
	 *
	 * @pre		Nothing
	 * @post	Script added to run
	 */
	ScriptableObject(std::string script);

	/**
	 * @brief	initialisation of game object. Not needed
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		object exists
	 * @post	Nothing
	 */
	void init(){};

	/**
	 * @brief	Updates the object by running the lua script
	 * @param	delta_time	- The time between frames
	 * @return	void
	 *
	 * @pre		lua script stored
	 * @post	Script run
	 */
	void update(float delta_time);

	/**
	 * @brief	Adds a draw call. Not used
	 * @param	No param
	 * @return	void
	 *
	 * @pre		object exists
	 * @post	Nothing
	 */
	void add_draw_call() {}

	/**
	 * @brief	Draws the object. Not used
	 * @param	shader	- The shader
	 * @return	void
	 *
	 * @pre		Object exists
	 * @post	Nothing
	 */
	void draw(std::shared_ptr<Shader> shader) {}

	/**
	 * @brief	Saves the object to lau file
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override;

	/**
	 * @brief	Destructor
	 * @param	No param
	 * @return	void
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
