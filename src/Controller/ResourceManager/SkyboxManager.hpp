#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <sol/sol.hpp>

#include "View/Renderer/OpenGL/Objects/Skybox.hpp"

/**
 * @author Andrew Ho
 * @class SkyboxManager
 * @brief The skybox manager is used to manage the skybox faces to be used for
 * the skybox.
 */
class SkyboxManager {
public:
	/**
	 * @brief Loads a default skybox.
	 */
	SkyboxManager();

	/**
	 * @brief Register the skybox manager to Lua.
	 */
	void lua_access();

	/**
	 * @brief Load skybox faces in the map with the key as the name.
	 *
	 * @param skybox_name The name of the skybox.
	 * @param faces The faces of the skybox.
	 */
	void load_skybox(const std::string& skybox_name,
	                 const std::vector<std::string>& faces);

	/**
	 * @brief Use the skybox with the given name.
	 *
	 * @param skybox_name The name of the skybox.
	 */
	void use_skybox(const std::string& skybox_name);

	/**
	 * @brief Get the skybox.
	 *
	 * @return const Skybox&
	 */
	const Skybox& get_skybox() const;

private:
	/// The map of skybox faces.
	std::unordered_map<std::string, std::vector<std::string>> skybox_faces_map_;
	/// The skybox.
	Skybox skybox_;
};