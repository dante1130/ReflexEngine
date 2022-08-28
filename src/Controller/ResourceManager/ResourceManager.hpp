#pragma once

#include "TextureManager.hpp"
#include "ModelManager.hpp"
#include "MaterialManager.hpp"
#include "Md2ModelManager.hpp"
#include "LightManager.hpp"
#include "SkyboxManager.hpp"
#include "MeshManager.hpp"
#include "RigidbodyManager.hpp"
#include "TerrainManager.hpp"

/**
 * @class ResourceManager
 * @brief A singleton class for containing other asset managers.
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
	 * @brief Get the md2 model manager.
	 *
	 * @return Md2ModelManager&
	 */
	Md2ModelManager& get_md2_model_manager();

	/**
	 * @brief Get the texture manager.
	 *
	 * @return TextureManager&
	 */
	TextureManager& get_texture_manager();

	/**
	 * @brief Get the material manager.
	 *
	 * @return MaterialManager&
	 */
	MaterialManager& get_material_manager();

	/**
	 * @brief Get the light manager.
	 *
	 * @return LightManager&
	 */
	LightManager& get_light_manager();

	/**
	 * @brief Get the skybox manager.
	 *
	 * @return SkyboxManager&
	 */
	SkyboxManager& get_skybox_manager();

	/**
	 * @brief Get the rigidbody manager.
	 *
	 * @return RigidbodyManager&
	 */
	RigidbodyManager& get_rigidbody_manager();

	/**
	 * @brief Get the mesh manager.
	 *
	 * @return MeshManager&
	 */
	MeshManager& get_mesh_manager();

	/**
	 * @brief Get the terrain manager.
	 *
	 * @return TerrainManager&
	 */
	TerrainManager& get_terrain_manager();


	// These are deleted as a singleton pattern is used.
	ResourceManager(ResourceManager& other) = delete;
	ResourceManager(const ResourceManager& other) = delete;
	void operator=(ResourceManager&&) = delete;
	void operator=(const ResourceManager&) = delete;

private:
	/// The texture manager.
	TextureManager texture_manager_ = {};

	/// The model manager.
	ModelManager model_manager_ = {};

	/// The md2 model manager.
	Md2ModelManager md2_model_manager_ = {};

	/// The material manager.
	MaterialManager material_manager_ = {};

	/// The light manager.
	LightManager light_manager_ = {};

	/// The skybox manager.
	SkyboxManager skybox_manager_ = {};

	/// The rigidbody manager.
	RigidbodyManager rigidbody_manager_;

	/// The mesh manager.
	MeshManager mesh_manager_ = {};

	/// The terrain manager.
	TerrainManager terrain_manager_ = {};


	/**
	 * @brief Construct a new Resource Manager object
	 */
	ResourceManager();
};
