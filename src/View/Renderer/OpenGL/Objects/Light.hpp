#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShadowMap.hpp"

/**
 * @class Light
 * @brief A light in the scene.
 */
class Light {
public:
	Light() = default;

	/**
	 * @brief Parameterized constructor.
	 *
	 * @param shadow_width The width of the shadow map.
	 * @param shadow_height The height of the shadow map.
	 * @param color The color of the light.
	 * @param aIntensity The ambient intensity of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 */
	Light(GLuint shadow_width, GLuint shadow_height, glm::vec3 color,
	      GLfloat aIntensity, GLfloat dIntensity);

	/**
	 * @brief Get the shadow map.
	 *
	 * @return ShadowMap&
	 */
	const ShadowMap& get_shadow_map() const;

	/**
	 * @brief Returns if the light is active.
	 *
	 * @return true
	 * @return false
	 */
	bool is_active() const;

	/**
	 * @brief Destructor.
	 */
	virtual ~Light() = default;

protected:
	// Ambient lighting
	/// The color of the ambient lighting.
	glm::vec3 m_color = glm::vec3(1.0f);

	/// The intensity of the ambient lighting.
	GLfloat m_ambientIntensity = {1.0f};

	// Diffuse lighting
	/// The intensity of the diffuse lighting.
	GLfloat m_diffuseIntensity = {1.0f};

	/// The shadow map.
	ShadowMap shadow_map_ = {};

	/// The light projection.
	glm::mat4 light_projection_;

	/// Whether the light is active.
	bool is_active_ = false;
};
