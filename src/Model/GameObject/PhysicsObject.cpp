#include "PhysicsObject.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

PhysicsObject::PhysicsObject() {}

void PhysicsObject::initModel(const std::string& model_path, GLfloat shininess,
                              GLfloat spec_intensity) {
	// model_.LoadModel(model_path);
	m_modelName = model_path;
	material_ = Reflex::Material(shininess, spec_intensity);
}

void PhysicsObject::initRB(glm::vec3 pos, glm::vec3 rotation, float angle) {
	rb.init(pos, rotation, angle);
}

void PhysicsObject::update(float delta_time) {
	position = rb.getPosition();
	rotation = rb.getRotation();
	angle = rb.getAngle();
}

void PhysicsObject::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void PhysicsObject::draw(std::shared_ptr<Shader> shader) {
	auto default_shader = ReflexEngine::get_instance().renderer_.get_shader();

	glm::mat4 model(1.0f);
	model =
	    glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, glm::radians(angle),
	                    glm::vec3(rotation.x, rotation.y, rotation.z));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
	glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader->GetUsingTexture(), true);
	material_.UseMaterial(default_shader->GetShininessLocation(),
	                      default_shader->GetSpecularIntensityLocation());
	ModelManager& mm = ResourceManager::get_instance().get_model_manager();
	mm.get_model(m_modelName).RenderModel();
}

void PhysicsObject::saveSphereCollider(int index) {
	for (int count = 0; count < m_sphere.size(); count++) {
		if (m_sphere[count].m_colliderStored == index) {
			ObjectSaving::addValue("radius", m_sphere[count].m_radius, false);
			return;
		}
	}
}

void PhysicsObject::saveCapsuleCollider(int index) {
	for (int count = 0; count < m_capsule.size(); count++) {
		if (m_capsule[count].m_colliderStored == index) {
			ObjectSaving::addValue("radius", m_capsule[count].m_radius, false);
			ObjectSaving::addValue("height", m_capsule[count].m_height, false);
			return;
		}
	}
}

void PhysicsObject::saveBoxCollider(int index) {
	for (int count = 0; count < m_box.size(); count++) {
		if (m_box[count].m_colliderStored == index) {
			ObjectSaving::addValue("xBox", m_box[count].m_size.x, false);
			ObjectSaving::addValue("yBox", m_box[count].m_size.y, false);
			ObjectSaving::addValue("zBox", m_box[count].m_size.z, false);
			return;
		}
	}
}

void PhysicsObject::saveCollider(int index, int type) {
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
	}
	ObjectSaving::addValue("bounciness", rb.getBounciness(index), false);
	ObjectSaving::addValue("friction", rb.getFriction(index), true);
}

void PhysicsObject::saveObject() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle,
	                             "PhysicsObject");
	ObjectSaving::addComma();
	ObjectSaving::addValue("modelName", "cat", false);
	ObjectSaving::addValue("shininess", material_.getShininess(), false);
	ObjectSaving::addValue("spec_intensity", material_.getSpecIntensity(),
	                       false);
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
	ObjectSaving::addValue("numOfColliders", rb.getNumberOfColliders() - 1,
	                       true);
	ObjectSaving::closeSctruct();

	for (int count = 1; count < rb.getNumberOfColliders(); count++) {
		int type = rb.getColliderType(count);
		ObjectSaving::createStruct("collider" + std::to_string(count));
		saveCollider(count, type);
		ObjectSaving::closeSctruct();
	}

	ObjectSaving::closeFile();
}
