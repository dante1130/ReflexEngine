#include "multiTextureCreator.hpp"

void multiTextureCreator::set_texture(std::string texture_path) {
	m_texture_ids[m_number_of_textures] = stbi_load(
	    texture_path.c_str(), &m_texture_param[m_number_of_textures].m_width,
	    &m_texture_param[m_number_of_textures].m_height,
	    &m_texture_param[m_number_of_textures].m_bitDepth, 0);

	std::cout << texture_path << " loading for multi texture creator"
	          << "\nHeight = " << m_texture_param[m_number_of_textures].m_height
	          << "\nWidth = " << m_texture_param[m_number_of_textures].m_width
	          << m_texture_param[m_number_of_textures].m_bitDepth << std::endl;

	m_number_of_textures++;
}

void multiTextureCreator::set_height_map(uint8_t* height, int xSize, int zSize,
                                         bool makeIsland) {
	m_x_size = xSize;
	m_z_size = zSize;
	make_island(height);
	m_height_map = height;
}

void multiTextureCreator::make_island(uint8_t* height) {
	for (int z = 0; z < 10; z++) {
		for (int x = 0; x < m_x_size; x++) {
			height[z * m_x_size + x] =
			    height[z * m_x_size + x] * ((z + 0.1) / 10.0);
		}
	}

	for (int z = m_z_size - 1; z > m_z_size - 10; z--) {
		for (int x = 0; x < m_x_size; x++) {
			height[z * m_x_size + x] =
			    height[z * m_x_size + x] * ((m_z_size - z + 0.1) / 10.0);
		}
	}

	for (int x = 0; x < 10; x++) {
		for (int z = 0; z < m_x_size; z++) {
			height[z * m_x_size + x] =
			    height[z * m_x_size + x] * ((x + 0.1) / 10.0);
		}
	}

	for (int x = m_x_size - 1; x > m_x_size - 10; x--) {
		for (int z = 0; z < m_z_size; z++) {
			height[z * m_x_size + x] =
			    height[z * m_x_size + x] * ((m_x_size - x + 0.1) / 10.0);
		}
	}
}

void multiTextureCreator::create_multi_texture() {
	// Processing new texture
	int range = get_range() - 5;
	float weight = 0;
	int heightValue;
	unsigned char rgb[3] = {};
	int max;
	int bpp = 4;
	int index;
	int tempX, tempZ;

	int z_size = m_z_size;
	int x_size = m_x_size;

	if (use_super_height_map) {
		generate_super_height_map();
		z_size = z_size * pow(2, m_super_scale);
		x_size = x_size * pow(2, m_super_scale);
	}

	unsigned char* mult_texture = new unsigned char[x_size * z_size * 4];

	for (int z = 0; z < z_size; z++) {
		for (int x = 0; x < x_size; x++) {
			heightValue = get_height_value(x, z);
			// std::cout << heightValue << std::endl;
			for (int count = 0; count < m_number_of_textures; count++) {
				max = (count + 1) * range;
				weight = (range - abs(heightValue - max)) / (float)range;
				// weight = (range - abs(heightValue - max)) /
				// (float)heightValue;
				if (weight > 0) {
					// Get correct point on texture (if texture different size
					// to height map)
					tempX = x * m_texture_param[count].m_width / x_size;
					tempZ = z * m_texture_param[count].m_height / z_size;
					index = tempZ * m_texture_param[count].m_width * 3;
					// RED
					rgb[0] += m_texture_ids[count][index + tempX * 3] * weight;
					// GREEN
					rgb[1] +=
					    m_texture_ids[count][index + tempX * 3 + 1] * weight;
					// BLUE
					rgb[2] +=
					    m_texture_ids[count][index + tempX * 3 + 2] * weight;
				}
			}
			mult_texture[z * (x_size * bpp) + (x * bpp)] = rgb[0];
			mult_texture[z * (x_size * bpp) + (x * bpp) + 1] = rgb[1];
			mult_texture[z * (x_size * bpp) + (x * bpp) + 2] = rgb[2];
			mult_texture[z * (x_size * bpp) + (x * bpp) + 3] = 255;
			rgb[0] = 0;
			rgb[1] = 0;
			rgb[2] = 0;
		}
	}

	if (use_better_lighting) {
		add_slope_based_lighting(mult_texture);
	} else {
		add_height_based_lighting(mult_texture);
	}

	// Biding texture
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, x_size, z_size, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, mult_texture);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Deleting uses textures
	for (int count = 0; count < m_number_of_textures; count++) {
		stbi_image_free(m_texture_ids[count]);
	}
	delete[] mult_texture;

	if (use_super_height_map) {
		delete[] m_super_height_map;
	}
}

GLuint multiTextureCreator::get_multi_texture() { return m_id; }

int multiTextureCreator::get_range() {
	if (m_number_of_textures == 0) {
		return 1;
	}
	return m_max / m_number_of_textures;
}

void multiTextureCreator::set_max_height(int max) { m_max = max; }

int multiTextureCreator::get_height_value(int x, int z) {
	if (use_super_height_map) {
		int xSize = m_x_size * pow(2, m_super_scale);
		return m_super_height_map[z * xSize + x];
	} else {
		return m_height_map[z * m_x_size + x];
	}
}

