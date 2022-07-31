#include "Md2Model.hpp"

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

void Md2Model::render_animated() {
	if (!mesh_) return;

	render_frame(animstate_.curr_frame);
}

void Md2Model::render_animated_interpolated() {
	if (!mesh_) return;

	render_interpolated_frame(animstate_.curr_frame, animstate_.next_frame,
	                          animstate_.interpol);
}

void Md2Model::render_frame(int frame_num) {
	load_frame_mesh(frame_num);

	mesh_->render_mesh();
}

void Md2Model::render_interpolated_frame(int frame_a, int frame_b,
                                         float interpolation) {
	load_interpolated_frame_mesh(frame_a, frame_b, interpolation);

	mesh_->render_mesh();
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

	pre_load_frames();

	return true;
}

void Md2Model::pre_load_frames() {
	frame_vertices_.resize(header_.num_frames);

	const int num_vertices = (header_.num_triangles * 3) * 8;

	for (size_t frame = 0; frame < header_.num_frames; ++frame) {
		frame_vertices_[frame].reserve(num_vertices);
		for (size_t tri = 0; tri < header_.num_triangles; ++tri) {
			for (size_t vert = 0; vert < 3; ++vert) {
				const md2::frame_t* ptr_frame = &frames_[frame];
				const md2::vertex_t* ptr_vert =
				    &ptr_frame->vertices[triangles_[tri].index_vert[vert]];
				const md2::texcoord_t* ptr_texcoord =
				    &texcoords_[triangles_[tri].index_st[vert]];

				if (frame == 0) {
					indices_.emplace_back(tri * 3 + (2 - vert));
				}

				frame_vertices_[frame].emplace_back(ptr_vert->vertex[0] *
				                                        ptr_frame->scale[0] +
				                                    ptr_frame->translate[0]);
				frame_vertices_[frame].emplace_back(ptr_vert->vertex[1] *
				                                        ptr_frame->scale[1] +
				                                    ptr_frame->translate[1]);
				frame_vertices_[frame].emplace_back(ptr_vert->vertex[2] *
				                                        ptr_frame->scale[2] +
				                                    ptr_frame->translate[2]);

				frame_vertices_[frame].emplace_back(
				    static_cast<float>(ptr_texcoord->s) /
				    static_cast<float>(header_.skinwidth));
				frame_vertices_[frame].emplace_back(
				    static_cast<float>(ptr_texcoord->t) /
				    static_cast<float>(header_.skinheight));

				frame_vertices_[frame].emplace_back(
				    -pre_normals_[ptr_vert->normal_index][0]);
				frame_vertices_[frame].emplace_back(
				    -pre_normals_[ptr_vert->normal_index][1]);
				frame_vertices_[frame].emplace_back(
				    -pre_normals_[ptr_vert->normal_index][2]);
			}
		}
	}
}

void Md2Model::load_frame_mesh(int frame_num) {
	if (frame_num < 0 || frame_num >= header_.num_frames) return;

	mesh_ = std::make_unique<Mesh>();
	mesh_->create_mesh(frame_vertices_[frame_num].data(), indices_.data(),
	                   frame_vertices_[frame_num].size(), indices_.size());
}

void Md2Model::load_interpolated_frame_mesh(int frame_a, int frame_b,
                                            float interpolation) {
	if ((frame_a < 0 || frame_a >= header_.num_frames || frame_b < 0 ||
	     frame_b >= header_.num_frames)) {
		return;
	}

	// Vertices for vertex buffer. (vertex, texcoord, normal)
	std::vector<float> vertices;

	const int num_vertices = header_.num_triangles * 3;

	const int num_vertices_layout = num_vertices * 8;

	vertices.reserve(num_vertices_layout);

	for (int i = 0; i < num_vertices; ++i) {
		const float* vert_a = &frame_vertices_[frame_a][i * 8];
		const float* vert_b = &frame_vertices_[frame_b][i * 8];

		const float* texcoords = &vert_a[3];

		const float* norm_a = &vert_a[5];
		const float* norm_b = &vert_b[5];

		// Load interpolated vertices.
		vertices.emplace_back(vert_a[0] +
		                      interpolation * (vert_b[0] - vert_a[0]));
		vertices.emplace_back(vert_a[1] +
		                      interpolation * (vert_b[1] - vert_a[1]));
		vertices.emplace_back(vert_a[2] +
		                      interpolation * (vert_b[2] - vert_a[2]));

		// Load texcoords.
		vertices.emplace_back(texcoords[0]);
		vertices.emplace_back(texcoords[1]);

		// Load interpolated normals.
		vertices.emplace_back(norm_a[0] +
		                      interpolation * (norm_b[0] - norm_a[0]));
		vertices.emplace_back(norm_a[1] +
		                      interpolation * (norm_b[1] - norm_a[1]));
		vertices.emplace_back(norm_a[2] +
		                      interpolation * (norm_b[2] - norm_a[2]));
	}

	mesh_ = std::make_unique<Mesh>();
	mesh_->create_mesh(vertices.data(), indices_.data(), vertices.size(),
	                   indices_.size());
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
