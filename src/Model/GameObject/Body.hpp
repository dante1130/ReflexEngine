#pragma once

#include "Model/GameObject/GameObject.hpp"
#include "Controller/Physics.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"
#include "Controller/GenericFunctions.h"

class Body : public GameObject {
public:
	/**
	 * @brief	Initialises the body object
	 *
	 * @pre		Must be creator body object variant
	 * @post	Body object created
	 */
	void init();

	/**
	 * @brief	Sets if the object is a creator (true) or destructor (false). A
	 * creator should be one of the fist game objects while a destoryer should
	 * be one of the last
	 * @param	bool	- true for creator, false for destructor
	 *
	 * @pre		Object initialised
	 * @post	Creator set
	 */
	void setCreator(bool val);

	/**
	 * @brief	Updates the body object using a delta time value
	 * @param	delta_time	- The time between the last call
	 *
	 * @pre		Object initialised
	 * @post	Object updated
	 */
	void update(float delta_time);

	/**
	 * @brief	NOT CURRENTLY USED
	 *
	 * @pre		Nothing
	 * @post	Nothing
	 */
	void add_draw_call() {}

	/**
	 * @brief	NOT CURRENTLY USED
	 *
	 * @pre		Nothing
	 * @post	Nothing
	 */
	void draw(std::shared_ptr<Shader> shader) {}

	/**
	 * @brief	Adds all possible physic debugger options
	 *
	 * @pre		Object initialised
	 * @post	Physic objects added
	 */
	void physicsDebugger();

	/**
	 * @brief	Destoryes physic world
	 *
	 * @pre		Must be destroyer body object variant
	 * @post	Body object destroyed
	 */
	void physicsWorldDestroyer();

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
	 * @pre		Must be destoryer body object variant
	 * @post	Body object deleted
	 */
	~Body();

private:
	/// <summary>
	/// True if creator, false if destroyer
	/// </summary>
	bool creator = true;
};
