#ifndef TELEGRAM_H
#define TELEGRAM_H
//------------------------------------------------------------------------
//
//  Name:   telegram.h
//
//  Desc:   This defines a telegram. A telegram is a data structure that
//          records information required to dispatch messages. Messages
//          are used by game agents to communicate with each other.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <iostream>
#include <math.h>

struct telegram {
	// the entity that sent this telegram
	int sender;

	// the entity that is to receive this telegram
	int receiver;

	// the message itself. These are all enumerated in the file
	//"MessageTypes.h"
	int msg;

	// messages can be dispatched immediately or delayed for a specified amount
	// of time. If a delay is necessary this field is stamped with the time
	// the message should be dispatched.
	double dispatchTime;

	// any additional information that may accompany the message
	void* extraInfo;

	telegram() : dispatchTime(-1), sender(-1), receiver(-1), msg(-1) {}

	telegram(double time, int sender, int receiver, int msg, void* info = NULL)
	    : dispatchTime(time),
	      sender(sender),
	      receiver(receiver),
	      msg(msg),
	      extraInfo(info) {}
};

// these telegrams will be stored in a priority queue. Therefore the >
// operator needs to be overloaded so that the PQ can sort the telegrams
// by time priority. Note how the times must be smaller than
// SmallestDelay apart before two telegrams are considered unique.
const double smallestDelay = 0.25;

inline bool operator==(const telegram& t1, const telegram& t2) {
	return (fabs(t1.dispatchTime - t2.dispatchTime) < smallestDelay) &&
	       (t1.sender == t2.sender) && (t1.receiver == t2.receiver) &&
	       (t1.msg == t2.msg);
}

inline bool operator<(const telegram& t1, const telegram& t2) {
	if (t1 == t2) {
		return false;
	}

	else {
		return (t1.dispatchTime < t2.dispatchTime);
	}
}

inline std::ostream& operator<<(std::ostream& os, const telegram& t) {
	os << "time: " << t.dispatchTime << "  Sender: " << t.sender
	   << "   Receiver: " << t.receiver << "   Msg: " << t.msg;

	return os;
}

// handy helper function for dereferencing the ExtraInfo field of the telegram
// to the required type.
template <class T>
inline T DereferenceToType(void* p) {
	return *(T*)(p);
}

#endif
