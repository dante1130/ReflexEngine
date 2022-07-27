#pragma once

#include <string>
#include <vector>

namespace Component {
/**
 * @brief A mesh component.
 */
struct Mesh {
	/// The mesh name in the mesh manager.
	std::string mesh_name;
	/// The material name in the material manager.
	std::string texture_name;
	/// The material name in the material manager.
	std::string material_name;

	Mesh() = default;

	Mesh(const Mesh&) = default;

	Mesh(const std::string& mesh_name, const std::string& texture_name,
	     const std::string& material_name)
	    : mesh_name(mesh_name),
	      texture_name(texture_name),
	      material_name(material_name) {}
};
};  // namespace Component