#include "DirectionalLightObject.hpp"

#include "Controller/ResourceManager/ObjectSaving.hpp"
#include "Controller/ReflexEngine/ReflexEngine.hpp"

DirectionalLightObject::DirectionalLightObject(
    const DirectionalLightData& light_data)
    : light_data_(light_data) {}

void DirectionalLightObject::add_draw_call() {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	renderer.add_directional_light(light_data_);
}

void DirectionalLightObject::save_object() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle,
	                             "DirectionalLight");
	ObjectSaving::closeStruct();

	ObjectSaving::createStruct("light");

	ObjectSaving::createStruct("color");
	ObjectSaving::addValue("r", light_data_.color.x, false);
	ObjectSaving::addValue("g", light_data_.color.y, false);
	ObjectSaving::addValue("b", light_data_.color.z, true);
	ObjectSaving::closeStruct();
	ObjectSaving::addComma();

	ObjectSaving::addValue("ambient_intensity", light_data_.ambient_intensity,
	                       false);
	ObjectSaving::addValue("diffuse_intensity", light_data_.diffuse_intensity,
	                       false);

	ObjectSaving::createStruct("direction");
	ObjectSaving::addValue("x", light_data_.direction.x, false);
	ObjectSaving::addValue("y", light_data_.direction.y, false);
	ObjectSaving::addValue("z", light_data_.direction.z, true);
	ObjectSaving::closeStruct();

	ObjectSaving::closeStruct();
	ObjectSaving::closeFile();
}
