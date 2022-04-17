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
	 * @param shine
	 * @param sIntensity
	 */
	Material(GLfloat shine, GLfloat sIntensity);

	/**
	 * @brief Enable the material by passing the uniforms to the shader.
	 *
	 * @param shininessLoc
	 * @param specularIntensityLoc
	 */
	void UseMaterial(GLuint shininessLoc, GLuint specularIntensityLoc);

	/**
	 * @brief Returns the specular intensity
	 * @param No param
	 * @return	float	- specular intensity
	 *
	 * @pre	Object exists
	 * @post intensity returned
	 */
	float getSpecIntensity();

	/**
	 * @brief Returns the shininess intensity
	 * @param No param
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
