#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gui {
////METHOD NEEDED FOR GUI TO OPERATE////
/**
 * @brief	Initialises gui
 *
 * @param	window			- The GLFW window
 * @param	openglVersion	- String of opengl version. I.e., OpenGL 4.6 uses
 * "#version 460", check imGUI documentation if unsure
 *
 * @pre		GLFW window & correct opengl version
 * @post	gui initialised
 */
void init(GLFWwindow* window, std::string openglVersion);

/**
 * @brief	Does per frame initialise for gui. Should be placed after glClear &
 * glClearColor in the main loop
 *
 * @pre		Init has been run for the window
 * @post	start gui frame
 */
void mainLoopStart();

/**
 * @brief	Renders gui. Should be placed at the end of the main loop
 *
 * @pre		mainLoopStart has been run
 * @post	ends gui frame
 */
void mainLoopEnd();

/**
 * @brief	Shuts down gui
 *
 * @pre		gui running
 * @post	gui stopped
 */
void shutdown();

////END OF METHODS NEEDED FOR GUI TO OPERATE////

////GUI WINDOW OPERATION////
/**
 * @brief	Begins a window. Sandwich inside gui window methods between begin
 * and end.
 * @param	title	- The title of the window
 *
 * @pre		rui running
 * @post	window created
 */
void begin(const std::string title);

/**
 * @brief	Ends the window. Sandwich inside gui window methods between begin
 * and end.
 *
 * @pre		window created
 * @post	window ended
 */
void end();

/**
 * @brief	Sets the windows position
 * @param	xPos		- x position of the window
 * @param	yPos		- y position of the window
 * @param	constraint	- The constraint of the window
 *
 * @pre		window created
 * @post	window position adjusted
 */
void setWindowPos(int xPos, int yPos, int constraint);

/**
 * @brief	Sets the windows size
 * @param	xSize		- x size of the window
 * @param	ySize		- y size of the window
 * @param	constraint	- The constraint of the window
 *
 * @pre		window created
 * @post	window size adjusted
 */
void setWindowSize(int xSize, int ySize, int constraint);

////END OF GUI WINDOW OPERATION////

////ITEMS INSIDE GUI WINDOW////
/**
 * @brief	Displays text in the gui window
 * @param	text	- The text you want to display
 *
 * @pre		window created
 * @post	module added
 */
void text(const std::string text);

/**
 * @brief	A checkbox which changes a boolean variable between true & false.
 * Not lua ready
 * @param	name	- The name of the value you are changing
 * @param	bool	- The boolean which is being changed
 *
 * @pre		window created
 * @post	module added
 */
void checkbox(const std::string name, bool* option);

/**
 * @brief	A checkbox which changes a boolean variable between true & false.
 * Lua ready
 * @param	name	- The name of the value you are changing
 * @param	state	- current state of checkbox
 * @return	bool	- Current checkbox state
 *
 * @pre		window created
 * @post	module added
 */
bool luaCheckBox(const std::string name, bool state);

/**
 * @brief	A slider which changes a float variable between min & max
 * @param	name	- The name of the value you are changing
 * @param	*value	- The value being changed
 * @param	min		- The minimum value of the value
 * @param	max		- The maximum value of the value
 *
 * @pre		window created
 * @post	module added
 */
void sliderFloat(const std::string name, float* value, float min, float max);

/**
 * @brief	A slider which changes an integer variable between min & max
 * @param	name	- The name of the value you are changing
 * @param	*value	- The value being changed
 * @param	min		- The minimum value of the value
 * @param	max		- The maximum value of the value
 *
 * @pre		window created
 * @post	module added
 */
void sliderInt(const std::string name, int* value, int min, int max);

/**
 * @brief	A slider which changes an angle variable between min & max
 * @param	name	- The name of the value you are changing
 * @param	*angle	- The angle you want to change
 * @param	min		- The minimum angle
 * @param	max		- The maximum angle
 *
 * @pre		window created
 * @post	module added
 */
void sliderAngle(const std::string name, float* angle, float min, float max);

/**
 * @brief	Can change values independently or use a colour picker
 * @param	name		- The name of the value you are changing
 * @param	colour[3]	- Float of 3 different variables
 *
 * @pre		window created
 * @post	module added
 */
