#pragma once

#include "Model/GameObject/PhysicsObject.hpp"
#include "stateMachine.h"
#include "telegram.h"
#include <queue>
#include "AI/movement.h"
#include <cmath>
#include "Model/ModelData.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"
#include "AI/vector2D.hpp"

class NPC : public PhysicsObject {
public:
	/**
	 * @brief	Constructor
	 * @param	model_name		- The name of the model to use
	 * @param	texture_name	- the texture name the model uses
	 * @param	is_animated		- if the NPC is animated
	 * @param	is_loop_		- if the animation loops by default
	 */
	NPC(const std::string& model_name, const std::string& texture_name,
	    bool is_animated, bool is_loop_);

	/**
	 * @brief	Destructor
	 */
	~NPC();

	/**
	 * @brief	Initialises the game object
	 */
	void init() override;

	/**
	 * @brief	Updates the game object
	 * @param	delta_time	- The change in time since it was last called
	 */
	void update(double delta_time) override;

	/**
	 * @brief	Updates the game object on a fixed update loop
	 * @param	delta_time	- The change in time since it was last called
	 */
	void fixed_update(double delta_time) override;

	/**
	 * @brief	adds a draw call, so it will be rendered
	 */
	void add_draw_call() override;

	/**
	 * @brief	Draws the object
	 * @param	shader	- The shader
	 */
	void draw(std::shared_ptr<Shader> shader) override;

	/**
	 * @brief	Saves the object
	 */
	void save_object() override;

	/**
	 * @brief	Handles incomming messages
	 * @param	msg	- The message to be handled
	 */
	bool handleMessage(const telegram& msg);

	/**
	 * @brief	(DANGEROUS) Sets the NPC's identification (DANGEROUS) AUTOMATIC
	 * ID IS USED BY DEFAULT, TO ENSURE NO DUPLICATES, USE AT OWN RISK.
	 * @param	new_id	- New NPC identification (DANGEROUS)
	 */
	void set_id(int new_id);

	/**
	 * @brief	NPC's identificaiton
	 * @return	Returns the NPC's id (int)
	 */
	int get_id();

	/**
	 * @brief	if you should kill the NPC
	 * @param	kill	- True to kill NPC
	 */
	void kill_npc(bool kill);

	/**
	 * @brief	Gets if NPC is dead
	 * @return	bool	- True if NPC is dead
	 */
	bool is_dead();

	/**
	 * @brief	Sets health of NPC
	 * @param	new_health	- The new health of the NPC
	 */
	void set_health(float new_health);

	/**
	 * @brief	Gets the NPC's health
	 * @return	float	- health of NPC
	 */
	float get_health();

	/**
	 * @brief	Sets the power of the NPC
	 * @param	new_power	- New power of the NPC
	 */
	void set_power(float new_power);

	/**
	 * @brief	Gets the power of the NPC
	 * @return	float	- Power of NPC
	 */
	float get_power();

	/**
	 * @brief	Sets the position of the NPC
	 * @param	pos	- The new position you want
	 */
	void set_pos(vector2D pos);

	/**
	 * @brief	Gets the NPC's x position
	 * @return	float	- x position
	 */
	float get_pos_x();

	/**
	 * @brief	Gets the NPC's y position
	 * @return	float	- y position
	 */
	float get_pos_y();

	/**
	 * @brief	Gets the NPC's z position
	 * @return	float	- z position
	 */
	float get_pos_z();

	/**
	 * @brief	Gets the number of wayponts currently stored
	 * @return	int	- number of waypoints
	 */
	int get_waypoint_count();

	/**
	 * @brief	Adds a new waypoint of type glm::vec2
	 * @param	waypont	- The new waypoint to add
	 */
	void add_waypointGLM(glm::vec2 waypoint);

	/**
	 * @brief	Adds a new waypoint
	 * @param	x	- x position of waypoint
	 * @param	z	- z position of waypoint
	 */
	void add_waypoint(float x, float z);

	/**
	 * @brief	Uses pathfinding algorithm to create set of waypoints
	 * @param	x1	- current x position
	 * @param	z1	- current z position
	 * @param	x2	- target x position
	 * @param	z2	- target z position
	 */
	void use_pathfinding(float x1, float z1, float x2, float z2);

	/**
	 * @brief	Sets a queue of new waypoints and clears existing waypoints
	 * @param	new_waypoints	- The new waypoints
	 */
	void add_waypoints(const std::queue<glm::vec2>& new_waypoints);

	/**
	 * @brief	Removes all the currently stored waypoints
	 */
	void remove_waypoints();

	/**
	 * @brief	Sets a new state for the FSM
	 * @param	new_state	- new state
	 */
	void new_state(std::string new_state);

