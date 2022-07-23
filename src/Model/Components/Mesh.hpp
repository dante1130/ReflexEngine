#pragma once

#include <string>
#include <vector>

namespace component {
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
};
};  // namespace component