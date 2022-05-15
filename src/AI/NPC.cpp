#include "AI/NPC.hpp"

NPC::NPC() { m_NPC_FSM = new stateMachine<NPC>(this); }

NPC::~NPC() { delete m_NPC_FSM; }

void NPC::init() {}
void NPC::update(float delta_time) {}
void NPC::fixed_update(float delta_time) {
	m_AI_time_elapsed += delta_time;

	if (m_AI_time_elapsed > m_AI_update_delay) {
		m_NPC_FSM->update();
		m_AI_time_elapsed = 0;
	}
}
void NPC::add_draw_call() {}
void NPC::draw(std::shared_ptr<Shader> shader) {}
void NPC::save_object() {}

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

void NPC::add_waypoint(glm::vec2 waypoint) { m_waypoints.push(waypoint); }
void NPC::add_waypoint(float x, float z) { add_waypoint(glm::vec2(x, z)); }
void NPC::remove_waypoints() { m_waypoints.empty(); }

stateMachine<NPC>* NPC::get_FSM() { return m_NPC_FSM; }

void NPC::set_faction(int new_faction) { m_faction = new_faction; }
int NPC::get_faction() { return m_faction; }

void NPC::set_enemy_target(glm::vec2 target_pos) { m_target_pos = target_pos; }
glm::vec2 NPC::get_enemy_target() { return m_target_pos; }

void NPC::waypoint_follow() {}
bool NPC::move_NPC(glm::vec2 new_pos, float offset) { return true; }
bool NPC::watch_for_enemy() { return true; }
bool NPC::move_to_enemy() { return true; }
