#include "Mesh.hpp"

#include <glm/glm.hpp>

Mesh::Mesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &IBO);
	glGenBuffers(1, &VBO);
}

void Mesh::create_mesh(const GLfloat* vertices, const GLuint* indices,
                       GLuint noOfVerts, GLuint noOfIndices) {
	indexCount = noOfIndices;

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * noOfIndices,
	             indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * noOfVerts, vertices,
	             GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
	                      (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8,
	                      (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::CreateColorMesh(const GLfloat* vertices, const GLuint* indices,
                           GLuint noOfVerts, GLuint noOfIndices) {
	indexCount = noOfIndices;

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * noOfIndices,
	             indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * noOfVerts, vertices,
	             GL_STATIC_DRAW);

	// Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11,
	                      (void*)0);
	glEnableVertexAttribArray(0);

	// Texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11,
	                      (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	// Normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11,
	                      (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	// Colors
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 11,
	                      (void*)(sizeof(vertices[0]) * 8));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	has_color_ = true;
}

void Mesh::render_mesh() const {
	if (IBO == 0 || VBO == 0 || VAO == 0 || indexCount == 0) {
		return;
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::ClearMesh() {
	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

bool Mesh::has_color() const { return has_color_; }

Mesh::~Mesh() { ClearMesh(); }
