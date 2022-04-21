#pragma once

#include "GameObject.hpp"
#include "BttController.hpp"
#include "Controller/multiTextureCreator.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"

class TerrainObject : public GameObject {
public:
	TerrainObject();

	void init();

	void fixed_update(float delta_time) override;

	void update(float delta_time) override{};

	void add_draw_call() override;

	void draw(std::shared_ptr<Shader> shader) override;

	void save_object() override;

	void add_texture(std::string file_name);

	void add_height_map(uint8_t* heightmap, int xSize, int ySize, bool island);

	void add_detail_map(std::string file_name);

	void create_terrain(int chunckSize, int chunkDetail, int n, int heightSize,
	                    glm::vec3 scale);

	uint8_t* get_height_map();

	void add_storage_text(std::string text, int n);

private:
	BttController bttControl;
	multiTextureCreator mtc;
	float lastUpdate = -1;
	std::string m_text[6];
};