void multiTextureCreator::add_height_based_lighting(
    unsigned char* mult_texture) {
	float lightValue;
	int index;
	int bpp = 4;

	int z_size = m_z_size;
	int x_size = m_x_size;

	if (use_super_height_map) {
		z_size = z_size * pow(2, m_super_scale);
		x_size = x_size * pow(2, m_super_scale);
	}

	for (int z = 0; z < z_size; z++) {
		for (int x = 0; x < x_size; x++) {
			lightValue = (get_height_value(x, z) + 50) / (m_max * 1.0f);
			if (lightValue > 1) {
				lightValue = 1;
			}
			// std::cout << lightValue << std::endl;
			index = get_index(z, x, x_size, bpp);
			mult_texture[index] = (int)(mult_texture[index] * lightValue);
			mult_texture[index + 1] =
			    (int)(mult_texture[index + 1] * lightValue);
			mult_texture[index + 2] =
			    (int)(mult_texture[index + 2] * lightValue);
		}
	}
}

int multiTextureCreator::get_index(int z, int x, int x_size, int bpp) {
	return (z * x_size * bpp + x * bpp);
}

void multiTextureCreator::add_slope_based_lighting(
    unsigned char* mult_texture) {
	int xl;
	int zl;
	float shade;
	int index;
	int bpp = 4;

	int z_size = m_z_size;
	int x_size = m_x_size;

	if (use_super_height_map) {
		z_size = z_size * pow(2, m_super_scale);
		x_size = x_size * pow(2, m_super_scale);
	}

	for (int z = 0; z < z_size; z++) {
		for (int x = 0; x < x_size; x++) {
			xl = x - m_dirX;
			zl = z - m_dirZ;
			if (xl < 0 || xl >= x_size || zl < 0 || zl >= z_size) {
				shade = 1.0f;
			} else {
				shade = 1.0f - (get_height_value(xl, zl) / (float)m_max -
				                get_height_value(x, z) / (float)m_max) /
				                   softness;
			}

			if (shade < m_minBrightness) {
				shade = m_minBrightness;
			} else if (shade > m_maxBrightness) {
				shade = m_maxBrightness;
			}
			index = get_index(z, x, x_size, bpp);
			mult_texture[index] = (int)(mult_texture[index] * shade);
			mult_texture[index + 1] = (int)(mult_texture[index + 1] * shade);
			mult_texture[index + 2] = (int)(mult_texture[index + 2] * shade);
		}
	}
}

float distance(int x1, int z1, int x2, int z2) {
	return sqrt(pow(x1 - x2, 2) + pow(z1 - z2, 2));
}

int multiTextureCreator::interpolate_height(int x1, int z1, int x2, int z2,
                                            int x3, int z3, int x, int z) {
	int mult = pow(2, m_super_scale);
	int y1 = original_height_map_value(x1 / mult, z1 / mult);
	int y2 = original_height_map_value(x2 / mult, z2 / mult);
	int y3 = original_height_map_value(x3 / mult, z3 / mult);
	glm::vec3 v1 = {x1 - x2, y1 - y2, z1 - z2};
	glm::vec3 v2 = {x1 - x3, y1 - y3, z1 - z3};
	glm::vec3 crossProd;
	crossProd.x = v1.y * v2.z - v1.z * v2.y;
	crossProd.y = v1.z * v2.x - v1.x * v2.z;
	crossProd.z = v1.x * v2.y - v1.y * v2.x;
	float xCalc = -crossProd.x * (x - x1);
	float zCalc = -crossProd.z * (z - z1);
	int val = (xCalc + zCalc) / crossProd.y + y1;
	return val;
}

void multiTextureCreator::generate_super_height_map() {
	m_super_height_map = new unsigned char[m_x_size * pow(2, m_super_scale) *
	                                       m_z_size * pow(2, (m_super_scale))];

	int z1, z2, x1, x2, interp;
	float interpX1, interpX2, interpZ1, interpZ2, sum;
	int index;

	int mult = pow(2, m_super_scale);
	int z_size = m_z_size * mult;
	int x_size = m_x_size * mult;
	std::cout << z_size << " : " << x_size << std::endl;
	std::cout << "Starting creation of super height map" << std::endl;
	for (int z = 0; z < z_size; z++) {
		for (int x = 0; x < x_size; x++) {
			z1 = upper_original_val(z, mult);
			x1 = upper_original_val(x, mult);
			z2 = lower_original_val(z, mult);
			x2 = lower_original_val(x, mult);

			if (distance(x, z, x1, z1) < distance(x, z, x2, z2)) {
				interp = interpolate_height(x1, z1, x1, z2, x2, z1, x, z);
			} else {
				interp = interpolate_height(x2, z2, x1, z2, x2, z1, x, z);
			}

			if (interp > 255) {
				interp = 255;
			}
			index = get_index(z, x, x_size, 1);
			m_super_height_map[index] = interp;
		}
	}
	std::cout << "Creation of super height map is complete" << std::endl;
}

int multiTextureCreator::upper_original_val(int val, int mult) {
	int start = 0;
	while (start < val) {
		start += mult;
	}
	return start;
}
int multiTextureCreator::lower_original_val(int val, int mult) {
	int start = 0;
	while (start < val) {
		start += mult;
	}
	start -= mult;
	return start;
}

unsigned char multiTextureCreator::original_height_map_value(int x, int z) {
	if (x < 0) {
		x = 0;
	}
	if (z < 0) {
		z = 0;
	}

	return m_height_map[z * m_x_size + x];
}

uint8_t* multiTextureCreator::get_height_map() { return m_height_map; }
