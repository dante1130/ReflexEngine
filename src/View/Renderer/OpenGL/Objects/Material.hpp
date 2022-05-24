#pragma once

#include <glad/glad.h>

/**
 * @class Material
 * @brief A material to apply to an object of how shiny and how intense the
 * specular lighting should be.
 */
namespace Reflex {
class Material {
public:
	/**
	 * @brief Default constructor.
	 */
	Material();

	/**
	 * @brief Parameterized constructor.
	 *
	 * @param shine The shininess of the material.
	 * @param sIntensity The intensity of the specular lighting.
	 */
	Material(GLfloat shine, GLfloat sIntensity);

	/**
	 * @brief Enable the material by passing the uniforms to the shader.
	 *
	 * @param shininessLoc The location of the shininess uniform.
	 * @param specularIntensityLoc The location of the specular intensity
	 */
	void UseMaterial(GLuint shininessLoc, GLuint specularIntensityLoc) const;

	/**
	 * @brief Returns the specular intensity
	 * @return	float	- specular intensity
	 *
	 * @pre	Object exists
	 * @post intensity returned
	 */
	float getSpecIntensity();

	/**
	 * @brief Returns the shininess intensity
	 * @return	float	- shininess intensity
	 *
	 * @pre	Object exists
	 * @post shininess returned
	 */
	float getShininess();

private:
	/// The specular intensity.
	GLfloat m_specularIntensity;
	/// The shininess.
	GLfloat m_shininess;
};
}  // namespace Reflex
