#include "PhysicsObject.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

void PhysicsObject::init() { }

void PhysicsObject::initModel(const std::string& model_name,
                              const std::string& material_name) {
	model_name_ = model_name;
	material_name_ = material_name;
}

void PhysicsObject::initRB(glm::vec3 pos, glm::vec3 rotation, float angle) {

	pb = new ReactResolve();
	pb->init(pos, rotation, angle);

}

void PhysicsObject::initRB(glm::vec3 pos, glm::vec3 rotation, float angle, bool type) {
	if (type)
		pb = new EngineResolve();
	else
		pb = new ReactResolve();
	pb->init(pos, rotation, angle);
}

void PhysicsObject::update(double delta_time) {
	position = pb->getPosition();
	rotation = pb->getRotation();
	angle = pb->getAngle();

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
	const SphereShape* temp_sphere = pb->getColliderSphere(index);
	ObjectSaving::addValue("radius", temp_sphere->getRadius(), false);
}

void PhysicsObject::saveCapsuleCollider(size_t index) {
	const CapsuleShape* temp_capsule = pb->getColliderCapsule(index);
	ObjectSaving::addValue("radius", temp_capsule->getRadius(), false);
	ObjectSaving::addValue("height", temp_capsule->getHeight(), false);
}

void PhysicsObject::saveBoxCollider(size_t index) {
	const BoxShape* temp_box = pb->getColliderBox(index);
	Vector3 box_size = temp_box->getHalfExtents();
	ObjectSaving::addValue("xBox", box_size.x * 2, false);
	ObjectSaving::addValue("yBox", box_size.y * 2, false);
	ObjectSaving::addValue("zBox", box_size.z * 2, false);

}

void PhysicsObject::saveCollider(size_t index, int type) {
	std::string typeString;
	glm::vec3 temp_pos = pb->getColliderPosition(index, Apply::LOCAL);

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
	ObjectSaving::addValue("bounciness", pb->getColliderBounce(index), false);
	ObjectSaving::addValue("friction", pb->getColliderFriction(index), true);
}

void PhysicsObject::save_object() {

	glm::vec3 temp_velocity = pb->getVelocity();
	glm::vec3 temp_ang_velocity = pb->getAngVelocity();

	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle + 0.01,
	                             "PhysicsObject");
	ObjectSaving::addComma();
	ObjectSaving::addValue("modelName", model_name_, false);
	ObjectSaving::addValue("material_name", material_name_, false);
	ObjectSaving::addValue("rbType", (int)pb->getType(), false);
	ObjectSaving::addValue("gravity", (int)pb->getIsGravityEnabled(), false);
	ObjectSaving::addValue("xForce", temp_velocity.x, false);
	ObjectSaving::addValue("yForce", temp_velocity.y, false);
	ObjectSaving::addValue("zForce", temp_velocity.z, false);
	ObjectSaving::addValue("xTorque", temp_ang_velocity.x, false);
	ObjectSaving::addValue("yTorque", temp_ang_velocity.y, false);
	ObjectSaving::addValue("zTorque", temp_ang_velocity.z, false);
	ObjectSaving::addValue("linearDamping", pb->getDragForce(), false);
	ObjectSaving::addValue("angularDamping", pb->getDragTorque(), false);
	ObjectSaving::addValue("sleep", (int)pb->getCanSleep(), false);
	ObjectSaving::addValue("numOfColliders", pb->colliderSize(), true);
	ObjectSaving::closeStruct();

	for (size_t count = 0; count < pb->colliderSize(); count++) {
		int type = pb->getColliderType(count);
		ObjectSaving::createStruct("collider" + std::to_string(count + 1));
		saveCollider(count, type);
		ObjectSaving::closeStruct();
	}

	ObjectSaving::closeFile();
}


//**********************************
// Physic stuff (temporary placement)
// lord forgive me...
//***********************************

int PhysicsObject::colliderSize() { return pb->colliderSize(); }

glm::vec3 PhysicsObject::getColliderPosition(int index, Apply type) {return pb->getColliderPosition(index, type);}

glm::vec4 getColliderOrientation(int index, Apply type);

float PhysicsObject::getColliderBounce(int index) { return pb->getColliderBounce(index); }

float PhysicsObject::getColliderFriction(int index) { return pb->getColliderFriction(index); }

float PhysicsObject::getColliderMassDesity(int index) { return pb->getColliderMassDesity(index); }

