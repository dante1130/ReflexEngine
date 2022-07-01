#pragma once

#include <vector>

#include "Md2.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

/**
 * @class Md2Model
 * @brief A md2 model from Quake that can be used for keyframe animation.
 */
class Md2Model {
public:
	/**
	 * @brief Loads in an md2 model file.
	 *
	 * @param filename The filename of the model.
	 * @return bool
	 */
	bool load_md2(const std::string& filename);

	/**
	 * @brief Loads in a texture for the md2 model.
	 *
	 * @param filename The filename of the texture.
	 * @return bool
	 */
	bool load_texture(const std::string& filename);

	/**
	 * @brief Animate the md2 model.
	 *
	 * @param delta_time The time since the last frame.
	 */
	void animate(float delta_time);

	/**
	 * @brief Set the animation type of the md2 model.
	 *
	 * @param animation_type The animation type.
	 */
	void set_animation(md2::animation_type animation_type);

	void set_animstate(const md2::animstate_t& animstate);

	/**
	 * @brief Render the md2 model frame by frame.
	 *
	 * @param delta_time The time since the last frame.
	 */
	void render_animated(float delta_time);

	/**
	 * @brief Render the md2 model with interpolated frames.
	 *
	 * @param delta_time The time since the last frame.
	 */
	void render_animated_interpolated(float delta_time);

	/**
	 * @brief Render a single frame given the frame number.
	 *
	 * @param frame_num The frame number.
	 */
	void render_frame(int frame_num);

	/**
	 * @brief Render a interpolated frame between 2 frames.
	 *
	 * @param frame_a The first frame number.
	 * @param frame_b The second frame number.
	 * @param interpolation The interpolation value.
	 */
	void render_interpolated_frame(int frame_a, int frame_b,
	                               float interpolation);

	/**
	 * @brief Destroy the Md2 Model object
	 */
	~Md2Model();

private:
	void pre_load_frames();

	/**
	 * @brief Loads a frame to a mesh given a frame number.
	 *
	 * @param frame_num The frame number.
	 */
	void load_frame_mesh(int frame_num);

	/**
	 * @brief Loads an interpolated frame to a mesh given 2 frame numbers.
	 *
	 * @param frame_a The first frame number.
	 * @param frame_b The second frame number.
	 * @param interpolation The interpolation value.
	 */
	void load_interpolated_frame_mesh(int frame_a, int frame_b,
	                                  float interpolation);

	/// The md2 model header.
	md2::header_t header_;
	/// The md2 model texture coordinates.
	md2::texcoord_t* texcoords_;
	/// The md2 model triangles.
	md2::triangle_t* triangles_;
	/// The md2 model frames.
	md2::frame_t* frames_;

	/// The md2 precaulated normals.
	static md2::vec3_t pre_normals_[162];

	/// The animation state of the md2 model.
	md2::animstate_t animstate_;

	/// All the frame meshes of the md2 model.
	std::vector<std::vector<float>> frame_vertices_;
	std::vector<uint32_t> indices_;

	/// The md2 model mesh.
	std::unique_ptr<Mesh> mesh_ = nullptr;
	/// The md2 model texture.
	std::unique_ptr<Texture> texture_ = nullptr;
};
