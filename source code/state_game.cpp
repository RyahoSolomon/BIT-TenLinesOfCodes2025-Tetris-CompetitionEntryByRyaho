#include "state_game.h"

void GameState::on_enter()
{
	count = 0;
	block_movedown_timer = 0;
	score = 0;
	srand(time(0));
	current_shape = init_random_shape(true);
	next_shape = init_random_shape(false);
	block_movedown_cooldown = COOLDOWN_EASY;
	is_gotten_new_highest_score = false;
}

void GameState::input(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case 65:
			mciSendString(_T("play click from 0"), NULL, 0, NULL);
			current_shape->try_move_left();
			break;
		case 68:
			mciSendString(_T("play click from 0"), NULL, 0, NULL);
			current_shape->try_move_right();
			break;
		case VK_SPACE:
			if (current_shape->qucik_fall())
			{
				srand(time(0));
				if (rand() % 2)
				{
					mciSendString(_T("play fall_1 from 0"), NULL, 0, NULL);
				}
				else
				{
					mciSendString(_T("play fall_2 from 0"), NULL, 0, NULL);
				}
				reset_timer();
			}
			break;
		case 81:
			mciSendString(_T("play click from 0"), NULL, 0, NULL);
			current_shape->try_rotate_anticlockwise();
			break;
		case 69:
			mciSendString(_T("play click from 0"), NULL, 0, NULL);
			current_shape->try_rotate_clockwise();
			break;
		}
	}
}

void GameState::on_exit()
{
	if (current_shape != nullptr)
	{
		delete current_shape;
		current_shape = nullptr;
	}
	if (next_shape != nullptr)
	{
		delete next_shape;
		next_shape = nullptr;
	}
	for (int row = 0; row < block_row_count; row++)
	{
		for (int col = 0; col < block_col_count; col++)
		{
			if (stable_blocks[col][row] != nullptr)
			{
				delete stable_blocks[col][row];
				stable_blocks[col][row] = nullptr;
			}
		}
	}
}

void GameState::update(int delta)
{
	// 更新状态栏信息
	update_texts();
	block_movedown_timer += delta;
	if (block_movedown_timer >= block_movedown_cooldown)
	{
		block_movedown_timer -= block_movedown_cooldown;
		if (!current_shape->move_down())
		{
			fetch_shape_blocks();
			delete current_shape;
			current_shape = next_shape;
			current_shape->set_pos();
			srand(time(0));
			next_shape = init_random_shape(false);
			count++;
			update_difficulty();
			eliminate_blocks();
			if (is_lose())
			{
				state_manager.switch_state(State::StateName::end);
			}
			if (count == MEDIUM_MINCOUNT + 1 || count == DIFFICULT_MINCOUNT + 1 || count == HELL_MINCOUNT + 1)
			{
				mciSendString(_T("play level_up from 0"), NULL, 0, NULL);
			}
		}
	}
}

void GameState::draw()
{
	// 绘制方块
	setlinecolor(GRIDLINE_COLOR);
	for (int col = 1; col < block_col_count; col++)
	{
		line(col * block_size, 0, col * block_size, block_row_count * block_size);
	}
	for (int row = 1; row < block_row_count; row++)
	{
		line(0, row * block_size, block_col_count * block_size, row * block_size);
	}
	current_shape->draw();
	next_shape->draw_at_preview();
	for (int col = 0; col < 10; col++)
	{
		for (int row = 0; row < 20; row++)
		{
			if (stable_blocks[col][row] != nullptr)
			{
				stable_blocks[col][row]->draw();
			}
		}
	}

	// 绘制状态栏和信息
	putimage_alpha(400, 0, &gamebar);

	settextstyle(32, 0, _T("IPix"));
	settextcolor(RGB(109, 75, 39));
	outtextxy(400 + (200 - width_count_text) / 2, 336, count_text.c_str());
	outtextxy(400 + (200 - width_count_until_next_difficulty_text) / 2, 461, count_until_next_difficulty_text.c_str());
	outtextxy(360 + (200 - width_highest_score_text) / 2, 524, highest_score_text.c_str());

	settextcolor(RGB(197, 135, 71));
	outtextxy(400 + (200 - width_count_text) / 2, 335, count_text.c_str());
	outtextxy(400 + (200 - width_count_until_next_difficulty_text) / 2, 460, count_until_next_difficulty_text.c_str());
	outtextxy(360 + (200 - width_highest_score_text) / 2, 523, highest_score_text.c_str());

	settextcolor(RGB(142, 63, 56));
	outtextxy(360 + (200 - width_score_text) / 2, 253, score_text.c_str());
	settextcolor(RGB(226, 102, 91));
	outtextxy(360 + (200 - width_score_text) / 2, 252, score_text.c_str());

	settextstyle(16, 0, _T("IPix"));
	settextcolor(RGB(109, 75, 39));
	outtextxy(400 + (200 - width_difficulty_text) / 2, 407, difficulty_text.c_str());
	settextcolor(RGB(197, 135, 71));
	outtextxy(400 + (200 - width_difficulty_text) / 2, 406, difficulty_text.c_str());
}

