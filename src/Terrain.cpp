#include "Terrain.hpp"

#include <iostream>
#include <algorithm>
#include "StbImage.hpp"

bool Terrain::load_heightfield(const char* file_name) {
	int width, length;

	heightmap_ = stbi_load(file_name, &width, &length, &bit_depth_, 0);

	width_ = width;
	length_ = length;

	if (!heightmap_) {
		std::cout << "Failed to load image " << file_name << std::endl;
		return false;
	}

	return true;
}

bool Terrain::gen_faultformation(int iterations, size_t size, int min_height,
                                 int max_height, float weight) {
	if (size <= 0) {
		std::cout << "Invalid size: " << size << std::endl;
		return false;
	}

	//srand(time(nullptr));

	width_ = size;
	length_ = size;

	heightmap_ = new uint8_t[width_ * length_];
	std::vector<float> heights(width_ * length_);

	for (size_t i = 0; i < iterations; ++i) {
		int displacement =
		    max_height - ((max_height - min_height) * i) / iterations;

		int x1 = rand() % width_;
		int z1 = rand() % length_;

		int x2 = 0;
		int z2 = 0;

		do {
			x2 = rand() % width_;
			z2 = rand() % length_;
		} while (x2 == x1 && z2 == z1);

		for (size_t z = 0; z < length_; ++z) {
			for (size_t x = 0; x < width_; ++x) {
				int y = (x2 - x1) * (z - z1) - (z2 - z1) * (x - x1);
				if (y > 0) {
					heights[z * width_ + x] += static_cast<float>(displacement);
				}
			}
		}
		add_filter(heights, weight);
	}

	normalize_terrain(heights);

	for (size_t z = 0; z < length_; ++z) {
		for (size_t x = 0; x < width_; ++x) {
			heightmap_[z * width_ + x] =
			    static_cast<uint8_t>(heights[z * width_ + x]);
		}
	}

	return true;
}

float Terrain::get_height(int x, int z) const {
	if (is_in_bounds(x, z)) {
		return static_cast<float>(heightmap_[x + (z * width_)] * scale_.y);
	}

	return 0.0f;
}

float Terrain::get_height_world(float x, float z) const {
	glm::vec3 origin = get_origin();

	// Get the x and z position on the terrain
	float norm_x = (x - origin.x) / scale_.x;
	float norm_z = (z - origin.z) / scale_.z;

	// Gets the grid position on the terrain
	float grid_square_size = width_ / ((float)length_ - 1);
	int grid_x = static_cast<int>(norm_x / grid_square_size);
	int grid_z = static_cast<int>(norm_z / grid_square_size);

	if (!is_in_bounds(grid_x, grid_z)) {
		return 0.0f;
	}

	// Gets the coordinates in the grid
	float coord_x = std::fmod(norm_x, grid_square_size) / grid_square_size;
	float coord_z = std::fmod(norm_z, grid_square_size) / grid_square_size;

	// Barycentric coordinates calculation:
	// Gets the four surrounding heights
	float height_1 = get_height(grid_x, grid_z);
	float height_2 = get_height(grid_x + 1, grid_z);
	float height_3 = get_height(grid_x, grid_z + 1);
	float height_4 = get_height(grid_x + 1, grid_z + 1);

	// Get 2 interpolated heights
	float height_1_2 = height_1 + (height_2 - height_1) * coord_x;
	float height_3_4 = height_3 + (height_4 - height_3) * coord_x;

	// Get the final height
	float height = height_1_2 + (height_3_4 - height_1_2) * coord_z;

	return height * scale_.y;
}

uint8_t Terrain::get_height_color(int x, int z) const {
	if (is_in_bounds(x, z)) {
		return heightmap_[x + (z * width_)];
	}

	return 1u;
}

glm::vec3 Terrain::get_origin() const {
	return glm::vec3(-(get_width() / 2.0f) * scale_.x, 0.0f,
	                 -(get_length() / 2.0f) * scale_.z);
}

glm::vec3 Terrain::get_scale() const { return scale_; }

size_t Terrain::get_width() const { return width_; }

size_t Terrain::get_length() const { return length_; }

uint8_t* Terrain::get_height_map() { return heightmap_; }

void Terrain::set_scale(glm::vec3 scale) { scale_ = scale; }

bool Terrain::is_in_bounds(int x, int z) const {
	return (x >= 0 && x < width_) && (z >= 0 && z < length_);
}

void Terrain::add_filter(std::vector<float>& heights, float weight) {
	for (size_t i = 0; i < width_; ++i)
		filter_pass(&heights[i * width_], 1, weight);

	for (size_t i = 0; i < width_; ++i)
		filter_pass(&heights[width_ * i + width_ - 1], -1, weight);

	for (size_t i = 0; i < width_; ++i)
		filter_pass(&heights[i], width_, weight);

	for (size_t i = 0; i < width_; ++i)
		filter_pass(&heights[width_ * (width_ - 1) + i], -width_, weight);
}

void Terrain::filter_pass(float* start_point, int increment, float weight) {
	float prev_y = start_point[0];
	int j = increment;

	for (size_t i = 1; i < width_; ++i) {
		start_point[j] = weight * prev_y + (1 - weight) * start_point[j];
		prev_y = start_point[j];
		j += increment;
	}
}

glm::vec3 Terrain::calculate_terrain_normal(int x, int z) const {
	float height_left = get_height(x - 1, z);
	float height_right = get_height(x + 1, z);
	float height_top = get_height(x, z + 1);
	float height_bottom = get_height(x, z - 1);

	glm::vec3 normal =
	    glm::vec3(height_left - height_right, 2.0f, height_top - height_bottom);

	return glm::normalize(normal);
}

void Terrain::normalize_terrain(std::vector<float>& heights) {
	float min = *std::min_element(heights.begin(), heights.end());
	float max = *std::max_element(heights.begin(), heights.end());

	if (min >= max) return;

	float height = max - min;

	for (size_t i = 0; i < heights.size(); ++i) {
		heights[i] = ((heights[i] - min) / height) * 255.0f;
	}
}

Terrain::~Terrain() {
	stbi_image_free(heightmap_);
	heightmap_ = nullptr;
}

void Terrain::set_height_map(uint8_t* map) { heightmap_ = map; }
