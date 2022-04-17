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

private:
	/// The specular intensity.
	GLfloat m_specularIntensity;
	/// The shininess.
	GLfloat m_shininess;
};
}  // namespace Reflex
