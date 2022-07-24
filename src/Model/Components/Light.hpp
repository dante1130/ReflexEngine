#pragma once

#include <glm/glm.hpp>

namespace Component {

struct Light {
	/// The color of the light.
	glm::vec3 color = glm::vec3(1.0f);
	/// The ambient intensity of the light.
	float ambient_intensity = 0.0f;
	/// The diffuse intensity of the light.
	float diffuse_intensity = 0.0f;
};

/**
 * @struct DirectionalLight
 * @brief A directional light component.
 */
struct DirectionalLight : public Light {
	/// The direction of the light.
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
};

/**
 * @struct PointLight
 * @brief A point light component.
 */
struct PointLight : public Light {
	/// The position of the light.
	glm::vec3 position = glm::vec3(0.0f);
	/// The constant attenuation of the light.
	float constant = 0.0f;
	/// The linear attenuation of the light.
	float linear = 0.0f;
	/// The quadratic attenuation of the light.
	float quadratic = 0.0f;
	/// The point light id in the Light manager.
	size_t light_id;
};

/**
 * @struct SpotLight
 * @brief A point light component.
 */
struct SpotLight : public PointLight {
	/// The direction of the light.
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
	/// The inner cutoff of the light.
	float edge = 0.0f;
};

};  // namespace Component