#pragma once

#include <unordered_map>

#include "View/Renderer/OpenGL/Objects/Model.hpp"
#include "Controller/LuaManager.hpp"
/**
 * @class ModelManager
 * @brief An encapsulated class for an unordered map of models.
 */
class ModelManager {
public:
	void lua_access();

	/**
	 * @brief Construct a new Model Manager object
	 */
	ModelManager() = default;

	/**
	 * @brief Loads a model into the model manager.
	 *
	 * @param model_name
	 * @param file_name
	 * @return true
	 * @return false
	 */
	bool load_model(const std::string& model_name,
	                const std::string& file_name);

	/**
	 * @brief Get the model given the model name.
	 *
	 * @param model_name
	 * @return const Model&
	 */
	const Model& get_model(const std::string& model_name) const;

	/**
	 * @brief Destroy the Model Manager object
	 */
	~ModelManager();

private:
	/// A hashmap of models.
	std::unordered_map<std::string, Model*> model_hashmap;
};
