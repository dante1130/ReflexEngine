#include "ModelData.hpp"

#include "Controller/ResourceManager/ResourceManager.hpp"

ModelData::ModelData(const std::string& model_name,
                     const std::string& texture_name, bool is_animated)
    : model_name_(model_name),
      texture_name_(texture_name),
      is_animated_(is_animated) {}

void ModelData::render(float delta_time) {
	if (is_animated_ && delta_time > 0.0f) {
		animate(delta_time);
		render_animated(delta_time);
	} else {
		render_model();
	}
}

void ModelData::render_animated(float delta_time) {
	auto& md2_model_manager =
	    ResourceManager::get_instance().get_md2_model_manager();

	auto& md2_model = md2_model_manager.get_md2_model(model_name_);

	md2_model.set_animstate(animstate_);

	md2_model.render_animated_interpolated(delta_time);
}

void ModelData::render_model() {
	auto& model_manager = ResourceManager::get_instance().get_model_manager();

	model_manager.get_model(model_name_).RenderModel();
}

void ModelData::set_fps(float fps) { animstate_.fps = fps; }

void ModelData::set_animation(md2::animation_type animation_type) {
	animstate_.type = animation_type;

	md2::anim_t anim = md2::animations_[static_cast<int>(animation_type)];

	animstate_.start_frame = anim.first_frame;
	animstate_.end_frame = anim.last_frame;
	animstate_.next_frame = anim.first_frame + 1;
	animstate_.fps = anim.fps;
}

void ModelData::animate(float delta_time) {
	animstate_.curr_time += delta_time;

	if (animstate_.curr_time - animstate_.prev_time > (1.0f / animstate_.fps)) {
		animstate_.curr_frame = animstate_.next_frame;
		++animstate_.next_frame;

		if (animstate_.next_frame > animstate_.end_frame) {
			animstate_.next_frame = animstate_.start_frame;
		}

		animstate_.prev_time = animstate_.curr_time;
	}

	animstate_.interpol =
	    animstate_.fps * (animstate_.curr_time - animstate_.prev_time);
}

bool ModelData::get_is_animated() const { return is_animated_; }
