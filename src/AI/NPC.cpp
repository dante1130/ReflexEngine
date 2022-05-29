#include "AI/NPC.hpp"

#include "singletons.h"

NPC::NPC(const std::string& model_name, const std::string& texture_name,
         bool is_animated, bool is_loop_)
    : m_animation(model_name, texture_name, is_animated, is_loop_) {
	m_NPC_FSM = new stateMachine<NPC>(this);
	m_animation.set_animation(md2::animation_type::JUMP);
	m_id = idMgr.increment_count();
	m_model_texture = texture_name;
}

NPC::~NPC() { delete m_NPC_FSM; }

void NPC::init() {}

void NPC::update(double delta_time) {}

void NPC::fixed_update(double delta_time) {
	if (!EngineTime::is_paused()) {
		m_AI_time_elapsed += delta_time;
		if (m_AI_time_elapsed > m_AI_update_delay) {
			m_NPC_FSM->update();

			position = rb.getPosition();
			position.y = GenericFunctions::getHeight(position.x, position.z);
			rb.set_position(glm::vec3(position.x, position.y + 1, position.z));
			m_AI_time_elapsed = 0.0f;
		}
	}
}

void NPC::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}

void NPC::draw(std::shared_ptr<Shader> shader) {
	auto default_shader = ReflexEngine::get_instance().renderer_.get_shader();

	glm::mat4 model(1.0f);
	model = glm::translate(model,
	                       glm::vec3(position.x, position.y + 0.5, position.z));
	model = glm::rotate(model, glm::radians(-angle),
	                    glm::vec3(rotation.x, rotation.y, rotation.z));
	model =
	    glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// model =
	//     glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
	glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader->GetUsingTexture(), true);

	auto& material_m = ResourceManager::get_instance().get_material_manager();
	material_m.get_material(material_name_)
	    .UseMaterial(default_shader->GetShininessLocation(),
	                 default_shader->GetSpecularIntensityLocation());

	// auto& model_m = ResourceManager::get_instance().get_md2_model_manager();
	// model_m.get_md2_model(model_name_);
	m_animation.render(EngineTime::get_delta_time());
}

void NPC::save_object() {
	ObjectSaving::openFile();
	ObjectSaving::saveGameObject(position, rotation, scale, angle, "NPC");
	ObjectSaving::addComma();
	ObjectSaving::addValue("modelName", model_name_, false);
	ObjectSaving::addValue("model_texture", m_model_texture, false);
	ObjectSaving::addValue("material_name", material_name_, false);
	ObjectSaving::addValue("animate", m_animation.get_is_animated(), false);
	ObjectSaving::addValue("loopAnimation", m_animation.get_loop(), false);
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
	ObjectSaving::addValue("numOfColliders", rb.getNumberOfColliders(), true);
	ObjectSaving::closeStruct();

	ObjectSaving::createStruct("AI");
	ObjectSaving::addValue("setUpFSM", m_setup, false);
	ObjectSaving::addValue("faction", m_faction, false);
	ObjectSaving::addValue("health", m_health, false);
	ObjectSaving::addValue("power", m_power, false);
	ObjectSaving::addValue("moveSpeed", m_move_speed, true);
	ObjectSaving::closeStruct();

	for (int count = 0; count < rb.getNumberOfColliders(); count++) {
		int type = rb.getColliderType(count);
		ObjectSaving::createStruct("collider" + std::to_string(count + 1));
		saveCollider(count, type);
		ObjectSaving::closeStruct();
	}

	ObjectSaving::closeFile();
}

bool NPC::handleMessage(const telegram& msg) {
	return m_NPC_FSM->handleMessage(msg);
}

void NPC::set_id(int new_id) { m_id = new_id; }
int NPC::get_id() { return m_id; }

void NPC::kill_npc(bool kill) { m_dead = kill; }
bool NPC::is_dead() { return m_dead; }

void NPC::set_health(float new_health) { m_health = new_health; }
float NPC::get_health() { return m_health; }

void NPC::set_power(float new_power) { m_power = new_power; }
float NPC::get_power() { return m_power; }

int NPC::get_waypoint_count() { return m_waypoints.size(); }
void NPC::add_waypointGLM(glm::vec2 waypoint) { m_waypoints.push(waypoint); }
void NPC::add_waypoint(float x, float z) { add_waypointGLM(glm::vec2(x, z)); }
void NPC::add_waypoints(const std::queue<glm::vec2>& new_waypoints) {
	remove_waypoints();
	m_waypoints = new_waypoints;
}
void NPC::remove_waypoints() {
	if (m_waypoints.size() != 0) {
		m_waypoints.empty();
	}
}
void NPC::use_pathfinding(float x1, float z1, float x2, float z2) {
	remove_waypoints();
	m_waypoints = gameWorld.pathFinding(x1, z1, x2, z2);
}

void NPC::new_state(std::string new_state) {
	m_NPC_FSM->changeState(new_state);
}

stateMachine<NPC>* NPC::get_FSM() { return m_NPC_FSM; }

void NPC::set_faction(int new_faction) { m_faction = new_faction; }
int NPC::get_faction() { return m_faction; }

