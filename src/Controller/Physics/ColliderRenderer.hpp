#pragma once

#include <reactphysics3d/reactphysics3d.h>

#include "View/Renderer/OpenGL/Objects/Shader.hpp"
#include "View/Renderer/OpenGL/Objects/ReactMesh.hpp"

/**
 * @author Andrew Ho
 * @class ColliderRenderer
 * @brief A class that renders rp3d debug collider entities.
 */
class ColliderRenderer {
public:
	ColliderRenderer() = default;

	/**
	 * @brief Update the debug meshes.
	 *
	 * @param debug_renderer The debug renderer.
	 */
	void update(const reactphysics3d::DebugRenderer& debug_renderer);

	/**
	 * @brief Draw the debug meshes.
	 *
	 * @param shader The shader.
	 *
	 * @pre Projection and view matrices have been set, and wireframe mode on.
	 */
	void draw(const Shader& shader);

private:
	/// The line mesh.
	ReactMesh line_mesh_;
	/// The triangle mesh.
	ReactMesh triangle_mesh_;
};