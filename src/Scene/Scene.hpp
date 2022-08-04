#pragma once

#include <string>

/**
 * @class Scene
 * @brief A scene in the game.
 */
class Scene {
public:
	/**
	 * @brief Constructs a new scene.
	 *
	 * @param master_lua_script The master lua script.
	 */
	Scene(const std::string& master_lua_script)
	    : master_lua_script_(master_lua_script) {}

	/**
	 * @brief Initializes the scene.
	 */
	virtual void init() = 0;

	/**
	 * @brief	Adds a game object
	 * @param	luaScript	- The lua script of the object you want to add
	 *
	 * @pre	Nothing
	 * @post	Object adde
	 */
	virtual void add_game_object(const std::string& luaScript) = 0;

	/**
	 * @brief The function to specify controls for the mouse.
	 *
	 * @param xpos	- the x position of mouse on screen
	 * @param ypos	- the y position of mouse on screen
	 */
	virtual void mouse_controls(double xpos, double ypos) = 0;

	/**
	 * @brief The update loop of the scene.
	 *
	 * @param delta_time	- the time between frames
	 */
	virtual void update(double delta_time) = 0;

	/**
	 * @brief The fixed update loop of the scene.
	 *
	 * @param delta_time
	 */
	virtual void fixed_update(double delta_time) = 0;

	/**
	 * @brief Adds any draw calls to the renderer.
	 */
	virtual void add_draw_call() = 0;

	/**
	 * @brief	Saves game objects
	 *
	 * @pre		Game objects exists
	 * @post	Game objects saved
	 */
	virtual void save() = 0;

	/**
	 * @brief	loads game objects
	 *
	 * @pre		Game objects exists in files
	 * @post	Game objects added
	 */
	virtual void load() = 0;

	/**
	 * @brief	Deleted game objects which are considered finished
	 *
	 * @pre		Game objects exists
	 * @post	Removed bad game objects
	 */
	virtual void garbage_collection() = 0;

	/**
	 * @brief Get the master lua script
	 *
	 * @return const std::string& The master lua script
	 */
	virtual const std::string& get_master_lua_script() const = 0;

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Scene() = default;

protected:
	std::string master_lua_script_;
};
