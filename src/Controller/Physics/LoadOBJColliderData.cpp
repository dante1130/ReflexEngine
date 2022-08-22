#include "LoadOBJColliderData.hpp"

#include "Model/Components/RigidBody.hpp"

#include <iostream>
#include <fstream>
#include <string>

float min(float min_val, float new_val, bool first);
float max(float max_val, float new_val, bool first);

void loadOBJColliderData::lua_access() {}

void loadOBJColliderData::load_obj_collider_data(const std::string &file) {
	// if (!entity->any_component<Component::Rigidbody>()) {
	//	return;
	// }

	// Opens file
	std::ifstream open_file(file);
	if (!open_file.is_open()) {
		return;
	}

	std::string input_line;
	std::string inner_line;
	std::stringstream ss;
	bool first_point = true;
	int counter;
	float min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0,
	      value = 0;
	// For each object in obj
	while (std::getline(open_file, input_line)) {
		// If new object
		if (input_line[0] == 'o') {
			first_point = true;
		} else if (input_line[0] == 'v' && input_line[1] == ' ') {  // If point
			ss = std::stringstream(input_line);
			counter = 0;

			while (std::getline(ss, inner_line, ' ')) {
				if (counter != 0) {
					value = std::stof(inner_line);
				}

				switch (counter) {
					case 0:
						break;
					case 1:
						min_x = min(min_x, value, first_point);
						max_x = max(max_x, value, first_point);
						break;
					case 2:
						min_y = min(min_y, value, first_point);
						max_y = max(max_y, value, first_point);
						break;
					case 3:
						min_z = min(min_z, value, first_point);
						max_z = max(max_z, value, first_point);
					default:
						break;
				}
				counter++;
			}
			first_point = false;
		}
	}
	open_file.close();
}

float min(float min_val, float new_val, bool first) {
	if (first) {
		return new_val;
	}

	if (min_val < new_val) {
		return min_val;
	}

	return new_val;
}

float max(float max_val, float new_val, bool first) {
	if (first) {
		return new_val;
	}

	if (max_val > new_val) {
		return max_val;
	}

	return new_val;
}