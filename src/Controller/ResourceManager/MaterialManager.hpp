#pragma once

#include <unordered_map>

#include "View/Renderer/OpenGL/Objects/Material.hpp"
#include "Controller/LuaManager.hpp"

/**
 * @class ModelManager
 * @brief An encapsulated class for an unordered map of models.
 */
class MaterialManager {
public:
	/**
	 * @brief Construct a new Material Manager object
	 */
	MaterialManager() = default;

	/**
	 * @brief Expose the MaterialManager to Lua
	 */
	void lua_access();

	/**
	 * @brief Load a material into the material manager.
	 *
	 * @param material_name
	 * @param shine
	 * @param spec_intensity
	 * @return true
	 * @return false
	 */
	bool load_material(const std::string& material_name, float shine,
	                   float spec_intensity);

	/**
	 * @brief Get the model given the model name.
	 *
	 * @param material_name
	 * @return const Reflex::Material&
	 */
	const Reflex::Material& get_material(
	    const std::string& material_name) const;

	/**
	 * @brief Destroy the Model Manager object
	 */
	~MaterialManager();

private:
	std::unordered_map<std::string, Reflex::Material*> material_hashmap;
};
