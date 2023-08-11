#include "ReactMesh.hpp"

ReactMesh::ReactMesh() {
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
}

void ReactMesh::create_line_mesh(const Line* lines, size_t array_size) {
	if (array_size == 0) return;

	draw_mode_ = GL_LINES;
	draw_size_ = array_size * 2;

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, array_size * sizeof(Line), lines,
	             GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribIPointer(1, 3, GL_UNSIGNED_INT, vertex_stride,
	                       (void*)(sizeof(rp3d::Vector3)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	is_created_ = true;
}

void ReactMesh::create_triangle_mesh(const Triangle* triangles,
                                     size_t array_size) {
	if (array_size == 0) return;

	draw_mode_ = GL_TRIANGLES;
	draw_size_ = array_size * 3;

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, array_size * sizeof(Triangle), triangles,
	             GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribIPointer(1, 3, GL_UNSIGNED_INT, vertex_stride,
	                       (void*)(sizeof(rp3d::Vector3)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	is_created_ = true;
}

void ReactMesh::render_mesh() const {
	if (!is_created_) return;

	glBindVertexArray(vao_);
	glDrawArrays(draw_mode_, 0, draw_size_);
	glBindVertexArray(0);
}

ReactMesh::~ReactMesh() {
	if (vao_ != 0) {
		glDeleteVertexArrays(1, &vao_);
		vao_ = 0;
	}

	if (vbo_ != 0) {
		glDeleteBuffers(1, &vbo_);
		vbo_ = 0;
	}
}