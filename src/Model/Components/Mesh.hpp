#pragma once

#include <string>
#include <vector>

namespace Component {
/**
 * @author Andrew Ho
 * @struct Mesh
 * @brief A mesh component, that contains the names of the mesh, texture and
 * material used in the ResourceManager.
 */
struct Mesh {
	/// The mesh name in the mesh manager.
	std::string mesh_name = {"default"};
	/// The material name in the material manager.
	std::string texture_name = {"default"};
	/// The material name in the material manager.
	std::string material_name = {"default"};

	Mesh() = default;

	Mesh(const Mesh&) = default;

	Mesh(const std::string& mesh_name, const std::string& texture_name,
	     const std::string& material_name)
	    : mesh_name(mesh_name),
	      texture_name(texture_name),
	      material_name(material_name) {}
};
};  // namespace Component