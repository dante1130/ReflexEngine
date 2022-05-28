#pragma once

#include <string>
#include <memory>
#include "View/Renderer/OpenGL/Objects/Shader.hpp"
#include "View/Renderer/OpenGL/Objects/Md2.hpp"

/**
 * @class ModelData
 * @brief A class for storing the data of a static or animated model.
 */
class ModelData {
public:
	/**
	 * @brief Construct a new Model Data object
	 *
	 * @param model_name The name of the model.
	 * @param texture_name The name of the texture.
	 * @param is_animated Whether the model is animated or not.
	 * @param is_loop Whether the model should loop.
	 */
	ModelData(const std::string& model_name, const std::string& texture_name,
	          bool is_animated, bool is_loop);

	/**
	 * @brief Render the model.
	 *
	 * @param delta_time The time since the last frame.
	 */
	void render(double delta_time);

	/**
	 * @brief Set the fps of the animation.
	 *
	 * @param fps The fps of the animation.
	 */
	void set_fps(int fps);

	/**
	 * @brief Set whether the animation should loop.
	 *
	 * @param loop Whether the animation should loop.
	 */
	void set_loop(bool loop);

	/**
	 * @brief Set the animation object
	 *
	 * @param animation_type The animation type.
	 */
	void set_animation(md2::animation_type animation_type);

	/**
	 * @brief Animate the model.
	 *
	 * @param delta_time
	 */
	void animate(float delta_time);

	/**
	 * @brief	If the model should be animated
	 *
	 * @param	run	- True to animated the model
	 */
	void set_is_animated(bool run);

	/**
	 * @brief Get if the model is animated.
	 *
	 * @return bool
	 */
	bool get_is_animated() const;

	/**
	 * @brief Get if the model is running.
	 *
	 * @return bool
	 */
	bool get_is_running() const;

	/**
	 * @brief Get if the model is looping.
	 *
	 * @return bool
	 */
	bool get_loop() const;

private:
	/**
	 * @brief Render the model animated.
	 *
	 * @param delta_time
	 */
	void render_animated(double delta_time);

	/**
	 * @brief Render the model statically.
	 */
	void render_model();

	/// The name of the model.
	std::string model_name_;
	/// The name of the texture.
	std::string texture_name_;

	/// The animation state of the model.
	md2::animstate_t animstate_;

	/// Whether the animation has finished.
	bool is_animation_done_ = false;
	/// Whether the animation should loop.
	bool is_loop_ = false;
	/// Whether the model is animated.
	bool is_animated_ = false;
};
