#include "TextureManager.hpp"

bool TextureManager::load_texture_rgb(const std::string& texture_name,
                                      const std::string& file_path) {
	Texture* texture = new Texture(file_path.c_str());

	if (texture->LoadTexture()) {
		texture_hashmap[texture_name] = texture;
		return true;
	}

	return false;
}

bool TextureManager::load_texture_rgba(const std::string& texture_name,
                                       const std::string& file_path) {
	Texture* texture = new Texture(file_path.c_str());

	if (texture->LoadTextureA()) {
		texture_hashmap[texture_name] = texture;
		return true;
	}

	return false;
}

const Texture& TextureManager::get_texture(
    const std::string& texture_name) const {
	// Returns a reference instead of the pointer.
	return *texture_hashmap.at(texture_name);
}

TextureManager::~TextureManager() {
	for (auto& texture : texture_hashmap) {
		delete texture.second;
	}
}
