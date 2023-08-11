#pragma once

#include <unordered_map>

#include "View/Renderer/OpenGL/Objects/Texture.hpp"

/**
 * @class TextureManager
 * @brief An encapsulated class for an unordered map of textures.
 */
class TextureManager {
public:
	/**
	 * @brief Construct a new Texture Manager object
	 */
	TextureManager() = default;

	/**
	 * @brief Expose the TextureManager to Lua.
	 */
	void lua_access();

	/**
	 * @brief Loads a texture without alpha to the texture manager.
	 *
	 * @param texture_name The name of the texture.
	 * @param file_path The path to the texture file.
	 * @return bool
	 */
	bool load_texture(const std::string& texture_name,
	                  const std::string& file_path);

	/**
	 * @brief Loads a texture with alpha to the texture manager.
	 *
	 * @param texture_name The name of the texture.
	 * @param file_path The path to the texture file.
	 * @return bool
	 */
	bool load_texture_rgba(const std::string& texture_name,
	                       const std::string& file_path);

	/**
	 * @brief Get the texture given the texture name.
	 *
	 * @param texture_name The name of the texture.
	 * @return const Texture&
	 */
	Texture& get_texture(const std::string& texture_name);

private:
	/// The unordered map of string as key to value of textures.
	std::unordered_map<std::string, Texture> texture_hashmap;
};
