#pragma once

#include <unordered_map>

#include "View/Renderer/OpenGL/Objects/Model.hpp"
#include "Controller/LuaManager.hpp"
#include <mutex>

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

	void workaround(int index);

	void set_model_table(sol::table *model_table);

	/**
	 * @brief Loads a model into the model manager.
	 *
	 * @param model_name The name given to the model.
	 * @param file_name The file name of the model.
	 * @return bool
	 */
	bool load_model(const std::string& model_name,
	                const std::string& file_name);

	bool load_model_async();

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

	std::unordered_map<std::string, std::string> file_hashmap;

	std::mutex locker;

	int counter = 0;
};
