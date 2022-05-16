#include "playerStates.h"

#include "NPC.hpp"

/******************************************************************************/
void fight::Enter(NPC* curPlayer) {
	cout << "entered fight state.." << endl;
	// curPlayer->addAmmo(50);
	srand(static_cast<unsigned>(time(0)));
}

void fight::Execute(NPC* curPlayer) {
	if (!curPlayer->watch_for_enemy()) {
		curPlayer->get_FSM()->changeState(&patrol_state::Instance());
	}
	if (!curPlayer->watch_for_enemy(2)) {
		curPlayer->get_FSM()->changeState(&chase_state::Instance());
	}

	double f = rand() % 10 * .1;
	if (f > 0.85) {
		cout << "agent " << curPlayer->get_id() << "attacks" << endl;
		messageMgr.dispatchMsg(0, curPlayer->get_id(),
		                       curPlayer->get_target_id(), 3, NULL);
	}
}

void fight::Exit(NPC* curPlayer) {
	cout << "Preparing to flee like a little girl ... leaving fight state"
	     << endl;
}

bool fight::onMessage(NPC* curPlayer, const telegram& msg) {
	if (msg.msg == 2) {
		// curPlayer->decreaseVelocity();
		curPlayer->get_FSM()->changeState(&patrol_state::Instance());
		return true;
	}
	return false;
}

/******************************************************************************/
void global::Enter(NPC* curPlayer) {
	/// not used
}

void global::Execute(NPC* curPlayer) {
	if (curPlayer->get_id() == 0 && !curPlayer->is_dead()) {
		// cout << "health " << curPlayer->get_health() << endl;
	}
}

void global::Exit(NPC* curPlayer) {
	// not used
}

bool global::onMessage(NPC* curPlayer, const telegram& msg) {
	if (msg.msg == 3 && curPlayer->get_id() == 0) {
		curPlayer->set_health(curPlayer->get_health() - 5);
		if (curPlayer->is_dead()) {
			curPlayer->get_FSM()->changeState(&die_state::Instance());
			messageMgr.dispatchMsg(0, curPlayer->get_id(), 1, 2, NULL);
			messageMgr.dispatchMsg(0, curPlayer->get_id(), 2, 2, NULL);
		}
		return true;
	}
	return false;
}
/******************************************************************************/
void die::Enter(NPC* curPlayer) {
	cout << "he dead!" << endl;
	// curPlayer->addAmmo(50);
}

void die::Execute(NPC* curPlayer) {}

void die::Exit(NPC* curPlayer) {}

bool die::onMessage(NPC* curPlayer, const telegram& msg) { return false; }

/******************************************************************************/
void idle::Enter(NPC* curPlayer) { cout << "idle state" << endl; }

void idle::Execute(NPC* curPlayer) {}

void idle::Exit(NPC* curPlayer) {}

bool idle::onMessage(NPC* curPlayer, const telegram& msg) { return false; }

/******************************************************************************/
void Flee::Enter(NPC* curPlayer) {}

void Flee::Execute(NPC* curPlayer) {}

void Flee::Exit(NPC* curPlayer) {}

bool Flee::onMessage(NPC* curPlayer, const telegram& msg) { return false; }

/******************************************************************************/
void backup::Enter(NPC* curPlayer) {  // curPlayer->increaseVelocity();
	std::cout << "Unit: " << curPlayer->get_id() << " backing up by heading to "
	          << curPlayer->get_enemy_target().x << " : "
	          << curPlayer->get_enemy_target().y << std::endl;
}

void backup::Execute(NPC* curPlayer) {
	if (curPlayer->move_NPC(curPlayer->get_enemy_target(), 10)) {
		if (curPlayer->watch_for_enemy())
			curPlayer->get_FSM()->changeState(&fight_state::Instance());
		else
			curPlayer->get_FSM()->revertToPreviousState();
	}
}

void backup::Exit(NPC* curPlayer) {  // curPlayer->decreaseVelocity();
}

bool backup::onMessage(NPC* curPlayer, const telegram& msg) { return false; }

/******************************************************************************/
void chase::Enter(NPC* curPlayer) {
	cout << "chasing enter" << endl;
	// curPlayer->increaseVelocity();
}

void chase::Execute(NPC* curPlayer) {
	// curPlayer->move_to_enemy();
	if (curPlayer->move_to_enemy())
		curPlayer->get_FSM()->changeState(&fight_state::Instance());
	if (!curPlayer->watch_for_enemy())
		curPlayer->get_FSM()->revertToPreviousState();
}

void chase::Exit(NPC* curPlayer) {  // curPlayer->decreaseVelocity();
	cout << "Chase exit" << endl;
}

bool chase::onMessage(NPC* curPlayer, const telegram& msg) { return false; }

/******************************************************************************/
void patrol::Enter(NPC* curPlayer) {  // curPlayer->setCurwayPointNo(0);
}

void patrol::Execute(NPC* curPlayer) {
	curPlayer->waypoint_follow(true);
	if (curPlayer->watch_for_enemy()) {
		curPlayer->get_FSM()->changeState(&chase_state::Instance());
		NPC* target = entityMgr.getEntityFromID(curPlayer->get_target_id());

		messageMgr.dispatchMsg(
		    0, curPlayer->get_id(), 2, 1,
		    &glm::vec2(target->position.x, target->position.z));
	}
}

void patrol::Exit(NPC* curPlayer) {}

bool patrol::onMessage(NPC* curPlayer, const telegram& msg) {
	if (msg.msg == 1 &&
	    curPlayer->get_faction() ==
	        entityMgr.getEntityFromID(msg.sender)->get_faction()) {
		cout << "message recived from agent " << msg.sender << " to "
		     << msg.receiver << endl;
		curPlayer->set_enemy_target(*(glm::vec2*)msg.extraInfo);
		curPlayer->get_FSM()->changeState(&backup_state::Instance());
		// signal that we recieved message
		return true;
	}
	return false;
}
