#include "SkyboxManager.hpp"

#include "Controller/LuaManager.hpp"

SkyboxManager::SkyboxManager() {
	
	static const std::vector<std::string> default_skybox = {
	    "textures/skyboxes/default/right.jpg",
	    "textures/skyboxes/default/left.jpg",
	    "textures/skyboxes/default/top.jpg",
	    "textures/skyboxes/default/bottom.jpg",
	    "textures/skyboxes/default/front.jpg",
	    "textures/skyboxes/default/back.jpg"};

	load_skybox("default", default_skybox);
	
}

void SkyboxManager::lua_access() {
	
	auto& lua = LuaManager::get_instance().get_state();

	auto skybox_table = lua.create_named_table("Skybox");

	
	skybox_table["load_skybox"] = [this](const std::string& skybox_name,
	                                     const sol::table& faces) {
		std::vector<std::string> skybox_faces;
		std::string faces_right = faces["right"];
		std::string faces_left = faces["left"];
		std::string faces_top = faces["top"];
		std::string faces_bottom = faces["bottom"];
		std::string faces_front = faces["front"];
		std::string faces_back = faces["back"];
		skybox_faces.reserve(6);
		
		skybox_faces.emplace_back(faces_right);
		skybox_faces.emplace_back(faces_left);
		skybox_faces.emplace_back(faces_top);
		skybox_faces.emplace_back(faces_bottom);
		skybox_faces.emplace_back(faces_front);
		skybox_faces.emplace_back(faces_back);
		
		load_skybox(skybox_name, skybox_faces);
	};
	
	skybox_table.set_function("use_skybox", &SkyboxManager::use_skybox, this);
	
}

void SkyboxManager::load_skybox(const std::string& skybox_name,
                                const std::vector<std::string>& faces) {
	skybox_faces_map_[skybox_name] = faces;
}

void SkyboxManager::use_skybox(const std::string& skybox_name) {
	skybox_ = Skybox(skybox_faces_map_.at(skybox_name));
}

const Skybox& SkyboxManager::get_skybox() const { return skybox_; }