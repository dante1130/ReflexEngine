#pragma once

#include "Model/GameObject/GameObject.hpp"
#include <iostream>

namespace ObjectSaving {
void setFreshSave();

void openFile();
void saveGameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, float angle,
                    std::string type);
void addComma();
void addValue(std::string varName, int val, bool endStruct);
void addValue(std::string varName, float val, bool endStruct);
void addValue(std::string varName, std::string val, bool endStruct);
void createStruct(std::string structName);
void closeSctruct();
void closeFile();

void addPrint();
}  // namespace ObjectSaving
