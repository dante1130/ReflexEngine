#ifndef __PLAYERSTATES_H
#define __PLAYERSTATES_H

#include "singleton.h"
#include "state.h"
#include <glm.hpp>

#include <iostream>

#include "movement.h"
#include "singletons.h"
#include <time.h>

using namespace std;

#include <windows.h>
#pragma comment(lib, "winmm.lib")

class NPC;
struct telegram;

class fight : public State<NPC> {
public:
	virtual void Enter(NPC* dude);
	virtual void Execute(NPC* dude);
	virtual void Exit(NPC* dude);
	virtual bool onMessage(NPC* dude, const telegram& msg);
};

class global : public State<NPC> {
public:
	virtual void Enter(NPC* dude);
	virtual void Execute(NPC* dude);
	virtual void Exit(NPC* dude);
	virtual bool onMessage(NPC* dude, const telegram& msg);
};

class die : public State<NPC> {
public:
	virtual void Enter(NPC* dude);
	virtual void Execute(NPC* dude);
	virtual void Exit(NPC* dude);
	virtual bool onMessage(NPC* dude, const telegram& msg);
};

class idle : public State<NPC> {
public:
	virtual void Enter(NPC* dude);
	virtual void Execute(NPC* dude);
	virtual void Exit(NPC* dude);
	virtual bool onMessage(NPC* dude, const telegram& msg);
};

class backup : public State<NPC> {
public:
	virtual void Enter(NPC* dude);
	virtual void Execute(NPC* dude);
	virtual void Exit(NPC* dude);
	virtual bool onMessage(NPC* dude, const telegram& msg);
};

class chase : public State<NPC> {
public:
	virtual void Enter(NPC* dude);
	virtual void Execute(NPC* dude);
	virtual void Exit(NPC* dude);
	virtual bool onMessage(NPC* dude, const telegram& msg);
};

class patrol : public State<NPC> {
public:
	virtual void Enter(NPC* dude);
	virtual void Execute(NPC* dude);
	virtual void Exit(NPC* dude);
	virtual bool onMessage(NPC* dude, const telegram& msg);
};

class Flee : public State<NPC> {
public:
	virtual void Enter(NPC* dude);
	virtual void Execute(NPC* dude);
	virtual void Exit(NPC* dude);
	virtual bool onMessage(NPC* dude, const telegram& msg);
};

typedef singleton<fight> fight_state;
typedef singleton<global> global_state;
typedef singleton<die> die_state;
typedef singleton<idle> idle_state;
typedef singleton<Flee> flee_state;
typedef singleton<backup> backup_state;
typedef singleton<chase> chase_state;
typedef singleton<patrol> patrol_state;

#endif
