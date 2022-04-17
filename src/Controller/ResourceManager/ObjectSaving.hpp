#pragma once

#include "Model/GameObject/GameObject.hpp"
#include <iostream>

namespace ObjectSaving {
/**
 * @brief   Resets the number counter for the file name to 0
 * @param   No param
 * @return  Void
 *
 * @pre     nothing
 * @post    counter reset
 */
void setFreshSave();

/**
 * @brief   Opens a file to save data too
 * @param   No param
 * @return  Void
 *
 * @pre     nothing
 * @post    file opened
 */
void openFile();

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
void saveGameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, float angle,
                    std::string type);

/**
 * @brief   Adds a comma to the file
 * @param   No param
 * @return  Void
 *
 * @pre     file is open
 * @post    comma added
 */
void addComma();

/**
 * @brief   Adds a value to the file
 * @param   varName     - The name to store with the value
 * @param   val         - The value
 * @param   endStruct   - If in struct and not at end put true. Just adds comma
 * @return  Void
 *
 * @pre     file is open
 * @post    value added
 */
void addValue(std::string varName, int val, bool endStruct);

/**
 * @brief   Adds a value to the file
 * @param   varName     - The name to store with the value
 * @param   val         - The value
 * @param   endStruct   - If in struct and not at end put true. Just adds comma
 * @return  Void
 *
 * @pre     file is open
 * @post    value added
 */
void addValue(std::string varName, float val, bool endStruct);

/**
 * @brief   Adds a value to the file
 * @param   varName     - The name to store with the value
 * @param   val         - The value
 * @param   endStruct   - If in struct and not at end put true. Just adds comma
 * @return  Void
 *
 * @pre     file is open
 * @post    value added
 */
void addValue(std::string varName, std::string val, bool endStruct);

/**
 * @brief   Creates a struct in the file
 * @param   structName  - The name of the struct
 * @return  Void
 *
 * @pre     file is open
 * @post    start of struct added
 */
void createStruct(std::string structName);

/**
 * @brief   Closes the struct in the file
 * @param   No param
 * @return  Void
 *
 * @pre     file is open
 * @post    end of struct added
 */
void closeSctruct();

/**
 * @brief   Closes the file
 * @param   No param
 * @return  Void
 *
 * @pre     file is open
 * @post    file closed
 */
void closeFile();

/**
 * @brief   Adds a print line in the script (for debugging)
 * @param   No param
 * @return  Void
 *
 * @pre     file is open
 * @post    print added
 */
void addPrint();
}  // namespace ObjectSaving
