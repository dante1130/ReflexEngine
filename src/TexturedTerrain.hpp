#pragma once

#include "Terrain.hpp"

/**
 * @class TexturedTerrain
 * @brief A terrain that uses a texture to render the terrain.
 */
class TexturedTerrain : public Terrain {
public:
	/**
	 * @brief Renders the terrain.
	 *
	 * @param shader
	 */
	void render(const Shader* shader) override;

	/**
	 * @brief Reads the heightmap and loads the mesh.
	 *
	 * @return true
	 * @return false
	 */
	bool load_mesh() override;

	/**
	 * @brief Reads the texture image file and loads the texture.
	 *
	 * @param file_name
	 * @return true
	 * @return false
	 */
	bool load_texture(const char* file_name);

private:
	/// The mesh.
	std::shared_ptr<Mesh> mesh_ = nullptr;
	/// The texture.
	std::shared_ptr<Texture> texture_ = nullptr;
};