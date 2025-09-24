#pragma once
#include <string>
#include <locale>
#include <codecvt>
#include "state.h"
#include "class_statemanager.h"
#include "class_shape.h"
#include "class_block.h"
#include "utils.h"

#include <iostream>
using namespace std;

// ÿ���Ѷ��·�������ļ��(����)
#define COOLDOWN_EASY 800
#define COOLDOWN_MEDIUM 640
#define COOLDOWN_DIFFICULT 500
#define COOLDOWN_HELL 360

// �Ѷ���������ķ���
#define MEDIUM_MINCOUNT 10
#define DIFFICULT_MINCOUNT 25
#define HELL_MINCOUNT 50

//����ÿ�еĻ����÷ֺ���������
#define BASE_SCORE_PER_ROW 1000
#define SCORE_FACTOR 1.44

//�ָ�����ɫ:��̿
#define GRIDLINE_COLOR RGB(67, 67, 67)

extern int score;
extern int highest_score;

extern Block* stable_blocks[10][20];
extern Shape* current_shape;
extern Shape* next_shape;

extern string debug_info;

extern Vector default_shape_spawn_pos;

extern StateManager state_manager;

extern const int block_col_count;
extern const int block_row_count;

extern const int default_window_width;
extern const int default_window_height;

extern IMAGE gamebar;

extern bool is_gotten_new_highest_score;

class GameState : public State
{
public:
	void on_enter();
	void input(const ExMessage& msg);
	void on_exit();
	void update(int delta);
	void draw();

private:

	//�����ʱ��
	int block_movedown_timer = 0;
	int count = 0;
	int block_movedown_cooldown = 0;

	void fetch_shape_blocks();
	void update_difficulty();
	void eliminate_blocks();
	bool is_lose();

	// ״̬����Ϣ
	std::wstring score_text;
	std::wstring highest_score_text;
	std::wstring count_text;
	std::wstring count_until_next_difficulty_text;
	std::wstring difficulty_text;
	int width_score_text;
	int width_highest_score_text;
	int width_count_text;
	int width_count_until_next_difficulty_text;
	int width_difficulty_text;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	void update_texts();

	// ���������ʱ��
	void reset_timer();
};