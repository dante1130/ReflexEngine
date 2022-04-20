#pragma once

#include <glad/glad.h>

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
	 * @param vertices
	 * @param indices
	 * @param noOfVerts
	 * @param noOfIndices
	 */
	void CreateMesh(const GLfloat* vertices, const GLuint* indices,
	                GLuint noOfVerts, GLuint noOfIndices);

	void CreateIndices(GLuint* indices, GLuint noOfIndices);

	/**
	 * @brief Takes in an array of vertices, texture coordinates, normals, and
	 * indices and passing it to the GPU using VBO, VAO, and IBO.
	 *
	 * @param vertices
	 * @param indices
	 * @param noOfVerts
	 * @param noOfIndices
	 */
	void CreateColorMesh(const GLfloat* vertices, const GLuint* indices, GLuint noOfVerts,
	                     GLuint noOfIndices);

	/**
	 * @brief Binds the VAO and IBO and renders the mesh.
	 */
	void RenderMesh();

	/**
	 * @brief Clears the mesh.
	 */
	void ClearMesh();

	/**
	 * @brief Returns a boolean whether the mesh is colored.
	 *
	 * @return true
	 * @return false
	 */
	bool has_color() const;

	/**
	 * @brief Destroy the Mesh object.
	 */
	~Mesh();

private:
	/// Vertex array object, specifying the layout of the mesh.
	GLuint VAO;
	/// Vertex buffer object, containing the data of the mesh.
	GLuint VBO;
	/// Index buffer object, containing the indices of the mesh.
	GLuint IBO;

	/// The number of indices in the mesh.
	GLsizei indexCount;

	/// Boolean to check whether it is a colored mesh.
	bool has_color_ = false;
};
