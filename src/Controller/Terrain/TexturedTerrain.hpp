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
	void render(std::shared_ptr<Shader> shader) override;

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

	/**
	 * @brief Reads an image file as a detail map.
	 *
	 * @param file_name
	 * @return true
	 * @return false
	 */
	bool load_detailmap(const char* file_name);

	void set_texture(GLuint id) {
		texture_ = std::make_shared<Texture>();
		texture_->set_texture_id(id);
	}

private:
	/// The mesh.
	std::shared_ptr<Mesh> mesh_ = nullptr;
	/// The texture.
	std::shared_ptr<Texture> texture_ = nullptr;
	/// The detailmap.
	std::shared_ptr<Texture> detailmap = nullptr;
};
