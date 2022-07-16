#include "PhysicsObject.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

void PhysicsObject::initModel(const std::string& model_name,
                              const std::string& material_name) {
	model_name_ = model_name;
	material_name_ = material_name;
}

void PhysicsObject::initRB(glm::vec3 pos, glm::vec3 rotation, float angle) {
	rb.init(pos, rotation, angle);
}

void PhysicsObject::update(double delta_time) {
	position = rb.getPosition();
	rotation = rb.getRotation();
	angle = rb.getAngle();
}

void PhysicsObject::fixed_update(double delta_time) {
	// position.y = GenericFunctions::getHeight(position.x, position.z);
	// rb.set_position(position);
}

void PhysicsObject::add_draw_call() {
	DrawCall draw_call = [this](const Shader& shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void PhysicsObject::draw(const Shader& shader) {
	glm::mat4 model(1.0f);
	model =
	    glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, glm::radians(angle),
	                    glm::vec3(rotation.x, rotation.y, rotation.z));

	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
	glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader.GetUsingTexture(), true);

	auto& material_m = ResourceManager::get_instance().get_material_manager();
	material_m.get_material(material_name_)
	    .UseMaterial(shader.GetShininessLocation(),
	                 shader.GetSpecularIntensityLocation());

	auto& model_m = ResourceManager::get_instance().get_model_manager();
	model_m.get_model(model_name_).RenderModel();
}

void PhysicsObject::saveSphereCollider(size_t index) {
	for (const auto& sphere : m_sphere) {
		if (sphere.m_colliderStored == index) {
			ObjectSaving::addValue("radius", sphere.m_radius, false);
			return;
		}
	}
}

void PhysicsObject::saveCapsuleCollider(size_t index) {
	for (const auto& capsule : m_capsule) {
		if (capsule.m_colliderStored == index) {
			ObjectSaving::addValue("radius", capsule.m_radius, false);
			ObjectSaving::addValue("height", capsule.m_height, false);
			return;
		}
	}
}

void PhysicsObject::saveBoxCollider(size_t index) {
	for (const auto& box : m_box) {
		if (box.m_colliderStored == index) {
			ObjectSaving::addValue("xBox", box.m_size.x, false);
			ObjectSaving::addValue("yBox", box.m_size.y, false);
			ObjectSaving::addValue("zBox", box.m_size.z, false);
			return;
		}
	}
}

void PhysicsObject::saveCollider(size_t index, int type) {
	std::string typeString;

	switch (type) {
		case 1:
			typeString = "Sphere";
			break;
		case 2:
			typeString = "Capsule";
			break;
		case 3:
			typeString = "Box";
			break;
		default:
			break;
	}

	ObjectSaving::addValue("colliderType", typeString, false);
	ObjectSaving::addValue("xPos", rb.getLocalColliderPos(index).x, false);
	ObjectSaving::addValue("yPos", rb.getLocalColliderPos(index).y, false);
	ObjectSaving::addValue("zPos", rb.getLocalColliderPos(index).z, false);

	switch (type) {
		case 1:
			saveSphereCollider(index);
			break;
		case 2:
			saveCapsuleCollider(index);
			break;
		case 3:
			saveBoxCollider(index);
			break;
		default:
			break;
	}
	ObjectSaving::addValue("bounciness", rb.getBounciness(index), false);
	ObjectSaving::addValue("friction", rb.getFriction(index), true);
}

void PhysicsObject::save_object() {
	if (savable) {
		ObjectSaving::openFile();
		ObjectSaving::saveGameObject(position, rotation, scale, angle + 0.01,
		                             "PhysicsObject", savable);
		ObjectSaving::addComma();
		ObjectSaving::addValue("modelName", model_name_, false);
		ObjectSaving::addValue("material_name", material_name_, false);
		ObjectSaving::addValue("rbType", rb.getRBType(), false);
		ObjectSaving::addValue("gravity", (int)rb.getIfGravityActive(), false);
		ObjectSaving::addValue("xForce", rb.getLinearVelocity().x, false);
		ObjectSaving::addValue("yForce", rb.getLinearVelocity().y, false);
		ObjectSaving::addValue("zForce", rb.getLinearVelocity().z, false);
		ObjectSaving::addValue("xTorque", rb.getAngularVelocity().x, false);
		ObjectSaving::addValue("yTorque", rb.getAngularVelocity().y, false);
		ObjectSaving::addValue("zTorque", rb.getAngularVelocity().z, false);
		ObjectSaving::addValue("linearDamping", rb.getLinearDamping(), false);
		ObjectSaving::addValue("angularDamping", rb.getAngularDamping(), false);
		ObjectSaving::addValue("sleep", (int)rb.getIfAllowedSleep(), false);
		ObjectSaving::addValue("numOfColliders", rb.getNumberOfColliders(),
		                       true);
		ObjectSaving::closeStruct();

		for (size_t count = 0; count < rb.getNumberOfColliders(); count++) {
			int type = rb.getColliderType(count);
			ObjectSaving::createStruct("collider" + std::to_string(count + 1));
			saveCollider(count, type);
			ObjectSaving::closeStruct();
		}

		ObjectSaving::closeFile();
	}
}