	/**
	 * @brief	Gets FSM for the NPC
	 * @return	stateMachine<NPC>	- The FSM of the NPC
	 */
	stateMachine<NPC>* get_FSM();

	/**
	 * @brief	Sets the NPC's faction
	 * @param	new_faction	- The faction for the NPC
	 */
	void set_faction(int new_faction);

	/**
	 * @brief	Gets the NPC's faction they are alligned with
	 * @return	int	- the faction it identifies with
	 */
	int get_faction();

	/**
	 * @brief	Sets the enemy targets position
	 * @param	x	- The target's x position
	 * @param	z	- The target's z position
	 */
	void set_enemy_target(float x, float z);

	/**
	 * @brief	Gets the enemy target position
	 * @return	glm::vec2	- Target position
	 */
	vector2D get_enemy_target();

	/**
	 * @brief	Sets the ID of the NPC's target
	 * @param	new_target	- The new target ID
	 */
	void set_target_id(int new_target);

	/**
	 * @brief	Gets the current target's ID
	 * @return	int	- the target's ID
	 */
	int get_target_id();

	/**
	 * @brief	Sets the new NPC's move speed
	 * @param	new_speed	- new NPC's move speed
	 */
	void set_move_speed(float new_speed);

	/**
	 * @brief	Gets the NPC's move speed
	 * @return	float	- move speed
	 */
	float get_move_speed();

	/**
	 * @brief	Follows a given waypoint
	 * @param	gen_new	- If it should generate new wayponts if there is none
	 * (not currently implemented)
	 * @return	bool	- Finished following a waypont (could have more to
	 * follow)
	 */
	bool waypoint_follow(bool gen_new);

	/**
	 * @brief	Moves current NPC to position or within offset.
	 * @param	x		- x position to move to
	 * @param	z		- z position to move to
	 * @param	offset	- stop within an offset of this value
	 * @return	bool	- true if at destination
	 */
	bool move_NPC(float x, float z, float offset);

	/**
	 * @brief	Searches for an enemy based on a distance of 10. If it sees an
	 * enemy will set its target ID & return true
	 * @return	bool	- true if it finds an enemy
	 */
	bool watch_for_enemy();

	/**
	 * @brief	Searches for an enemy based on a max distance. If it sees an
	 * enemy will set its target ID & return true
	 * @param	range	- The distance to watch from
	 * @return	bool	- true if it finds an enemy
	 */
	bool watch_for_enemyVal(float range);

	/**
	 * @brief	Moves to a targeted enemy
	 * @param	offset	- The offset to stop at
	 * @return	bool	- True if at destination or enemy is dead
	 */
	bool move_to_enemy(float offset);

	/**
	 * @brief	Sends a message to another AI agent
	 * @param	time		- delay before sending the message
	 * @param	sender		- the senders ID
	 * @param	reciever	- the recievers ID
	 * @param	msg			- the message
	 * @param	extra		- extra info in the message
	 */
	void send_message(double time, int sender, int reciever, int msg,
	                  sol::object extra);

	/**
	 * @brief	Sends a group message to a AI faction in range
	 * @param	time		- delay before sending the message
	 * @param	faction		- the faction to send the message too
	 * @param	range		- the range of the message
	 * @param	reciever	- the recievers ID
	 * @param	msg			- the message
	 * @param	extra		- extra info in the message
	 */
	void send_group_message(double time, int faction, float range, int reciever,
	                        int msg, sol::object extra);

	/**
	 * @brief	Sets the linear velocity to 0
	 */
	void freezeNPC();

	/**
	 * @brief	Gets the animation data
	 * @return	ModelDate	- The animation data for the NPC
	 */
	ModelData& get_animation();

	/**
	 * @brief	Sets the setup finite state machine to call
	 * @param	set	- The lua function which sets up the AI FSM
	 */
	void setSetup(std::string set);

private:
	/// NPC's unique identifier
	int m_id;
	/// NPC's faction
	int m_faction = 0;
	/// NPC's health
	float m_health = 15;
	/// If they are dead
	bool m_dead = false;
	/// The power of their attacks or whatever you want to use it for
	float m_power = 1;
	/// The move speed
	float m_move_speed = 1;

	/// The waypoints stored
	std::queue<glm::vec2> m_waypoints;

	/// The update delay
	float m_AI_update_delay = 1 / 20;
	/// The time elapsed since last AI update
	float m_AI_time_elapsed = 0;
	/// NPC's finite state machine
	stateMachine<NPC>* m_NPC_FSM;
	/// NPC's target position
	vector2D m_target_pos;
	/// NPC's target ID
	int m_target_id;

	std::string m_setup;
	std::string m_model_texture;

	/// Data for animating
	ModelData m_animation;
};
