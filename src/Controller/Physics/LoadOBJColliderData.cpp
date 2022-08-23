#include "LoadOBJColliderData.hpp"

#include "Model/Components/RigidBody.hpp"

#include "Controller/LuaManager.hpp"
#include <fstream>
#include <string>

#define BOUNCE 0.1
#define FRICTION 0.25

float min(float min_val, float new_val, bool first);
float max(float max_val, float new_val, bool first);

void loadOBJColliderData::lua_access() {
	auto &lua = LuaManager::get_instance().get_state();

	lua.set_function("LoadOBJCollider",
	                 &loadOBJColliderData::load_obj_collider_data);
}

void loadOBJColliderData::load_obj_collider_data(Reflex::Entity &entity,
                                                 const std::string &file) {
	if (!entity.any_component<Component::Rigidbody>()) {
		return;
	}
	Component::Rigidbody rb_comp = entity.get_component<Component::Rigidbody>();

	// Opens file
	std::ifstream open_file(file);
	if (!open_file.is_open()) {
		return;
	}

	std::string input_line;
	std::string inner_line;
	std::stringstream sstream;
	bool first_point = true;
	bool first_object = true;
	int counter;
	float min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0,
	      value = 0;
	glm::vec3 center = glm::vec3(0);
	// For each object in obj
	while (std::getline(open_file, input_line)) {
		// If new object
		if (input_line[0] == 'o') {
			first_point = true;
			if (first_object) {
				first_object = false;
				continue;
			}

			center.x = (max_x - min_x) / 2 + min_x;
			center.y = (max_y - min_y) / 2 + min_y;
			center.z = (max_z - min_z) / 2 + min_z;

			rb_comp.addBoxCollider(
			    center, glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z),
			    BOUNCE, FRICTION);

		} else if (input_line[0] == 'v' && input_line[1] == ' ') {  // If point
			sstream = std::stringstream(input_line);
			counter = 0;

			while (std::getline(sstream, inner_line, ' ')) {
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

	if (!first_object) {
		center.x = (max_x - min_x) / 2 + min_x;
		center.y = (max_y - min_y) / 2 + min_y;
		center.z = (max_z - min_z) / 2 + min_z;

		rb_comp.addBoxCollider(
		    center,
		    glm::vec3(center.x - min_x, center.y - min_y, center.z - min_z),
		    BOUNCE, FRICTION);
	}
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