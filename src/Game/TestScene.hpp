#pragma once

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Scene.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "GameObject/Item.hpp"
#include "DirectionalLight.hpp"

class TestScene : public Scene {
public:
	TestScene();

	void init() override;

	void update(float delta_time) override {}

	void draw() override;

private:
	DirectionalLight directional_light_ = {};
};
