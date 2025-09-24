#pragma once
#include "state.h"
#include "class_statemanager.h"

extern const int default_window_width;
extern const int default_window_height;

extern IMAGE cover;

extern StateManager state_manager;

class HomeState : public State
{
public:
	HomeState();
	void on_enter();
	void input(const ExMessage& msg);
	void on_exit();
	void update(int delta);
	void draw();
private:
	LPCTSTR author_info = _T("作者:Ryaho•Escall•Solomon");
};