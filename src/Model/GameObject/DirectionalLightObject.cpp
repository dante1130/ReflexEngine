#include "DirectionalLightObject.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

DirectionalLightObject::DirectionalLightObject(
    const DirectionalLightData& light_data)
    : light_data_(light_data) {}

void DirectionalLightObject::add_draw_call() {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	renderer.add_directional_light(light_data_);
}

void DirectionalLightObject::save_object() {}