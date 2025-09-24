#include "state_end.h"

EndState::EndState()
{
	title = _T("NEW HIGHEST SCORE!");
	title_width = textwidth(title);
	score_text_width = textwidth(title_width);
}

void EndState::on_enter()
{
	score_text = std::to_wstring(score);
	score_text_width = textwidth(score_text.c_str());
	mciSendString(_T("play end from 0"), NULL, 0, NULL);
}

void EndState::input(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		if (msg.vkcode == VK_SPACE)
		{
			mciSendString(_T("play click from 0"), NULL, 0, NULL);
			state_manager.switch_state(State::StateName::home);
		}
	}
}

void EndState::on_exit()
{
}

void EndState::update(int delta)
{

}

void EndState::draw()
{
	putimage(0, 0, &end_page);
	settextstyle(96, 0, _T("IPix"));
	settextcolor(RGB(109, 75, 39));
	outtextxy((default_window_width - score_text_width) / 2 - 100, 389, score_text.c_str());
	settextcolor(RGB(197, 135, 71));
	outtextxy((default_window_width - score_text_width) / 2 - 100, 388, score_text.c_str());
	if (is_gotten_new_highest_score)
	{
		settextstyle(32, 0, _T("IPix"));
		settextcolor(RGB(109, 75, 39));
		outtextxy((default_window_width - title_width) / 2, 525, title);
		settextcolor(RGB(197, 135, 71));
		outtextxy((default_window_width - title_width) / 2, 524, title);
	}
}
