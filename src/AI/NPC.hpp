#pragma once

#include <Model/GameObject/PhysicsObject.hpp>
#include "stateMachine.h"
#include "telegram.h"
#include <queue>
//#include "AI/singletons.h"
#include "AI/movement.h"
#include <cmath>

class NPC : public PhysicsObject {
public:
	NPC();
	~NPC();
	void init();
	void update(float delta_time);
	void fixed_update(float delta_time);
	void add_draw_call();
	void draw(std::shared_ptr<Shader> shader);
	void save_object();

	bool handleMessage(const telegram& msg);

	void set_id(int new_id);
	int get_id();

	void kill_npc(bool kill);
	bool is_dead();

	void set_health(float new_health);
	float get_health();

	void set_power(int new_power);
	float get_power();

	int get_waypoint_count();
	void add_waypoint(glm::vec2 waypoint);
	void add_waypoint(float x, float z);
	void remove_waypoints();

	void new_state(State<NPC>* new_state);
	stateMachine<NPC>* get_FSM();

	void set_faction(int new_faction);
	int get_faction();

	void set_enemy_target(glm::vec2 target_pos);
	glm::vec2 get_enemy_target();

	void set_target_id(int new_target);
	int get_target_id();

	void waypoint_follow(bool gen_new);
	bool move_NPC(glm::vec2 new_pos, float offset);
	bool watch_for_enemy();
	bool watch_for_enemy(float range);
	bool move_to_enemy();

private:
	int m_id;
	int m_faction = 0;
	float m_health = 15;
	bool m_dead = false;
	float m_power = 1;

	std::queue<glm::vec2> m_waypoints;

	float m_AI_update_delay = 1 / 20;
	float m_AI_time_elapsed = 0;
	stateMachine<NPC>* m_NPC_FSM;
	glm::vec2 m_target_pos;
	int m_target_id;
};
