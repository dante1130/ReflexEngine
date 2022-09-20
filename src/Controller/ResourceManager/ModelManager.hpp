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
	/**
	 * @brief Construct a new Model Manager object
	 */
	ModelManager() = default;

	/**
	 * @brief Exposes the model manager to Lua.
	 */
	void lua_access();

	/**
	 * @brief Loads a model into the model manager.
	 *
	 * @param model_name The name given to the model.
	 * @param file_name The file name of the model.
	 * @return bool
	 */
	bool load_model(const std::string& model_name,
	                const std::string& file_name);

	static bool load_model_async(Model* model, std::string model_name, std::string file_name);

	/**
	 * @brief Get the model given the model name.
	 *
	 * @param model_name The name given to the model.
	 * @return const Model&
	 */
	Model& get_model(const std::string& model_name);

private:
	/// A hashmap of models.
	std::unordered_map<std::string, Model> model_hashmap;
};