int PhysicsObject::getColliderType(int index) { return pb->getColliderType(index); }

const BoxShape* PhysicsObject::getColliderBox(int index) { return pb->getColliderBox(index); }

const SphereShape* PhysicsObject::getColliderSphere(int index) { return pb->getColliderSphere(index); }

const CapsuleShape* PhysicsObject::getColliderCapsule(int index) { return pb->getColliderCapsule(index); }

void PhysicsObject::addMaterialToCollider(int index, float bounce, float mass_density, float friction)
{ return pb->addMaterialToCollider(index, bounce, mass_density, friction); }

void PhysicsObject::removeAllColliders() { pb->removeAllColliders(); }

void PhysicsObject::setObjectTrigger(bool ean) { pb->setObjectTrigger(ean); }

bool PhysicsObject::usingReactResolve() { return pb->usingReactResolve(); }

void PhysicsObject::init(glm::vec3 rot, glm::vec3 pos, float angle) { pb->init(rot, pos, angle); }

void PhysicsObject::addForce(glm::vec3 force, Apply type) { pb->addForce(force, type); }

void PhysicsObject::addForceAtPoint(glm::vec3 force, glm::vec3 point, ApplyPoint type)
{ pb->addForceAtPoint(force, point, type); }

void PhysicsObject::addTorque(glm::vec3 torque, Apply type) { pb->addTorque(torque, type); }

void PhysicsObject::addDragForce(float drag) { pb->addDragForce(drag); }

void PhysicsObject::addDragTorque(float ang_drag) { pb->addDragTorque(ang_drag); }

void PhysicsObject::setMass(float mass) { pb->setMass(mass); }

void PhysicsObject::setCenterOfMass(glm::vec3 p) { pb->setCenterOfMass(p); }

void PhysicsObject::setVelocity(glm::vec3 vel) { 
	pb->setVelocity(vel); 
}

void PhysicsObject::setAngVelocity(glm::vec3 ang_vel) { pb->setAngVelocity(ang_vel); }

void PhysicsObject::setType(BodyType type) { pb->setType(type); }

void PhysicsObject::setType(int type) { pb->setType(type); }

void PhysicsObject::enableGravity(bool ean) { pb->enableGravity(ean); }

void PhysicsObject::setCanSleep(bool ean) { pb->setCanSleep(ean); }

float PhysicsObject::getMass() { return pb->getMass(); }

glm::vec3 PhysicsObject::getVelocity() { return pb->getVelocity(); }

glm::vec3 PhysicsObject::getAngVelocity() { return pb->getAngVelocity(); }

float PhysicsObject::getDragForce() { return pb->getDragForce(); }

float PhysicsObject::getDragTorque() { return pb->getDragTorque(); }

BodyType PhysicsObject::getType() { return pb->getType(); }

bool PhysicsObject::getIsGravityEnabled() { return pb->getIsGravityEnabled(); }

bool PhysicsObject::getCanSleep() { return pb->getCanSleep(); }

void PhysicsObject::addBoxCollider(glm::vec3 pos, glm::vec3 size){ pb->addBoxCollider(pos, size); }

void PhysicsObject::addSphereCollider(glm::vec3 pos, float radius) { pb->addSphereCollider(pos, radius); }

void PhysicsObject::addCapsuleCollider(glm::vec3 pos, float radius, float height) { pb->addCapsuleCollider(pos, radius, height); }

void PhysicsObject::addBoxCollider(glm::vec3 pos, glm::vec3 size, float bounce, float friction) {
	pb->addBoxCollider(pos, size, bounce, friction);
}
void PhysicsObject::addSphereCollider(glm::vec3 pos, float radius, float bounce, float friction)
{
	pb->addSphereCollider(pos, radius, bounce, friction);
}
void PhysicsObject::addCapsuleCollider(glm::vec3 pos, float radius, float height, float bounce, float friction)
{
	pb->addCapsuleCollider(pos, radius, height, bounce, friction);
}

glm::vec3 PhysicsObject::getPosition() { return pb->getPosition(); }

glm::vec3 PhysicsObject::getRotation() { return pb->getRotation(); }

float PhysicsObject::getAngle() { return pb->getAngle(); }

void PhysicsObject::setPosition(glm::vec3 pos) { pb->setPosition(pos); }

void PhysicsObject::setRotation(glm::vec3 rot) { pb->setRotation(rot); }

void PhysicsObject::setAngle(float ang) { pb->setAngle(ang); }


