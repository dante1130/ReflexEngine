#include "SimpleTerrainObject.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"

void SimpleTerrainObject::init() {
	auto& texture_manager =
	    ResourceManager::get_instance().get_texture_manager();

	if (!texture_name_.empty()) {
		const auto& texture = texture_manager.get_texture(texture_name_);
		terrain_.set_texture(texture.get_texture_id());
	}

	if (!detailmap_name_.empty()) {
		const auto& texture = texture_manager.get_texture(detailmap_name_);
		terrain_.set_detailmap(texture.get_texture_id());
	}

	terrain_.load_mesh();
}

void SimpleTerrainObject::add_draw_call() {
	DrawCall draw_call = [this](const Shader& shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void SimpleTerrainObject::draw(const Shader& shader) {
	terrain_.render(shader);
}
