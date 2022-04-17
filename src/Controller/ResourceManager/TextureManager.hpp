#pragma once

#include <unordered_map>

#include "Texture.hpp"
#include "Controller/LuaManager.hpp"

/**
 * @class TextureManager
 * @brief An encapsulated class for an unordered map of textures.
 * @todo Maybe a singleton?
 */
class TextureManager {
public:
	void luaAccess();

	/**
	 * @brief Construct a new Texture Manager object
	 */
	TextureManager() = default;

	/**
	 * @brief Loads a texture without alpha to the texture manager.
	 *
	 * @param texture_name
	 * @param file_path
	 * @return true
	 * @return false
	 */
	bool load_texture_rgb(const std::string& texture_name,
	                      const std::string& file_path);

	/**
	 * @brief Loads a texture with alpha to the texture manager.
	 *
	 * @param texture_name
	 * @param file_path
	 * @return true
	 * @return false
	 */
	bool load_texture_rgba(const std::string& texture_name,
	                       const std::string& file_path);

	/**
	 * @brief Get the texture given the texture name.
	 *
	 * @param texture_name
	 * @return const Texture&
	 */
	const Texture& get_texture(const std::string& texture_name) const;

	/**
	 * @brief Destroy the Texture Manager object
	 */
	~TextureManager();

private:
	std::unordered_map<std::string, Texture*> texture_hashmap;
};
