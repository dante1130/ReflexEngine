#include "TerrainObject.hpp"
#include "Controller/ReflexEngine/ReflexEngine.hpp"

TerrainObject::TerrainObject() { position = glm::vec3(0.0f); }

void TerrainObject::init() { bttControl.set_scale(glm::vec3(1, 0.1, 1)); }

void TerrainObject::fixed_update(float delta_time) {
	if (glfwGetTime() - lastUpdate > 0.2) {
		bttControl.Update(ReflexEngine::get_instance().camera_.get_position());
		lastUpdate = glfwGetTime();
	}
}

void TerrainObject::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };
	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void TerrainObject::draw(std::shared_ptr<Shader> shader) {
	bttControl.render(shader);
}

void TerrainObject::add_storage_text(std::string text, int n) {
	m_text[n] = text;
}

void TerrainObject::save_object() {
	/*
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle,
	                             "TerrainObject");
	ObjectSaving::closeStruct();
	ObjectSaving::createStruct("terrain");
	ObjectSaving::addValue("text1", m_text[0], false);
	ObjectSaving::addValue("text2", m_text[1], false);
	ObjectSaving::addValue("text3", m_text[2], false);
	ObjectSaving::addValue("text4", m_text[3], false);
	ObjectSaving::addValue("detailMap", m_text[5], false);
	ObjectSaving::addValue("heightMap", m_text[4], false);
	ObjectSaving::addValue("heightSize", 241, false);
	ObjectSaving::addValue("chunkSize", 30, false);
	ObjectSaving::addValue("chunkDetail", 9, false);
	ObjectSaving::addValue("n", 3, false);
	ObjectSaving::addValue("island", true, true);
	ObjectSaving::closeStruct();
	ObjectSaving::closeFile();
	*/
}

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
