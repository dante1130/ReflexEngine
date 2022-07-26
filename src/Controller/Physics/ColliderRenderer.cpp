#include "ColliderRenderer.hpp"

void ColliderRenderer::update(
    const reactphysics3d::DebugRenderer& debug_renderer) {
	line_mesh_.create_line_mesh(debug_renderer.getLinesArray(),
	                            debug_renderer.getNbLines());

	triangle_mesh_.create_triangle_mesh(debug_renderer.getTrianglesArray(),
	                                    debug_renderer.getNbTriangles());
}

void ColliderRenderer::draw(const Shader& shader) {
	line_mesh_.render_mesh();
	triangle_mesh_.render_mesh();
}