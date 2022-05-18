#pragma once

#include <glm/glm.hpp>

struct LightData {
	glm::vec3 color = glm::vec3(1.0f);
	float ambient_intensity = 0.0f;
	float diffuse_intensity = 0.0f;
};

struct DirectionalLightData : public LightData {
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
};

struct PointLightData : public LightData {
	glm::vec3 position = glm::vec3(0.0f);
	float constant = 0.0f;
	float linear = 0.0f;
	float quadratic = 0.0f;
};

struct SpotLightData : public PointLightData {
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
	float edge = 0.0f;
};
