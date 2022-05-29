#include "Md2Model.hpp"

#include <vector>
#include <fstream>

md2::vec3_t Md2Model::pre_normals_[] = {
#include "Anorms.h"
};

void Md2Model::set_animation(md2::animation_type animation_type) {
	animstate_.type = animation_type;

	md2::anim_t anim = md2::animations_[static_cast<int>(animation_type)];

	animstate_.start_frame = anim.first_frame;
	animstate_.end_frame = anim.last_frame;
	animstate_.next_frame = anim.first_frame + 1;
	animstate_.fps = anim.fps;
}

void Md2Model::set_animstate(const md2::animstate_t& animstate) {
	animstate_ = animstate;
}

void Md2Model::render_animated(float delta_time) {
	render_frame(animstate_.curr_frame);
}

void Md2Model::render_animated_interpolated(float delta_time) {
	render_interpolated_frame(animstate_.curr_frame, animstate_.next_frame,
	                          animstate_.interpol);
}

void Md2Model::render_frame(int frame_num) {
	load_frame_mesh(frame_num);

	// texture_->UseTexture();
	mesh_->RenderMesh();
}

void Md2Model::render_interpolated_frame(int frame_a, int frame_b,
                                         float interpolation) {
	load_interpolated_frame_mesh(frame_a, frame_b, interpolation);

	// texture_->UseTexture();
	mesh_->RenderMesh();
}

bool Md2Model::load_md2(const std::string& filename) {
	std::ifstream file(filename, std::ios::in | std::ios::binary);

	if (!file.is_open()) return false;

	// Read header.
	file.read(reinterpret_cast<char*>(&header_), sizeof(header_));

	if (header_.ident != static_cast<int>(md2::ident) ||
	    header_.version != md2::version)
		return false;

	texcoords_ = new md2::texcoord_t[header_.num_texcoords];
	triangles_ = new md2::triangle_t[header_.num_triangles];
	frames_ = new md2::frame_t[header_.num_frames];

	// Read texture coordinates.
	file.seekg(header_.offset_texcoords);
	file.read(reinterpret_cast<char*>(texcoords_),
	          sizeof(md2::texcoord_t) * header_.num_texcoords);

	// Read triangles.
	file.seekg(header_.offset_triangles);
	file.read(reinterpret_cast<char*>(triangles_),
	          sizeof(md2::triangle_t) * header_.num_triangles);

	// Read frames.
	file.seekg(header_.offset_frames);
	for (int i = 0; i < header_.num_frames; ++i) {
		frames_[i].vertices = new md2::vertex_t[header_.num_vertices];

		file.read(reinterpret_cast<char*>(&frames_[i].scale),
		          sizeof(md2::vec3_t));

		file.read(reinterpret_cast<char*>(&frames_[i].translate),
		          sizeof(md2::vec3_t));

		file.read(reinterpret_cast<char*>(frames_[i].name), sizeof(char) * 16);

		file.read(reinterpret_cast<char*>(frames_[i].vertices),
		          sizeof(md2::vertex_t) * header_.num_vertices);
	}

	file.close();

	return true;
}

bool Md2Model::load_texture(const std::string& filename) {
	texture_ = std::make_unique<Texture>(filename.c_str());
	return texture_->LoadTextureA();
}

void Md2Model::load_frame_mesh(int frame_num) {
	if (frame_num < 0 || frame_num >= header_.num_frames) return;

	// Vertices for vertex buffer. (vertex, texcoord, normal)
	std::vector<float> vertices;
	// Indices for index buffer.
	std::vector<uint32_t> indices;

	for (int i = 0; i < header_.num_triangles; ++i) {
		for (int j = 0; j < 3; ++j) {
			md2::frame_t* ptr_frame = &frames_[frame_num];
			md2::vertex_t* ptr_vert =
			    &ptr_frame->vertices[triangles_[i].index_vert[j]];
			md2::texcoord_t* ptr_texcoord =
			    &texcoords_[triangles_[i].index_st[j]];

			// Load vertices.
			vertices.push_back(ptr_vert->vertex[0] * ptr_frame->scale[0] +
			                   ptr_frame->translate[0]);
			vertices.push_back(ptr_vert->vertex[1] * ptr_frame->scale[1] +
			                   ptr_frame->translate[1]);
			vertices.push_back(ptr_vert->vertex[2] * ptr_frame->scale[2] +
			                   ptr_frame->translate[2]);

			// Load texcoords.
			vertices.push_back(static_cast<float>(ptr_texcoord->s) /
			                   static_cast<float>(header_.skinwidth));
			vertices.push_back(static_cast<float>(ptr_texcoord->t) /
			                   static_cast<float>(header_.skinheight));

			// Load normals.
			vertices.push_back(-pre_normals_[ptr_vert->normal_index][0]);
			vertices.push_back(-pre_normals_[ptr_vert->normal_index][1]);
			vertices.push_back(-pre_normals_[ptr_vert->normal_index][2]);

			// Reversed order for indices for back face culling.
			indices.push_back(i * 3 + (2 - j));
		}
	}

	mesh_ = std::make_unique<Mesh>();
	mesh_->CreateMesh(vertices.data(), indices.data(), vertices.size(),
	                  indices.size());
}

