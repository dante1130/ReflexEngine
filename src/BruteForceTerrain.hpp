#pragma once

#include "Terrain.hpp"

/**
 * @class BruteForceTerrain
 * @brief A terrain that uses uses the 8-bit values of the heightmap to color
 * and render the terrain.
 */
class BruteForceTerrain : public Terrain {
public:
	/**
	 * @brief Renders the terrain.
	 *
	 * @param shader
	 */
	void render(const Shader* shader) override;

	/**
	 * @brief Reads the heightmap and loads the mesh.
	 *
	 * @return true
	 * @return false
	 */
	bool load_mesh() override;

private:
	/// The mesh.
	std::shared_ptr<Mesh> mesh_ = nullptr;
};
