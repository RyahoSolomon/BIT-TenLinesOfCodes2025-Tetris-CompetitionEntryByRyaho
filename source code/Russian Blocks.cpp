#include <iostream>
#include <vector>
#include <graphics.h>
#include <wingdi.h>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")

#include "class_statemanager.h"
#include "state_home.h"
#include "state_game.h"
#include "state_end.h"
#include "class_block.h"
#include "class_shape.h"
#include "utils.h"

#define FPS 30
using namespace std;

int score = 0;
int highest_score = 0;

const int block_col_count = 10;
const int block_row_count = 20;

vector<COLORREF> color_list;

const int default_window_width = 600;
const int default_window_height = 800;

StateManager state_manager;

Block* stable_blocks[10][20];
Shape* current_shape;
Shape* next_shape;

State* state_home = nullptr;
State* state_game = nullptr;
State* state_end = nullptr;

Vector default_shape_spawn_pos(3, -4);

int block_size = 40;
int preview_block_size = 25;
Vector preview_lefttop(450, 50);

bool developer_mode = false;

void load_resources();

IMAGE gamebar;
IMAGE cover;
IMAGE end_page;

bool is_gotten_new_highest_score = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	init_color_list();
	load_resources();
	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	highest_score = get_highest_score();

	initgraph(default_window_width, default_window_height);
	setbkmode(TRANSPARENT);
	settextstyle(32, 0, _T("IPix"));

	ExMessage msg;

	state_home = new HomeState();
	state_game = new GameState();
	state_end = new EndState();
	state_manager.init_state();

	BeginBatchDraw();

	while (true)
	{
		//记录帧处理用时


		DWORD frame_start_time = GetTickCount();


		while (peekmessage(&msg))
		{
			state_manager.input(msg);
		}

		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;

		state_manager.update(delta_tick);
		last_tick_time = current_tick_time;

		cleardevice();

		state_manager.draw();

		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < (1000 / FPS))
		{
			Sleep(1000 / FPS - frame_delta_time);
		}
	}
	EndBatchDraw();
}

void load_resources()
{
	AddFontResourceEx(_T("assets/fonts/IPix.ttf"), FR_PRIVATE, 0);
	loadimage(&gamebar, _T("assets/ui/gamebar.png"));
	loadimage(&cover, _T("assets/ui/cover.png"));
	loadimage(&end_page, _T("assets/ui/end_page.png"));
	mciSendString(_T("open assets/music/call_of_magic.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open assets/sounds/gameover.mp3 alias end"), NULL, 0, NULL);
	mciSendString(_T("open assets/sounds/fall1.mp3 alias fall_1"), NULL, 0, NULL);
	mciSendString(_T("open assets/sounds/fall2.mp3 alias fall_2"), NULL, 0, NULL);
	mciSendString(_T("open assets/sounds/level_up.mp3 alias level_up"), NULL, 0, NULL);
	mciSendString(_T("open assets/sounds/click.mp3 alias click"), NULL, 0, NULL);
	mciSendString(_T("open assets/sounds/exp.mp3 alias eliminated"), NULL, 0, NULL);
}
