#pragma once

#include <string>
#include <glm/vec3.hpp>

namespace Component {
/**
 * @author Andrew Ho
 * @struct Terrain
 * @brief The terrain component.
 */
struct Terrain {
	/// The name of the terrain.
	std::string terrain_name = {"default"};
	/// The name of the texture.
	std::string texture_name = {"default"};
	/// The name of the material.
	std::string material_name = {"default"};
	/// The name of the detailmap.
	std::string detailmap_name = {"default"};

	Terrain() = default;

	Terrain(const Terrain&) = default;

	Terrain(const std::string& terrain_name, const std::string& texture_name,
	        const std::string& material_name, const std::string& detailmap_name)
	    : terrain_name(terrain_name),
	      texture_name(texture_name),
	      material_name(material_name),
	      detailmap_name(detailmap_name) {}
};
}  // namespace Component