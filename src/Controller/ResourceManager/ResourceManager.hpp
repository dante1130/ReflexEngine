#pragma once

#include "TextureManager.hpp"
#include "ModelManager.hpp"

/**
 * @class A singleton class for containing other asset managers; models,
 * textures, etc.
 *
 */
class ResourceManager {
public:
	/**
	 * @brief Get the instance of the Resource Manager.
	 *
	 * @return ResourceManager&
	 */
	static ResourceManager& get_instance();

	/**
	 * @brief Get the model manager.
	 *
	 * @return ModelManager&
	 */
	ModelManager& get_model_manager();

	/**
	 * @brief Get the texture manager.
	 *
	 * @return TextureManager&
	 */
	TextureManager& get_texture_manager();

	// These are deleted as a singleton pattern is used.
	ResourceManager(ResourceManager& other) = delete;
	ResourceManager(const ResourceManager& other) = delete;
	void operator=(ResourceManager&&) = delete;
	void operator=(const ResourceManager&) = delete;

private:
	/// The texture manager.
	TextureManager texture_manager_;

	/// The model manager
	ModelManager model_manager_;

	/**
	 * @brief Construct a new Resource Manager object
	 */
	ResourceManager();
};
