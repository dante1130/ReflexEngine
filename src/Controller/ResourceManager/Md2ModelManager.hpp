#pragma once

#include <unordered_map>

#include "View/Renderer/OpenGL/Objects/Md2Model.hpp"

/**
 * @class Md2ModelManager
 * @brief An encapsulated class for an unordered map of md2 models.
 */
class Md2ModelManager {
public:
	/**
	 * @brief Exposes the md2 model manager to lua.
	 */
	void lua_access();

	/**
	 * @brief Construct a new Md2 Model Manager object
	 */
	Md2ModelManager() = default;

	/**
	 * @brief Loads a md2 model into the md2 model manager.
	 *
	 * @param model_name
	 * @param file_name
	 * @return true
	 * @return false
	 */
	bool load_md2_model(const std::string& model_name,
	                    const std::string& file_name);

	/**
	 * @brief Loads a texture into a md2 model in the md2 model manager.
	 *
	 * @param model_name
	 * @param file_name
	 * @return true
	 * @return false
	 */
	bool load_texture(const std::string& model_name,
	                  const std::string& file_name);

	/**
	 * @brief Get the md2 model given the md2 model name.
	 *
	 * @param model_name
	 * @return const Model&
	 */
	const Md2Model& get_md2_model(const std::string& model_name) const;

	/**
	 * @brief Destroy the Md2 Model Manager object
	 */
	~Md2ModelManager();

private:
	/// A hashmap of models.
	std::unordered_map<std::string, Md2Model*> md2_model_hashmap;
};