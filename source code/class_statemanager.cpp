#include "class_statemanager.h"

StateManager::StateManager()
{
}

void StateManager::switch_state(State::StateName state_name)
{
	current_state->on_exit();
	switch (state_name)
	{
	case State::StateName::home:
		current_state = state_home;
		break;
	case State::StateName::game:
		current_state = state_game;
		break;
	case State::StateName::end:
		current_state = state_end;
		break;
	}
	current_state->on_enter();
}

void StateManager::input(const ExMessage& msg)
{
	//全局的按键操作在这里处理:
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case VK_F1:
			// 开发者模式
			mciSendString(_T("play click"), NULL, 0, NULL);
			developer_mode = !developer_mode;
			break;
		case VK_ESCAPE:
			//退出游戏
			mciSendString(_T("play click"), NULL, 0, NULL);
			exit(0);
			break;
		}
	}
	current_state->input(msg);
}

void StateManager::draw()
{
	current_state->draw();
}

void StateManager::update(int delta)
{
	current_state->update(delta);
}

void StateManager::init_state()
{
	state_home->on_enter();
	current_state = state_home;
}
