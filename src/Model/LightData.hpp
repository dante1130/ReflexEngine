#pragma once

#include <glm/glm.hpp>

/**
 * @struct LightData
 * @brief A struct containing the data for a light.
 */
struct LightData {
	/// The color of the light.
	glm::vec3 color = glm::vec3(1.0f);
	/// The ambient intensity of the light.
	float ambient_intensity = 0.0f;
	/// The diffuse intensity of the light.
	float diffuse_intensity = 0.0f;
};

/**
 * @struct DirectionalLightData
 * @brief A struct containing the data for a directional light.
 */
struct DirectionalLightData : public LightData {
	/// The direction of the light.
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
};

/**
 * @struct PointLightData
 * @brief A struct containing the data for a point light.
 */
struct PointLightData : public LightData {
	/// The position of the light.
	glm::vec3 position = glm::vec3(0.0f);
	/// The constant attenuation of the light.
	float constant = 0.0f;
	/// The linear attenuation of the light.
	float linear = 0.0f;
	/// The quadratic attenuation of the light.
	float quadratic = 0.0f;
};

/**
 * @struct SpotLightData
 * @brief A struct containing the data for a spot light.
 */
struct SpotLightData : public PointLightData {
	/// The direction of the light.
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
	/// The inner cutoff of the light.
	float edge = 0.0f;
};
