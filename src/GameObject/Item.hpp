#pragma once

#include <string>

#include "GameObject.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Material.hpp"

class Item : public GameObject {
public:
	Item(const std::string& model_path, GLfloat shininess,
	     GLfloat spec_intensity);

	void init() override {}

	void update(float delta_time) override {}

	void add_draw_call() override;

	void draw() override;

private:
	Model model_ = {};
	Material material_ = {};
};
