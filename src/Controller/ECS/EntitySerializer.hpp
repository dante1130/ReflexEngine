#pragma once

#include <fstream>
#include <string>

#include "Entity.hpp"

#include "Model/Components/Transform.hpp"
#include "Model/Components/Mesh.hpp"
#include "Model/Components/Model.hpp"
#include "Model/Components/Terrain.hpp"
#include "Model/Components/Statemachine.hpp"
#include "Model/Components/Script.hpp"
#include "Model/Components/Md2Animation.hpp"
#include "Model/Components/Light.hpp"

class EntitySerializer {
public:
private:
	std::ofstream entity_file;
	std::ofstream creation_script;

	void serialize_entity(Reflex::Entity& entity);
	void serialize_transform(const Component::Transform& transform);
};