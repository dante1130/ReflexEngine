#pragma once

#include <string>
#include <glm/vec3.hpp>

namespace Component {
/**
 * @struct Terrain
 * @brief The terrain component.
 */
struct Terrain {
	/// The name of the terrain.
	std::string terrain_name;
	/// The name of the texture.
	std::string texture_name;
	/// The name of the material.
	std::string material_name;
	/// The name of the detailmap.
	std::string detailmap_name;

	/// The scale of the terrain.
	glm::vec3 scale;
};
}  // namespace Component