void GameState::fetch_shape_blocks()
{
	std::vector<Vector> blocks_pos = current_shape->get_blocks_pos();
	for (int i = 0; i < blocks_pos.size(); i++)
	{
		if (stable_blocks[blocks_pos[i].x][blocks_pos[i].y] == nullptr)
		{
			stable_blocks[blocks_pos[i].x][blocks_pos[i].y] = new Block;
			stable_blocks[blocks_pos[i].x][blocks_pos[i].y]->set_invalid_color();
			stable_blocks[blocks_pos[i].x][blocks_pos[i].y]->set_pos(blocks_pos[i]);
		}
	}
}

void GameState::update_difficulty()
{
	if (count > HELL_MINCOUNT)
	{
		block_movedown_cooldown = COOLDOWN_HELL;
	}
	else if (count > DIFFICULT_MINCOUNT)
	{
		block_movedown_cooldown = COOLDOWN_DIFFICULT;
	}
	else if (count > MEDIUM_MINCOUNT)
	{
		block_movedown_cooldown = COOLDOWN_MEDIUM;
	}
}

void GameState::eliminate_blocks()
{
	float score_magnification = 1;
	for (int row = block_row_count - 1; row >= 0; row--)
	{
		bool flag = true;
		for (int col = 0; col < block_col_count; col++)
		{
			if (stable_blocks[col][row] == nullptr)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			mciSendString(_T("play eliminated from 0"), NULL, 0, NULL);
			score += score_magnification * BASE_SCORE_PER_ROW;
			score_magnification *= SCORE_FACTOR;
			//消除一行的方块
			for (int i = 0; i < block_col_count; i++)
			{
				if (stable_blocks[i][row] != nullptr)
				{
					delete stable_blocks[i][row];
					stable_blocks[i][row] = nullptr;
				}
			}
			//上面的方块下移
			for (int i = row; i > 0; i--)
			{
				for (int j = 0; j < block_col_count; j++)
				{
					stable_blocks[j][i] = stable_blocks[j][i - 1];
					if (stable_blocks[j][i] != nullptr)
					{
						stable_blocks[j][i]->set_pos(Vector(j, i));
					}
				}
			}
			for (int j = 0; j < block_col_count; j++)
			{
				stable_blocks[j][0] = nullptr;
			}
			row++;
		}
	}
}

bool GameState::is_lose()
{
	for (int i = 0; i < 8; i++)
	{
		if (stable_blocks[i][0] != nullptr)
		{
			return true;
		}
	}
	return false;
}

void GameState::update_texts()
{
	score_text = std::to_wstring(score);
	width_score_text = textwidth(score_text.c_str());

	count_text = std::to_wstring(count);
	width_count_text = textwidth(count_text.c_str());

	if (score > highest_score)
	{
		highest_score = score;
		set_highest_score(highest_score);
		is_gotten_new_highest_score = true;
	}

	highest_score_text = std::to_wstring(highest_score);
	width_highest_score_text = textwidth(highest_score_text.c_str());

	if (count > HELL_MINCOUNT)
	{
		count_until_next_difficulty_text = string_to_wstring("--");
		difficulty_text = string_to_wstring("HELL");
	}
	else if (count > DIFFICULT_MINCOUNT)
	{
		count_until_next_difficulty_text = to_wstring(HELL_MINCOUNT - count);
		difficulty_text = string_to_wstring("DIFFICULT");
	}
	else if (count > MEDIUM_MINCOUNT)
	{
		count_until_next_difficulty_text = to_wstring(DIFFICULT_MINCOUNT - count);
		difficulty_text = string_to_wstring("NORMAL");
	}
	else
	{
		count_until_next_difficulty_text = to_wstring(MEDIUM_MINCOUNT - count);
		difficulty_text = string_to_wstring("EASY");
	}
	width_count_until_next_difficulty_text = textwidth(count_until_next_difficulty_text.c_str());
	width_difficulty_text = textwidth(difficulty_text.c_str());
}

void GameState::reset_timer()
{
	block_movedown_timer = 0;
}
