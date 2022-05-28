#include "ModelData.hpp"

#include "Controller/ResourceManager/ResourceManager.hpp"

ModelData::ModelData(const std::string& model_name,
                     const std::string& texture_name, bool is_animated,
                     bool is_loop)
    : model_name_(model_name),
      texture_name_(texture_name),
      is_animated_(is_animated),
      is_loop_(is_loop) {}

void ModelData::render(double delta_time) {
	if (is_animated_) {
		animate(delta_time);
		render_animated(delta_time);
	} else {
		render_model();
	}
}

void ModelData::render_animated(double delta_time) {
	auto& md2_model_manager =
	    ResourceManager::get_instance().get_md2_model_manager();

	auto& texture_manager =
	    ResourceManager::get_instance().get_texture_manager();

	auto& md2_model = md2_model_manager.get_md2_model(model_name_);

	md2_model.set_animstate(animstate_);

	texture_manager.get_texture(texture_name_).UseTexture();
	md2_model.render_animated_interpolated(delta_time);
}

void ModelData::render_model() {
	auto& model_manager = ResourceManager::get_instance().get_model_manager();

	model_manager.get_model(model_name_).RenderModel();
}

void ModelData::set_loop(bool loop) { is_loop_ = loop; }

void ModelData::set_fps(int fps) { animstate_.fps = fps; }

void ModelData::set_animation(md2::animation_type animation_type) {
	animstate_.type = animation_type;

	md2::anim_t anim = md2::animations_[static_cast<int>(animation_type)];

	animstate_.start_frame = anim.first_frame;
	animstate_.end_frame = anim.last_frame;
	animstate_.next_frame = anim.first_frame + 1;
	animstate_.fps = anim.fps;

	is_animation_done_ = false;
}

void ModelData::animate(float delta_time) {
	if (is_animation_done_) return;

	animstate_.curr_time += delta_time;

	if (animstate_.curr_time - animstate_.prev_time > (1.0 / animstate_.fps)) {
		animstate_.curr_frame = animstate_.next_frame;
		++animstate_.next_frame;

		if (animstate_.next_frame > animstate_.end_frame) {
			if (is_loop_) {
				animstate_.next_frame = animstate_.start_frame;
			} else {
				is_animation_done_ = true;
				animstate_.next_frame = animstate_.end_frame;
			}
		}

		animstate_.prev_time = animstate_.curr_time;
	}

	if (animstate_.curr_frame > (24 - 1)) {
		animstate_.curr_frame = 0;
	}

	if (animstate_.next_frame > (24 - 1)) {
		animstate_.next_frame = 0;
	}

	animstate_.interpol =
	    animstate_.fps * (animstate_.curr_time - animstate_.prev_time);
}

bool ModelData::get_is_animated() const { return is_animated_; }

bool ModelData::get_is_running() const { return !is_animation_done_; }

bool ModelData::get_loop() const { return is_loop_; }
