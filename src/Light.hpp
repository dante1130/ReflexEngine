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
	/**
	 * @brief Default constructor.
	 */
	Light();

	/**
	 * @brief Parameterized constructor.
	 *
	 * @param shadowWidth
	 * @param shadowHeight
	 * @param color
	 * @param aIntensity
	 * @param dIntensity
	 */
	Light(GLuint shadowWidth, GLuint shadowHeight, glm::vec3 color,
	      GLfloat aIntensity, GLfloat dIntensity);

	/**
	 * @brief Returns a pointer to the shadow map.
	 *
	 * @return ShadowMap*
	 */
	ShadowMap* GetShadowMap() const;

	/**
	 * @brief Destructor.
	 */
	~Light();

protected:
	// Ambient lighting
	/// The color of the ambient lighting.
	glm::vec3 m_color;
	/// The intensity of the ambient lighting.
	GLfloat m_ambientIntensity;

	// Diffuse lighting
	/// The intensity of the diffuse lighting.
	GLfloat m_diffuseIntensity;

	/// The light projection.
	glm::mat4 m_lightProj;

	/// Shadow map.
	ShadowMap* m_shadowMap;
};
