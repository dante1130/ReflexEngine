#include "MeshManager.hpp"

#include "Controller/LuaManager.hpp"
#include <iostream>

void MeshManager::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto mesh = lua["Mesh"].get_or_create<sol::table>();

	mesh["load_mesh"] = [this](const std::string& name,
	                           const sol::table& vertices,
	                           const sol::table& indices) {
		size_t vertices_size = vertices.size();
		size_t indices_size = indices.size();

		std::vector<float> vertices_vec(vertices_size);
		std::vector<uint32_t> indices_vec(indices_size);

		for (size_t i = 1; i < vertices_size; ++i) {
			vertices_vec[i - 1] = vertices[i];
		}

		for (size_t i = 1; i < indices_size; ++i) {
			indices_vec[i - 1] = indices[i];
		}

		load_mesh(name, vertices_vec, indices_vec);
	};
}

void MeshManager::load_mesh(const std::string& mesh_name,
                            const std::vector<float>& vertices,
                            const std::vector<uint32_t>& indices) {
	auto& mesh = mesh_map[mesh_name];

	mesh.create_mesh(vertices.data(), indices.data(), vertices.size(),
	                 indices.size());
}

const Mesh& MeshManager::get_mesh(const std::string& mesh_name) const {
	return mesh_map.at(mesh_name);
}