#include "SkyboxObject.hpp"
#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"

SkyboxObject::SkyboxObject() { faces_.resize(6); }

void SkyboxObject::init() {
	auto& renderer = ReflexEngine::get_instance().renderer_;
	renderer.set_skybox(faces_);
}

void SkyboxObject::save_object() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle, "Skybox");
	ObjectSaving::closeStruct();
	ObjectSaving::createStruct("skybox_faces");
	ObjectSaving::addValue("right_face", faces_.at(0), false);
	ObjectSaving::addValue("left_face", faces_.at(1), false);
	ObjectSaving::addValue("top_face", faces_.at(2), false);
	ObjectSaving::addValue("bottom_face", faces_.at(3), false);
	ObjectSaving::addValue("back_face", faces_.at(4), false);
	ObjectSaving::addValue("front_face", faces_.at(5), true);
	ObjectSaving::closeStruct();
	ObjectSaving::closeFile();
}

void SkyboxObject::set_face(SkyboxFaces face, const std::string& texture_path) {
	faces_.at(static_cast<int>(face)) = texture_path;
}
