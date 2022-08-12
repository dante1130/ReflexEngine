#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Light.hpp"
#include "OmniShadowMap.hpp"

/**
 * @class PointLight
 * @brief A point light that illuminates in a sphere.
 */
class PointLight : public Light {
public:
	PointLight() = default;

	/**
	 * @brief Construct a new Point Light object
	 *
	 * @param shadow_width The width of the shadow map.
	 * @param shadow_height The height of the shadow map.
	 * @param near The near plane of the shadow map.
	 * @param far The far plane of the shadow map.
	 * @param color The color of the light
	 * @param aIntensity The ambient intensity of the light
	 * @param dIntensity The diffuse intensity of the light
	 * @param position The position of the light
	 * @param constant The constant attenuation of the light
	 * @param linear The linear attenuation of the light
	 * @param quadratic The quadratic attenuation of the light
	 */
	PointLight(GLuint shadow_width, GLuint shadow_height, GLfloat near,
	           GLfloat far, glm::vec3 color, GLfloat aIntensity,
	           GLfloat dIntensity, glm::vec3 position, GLfloat constant,
	           GLfloat linear, GLfloat quadratic);

	/**
	 * @brief Enables the light by passing uniforms to the shader.
	 *
	 * @param ambientColorLoc
	 * @param ambientIntensityLoc
	 * @param diffuseIntensityLoc
	 * @param positionLoc
	 * @param constantLoc
	 * @param linearLoc
	 * @param quadraticLoc
	 */
	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
	              GLuint diffuseIntensityLoc, GLuint positionLoc,
	              GLuint constantLoc, GLuint linearLoc,
	              GLuint quadraticLoc) const;

	/**
	 * @brief Calculates the light's view and projection matrices.
	 *
	 * @return std::vector<glm::mat4>
	 */
	std::vector<glm::mat4> calculate_light_transforms() const;

	/**
	 * @brief Set the point light object
	 *
	 * @param color The color of the light
	 * @param aIntensity The ambient intensity of the light
	 * @param dIntensity The diffuse intensity of the light
	 * @param position The position of the light
	 * @param constant The constant attenuation of the light
	 * @param linear The linear attenuation of the light
	 * @param quadratic The quadratic attenuation of the light
	 */
	void set_point_light(glm::vec3 color, GLfloat aIntensity,
	                     GLfloat dIntensity, glm::vec3 position,
	                     GLfloat constant, GLfloat linear, GLfloat quadratic);

	const glm::vec3& get_position() const;

	const OmniShadowMap& get_shadow_map() const;

	GLfloat get_far_plane() const;

	/**
	 * @brief Destroy the Point Light object
	 */
	~PointLight() = default;

protected:
	/// The omnidirectional shadow map.
	OmniShadowMap omni_shadow_map_;

	/// Position of the light.
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	/// Equation of the light.
	GLfloat m_constant = 1.0f;
	GLfloat m_linear = 0.0f;
	GLfloat m_quadratic = 0.0f;

	GLfloat far_plane_ = 100.0f;
};
