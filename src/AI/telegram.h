#pragma once
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
#include <sol/sol.hpp>

struct telegram {
	/// the entity that sent this telegram
	int sender;

	/// the entity that is to receive this telegram
	int receiver;

	/// the message itself. These are all enumerated in the file
	/// "MessageTypes.h"
	int msg;

	/// messages can be dispatched immediately or delayed for a specified amount
	/// of time. If a delay is necessary this field is stamped with the time
	/// the message should be dispatched.
	double dispatchTime;

	/// any additional information that may accompany the message
	sol::object extraInfo;

	/**
	 * @brief	Default constructor
	 */
	telegram() : dispatchTime(-1), sender(-1), receiver(-1), msg(-1) {}

	/**
	 * @brief	Non defautl constructor
	 * @param	time		- The time till it should send the message
	 * @param	sender		- The sender's id
	 * @param	reciever	- The reciever's id
	 * @param	msg			- The message to send
	 * @param	info		- The sol::object to send as extra information
	 */
	telegram(double time, int sender, int receiver, int msg, sol::object info)
	    : dispatchTime(time),
	      sender(sender),
	      receiver(receiver),
	      msg(msg),
	      extraInfo(info) {}
};

/// these telegrams will be stored in a priority queue. Therefore the >
/// operator needs to be overloaded so that the PQ can sort the telegrams
/// by time priority. Note how the times must be smaller than
/// SmallestDelay apart before two telegrams are considered unique.
const double smallestDelay = 0.25;

/**
 * @brief	Overloaded equality operator
 * @param	t1	- Object your checking
 * @param	t2	- Object your checking
 */
inline bool operator==(const telegram& t1, const telegram& t2) {
	return (fabs(t1.dispatchTime - t2.dispatchTime) < smallestDelay) &&
	       (t1.sender == t2.sender) && (t1.receiver == t2.receiver) &&
	       (t1.msg == t2.msg);
}

/**
 * @brief	Less than operator
 * @param	t1	- Object your comparing against
 * @param	t2	- Object your comparing against
 */
inline bool operator<(const telegram& t1, const telegram& t2) {
	if (t1 == t2) {
		return false;
	}

	else {
		return (t1.dispatchTime < t2.dispatchTime);
	}
}

/**
 * @brief	Overloaded << operator
 * @param	os	- Out stream
 * @param	t	- The telegram to output
 */
inline std::ostream& operator<<(std::ostream& os, const telegram& t) {
	os << "time: " << t.dispatchTime << "  Sender: " << t.sender
	   << "   Receiver: " << t.receiver << "   Msg: " << t.msg;

	return os;
}

/// handy helper function for dereferencing the ExtraInfo field of the telegram
/// to the required type.
template <class T>
inline T DereferenceToType(void* p) {
	return *(T*)(p);
}
