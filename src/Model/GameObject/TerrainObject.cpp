#include "TerrainObject.hpp"
#include "Controller/ReflexEngine/ReflexEngine.hpp"

TerrainObject::TerrainObject() {}

void TerrainObject::init() { bttControl.set_scale(glm::vec3(1, 0.1, 1)); }

void TerrainObject::fixed_update(float delta_time) {
	bttControl.Update(ReflexEngine::get_instance().camera_.get_position());
}

void TerrainObject::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };
	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void TerrainObject::draw(std::shared_ptr<Shader> shader) {
	bttControl.render(shader);
}

void TerrainObject::save_object() {}

void TerrainObject::add_texture(std::string fileName) {
	mtc.set_texture(fileName);
}

void TerrainObject::add_height_map(uint8_t* heightmap, int xSize, int ySize,
                                   bool island) {
	mtc.set_height_map(heightmap, xSize, ySize, island);
	mtc.create_multi_texture();
	bttControl.set_texture_id(mtc.get_multi_texture());
	bttControl.set_height_map(mtc.get_height_map());
}

void TerrainObject::add_detail_map(std::string fileName) {
	bttControl.load_detailmap(fileName.c_str());
}

void TerrainObject::create_terrain(int chunckSize, int chunkDetail, int n,
                                   int heightSize, glm::vec3 scale) {
	bttControl.set_scale(scale);
	bttControl.CreateTerrain(chunckSize, chunkDetail, n);
}

uint8_t* TerrainObject::get_height_map() { return mtc.get_height_map(); }
