#pragma once

namespace md2 {

/// The identity number of the md2 model.
constexpr int ident = 844121161;
/// The version number of the md2 model.
constexpr int version = 8;

typedef float vec2_t[2];
typedef float vec3_t[3];

/// The header of the md2 model.
struct header_t {
	int ident;
	int version;

	int skinwidth;
	int skinheight;

	int framesize;

	int num_skins;
	int num_vertices;
	int num_texcoords;
	int num_triangles;
	int num_glcmds;
	int num_frames;

	int offset_skins;
	int offset_texcoords;
	int offset_triangles;
	int offset_frames;
	int offset_glcmds;
	int offset_end;
};

/// A vertex of the md2 model.
struct vertex_t {
	uint8_t vertex[3];
	uint8_t normal_index;
};

/// A texture coordinate of the md2 model.
struct texcoord_t {
	uint16_t s;
	uint16_t t;
};

/// A triangle of the md2 model.
struct triangle_t {
	uint16_t index_vert[3];
	uint16_t index_st[3];
};

/// A frame of the md2 model.
struct frame_t {
	vec3_t scale;
	vec3_t translate;
	char name[16];
	vertex_t* vertices;

	~frame_t() { delete[] vertices; }
};

/// The animation types of the md2 model.
enum class animation_type {
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINT,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH,
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,
	MAX_ANIMATIONS
};

/// An animation of the md2 model.
struct anim_t {
	int first_frame;
	int last_frame;
	int fps;
};

/// The animation state of the md2 model.
struct animstate_t {
	int start_frame = 0;
	int end_frame = 0;
	int fps = 0;

	float curr_time = 0.0f;
	float prev_time = 0.0f;
	float interpol = 0.0f;

	animation_type type = animation_type::STAND;

	int curr_frame = 0;
	int next_frame = 0;
};

};  // namespace md2