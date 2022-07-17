#pragma once

#include "Model/GameObject/GameObject.hpp"
#include <fstream>

/**
 * @class ObjectSaving
 * @brief Class that writes the data of the game objects to a lua script, so it
 * can be used to load the game objects into the scene.
 */
class ObjectSaving {
public:
	/**
	 * @brief   Resets the number counter for the file name to 0
	 * @param   No param
	 * @return  Void
	 *
	 * @pre     nothing
	 * @post    counter reset
	 */
	static void setFreshSave();

	/**
	 * @brief On first call, opens the creation script file. And then adds the
	 * save files in number order into the creation script.
	 */
	static void appendCreationFile();

	/**
	 * @brief   Opens a file to save data too
	 * @param   No param
	 * @return  Void
	 *
	 * @pre     nothing
	 * @post    file opened
	 */
	static void openFile();

	/**
	 * @brief   Saves a base game object to a file
	 * @param   pos     - The position of the base object
	 * @param   rot     - The axis of rotation of the base object
	 * @param   scale   - The scale of the base object
	 * @param   angle   - The angle of rotation of the base object
	 * @param   type    - The type of the object (e.g,. ScriptableObject)
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    base object paramaters saved
	 */
	static void saveGameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale,
	                           float angle, std::string type, bool savable);

	/**
	 * @brief   Adds a comma to the file
	 * @param   No param
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    comma added
	 */
	static void addComma();

	/**
	 * @brief   Adds a value to the file
	 * @param   varName     - The name to store with the value
	 * @param   val         - The value
	 * @param   endStruct   - If in struct and not at end put true. Just adds
	 * comma
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    value added
	 */
	static void addValue(std::string varName, int val, bool endStruct);

	/**
	 * @brief   Adds a value to the file
	 * @param   varName     - The name to store with the value
	 * @param   val         - The value
	 * @param   endStruct   - If in struct and not at end put true. Just adds
	 * comma
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    value added
	 */
	static void addValue(std::string varName, float val, bool endStruct);

	/**
	 * @brief   Adds a value to the file
	 * @param   varName     - The name to store with the value
	 * @param   val         - The value
	 * @param   endStruct   - If in struct and not at end put true. Just adds
	 * comma
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    value added
	 */
	static void addValue(std::string varName, std::string val, bool endStruct);

	/**
	 * @brief   Creates a struct in the file
	 * @param   structName  - The name of the struct
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    start of struct added
	 */
	static void createStruct(std::string structName);

	/**
	 * @brief   Closes the struct in the file
	 * @param   No param
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    end of struct added
	 */
	static void closeStruct();

	/**
	 * @brief   Closes the file
	 * @param   No param
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    file closed
	 */
	static void closeFile();

	/**
	 * @brief   Adds a print line in the script (for debugging)
	 * @param   No param
	 * @return  Void
	 *
	 * @pre     file is open
	 * @post    print added
	 */
	static void addPrint();

private:
	static std::ofstream outfile;
	static std::ofstream creationScript;
	static int number;
};