void colourEdit3(const std::string name, float colour[3]);

/**
 * @brief	Can change values independently or use a colour picker
 * @param	name		- The name of the value you are changing
 * @param	colour[4]	- Float of 4 different variables
 *
 * @pre		window created
 * @post	module added
 */
void colourEdit4(const std::string name, float colour[4]);

/**
 * @brief	Creates a button
 * @param	name	- The name of the button
 * @return	bool	- If it has been pressed
 *
 * @pre		window created
 * @post	module added
 */
bool button(const std::string name, int xSize, int ySize);

/**
 * @brief	User can enter text into box and submit it with enter. Lua script
 * ready
 * @param	name		- The name of the input text
 * @return	std::stirng	- String of the current buffer
 *
 * @pre		window created
 * @post	module added
 */
std::string luaInputText(const std::string name);

/**
 * @brief	User can enter text into box and submit it with enter. Not lua
 * script ready
 * @param	name	- The name of the input text
 * @param	*buffer	- Where to store the text input
 * @param	size	- The size of the buffer
 * @return	bool	- If it contains a character
 *
 * @pre		window created
 * @post	module added
 */
bool inputText(const std::string name, char* buffer, int size);

/**
 * @brief	Creates a collapsing header (essentially a checkbox)
 * @param	name	- The name of the collapsing header
 * @return	bool	- If it is open or closed
 *
 * @pre		window created
 * @post	module added
 */
bool collapsingHeader(const std::string name);

/**
 * @brief	Creates a plot line
 * @param	name			- The name to be displayed
 * @param	*values			- The list of values
 * @param	numOfEntries	- The number of values
 *
 * @pre		window created
 * @post	module added
 */
void plotLines(const std::string name, const float* values, int numOfEntries);

/**
 * @brief	Creates a plot line
 * @param	name			- The name to be displayed
 * @param	*values			- The list of values
 * @param	numOfEntries	- The number of values
 * @param	xWindowSize		- Size of window in x direction
 * @param	yWindowSize		- Size of window in y direction
 *
 * @pre		window created
 * @post	module added
 */
void plotLines(const std::string name, const float* values, int numOfEntries,
               float xWindowSize, float yWindowSize);

/**
 * @brief	Creates a plot line
 * @param	name			- The name to be displayed
 * @param	*values			- The list of values
 * @param	numOfEntries	- The number of values
 * @param	minVal			- The minimum value (where graph ends)
 * @param	maxVal			- The maximum value (where graph ends)
 * @param	xWindowSize		- Size of window in x direction
 * @param	yWindowSize		- Size of window in y direction
 *
 * @pre		window created
 * @post	module added
 */
void plotLines(const std::string name, const float* values, int numOfEntries,
               float minVal, float maxVal, float xWindowSize,
               float yWindowSize);

/**
 * @brief	Create a progress bar
 * @param	percentage	- The percentage (0 - 100)
 *
 * @pre		window created
 * @post	module added
 */
void progressBar(float percentage);

////END OF ITEMS INSIDE GUI WINDOW////

/**
 * @brief	Returns the gui framerate
 * @param	No param
 * @return	float	- The frame rate
 *
 * @pre		gui running
 * @post	framerate returned
 */
float guiFrameRate();

enum {
	/// <summary>
	/// Window constraints always enforced. I.e., window size & pos
	/// </summary>
	SET_WINDOW_CONSTRAINTS_ALWAYS = 1,

	/// <summary>
	/// Window constraints enforced on program execution. I.e., window size &
	/// pos
	/// </summary>
	SET_WINDOW_CONSTRAINTS_ON_EXECUTION = 2,

	/// <summary>
	/// Window constraints enforced on first ever launch. I.e., window size &
	/// pos
	/// </summary>
	SET_WINDOW_CONSTRAINT_ON_FIRST_USE_EVER = 4,

	/// <summary>
	/// Window constraints enforced when window appears. I.e., window size & pos
	/// </summary>
	SET_WINDOW_CONSTRAINTS_WHEN_ACTIVATED = 8,

};

}  // namespace gui

#endif
