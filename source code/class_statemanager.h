#pragma once
#include <graphics.h>
#include "state.h"

extern State* state_home;
extern State* state_game;
extern State* state_end;

extern bool developer_mode;

class StateManager
{
public:
	StateManager();
	void switch_state(State::StateName state_name);
	void input(const ExMessage& msg);
	void draw();
	void update(int delta);
	void init_state();

private:
	State* current_state = nullptr;
};