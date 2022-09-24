#pragma once

#include <glad/glad.h>
#include <mutex>

/**
 * @class Mesh
 * @brief A mesh class representing vertices, texture coordinates, normals, and
 * its indices.
 * @todo Add in color meshes.
 */
class Mesh {
public:
	/**
	 * @brief Construct a new Mesh object.
	 */
	Mesh();

	/**
	 * @brief Takes in an array of vertices, texture coordinates, normals, and
	 * indices and passing it to the GPU using VBO, VAO, and IBO.
	 *
	 * @param vertices The vertices, texture coordinates, and normals.
	 * @param indices The indices of the mesh.
	 * @param noOfVerts The number of vertices.
	 * @param noOfIndices The number of indices.
	 * @param draw_usage The draw usage of the mesh. (Defaults to
	 * GL_STATIC_DRAW)
	 */
	void create_mesh(const GLfloat* vertices, const GLuint* indices,
	                 GLuint noOfVerts, GLuint noOfIndices,
	                 GLenum draw_usage = GL_STATIC_DRAW);

	/**
	 * @brief Takes in an array of vertices, texture coordinates, normals, and
	 * indices and passing it to the GPU using VBO, VAO, and IBO.
	 *
	 * @param vertices The vertices, texture coordinates, and normals.
	 * @param indices The indices of the mesh.
	 * @param noOfVerts The number of vertices.
	 * @param noOfIndices The number of indices.
	 */
	void CreateColorMesh(const GLfloat* vertices, const GLuint* indices,
	                     GLuint noOfVerts, GLuint noOfIndices);

	/**
	 * @brief Create a react mesh.
	 */
	void create_react_mesh();

	/**
	 * @brief Binds the VAO and IBO and renders the mesh.
	 */
	void render_mesh() const;

	/**
	 * @brief Clears the mesh.
	 */
	void ClearMesh();

	/**
	 * @brief Returns a boolean whether the mesh is colored.
	 *
	 * @return bool
	 */
	bool has_color() const;

	/**
	 * @brief Destroy the Mesh object.
	 */
	~Mesh();

private:
	/// Vertex array object, specifying the layout of the mesh.
	GLuint VAO = 0;
	/// Vertex buffer object, containing the data of the mesh.
	GLuint VBO = 0;
	/// Index buffer object, containing the indices of the mesh.
	GLuint IBO = 0;

	std::mutex locker;

	/// The number of indices in the mesh.
	GLsizei indexCount = 0;

	/// Boolean to check whether it is a colored mesh.
	bool has_color_ = false;
};