void Md2Model::load_interpolated_frame_mesh(int frame_a, int frame_b,
                                            float interpolation) {
	if ((frame_a < 0 || frame_a >= header_.num_frames || frame_b < 0 ||
	     frame_b >= header_.num_frames)) {
		return;
	}

	// Vertices for vertex buffer. (vertex, texcoord, normal)
	std::vector<float> vertices;
	// Indices for index buffer.
	std::vector<uint32_t> indices;

	for (int i = 0; i < header_.num_triangles; ++i) {
		for (int j = 0; j < 3; ++j) {
			md2::frame_t* ptr_frame_a = &frames_[frame_a];
			md2::frame_t* ptr_frame_b = &frames_[frame_b];

			md2::vertex_t* ptr_vert_a =
			    &ptr_frame_a->vertices[triangles_[i].index_vert[j]];
			md2::vertex_t* ptr_vert_b =
			    &ptr_frame_b->vertices[triangles_[i].index_vert[j]];

			md2::texcoord_t* ptr_texcoord =
			    &texcoords_[triangles_[i].index_st[j]];

			md2::vec3_t vert_a, vert_b, vertex;

			// Uncompress vertex positions.
			vert_a[0] = ptr_vert_a->vertex[0] * ptr_frame_a->scale[0] +
			            ptr_frame_a->translate[0];
			vert_a[1] = ptr_vert_a->vertex[1] * ptr_frame_a->scale[1] +
			            ptr_frame_a->translate[1];
			vert_a[2] = ptr_vert_a->vertex[2] * ptr_frame_a->scale[2] +
			            ptr_frame_a->translate[2];

			vert_b[0] = ptr_vert_b->vertex[0] * ptr_frame_b->scale[0] +
			            ptr_frame_b->translate[0];
			vert_b[1] = ptr_vert_b->vertex[1] * ptr_frame_b->scale[1] +
			            ptr_frame_b->translate[1];
			vert_b[2] = ptr_vert_b->vertex[2] * ptr_frame_b->scale[2] +
			            ptr_frame_b->translate[2];

			// Linear interpolation for vertex.
			vertex[0] = (vert_a[0] + interpolation * (vert_b[0] - vert_a[0]));
			vertex[1] = (vert_a[1] + interpolation * (vert_b[1] - vert_a[1]));
			vertex[2] = (vert_a[2] + interpolation * (vert_b[2] - vert_a[2]));

			// Load interpolated vertices.
			vertices.push_back(vertex[0]);
			vertices.push_back(vertex[1]);
			vertices.push_back(vertex[2]);

			// Load texcoords.
			vertices.push_back(static_cast<float>(ptr_texcoord->s) /
			                   static_cast<float>(header_.skinwidth));
			vertices.push_back(static_cast<float>(ptr_texcoord->t) /
			                   static_cast<float>(header_.skinheight));

			const float* norm_a = pre_normals_[ptr_vert_a->normal_index];
			const float* norm_b = pre_normals_[ptr_vert_b->normal_index];

			md2::vec3_t normal;

			// Linear interpolation for normals.
			normal[0] = norm_a[0] + interpolation * (norm_b[0] - norm_a[0]);
			normal[1] = norm_a[1] + interpolation * (norm_b[1] - norm_a[1]);
			normal[2] = norm_a[2] + interpolation * (norm_b[2] - norm_a[2]);

			// Load interpolated normals.
			vertices.push_back(-normal[0]);
			vertices.push_back(-normal[1]);
			vertices.push_back(-normal[2]);

			// Reverse order for indices back face culling.
			indices.push_back(i * 3 + (2 - j));
		}
	}

	mesh_ = std::make_unique<Mesh>();
	mesh_->CreateMesh(vertices.data(), indices.data(), vertices.size(),
	                  indices.size());
}
void Md2Model::animate(float delta_time) {
	animstate_.curr_time += delta_time;

	if (animstate_.curr_time - animstate_.prev_time > (1.0f / animstate_.fps)) {
		animstate_.curr_frame = animstate_.next_frame;
		++animstate_.next_frame;

		if (animstate_.next_frame > animstate_.end_frame) {
			animstate_.next_frame = animstate_.start_frame;
		}

		animstate_.prev_time = animstate_.curr_time;
	}

	if (animstate_.curr_frame > (header_.num_frames - 1)) {
		animstate_.curr_frame = 0;
	}

	if (animstate_.next_frame > (header_.num_frames - 1)) {
		animstate_.next_frame = 0;
	}

	animstate_.interpol =
	    animstate_.fps * (animstate_.curr_time - animstate_.prev_time);
}

Md2Model::~Md2Model() {
	delete[] texcoords_;
	delete[] triangles_;
	delete[] frames_;
}
