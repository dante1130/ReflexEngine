#pragma once

#include <glm/glm.hpp>

struct LightData {
	glm::vec3 color;
	float ambient_intensity;
	float diffuse_intensity;
};

struct DirectionalLightData : public LightData {
	glm::vec3 direction;
};

struct PointLightData : public LightData {
	glm::vec3 position;
	float near;
	float far;
	float constant;
	float linear;
	float quadratic;
};

struct SpotLightData : public PointLightData {
	float edge;
};
