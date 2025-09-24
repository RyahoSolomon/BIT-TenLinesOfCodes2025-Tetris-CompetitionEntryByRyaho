#pragma once
#include <string>
#include <string.h>
#include <graphics.h>
#include "state.h"
#include "class_statemanager.h"

#include <iostream>

extern StateManager state_manager;

extern int score;

extern const int default_window_width;
extern const int default_window_height;

extern IMAGE end_page;
extern bool is_gotten_new_highest_score;

class EndState : public State
{
public:
	EndState();
	void on_enter();
	void input(const ExMessage& msg);
	void on_exit();
	void update(int delta);
	void draw();
private:
	std::wstring score_text;
	int score_text_width;
	LPCTSTR title;
	int title_width;
};