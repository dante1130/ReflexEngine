#include "PhysicsObject.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/Physics/EngineResolve.hpp"
#include "Controller/Physics/ReactResolve.hpp"


void PhysicsObject::initModel(const std::string& model_name,
                              const std::string& material_name) {
	model_name_ = model_name;
	material_name_ = material_name;
}

void PhysicsObject::initRB(glm::vec3 pos, glm::vec3 rotation, float angle) {
	rb = new ReactResolve();
	rb->init(pos, rotation, angle);
}

void PhysicsObject::initRB(glm::vec3 pos, glm::vec3 rotation, float angle, bool type) {

	if (type)
		rb = new EngineResolve();
	else
		rb = new ReactResolve();
	rb->init(pos, rotation, angle);
}

void PhysicsObject::update(double delta_time) {
	position = rb->getPosition();
	rotation = rb->getRotation();
	angle = rb->getAngle();
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
	const SphereShape* temp_sphere = rb->getColliderSphere(index);
	ObjectSaving::addValue("radius", temp_sphere->getRadius(), false);
}

void PhysicsObject::saveCapsuleCollider(size_t index) {
	const CapsuleShape* temp_capsule = rb->getColliderCapsule(index);
	ObjectSaving::addValue("radius", temp_capsule->getRadius(), false);
	ObjectSaving::addValue("height", temp_capsule->getHeight(), false);
}

void PhysicsObject::saveBoxCollider(size_t index) {
	const BoxShape* temp_box = rb->getColliderBox(index);
	Vector3 box_size = temp_box->getHalfExtents();
	ObjectSaving::addValue("xBox", box_size.x * 2, false);
	ObjectSaving::addValue("yBox", box_size.y * 2, false);
	ObjectSaving::addValue("zBox", box_size.z * 2, false);

}

void PhysicsObject::saveCollider(size_t index, int type) {
	std::string typeString;
	glm::vec3 temp_pos = rb->getColliderPosition(index, Apply::LOCAL);

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
	ObjectSaving::addValue("xPos", temp_pos.x, false);
	ObjectSaving::addValue("yPos", temp_pos.y, false);
	ObjectSaving::addValue("zPos", temp_pos.z, false);

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
	ObjectSaving::addValue("bounciness", rb->getColliderBounce(index), false);
	ObjectSaving::addValue("friction", rb->getColliderFriction(index), true);
}

void PhysicsObject::save_object() {

	glm::vec3 temp_velocity = rb->getVelocity();
	glm::vec3 temp_ang_velocity = rb->getAngVelocity();

	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle + 0.01,
	                             "PhysicsObject");
	ObjectSaving::addComma();
	ObjectSaving::addValue("modelName", model_name_, false);
	ObjectSaving::addValue("material_name", material_name_, false);
	ObjectSaving::addValue("rbType", (int)rb->getType(), false);
	ObjectSaving::addValue("gravity", (int)rb->getIsGravityEnabled(), false);
	ObjectSaving::addValue("xForce", temp_velocity.x, false);
	ObjectSaving::addValue("yForce", temp_velocity.y, false);
	ObjectSaving::addValue("zForce", temp_velocity.z, false);
	ObjectSaving::addValue("xTorque", temp_ang_velocity.x, false);
	ObjectSaving::addValue("yTorque", temp_ang_velocity.y, false);
	ObjectSaving::addValue("zTorque", temp_ang_velocity.z, false);
	ObjectSaving::addValue("linearDamping", rb->getDragForce(), false);
	ObjectSaving::addValue("angularDamping", rb->getDragTorque(), false);
	ObjectSaving::addValue("sleep", (int)rb->getCanSleep(), false);
	ObjectSaving::addValue("numOfColliders", rb->colliderSize(), true);
	ObjectSaving::closeStruct();

	for (size_t count = 0; count < rb->colliderSize(); count++) {
		int type = rb->getColliderType(count);
		ObjectSaving::createStruct("collider" + std::to_string(count + 1));
		saveCollider(count, type);
		ObjectSaving::closeStruct();
	}

	ObjectSaving::closeFile();
}
