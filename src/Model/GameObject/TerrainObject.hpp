#pragma once

#include "GameObject.hpp"
#include "BttController.hpp"

class TerrainObject {
public:
	TerrainObject();

	void init();

	void update(float delta_time);

	void add_draw_call();

	void draw(std::shared_ptr<Shader> shader);

	void save_object();

	void addTexture();

	void addDetailMap();

private:
	BttController bttControl;
};
