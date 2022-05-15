#include "MessageDispatcher.h"
#include "singletons.h"
#include "NPC.hpp"

using std::set;

//----------------------------- Dispatch ---------------------------------
//
//  see description in header
//------------------------------------------------------------------------
void messageDispatcher::discharge(NPC* pReceiver, const telegram& msg) {
	if (!pReceiver->handleMessage(msg)) {
		cerr << "Message not handled" << endl;
	}
}

//---------------------------- DispatchMsg ---------------------------
//
//  given a message, a receiver, a sender and any time delay, this function
//  routes the message to the correct agent (if no delay) or stores
//  in the message queue to be dispatched at the correct time
//------------------------------------------------------------------------
void messageDispatcher::dispatchMsg(double delay, int sender, int receiver,
                                    int msg, void* additionalInfo = NULL) {
	// get a pointer to the receiver
	NPC* pReceiver = entityMgr.getEntityFromID(receiver);
	// make sure the receiver is valid
	if (pReceiver == NULL) {
		cerr << "\nWarning! No Receiver with ID of " << receiver << " found"
		     << endl;
		return;
	}
	// create the telegram
	telegram message(0, sender, receiver, msg, additionalInfo);
	// if there is no delay, route telegram immediately
	if (delay <= 0.0) {  // send the telegram to the recipient
		discharge(pReceiver, message);
	} else {  // else calculate the time when the telegram should be dispatched
		double currentTime = EngineTime::get_time_unpaused();
		message.dispatchTime = currentTime + delay;
		// and put it in the queue
		PriorityQ.insert(message);
	}
}

//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void messageDispatcher::dispatchDelayedMessages() {
	// get current time
	double currentTime = EngineTime::get_time_unpaused();
	// now peek at the queue to see if any telegrams need dispatching.
	// remove all telegrams from the front of the queue that have gone
	// past their sell by date
	while (!PriorityQ.empty() &&
	       (PriorityQ.begin()->dispatchTime < currentTime) &&
	       (PriorityQ.begin()->dispatchTime > 0)) {
		// read the telegram from the front of the queue
		const telegram& message = *PriorityQ.begin();
		// find the recipient
		NPC* pReceiver = entityMgr.getEntityFromID(message.receiver);
		// send the telegram to the recipient
		discharge(pReceiver, message);
		// remove it from the queue
		PriorityQ.erase(PriorityQ.begin());
	}
}