void NPC::set_enemy_target(float x, float z) { m_target_pos.set(x, z); }
vector2D NPC::get_enemy_target() { return m_target_pos; }

void NPC::set_target_id(int new_target) { m_target_id = new_target; }
int NPC::get_target_id() { return m_target_id; }

void NPC::set_move_speed(float new_speed) { m_move_speed = new_speed; }
float NPC::get_move_speed() { return m_move_speed; }

void NPC::set_pos(vector2D pos) {
	position.x = pos.getX();
	position.z = pos.getY();
	position.y = GenericFunctions::getHeight(position.x, position.z);
	rb.set_position(glm::vec3(position.x, position.y, position.z));
}
float NPC::get_pos_x() { return position.x; }
float NPC::get_pos_y() { return position.y; }
float NPC::get_pos_z() { return position.z; }

bool NPC::waypoint_follow(bool gen_new) {
	if (m_waypoints.size() == 0 && gen_new) {
		std::cout << "waypoints empty & gen new" << std::endl;
		rb.setLinearVelocity(glm::vec3(0, 0, 0));
		return true;

	} else if (m_waypoints.size() == 0) {
		std::cout << "waypoints empty" << std::endl;
		rb.setLinearVelocity(glm::vec3(0, 0, 0));
		return true;
	}

	if (move_NPC(m_waypoints.front().x, m_waypoints.front().y, 0)) {
		// std::cout << "removing: " << m_waypoints.front().x << " : "
		//           << m_waypoints.front().y << std::endl;
		m_waypoints.pop();
		return true;
	}
	return false;
}

bool NPC::move_NPC(float x, float z, float offset) {
	glm::vec2 new_pos = glm::vec2(x, z);
	glm::vec2 newPos = glm::vec2(position.x, position.z);

	bool ret = ai_movement::moveTo(newPos, new_pos, glm::vec2(1, 1),
	                               m_AI_time_elapsed, offset);

	// position.x = newPos.x;
	// position.z = newPos.y;

	if (ret == false) {
		glm::vec2 lookAt;
		lookAt.x = new_pos.x - newPos.x;
		lookAt.y = new_pos.y - newPos.y;
		lookAt = glm::normalize(lookAt);
		angle = atan2(lookAt.y, lookAt.x) * 180 / 3.151f;
		lookAt = lookAt * glm::vec2(m_move_speed, m_move_speed);
		rb.setLinearVelocity(glm::vec3(lookAt.x, 0, lookAt.y));
	}

	return ret;
}

bool NPC::watch_for_enemy() { return watch_for_enemyVal(10); }

bool NPC::watch_for_enemyVal(float range) {
	int size = entityMgr.numberOfEntities();

	NPC* npc;
	glm::vec2 lookAt = glm::vec2(-1, 0);
	glm::vec3 pos;
	for (int count = 0; count < size; count++) {
		npc = entityMgr.getEntityByIndex(count);
		if (m_faction != npc->get_faction()) {
			if (!npc->is_dead()) {
				pos = npc->position;
				lookAt.x = cos(angle / 180 * 3.151f);
				lookAt.y = sin(angle / 180 * 3.151f);
				if (ai_movement::seeTarget(glm::vec2(position.x, position.z),
				                           glm::vec2(pos.x, pos.z), lookAt,
				                           range, 160)) {
					m_target_id = npc->m_id;

					// Sets new angle of rotation, so NPC looks at target
					lookAt.x = pos.x - position.x;
					lookAt.y = pos.z - position.z;
					lookAt = glm::normalize(lookAt);
					angle = atan2(lookAt.y, lookAt.x) * 180 / 3.151f;
					// std::cout << "Angle: " << angle << " look at: " <<
					// lookAt.x
					//           << " : " << lookAt.y << std::endl;
					return true;  // target spotted
				}
			}
		}
	}
	return false;
}

bool NPC::move_to_enemy(float offset) {
	NPC* npc = entityMgr.getEntityFromID(m_target_id);
	if (npc->is_dead()) {
		return false;
	}

	return move_NPC(npc->position.x, npc->position.z, offset);
}

void NPC::send_message(double time, int sender, int reciever, int msg,
                       sol::object extra) {
	messageMgr.dispatchMsg(time, sender, reciever, msg, extra);
}

void NPC::send_group_message(double time, int faction, float range, int sender,
                             int msg, sol::object extra) {
	glm::vec3 temp;
	float distance;
	for (int count = 0; count < entityMgr.numberOfEntities(); count++) {
		if (entityMgr.getEntityByIndex(count)->m_faction != faction ||
		    sender == entityMgr.getEntityByIndex(count)->m_id) {
			continue;
		}

		temp = entityMgr.getEntityByIndex(count)->position;

		distance = glm::length(temp - position);
		if (distance < range) {
			messageMgr.dispatchMsg(time, sender,
			                       entityMgr.getEntityByIndex(count)->m_id, msg,
			                       extra);
		}
	}
}

void NPC::freezeNPC() { rb.setLinearVelocity(glm::vec3(0)); }

ModelData& NPC::get_animation() { return m_animation; }

void NPC::setSetup(std::string set) { m_setup = set; }
