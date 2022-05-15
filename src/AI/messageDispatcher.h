#ifndef __MESSAGEDISPATCHER_H
#define __MESSAGEDISPATCHER_H

#include <set>
#include <string>
#include "EngineTime.hpp"
#include "telegram.h"

class NPC;

// to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0;
const int NO_ADDITIONAL_INFO = 0;
const int SENDER_ID_IRRELEVANT = -1;

class messageDispatcher {
private:
	// a std::set is used as the container for the delayed messages
	// because of the benefit of automatic sorting and avoidance
	// of duplicates. Messages are sorted by their dispatch time.
	std::set<telegram> PriorityQ;

	// this method is utilized by DispatchMsg or DispatchDelayedMessages.
	// This method calls the message handling member function of the receiving
	// entity, pReceiver, with the newly created telegram
	void discharge(NPC* pReceiver, const telegram& msg);

public:
	// send a message to another agent. Receiving agent is referenced by ID.
	void dispatchMsg(double delay, int sender, int receiver, int msg,
	                 void* extraInfo);
	// send out any delayed messages. This method is called each time through
	// the main game loop.
	void dispatchDelayedMessages();
};

#endif
