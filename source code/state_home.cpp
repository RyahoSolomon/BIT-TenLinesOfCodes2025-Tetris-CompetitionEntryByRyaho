#include "state_home.h"

HomeState::HomeState()
{
}

void HomeState::on_enter()
{
}

void HomeState::input(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		if (msg.vkcode == VK_SPACE)
		{
			mciSendString(_T("play click from 0"), NULL, 0, NULL);
			state_manager.switch_state(State::StateName::game);
		}
	}
}

void HomeState::on_exit()
{
}

void HomeState::update(int delta)
{
}

void HomeState::draw()
{
	putimage(0, 0, &cover);
	settextstyle(16, 0, _T("IPix"));
	settextcolor(RGB(109, 75, 39));
	outtextxy(320, 19, author_info);
	settextcolor(RGB(197, 135, 71));
	outtextxy(320, 18, author_info);
}
