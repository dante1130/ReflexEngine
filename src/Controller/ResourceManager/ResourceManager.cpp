#include "ResourceManager.hpp"

#include <future>

ResourceManager& ResourceManager::get_instance() {
	static ResourceManager instance;
	return instance;
}

ModelManager& ResourceManager::get_model_manager() { return model_manager_; }

Md2ModelManager& ResourceManager::get_md2_model_manager() {
	return md2_model_manager_;
}

TextureManager& ResourceManager::get_texture_manager() {
	return texture_manager_;
}

MaterialManager& ResourceManager::get_material_manager() {
	return material_manager_;
}

LightManager& ResourceManager::get_light_manager() { return light_manager_; }

SkyboxManager& ResourceManager::get_skybox_manager() { return skybox_manager_; }

MeshManager& ResourceManager::get_mesh_manager() { return mesh_manager_; }

TerrainManager& ResourceManager::get_terrain_manager() {
	return terrain_manager_;
}
RigidbodyManager& ResourceManager::get_rigidbody_manager() { return rigidbody_manager_;  }

ResourceManager::ResourceManager() {
	/*
	std::future<void> AsyncLoadModel = std::async(
	    std::launch::deferred, [this]() { model_manager_.lua_access();
	    });
	//texture_manager_.lua_access();
	
	//std::thread ThreadLoadModel([&]() { model_manager_.lua_access(); });
	/*
	std::thread ThreadLoadMaterial([&]() { material_manager_.lua_access(); });
	std::thread ThreadLoadMd2([&]() { md2_model_manager_.lua_access(); });
	std::thread ThreadLoadSkybox([&]() { skybox_manager_.lua_access(); });
	std::thread ThreadLoadMesh([&]() { mesh_manager_.lua_access(); });
	std::thread ThreadLoadTerrain([&]() { terrain_manager_.lua_access(); });
	//ThreadLoadTexture.join();
	ThreadLoadModel.join();
	ThreadLoadMaterial.join();
	ThreadLoadMd2.join();
	ThreadLoadSkybox.join();
	ThreadLoadMesh.join();
	ThreadLoadTerrain.join();
	*/
	//ThreadLoadModel.join();
	texture_manager_.lua_access();
	//AsyncLoadModel.get();
	model_manager_.lua_access();
	material_manager_.lua_access();
	md2_model_manager_.lua_access();
	skybox_manager_.lua_access();
	mesh_manager_.lua_access();
	terrain_manager_.lua_access();
}
