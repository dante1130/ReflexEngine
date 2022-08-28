#pragma once

#include <glm/glm.hpp>

namespace Component {

/**
 * @author Andrew Ho
 * @struct Light
 * @brief An abstract base struct for all light components.
 */
struct Light {
	/// The width of the shadow map.
	uint32_t shadow_width = 1024U;
	/// The height of the shadow map.
	uint32_t shadow_height = 1024U;
	/// The color of the light.
	glm::vec3 color = glm::vec3(1.0f);
	/// The ambient intensity of the light.
	float ambient_intensity = 0.0f;
	/// The diffuse intensity of the light.
	float diffuse_intensity = 1.0f;
	/// The near plane of the light's projection.
	float near_plane = 1.0f;
	/// The far plane of the light's projection.
	float far_plane = 100.0f;

	Light() = default;

	Light(const Light&) = default;

	Light(uint32_t shadow_width, uint32_t shadow_height, float near_plane,
	      float far_plane, const glm::vec3& color, float ambient_intensity,
	      float diffuse_intensity)
	    : shadow_width(shadow_width),
	      shadow_height(shadow_height),
	      color(color),
	      ambient_intensity(ambient_intensity),
	      diffuse_intensity(diffuse_intensity),
	      near_plane(near_plane),
	      far_plane(far_plane) {}
};

/**
 * @author Andrew Ho
 * @struct DirectionalLight
 * @brief A directional light component.
 */
struct DirectionalLight : public Light {
	/// The orthogonal left vector of the light's projection.
	float ortho_left = -64.0f;
	/// The orthogonal right vector of the light's projection.
	float ortho_right = 64.0f;
	/// The orthogonal bottom vector of the light's projection.
	float ortho_bottom = -64.0f;
	/// The orthogonal top vector of the light's projection.
	float ortho_top = 64.0f;
	/// The direction of the light.
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);

	DirectionalLight() = default;

	DirectionalLight(const DirectionalLight&) = default;

	DirectionalLight(uint32_t shadow_width, uint32_t shadow_height,
	                 float near_plane, float far_plane, float ortho_left,
	                 float ortho_right, float ortho_bottom, float ortho_top,
	                 const glm::vec3& color, float ambient_intensity,
	                 float diffuse_intensity, const glm::vec3& direction)
	    : Light(shadow_width, shadow_height, near_plane, far_plane, color,
	            ambient_intensity, diffuse_intensity),
	      ortho_left(ortho_left),
	      ortho_right(ortho_right),
	      ortho_bottom(ortho_bottom),
	      ortho_top(ortho_top),
	      direction(direction) {}
};

/**
 * @author Andrew Ho
 * @struct PointLight
 * @brief A point light component.
 */
struct PointLight : public Light {
	/// The position of the light.
	glm::vec3 position = glm::vec3(0.0f);
	/// The constant attenuation of the light.
	float constant = 1.0f;
	/// The linear attenuation of the light.
	float linear = 0.0f;
	/// The quadratic attenuation of the light.
	float quadratic = 0.0f;
	/// The point light id in the Light manager.
	size_t light_id = 0ULL;

	PointLight() = default;

	PointLight(const PointLight&) = default;

	PointLight(uint32_t shadow_width, uint32_t shadow_height, float near_plane,
	           float far_plane, const glm::vec3& color, float ambient_intensity,
	           float diffuse_intensity, const glm::vec3& position,
	           float constant, float linear, float quadratic)
	    : Light(shadow_width, shadow_height, near_plane, far_plane, color,
	            ambient_intensity, diffuse_intensity),
	      position(position),
	      constant(constant),
	      linear(linear),
	      quadratic(quadratic) {}
};

/**
 * @author Andrew Ho
 * @struct SpotLight
 * @brief A point light component.
 */
struct SpotLight : public PointLight {
	/// The direction of the light.
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
	/// The inner cutoff of the light.
	float edge = 10.0f;

	SpotLight() = default;

	SpotLight(const SpotLight&) = default;

	SpotLight(uint32_t shadow_width, uint32_t shadow_height, float near_plane,
	          float far_plane, const glm::vec3& color, float ambient_intensity,
	          float diffuse_intensity, const glm::vec3& position,
	          float constant, float linear, float quadratic,
	          const glm::vec3& direction, float edge)
	    : PointLight(shadow_width, shadow_height, near_plane, far_plane, color,
	                 ambient_intensity, diffuse_intensity, position, constant,
	                 linear, quadratic),
	      direction(direction),
	      edge(edge) {}
};

};  // namespace Component