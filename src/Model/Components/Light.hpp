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

	Light() = default;

	Light(const Light&) = default;

	Light(const glm::vec3& color, float ambient_intensity,
	      float diffuse_intensity)
	    : color(color),
	      ambient_intensity(ambient_intensity),
	      diffuse_intensity(diffuse_intensity) {}
};

/**
 * @struct DirectionalLight
 * @brief A directional light component.
 */
struct DirectionalLight : public Light {
	/// The direction of the light.
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);

	DirectionalLight() = default;

	DirectionalLight(const DirectionalLight&) = default;

	DirectionalLight(const glm::vec3& color, float ambient_intensity,
	                 float diffuse_intensity, const glm::vec3& direction)
	    : Light(color, ambient_intensity, diffuse_intensity),
	      direction(direction) {}
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
	size_t light_id = 0ULL;

	PointLight() = default;

	PointLight(const PointLight&) = default;

	PointLight(const glm::vec3& color, float ambient_intensity,
	           float diffuse_intensity, const glm::vec3& position,
	           float constant, float linear, float quadratic)
	    : Light(color, ambient_intensity, diffuse_intensity),
	      position(position),
	      constant(constant),
	      linear(linear),
	      quadratic(quadratic) {}
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

	SpotLight() = default;

	SpotLight(const SpotLight&) = default;

	SpotLight(const glm::vec3& color, float ambient_intensity,
	          float diffuse_intensity, const glm::vec3& position,
	          float constant, float linear, float quadratic,
	          const glm::vec3& direction, float edge)
	    : PointLight(color, ambient_intensity, diffuse_intensity, position,
	                 constant, linear, quadratic),
	      direction(direction),
	      edge(edge) {}
};

};  // namespace Component