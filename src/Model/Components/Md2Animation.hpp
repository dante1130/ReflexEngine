#pragma once

#include <string>

#include "View/Renderer/OpenGL/Objects/Md2.hpp"

namespace Component {
struct Md2Animation {
	/// The name of the md2 model.
	std::string md2_name = {"default"};
	/// The name of the texture.
	std::string texture_name = {"default"};
	/// The name of the material.
	std::string material_name = {"default"};

	/// The animation state of the model.
	md2::animstate_t animstate;

	/// Whether the animation should be interpolated.
	bool is_interpolated = true;
	/// Whether the animation has finished.
	bool is_animation_done = false;
	/// Whether the animation should loop.
	bool is_loop = true;

	Md2Animation() = default;

	Md2Animation(const Md2Animation&) = default;

	Md2Animation(const std::string& md2_name, const std::string& texture_name,
	             const std::string& material_name)
	    : md2_name(md2_name),
	      texture_name(texture_name),
	      material_name(material_name) {}
};
}  // namespace Component