#pragma once

#include <string>

namespace Component {
/**
 * @struct Model
 * @brief The model component is used to store the name of the model and
 * material stored in the ResourceManager.
 */
struct Model {
	/// The name of the model.
	std::string model_name = {"default"};
	/// The name of the material.
	std::string material_name = {"default"};

	Model() = default;

	Model(const Model&) = default;

	Model(const std::string& model_name, const std::string& material_name)
	    : model_name(model_name), material_name(material_name) {}
};
};  // namespace Component