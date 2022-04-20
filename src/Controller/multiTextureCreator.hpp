#pragma once

#include "ReflexEngine/ReflexEngine.hpp"
#include "View/Renderer/OpenGL/Objects/Texture.hpp"
#include "StbImage.hpp"

struct multiTextureFileData {
	int m_text_num = 0;
	int m_width = 0;
	int m_height = 0;
	int m_bitDepth = 0;
};

class multiTextureCreator {
public:
	/**
	 * @brief	Sets the texture for the multi texture
	 * @param	texture_path	- The path of the texture
	 *
	 * @pre	multi texture creator exists
	 * @post	texture added
	 */
	void set_texture(std::string texture_path);

	/**
	 * @brief	Sets the height map and if it should be an island
	 * @param	height		- The height map
	 * @param	xSize		- x size of height map (width)
	 * @param	zSize		- z size of height map (height)
	 * @param	makeIsland	- If you want the height map to turn into an island
	 *
	 * @pre		object exists
	 * @post	height map added
	 */
	void set_height_map(uint8_t* height, int xSize, int zSize, bool makeIsland);

	/**
	 * @brief	creates the multi texture
	 *
	 * @pre		textures & height map loaded
	 * @post	multitexture created
	 */
	void create_multi_texture();

	/**
	 * @brief	Sets the max height of the height map
	 *
	 * @pre		objects exists
	 * @post	max height set
	 */
	void set_max_height(int max);

	/**
	 * @brief	Gets the multi texture texture id
	 *@return	GLuint	- multi texture texture id
	 *
	 * @pre		multi texture created
	 * @post	id returned
	 */
	GLuint get_multi_texture();

private:
	/// <summary>
	/// Array of raw texture data
	/// </summary>
	unsigned char* m_texture_ids[4];

	/// <summary>
	/// Array of texture information
	/// </summary>
	multiTextureFileData m_texture_param[4];

	/// <summary>
	/// If you want to turn the height map into an island
	/// </summary>
	bool m_make_island = false;

	/// <summary>
	/// The number of textures stored
	/// </summary>
	int m_number_of_textures = 0;

	/// <summary>
	/// The id of the multi texture
	/// </summary>
	GLuint m_id;

	/// <summary>
	/// The max height value
	/// </summary>
	int m_max = 256;

	/// <summary>
	/// The height map
	/// </summary>
	uint8_t* m_height_map;

	/// <summary>
	/// The x size
	/// </summary>
	int m_x_size = 0;

	/// <summary>
	/// The z size
	/// </summary>
	int m_z_size = 0;

	/**
	 * @brief	Gets the range of height value based on number of textures
	 *
	 * @pre		textures exists
	 * @post	height value found
	 */
	int get_range();

	/**
	 * @brief	Gets height value at coordinate
	 * @param	x	- x coord
	 * @param	z	- z coord
	 * @return	int	- height value at point
	 *
	 * @pre		height map exists
	 * @post	height value retrieved
	 */
	int get_height_value(int x, int z);

	/**
	 * @brief	Lowers the height map sides to make it into an island
	 * @param	height	- Height map
	 *
	 * @pre		height map exists
	 * @post	height map sides lowered
	 */
	void make_island(uint8_t* height);

	// lighting
	/// <summary>
	///	Light direction x
	///  <summary>
	int m_dirX = 1;

	/// <summary>
	/// Light direction z
	/// </summary>
	int m_dirZ = 1;

	/// <summary>
	/// Min brightness
	/// </summary>
	float m_minBrightness = 0.3;

	/// <summary>
	/// Max brightness
	/// </summary>
	float m_maxBrightness = 1;

	/// <summary>
	/// Softness value
	/// </summary>
	float softness = 0.01;

	/// <summary>
	/// Switch between slope lighting and height lighting
	/// </summary>
	bool use_better_lighting = true;

	/**
	 * @brief	Returns an index value
	 * @param	z		- The z point
	 * @param	x		- The x point
	 * @param	x_size	- The x size (width)
	 * @param	bpp		- The bytes per pixel value (e.g., RGBA = 4)
	 * @return	int	- An index value you can use
	 *
	 * @pre		nothing
	 * @post	index value
	 */
	int get_index(int z, int x, int x_size, int bpp);

	/**
	 * @brief	Adds height lighting to a texture
	 * @param	*mult_texture	- The multi texture to add height lighting too
	 *
	 * @pre		nothing
	 * @post	adds height based lighting
	 */
	void add_height_based_lighting(unsigned char* mult_texture);

	/**
	 * @brief	Adds slope lighting to a texture
	 * @param	*mult_texture	- The multi texture to add slope lighting too
	 *
	 * @pre		nothing
	 * @post	adds slope based lighting
	 */
	void add_slope_based_lighting(unsigned char* mult_texture);

	// upscaling height map
	/// <summary>
	/// If you want to upscale the height map (for large multi texture)
	/// </summary>
	bool use_super_height_map = true;

	/// <summary>
	/// Super height map
	/// </summary>
	uint8_t* m_super_height_map;

	/// <summary>
	/// Scale of super height map ( 2 ^ m_super_scale)
	/// </summary>
	int m_super_scale = 1;

	/**
	 * @brief	Generates super height map
	 *
	 * @pre		height map exists
	 * @post	super height map generated
	 */
	void generate_super_height_map();

	/**
	 * @brief	Gets upper original value
	 * @param	val		- The value of the current coordinate (x or z)
	 * @param	mult	- The scale of the height map
	 * @return	int		- upper value
	 *
	 * @pre		super height map used
	 * @post	gets upper value
	 */
	int upper_original_val(int val, int mult);

	/**
	 * @brief	Gets lower original value
	 * @param	val		- The value of the current coordinate (x or z)
	 * @param	mult	- The scale of the height map
	 * @return	int		- lower value
	 *
	 * @pre		super height map used
	 * @post	gets lower value
	 */
	int lower_original_val(int val, int mult);

	/**
	 * @brief	Gets original height map value
	 * @param	x				- x coord
	 * @param	z				- z coord
	 * @param	unsigned char	- The height data
	 *
	 * @pre		height map stored
	 * @post	gets height data
	 */
	unsigned char original_height_map_value(int x, int z);

	/**
	 * @brief	Interpolates a new height at point based on points on a plane
	 * @param	x1	- point 1 x coord
	 * @param	z1	- point 1 z coord
	 * @param	x2	- point 2 x coord
	 * @param	z2	- point 2 z coord
	 * @param	x3	- point 3 x coord
	 * @param	z3	- point 3 z coord
	 * @param	x	- x position
	 * @param	z	- z position
	 * @return	int	- The new height
	 *
	 * @pre		super height map used
	 * @post	gets new height
	 */
	int interpolate_height(int x1, int z1, int x2, int z2, int x3, int z3,
	                       int x, int z);
};
