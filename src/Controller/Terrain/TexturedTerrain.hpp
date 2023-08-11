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
	 * @param shader The shader to use.
	 */
	void render(const Shader& shader) override;

	/**
	 * @brief Reads the heightmap and loads the mesh.
	 *
	 * @return bool
	 */
	bool load_mesh() override;

	/**
	 * @brief Reads the texture image file and loads the texture.
	 *
	 * @param file_name The file name of the image.
	 * @return bool
	 */
	bool load_texture(const char* file_name);

	/**
	 * @brief Reads an image file as a detail map.
	 *
	 * @param file_name The file name of the image.
	 * @return bool
	 */
	bool load_detailmap(const char* file_name);

	/**
	 * @brief Set the texture by the ID.
	 *
	 * @param id
	 */
	void set_texture(GLuint id);

	/**
	 * @brief Set the detail map by the ID.
	 *
	 * @param id
	 */
	void set_detailmap(GLuint id);

private:
	/// The mesh.
	std::unique_ptr<Mesh> mesh_ = nullptr;
	/// The texture.
	std::unique_ptr<Texture> texture_ = nullptr;
	/// The detailmap.
	std::unique_ptr<Texture> detailmap_ = nullptr;
};
