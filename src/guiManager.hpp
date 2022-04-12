#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>
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
 * @return	Void
 */
void init(GLFWwindow* window, std::string openglVersion);

/**
 * @brief	Does per frame initialise for gui. Should be placed after glClear &
 * glClearColor in the main loop
 * @param	No param
 * @return	Void
 */
void mainLoopStart();

/**
 * @brief	Renders gui. Should be placed at the end of the main loop
 * @param	No param
 * @return	Void
 */
void mainLoopEnd();

/**
 * @brief	Shuts down gui
 * @param	No param
 * @return	Void
 */
void shutdown();

////END OF METHODS NEEDED FOR GUI TO OPERATE////

////GUI WINDOW OPERATION////
/**
 * @brief	Begins a window. Sandwich inside gui window methods between begin
 * and end.
 * @param	title	- The title of the window
 * @return	Void
 */
void begin(const std::string title);

/**
 * @brief	Begins a window. Sandwich inside gui window methods between begin
 * and end.
 * @param	title	- The title of the window
 * @return	Void
 */
void begin(const char* title);

/**
 * @brief	Ends the window. Sandwich inside gui window methods between begin
 * and end.
 * @param	No param
 * @return	Void
 */
void end();

/**
 * @brief	Sets the windows position
 *
 * @param	xPos		- x position of the window
 * @param	yPos		- y position of the window
 * @param	constraint	- The constraint of the window
 *
 * @return	Void
 */
void setWindowPos(int xPos, int yPos, int constraint);

/**
 * @brief	Sets the windows size
 *
 * @param	xSize		- x size of the window
 * @param	ySize		- y size of the window
 * @param	constraint	- The constraint of the window
 *
 * @return	Void
 */
void setWindowSize(int xSize, int ySize, int constraint);

////END OF GUI WINDOW OPERATION////

////ITEMS INSIDE GUI WINDOW////
/**
 * @brief	Displays text in the gui window
 * @param	text	- The text you want to display
 * @return	Void
 */
void text(const std::string text);

/**
 * @brief	Displays text in the gui window
 * @param	*text	- The text you want to display
 * @return	Void
 */
void text(const char* text);

/**
 * @brief	A checkbox which changes a boolean variable between true & false
 * @param	name	- The name of the value you are changing
 * @param	bool	- The boolean which is being changed
 * @return	Void
 */
void checkbox(const std::string name, bool* option);

/**
 * @brief	A checkbox which changes a boolean variable between true & false
 * @param	*name	- The name of the value you are changing
 * @param	bool	- The boolean which is being changed
 * @return	Void
 */
void checkbox(const char* name, bool* option);

/**
 * @brief	A slider which changes a float variable between min & max
 * @param	name	- The name of the value you are changing
 * @param	*value	- The value being changed
 * @param	min		- The minimum value of the value
 * @param	max		- The maximum value of the value
 * @return	Void
 */
void sliderFloat(const std::string name, float* value, float min, float max);

/**
 * @brief	A slider which changes a float variable between min & max
 * @param	*name	- The name of the value you are changing
 * @param	*value	- The value being changed
 * @param	min		- The minimum value of the value
 * @param	max		- The maximum value of the value
 * @return	Void
 */
void sliderFloat(const char* name, float* value, float min, float max);

/**
 * @brief	A slider which changes an integer variable between min & max
 * @param	name	- The name of the value you are changing
 * @param	*value	- The value being changed
 * @param	min		- The minimum value of the value
 * @param	max		- The maximum value of the value
 * @return	Void
 */
void sliderInt(const std::string name, int* value, int min, int max);

/**
 * @brief	A slider which changes an integer variable between min & max
 * @param	*name	- The name of the value you are changing
 * @param	*value	- The value being changed
 * @param	min		- The minimum value of the value
 * @param	max		- The maximum value of the value
 * @return	Void
 */
void sliderInt(const char* name, int* value, int min, int max);

/**
 * @brief	A slider which changes an angle variable between min & max
 * @param	name	- The name of the value you are changing
 * @param	*angle	- The angle you want to change
 * @param	min		- The minimum angle
 * @param	max		- The maximum angle
 * @return	Void
 */
void sliderAngle(const std::string name, float* angle, float min, float max);

/**
 * @brief	A slider which changes an angle variable between min & max
 * @param	*name	- The name of the value you are changing
 * @param	*angle	- The angle you want to change
 * @param	min		- The minimum angle
 * @param	max		- The maximum angle
 * @return	Void
 */
void sliderAngle(const char* name, float* angle, float min, float max);

/**
 * @brief	Can change values independently or use a colour picker
 * @param	name		- The name of the value you are changing
 * @param	colour[3]	- Float of 3 different variables
 * @return	Void
 */
void colourEdit3(const std::string name, float colour[3]);

