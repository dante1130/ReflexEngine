#pragma once

#include <set>
#include <string>
#include "Controller/ReflexEngine/EngineTime.hpp"
#include "telegram.h"

class NPC;

// to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0;
const int NO_ADDITIONAL_INFO = 0;
const int SENDER_ID_IRRELEVANT = -1;

class messageDispatcher {
private:
	/// a std::set is used as the container for the delayed messages
	/// because of the benefit of automatic sorting and avoidance
	/// of duplicates. Messages are sorted by their dispatch time.
	std::set<telegram> PriorityQ;

	// this method is utilized by DispatchMsg or DispatchDelayedMessages.
	// This method calls the message handling member function of the receiving
	// entity, pReceiver, with the newly created telegram
	/*
	 * @brief This method calls the message handling member function of the
	 * receiving entity, pReceiver, with the newly created telegram
	 * @param	pReciever	- The reciever of the message
	 * @paraqm	msg			- The message to send
	 */
	void discharge(NPC* pReceiver, const telegram& msg);

public:
	/**
	 * @breif	Send a message to anther agent. Recieving agent is referenced by
	 * ID
	 * @param	delay		- The dealy on the message before it should be sent
	 * @param	sender		- The id of the send of the message
	 * @param	reciever	- The id of the receiver of the message
	 * @param	msg			- The message contents
	 * @param	extraInfo	- Extra information of the message
	 *
	 */
	void dispatchMsg(double delay, int sender, int receiver, int msg,
	                 sol::object extraInfo);

	/**
	 * @brief	Send out any delayed messages. This method is calledeach time
	 * through the main game loop
	 */
	void dispatchDelayedMessages();
};
