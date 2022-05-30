#include "PointLightObject.hpp"

#include "Controller/ResourceManager/ObjectSaving.hpp"
#include "Controller/ReflexEngine/ReflexEngine.hpp"

PointLightObject::PointLightObject(const PointLightData& light_data)
    : light_data_(light_data) {}

void PointLightObject::add_draw_call() {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	renderer.add_point_light(light_data_);
}

void PointLightObject::save_object() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle,
	                             "PointLight");
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

	ObjectSaving::createStruct("position");
	ObjectSaving::addValue("x", light_data_.position.x, false);
	ObjectSaving::addValue("y", light_data_.position.y, false);
	ObjectSaving::addValue("z", light_data_.position.z, true);
	ObjectSaving::closeStruct();
	ObjectSaving::addComma();

	ObjectSaving::addValue("constant", light_data_.constant, false);
	ObjectSaving::addValue("linear", light_data_.linear, false);
	ObjectSaving::addValue("quadratic", light_data_.quadratic, true);

	ObjectSaving::closeStruct();
	ObjectSaving::closeFile();
}
