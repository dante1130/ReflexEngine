#pragma once

#include <glad/glad.h>
#include <reactphysics3d/reactphysics3d.h>

using Line = rp3d::DebugRenderer::DebugLine;
using Triangle = rp3d::DebugRenderer::DebugTriangle;

/**
 * @class ReactMesh
 * @brief A mesh class to be used in rendering debug lines and triangles for
 * ReactPhysics3D
 */
class ReactMesh {
public:
	/**
	 * @brief Generate buffers for the mesh.
	 */
	ReactMesh();

	/**
	 * @brief Create a line mesh.
	 *
	 * @param lines The lines array.
	 * @param array_size The size of the array.
	 */
	void create_line_mesh(const Line* lines, size_t array_size);

	/**
	 * @brief Create a triangle mesh.
	 *
	 * @param triangles The triangles array.
	 * @param array_size The size of the array.
	 */
	void create_triangle_mesh(const Triangle* triangles, size_t array_size);

	/**
	 * @brief Render the mesh.
	 */
	void render_mesh() const;

	/**
	 * @brief Delete the buffers.
	 */
	~ReactMesh();

private:
	/// Whether the mesh has been loaded.
	bool is_created_ = false;

	/// The VAO of the mesh.
	GLuint vao_ = 0U;
	/// The VBO of the mesh.
	GLuint vbo_ = 0U;

	/// The draw mode of the mesh. (GL_LINES or GL_TRIANGLES)
	int draw_mode_ = 0;
	/// The draw size of the mesh.
	size_t draw_size_ = 0ULL;

	/// The vertex stride of the mesh. (Vector3 and uint32)
	constexpr static size_t vertex_stride =
	    sizeof(rp3d::Vector3) + sizeof(rp3d::uint32);
};