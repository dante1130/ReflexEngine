#pragma once

#include "Light.hpp"
#include "ShadowMap.hpp"

/**
 * @class DirectionalLight
 * @brief A directional light that provides global illumination.
 */
class DirectionalLight : public Light {
public:
	/**
	 * @brief Construct a new Directional Light
	 */
	DirectionalLight() = default;

	/**
	 * @brief Parameterized constructor.
	 *
	 * @param shadow_width The width of the shadow map.
	 * @param shadow_height The height of the shadow map.
	 * @param light_projection The light projection, orthogonal.
	 * @param color The color of the light.
	 * @param aIntensity The ambient intensity of the light.
	 * @param direction The direction of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 */
	DirectionalLight(GLuint shadow_width, GLuint shadow_height,
	                 const glm::mat4& light_projection, const glm::vec3& color,
	                 GLfloat aIntensity, const glm::vec3& direction,
	                 GLfloat dIntensity);

	/**
	 * @brief Set the directional light object
	 *
	 * @param color The color of the light.
	 * @param aIntensity The ambient intensity of the light.
	 * @param direction The direction of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 */
	void set_directional_light(glm::vec3 color, GLfloat aIntensity,
	                           glm::vec3 direction, GLfloat dIntensity);

	/**
	 * @brief Calculates the light transform.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 calculate_light_transform() const;

	/**
	 * @brief Enables the light by passing the uniforms to the shader.
	 *
	 * @param ambientColorLoc The location of the ambient color uniform.
	 * @param ambientIntensityLoc The location of the ambient intensity uniform.
	 * @param directionLoc The location of the direction uniform.
	 * @param diffuseIntensityLoc The location of the diffuse intensity uniform.
	 */
	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
	              GLuint directionLoc, GLuint diffuseIntensityLoc) const;

	const ShadowMap& get_shadow_map() const;

	/**
	 * @brief Destructor.
	 */
	~DirectionalLight() = default;

private:
	/// The shadow map.
	ShadowMap shadow_map_;

	/// The direction the light is facing.
	glm::vec3 m_direction;
};
