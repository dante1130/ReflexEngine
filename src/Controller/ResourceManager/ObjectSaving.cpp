#include "ObjectSaving.hpp"

#include <string>

std::ofstream ObjectSaving::outfile;
std::ofstream ObjectSaving::creationScript;
int ObjectSaving::number = 0;

void ObjectSaving::setFreshSave() { number = 0; }

void ObjectSaving::appendCreationFile() {
	if (number == 0) {
		creationScript.open("scripts/save/_MasterCreation.lua");
	} else {
		creationScript.open("scripts/save/_MasterCreation.lua",
		                    std::ios_base::app);
	}

	creationScript << "addGameObject(\"scripts/save/" + std::to_string(number) +
	                      ".lua\")\n";
	creationScript.close();
	number++;
}

void ObjectSaving::saveGameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale,
                                  float angle, std::string type, bool savable) {
	/*
std::string isSavable;
if (savable) {
isSavable = "true";
outfile << "baseObject = {\n"
<< "type = \"" << type << "\",\nxPos = " << pos.x
<< ",\nyPos = " << pos.y << ",\nzPos = " << pos.z
<< ",\nxRotation = " << rot.x << ",\nyRotation = " << rot.y
<< ",\nzRotation = " << rot.z << ",\nangle = " << angle
<< ",\nxScale = " << scale.x << ",\nyScale = " << scale.y
<< ",\nzScale = " << scale.z << ",\nsavable = " << isSavable;
}
*/
}

void ObjectSaving::openFile() {
	outfile.open("scripts/save/" + std::to_string(number) + ".lua");
	appendCreationFile();
}

void ObjectSaving::addComma() { outfile << ",\n"; }

void ObjectSaving::addValue(std::string varName, int val, bool endStruct) {
	outfile << varName << " = " << val;
	if (endStruct == false) {
		outfile << ",";
	}
	outfile << "\n";
}

void ObjectSaving::addValue(std::string varName, float val, bool endStruct) {
	outfile << varName << " = " << val;
	if (endStruct == false) {
		outfile << ",";
	}
	outfile << "\n";
}

void ObjectSaving::addValue(std::string varName, std::string val,
                            bool endStruct) {
	outfile << varName << " = \"" << val << "\"";
	if (endStruct == false) {
		outfile << ",";
	}
	outfile << "\n";
}

void ObjectSaving::createStruct(std::string structName) {
	outfile << structName << " = {\n";
}

void ObjectSaving::closeStruct() { outfile << "}\n\n"; }

void ObjectSaving::closeFile() { outfile.close(); }

void ObjectSaving::addPrint() { outfile << "print(\"Here\")\n"; }
