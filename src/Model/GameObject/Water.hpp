#pragma once

#include <math.h>
#include <glm.hpp>
#include "GameObject.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

class Water : public GameObject {
public:
	/**
	 * @brief	Constructor used to set a texture and leave rest as default
	 * @param	&text	- The texture you want to add
	 *
	 * @pre		The texture has been created
	 * @post	A water object will be ready
	 */
	Water(std::string &text);

	/**
	 * @brief	Constructor used to set a texture, pos, scale & offMult
	 * @param	&text	- The texture you want to add
	 * @param	pos		- The position of the center of the water
	 * @param	scale	- The intensity of the water movement (i.e. how
	 * height/to the side it moves)
	 * @param	offMult	- Offset multiplier, change how fast it moves on each
	 * axis for more random look
	 *
	 * @pre		The texture has been created & pos, scale, offMult have all been
	 * set
	 * @post	A water object will be ready
	 */
	Water(std::string &text, glm::vec3 pos, glm::vec3 scale, glm::vec3 offMult);

	/**
	 * @brief	Initialises the water
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Texture must have been set
	 * @post	Water object ready to be used
	 */
	void init() override;

	/**
	 * @brief	Updates the water object
	 * @param	delta_time	- The time between frames
	 * @return	Void
	 *
	 * @pre		Water object has been created
	 * @post	Water position moved according to time difference
	 */
	void update(float delta_time) override;

	/**
	 * @brief	Adds a draw call for the water object
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Water object has been created
	 * @post	Adds to draw call
	 */
	void add_draw_call() override;

	/**
	 * @brief	Initialises the water
	 * @param	shader	- the shader in use
	 * @return	Void
	 *
	 * @pre		Water object is created & draw call has been added
	 * @post	Water object displayed to screen
	 */
	void draw(std::shared_ptr<Shader> shader) override;

	/**
	 * @brief	Initialises the water
	 * @param	scale	- Vector of intensity of water movement
	 * @return	Void
	 *
	 * @pre		Water object has been created & scale cannot be 0 on any axis
	 * @post	Intensity of water movement set
	 */
	void setIntensity(glm::vec3 scale);

	/**
	 * @brief	Initialises the water
	 * @param	offMult	- Vector of the offset multipler
	 * @return	Void
	 *
	 * @pre		Water object has been created
	 * @post	Offset of water movement set
	 */
	void setOffsetMult(glm::vec3 offMult);

private:
	/// <summary>
	/// Total time run
	/// </summary>
	double m_time = 0;

	/// <summary>
	/// Position of the new water after update
	/// </summary>
	glm::vec3 m_pos = {0, 0, 0};

	/// <summary>
	/// Intensity of the water movement
	/// </summary>
	glm::vec3 m_intensity = {5, 10, 5};

	/// <summary>
	/// Multipler for the water offset
	/// </summary>
	glm::vec3 m_offsetMult = {1.1, 1.2, 1.7};

	/// <summary>
	/// The texture of the water
	/// </summary>
	std::string m_textureName;

	/// <summary>
	/// The mesh of the water
	/// </summary>
	Mesh m_mesh;

	/// <summary>
	/// Underneath mesh of the water
	/// </summary>
	Mesh m_mesh_under;
};