/**
 * @brief	Can change values independently or use a colour picker
 * @param	*name		- The name of the value you are changing
 * @param	colour[3]	- Float of 3 different variables
 * @return	Void
 */
void colourEdit3(const char* name, float colour[3]);

/**
 * @brief	Can change values independently or use a colour picker
 * @param	name		- The name of the value you are changing
 * @param	colour[4]	- Float of 4 different variables
 * @return	Void
 */
void colourEdit4(const std::string name, float colour[4]);

/**
 * @brief	Can change values independently or use a colour picker
 * @param	*name		- The name of the value you are changing
 * @param	colour[4]	- Float of 4 different variables
 * @return	Void
 */
void colourEdit4(const char* name, float colour[4]);

/**
 * @brief	Creates a button
 * @param	name	- The name of the button
 * @return	bool	- If it has been pressed
 */
bool button(const std::string name);

/**
 * @brief	Creates a button
 * @param	*name	- The name of the button
 * @return	bool	- If it has been pressed
 */
bool button(const char* name);

/**
 * @brief	Creates a button
 * @param	name	- The name of the button
 * @param	xSize	- The size of the button in the x direction
 * @param	ySize	- The size of the button in the y direction
 * @return	bool	- If it has been pressed
 */
bool button(const std::string name, float xSize, float ySize);

/**
 * @brief	Creates a button
 * @param	*name	- The name of the button
 * @param	xSize	- The size of the button in the x direction
 * @param	ySize	- The size of the button in the y direction
 * @return	bool	- If it has been pressed
 */
bool button(const char* name, float xSize, float ySize);

/**
 * @brief	User can enter text into box and submit it with enter
 * @param	name	- The name of the input text
 * @param	*buffer	- Where to store the text input
 * @param	size	- The size of the buffer
 * @return	bool	- If it contains a character
 */
bool inputText(const std::string name, char* buffer, int size);

/**
 * @brief	User can enter text into box and submit it with enter
 * @param	*name	- The name of the input text
 * @param	*buffer	- Where to store the text input
 * @param	size	- The size of the buffer
 * @return	bool	- If it contains a character
 */
bool inputText(const char* name, char* buffer, int size);

/**
 * @brief	Creates a collapsing header (essentially a checkbox)
 * @param	name	- The name of the collapsing header
 * @return	bool	- If it is open or closed
 */
bool collapsingHeader(const std::string name);

/**
 * @brief	Creates a collapsing header (essentially a checkbox)
 * @param	*name	- The name of the collapsing header
 * @return	bool	- If it is open or closed
 */
bool collapsingHeader(const char* name);

/**
 * @brief	Creates a plot line
 * @param	name			- The name to be displayed
 * @param	*values			- The list of values
 * @param	numOfEntries	- The number of values
 * @return	void
 */
void plotLines(const std::string name, const float* values, int numOfEntries);

/**
 * @brief	Creates a plot line
 * @param	*name			- The name to be displayed
 * @param	*values			- The list of values
 * @param	numOfEntries	- The number of values
 * @return	void
 */
void plotLines(const char* name, const float* values, int numOfEntries);

/**
 * @brief	Creates a plot line
 * @param	name			- The name to be displayed
 * @param	*values			- The list of values
 * @param	numOfEntries	- The number of values
 * @param	xWindowSize		- Size of window in x direction
 * @param	yWindowSize		- Size of window in y direction
 * @return	void
 */
void plotLines(const std::string name, const float* values, int numOfEntries,
               float xWindowSize, float yWindowSize);

/**
 * @brief	Creates a plot line
 * @param	*name			- The name to be displayed
 * @param	*values			- The list of values
 * @param	numOfEntries	- The number of values
 * @param	xWindowSize		- Size of window in x direction
 * @param	yWindowSize		- Size of window in y direction
 * @return	void
 */
void plotLines(const char* name, const float* values, int numOfEntries,
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
 * @return	void
 */
void plotLines(const std::string name, const float* values, int numOfEntries,
               float minVal, float maxVal, float xWindowSize,
               float yWindowSize);

/**
 * @brief	Creates a plot line
 * @param	*name			- The name to be displayed
 * @param	*values			- The list of values
 * @param	numOfEntries	- The number of values
 * @param	minVal			- The minimum value (where graph ends)
 * @param	maxVal			- The maximum value (where graph ends)
 * @param	xWindowSize		- Size of window in x direction
 * @param	yWindowSize		- Size of window in y direction
 * @return	void
 */
void plotLines(const char* name, const float* values, int numOfEntries,
               float minVal, float maxVal, float xWindowSize,
               float yWindowSize);

/**
 * @brief	Create a progress bar
 * @param	percentage	- The percentage (0 - 100)
 * @return	void
 */
void progressBar(float percentage);

////END OF ITEMS INSIDE GUI WINDOW////

/**
 * @brief	Returns the gui framerate
 * @param	No param
 * @return	float	- The frame rate
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