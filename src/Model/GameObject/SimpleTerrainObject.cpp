#include "SimpleTerrainObject.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"

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

	terrain_.set_scale(scale);

	terrain_.load_mesh();
}

void SimpleTerrainObject::add_draw_call() {
	DrawCall draw_call = [this](const Shader& shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void SimpleTerrainObject::draw(const Shader& shader) {
	terrain_.render(shader);
}

void SimpleTerrainObject::save_object() {
	if (savable) {
		ObjectSaving::openFile();
		ObjectSaving::saveGameObject(position, rotation, scale, angle,
		                             "SimpleTerrainObject", savable);
		ObjectSaving::closeStruct();
		ObjectSaving::createStruct("terrain");
		ObjectSaving::addValue("texture", texture_name_, false);
		ObjectSaving::addValue("detailmap", detailmap_name_, false);
		ObjectSaving::addValue("heightmap", heightmap_name_, true);
		ObjectSaving::closeStruct();
		ObjectSaving::closeFile();
	}
}

void SimpleTerrainObject::set_heightmap_name(
    const std::string& heightmap_name) {
	heightmap_name_ = heightmap_name;
}

void SimpleTerrainObject::set_texture_name(const std::string& texture_name) {
	texture_name_ = texture_name;
}

void SimpleTerrainObject::set_detailmap_name(
    const std::string& detailmap_name) {
	detailmap_name_ = detailmap_name;
}