#pragma once

#include <unordered_map>

#include "View/Renderer/OpenGL/Objects/Mesh.hpp"

/**
 * @class MeshManager
 * @brief An encapsulated class for an unordered map of meshes.
 */
class MeshManager {
public:
	MeshManager() = default;

	/**
	 * @brief Register the mesh manager to Lua.
	 */
	void lua_access();

	/**
	 * @brief Loads a mesh into the mesh manager.
	 *
	 * @param mesh_name The name given to the mesh.
	 * @param vertices The vertices of the mesh.
	 * @param indices The indices of the mesh.
	 */
	void load_mesh(const std::string& mesh_name,
	               const std::vector<float>& vertices,
	               const std::vector<uint32_t>& indices);

	const Mesh& get_mesh(const std::string& mesh_name) const;

private:
	/// A hashmap of meshes.
	std::unordered_map<std::string, Mesh> mesh_map;
};