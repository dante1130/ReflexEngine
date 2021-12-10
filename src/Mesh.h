#pragma once

#include <glad/glad.h>

class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat* vertices, GLuint* indices, GLuint noOfVerts, GLuint noOfIndices);
	void RenderMesh();
	void ClearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};
