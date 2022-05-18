#include "AI/NPC.hpp"
#include "playerStates.h"

NPC::NPC() {
	m_NPC_FSM = new stateMachine<NPC>(this);
	m_NPC_FSM->setCurrentState(&idle_state::Instance());
	m_NPC_FSM->setGlobalState(&global_state::Instance());
}

NPC::~NPC() { delete m_NPC_FSM; }

void NPC::init() {}
void NPC::update(float delta_time) {}
void NPC::fixed_update(float delta_time) {
	if (!EngineTime::is_paused()) {
		m_AI_time_elapsed += delta_time;
		if (m_AI_time_elapsed > m_AI_update_delay) {
			m_NPC_FSM->update();

			if (m_id == 0) {
				// position.x = GenericFunctions::luaCamPosX();
				// position.z = GenericFunctions::luaCamPosZ();
			}
			position.y = GenericFunctions::getHeight(position.x, position.z);

			m_AI_time_elapsed = 0;
		}
	}

	if (m_health < 0) {
		// m_dead = true;
	}
}
void NPC::add_draw_call() {
	DrawCall draw_call = [=](std::shared_ptr<Shader> shader) { draw(shader); };

	ReflexEngine::get_instance().renderer_.add_draw_call(draw_call);
}
void NPC::draw(std::shared_ptr<Shader> shader) {
	auto default_shader = ReflexEngine::get_instance().renderer_.get_shader();

	glm::mat4 model(1.0f);
	model =
	    glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, glm::radians(-angle),
	                    glm::vec3(rotation.x, rotation.y, rotation.z));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
	glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE,
	                   glm::value_ptr(model));
	glUniform1i(shader->GetUsingTexture(), true);

	auto& material_m = ResourceManager::get_instance().get_material_manager();
	material_m.get_material(material_name_)
	    .UseMaterial(default_shader->GetShininessLocation(),
	                 default_shader->GetSpecularIntensityLocation());

	auto& model_m = ResourceManager::get_instance().get_model_manager();
	model_m.get_model(model_name_).RenderModel();
}
void NPC::save_object() {
	//
	//
	//
}

//
//
//
//
//

bool NPC::handleMessage(const telegram& msg) {
	return m_NPC_FSM->handleMessage(msg);
}

void NPC::set_id(int new_id) { m_id = new_id; }
int NPC::get_id() { return m_id; }

void NPC::kill_npc(bool kill) { m_dead = kill; }
bool NPC::is_dead() { return m_dead; }

void NPC::set_health(float new_health) { m_health = new_health; }
float NPC::get_health() { return m_health; }

void NPC::set_power(int new_power) { m_power = new_power; }
float NPC::get_power() { return m_power; }

int NPC::get_waypoint_count() { return m_waypoints.size(); }
void NPC::add_waypoint(glm::vec2 waypoint) { m_waypoints.push(waypoint); }
void NPC::add_waypoint(float x, float z) { add_waypoint(glm::vec2(x, z)); }
void NPC::add_waypoints(std::queue<glm::vec2>& new_waypoints) {
	remove_waypoints();
	m_waypoints = new_waypoints;
}
void NPC::remove_waypoints() {
	if (m_waypoints.size() != 0) {
		m_waypoints.empty();
	}
}

void NPC::new_state(State<NPC>* new_state) {
	m_NPC_FSM->changeState(new_state);
}
stateMachine<NPC>* NPC::get_FSM() { return m_NPC_FSM; }

void NPC::set_faction(int new_faction) { m_faction = new_faction; }
int NPC::get_faction() { return m_faction; }

void NPC::set_enemy_target(glm::vec2 target_pos) { m_target_pos = target_pos; }
glm::vec2 NPC::get_enemy_target() { return m_target_pos; }

void NPC::set_target_id(int new_target) { m_target_id = new_target; }
int NPC::get_target_id() { return m_target_id; }

//
//
//

void NPC::waypoint_follow(bool gen_new) {
	if (m_waypoints.size() == 0 && gen_new) {
		std::cout << "waypoints empty & gen new" << std::endl;
		return;

	} else if (m_waypoints.size() == 0) {
		std::cout << "waypoints empty" << std::endl;
		return;
	}

	if (move_NPC(m_waypoints.front(), 0)) {
		m_waypoints.pop();
	}
}

bool NPC::move_NPC(glm::vec2 new_pos, float offset) {
	glm::vec2 newPos = glm::vec2(position.x, position.z);

	bool ret = ai_movement::moveTo(newPos, new_pos, glm::vec2(1, 1),
	                               m_AI_time_elapsed, offset);

	position.x = newPos.x;
	position.z = newPos.y;

	// Look at angle
	if (ret == false) {
		glm::vec2 lookAt;
		lookAt.x = new_pos.x - newPos.x;
		lookAt.y = new_pos.y - newPos.y;
		lookAt = glm::normalize(lookAt);
		angle = atan2(lookAt.y, lookAt.x) * 180 / 3.151f;
	}

	return ret;
}

bool NPC::watch_for_enemy() { return watch_for_enemy(10); }

bool NPC::watch_for_enemy(float range) {
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

bool NPC::move_to_enemy() {
	NPC* npc = entityMgr.getEntityFromID(m_target_id);
	if (npc->is_dead()) {
		return false;
	}

	glm::vec2 newPos = glm::vec2(position.x, position.z);
	bool ret =
	    ai_movement::moveTo(newPos, glm::vec2(npc->position.x, npc->position.z),
	                        glm::vec2(2, 2), m_AI_time_elapsed, 3);
	position.x = newPos.x;
	position.z = newPos.y;

	return ret;
}
