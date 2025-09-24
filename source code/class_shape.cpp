#include "class_shape.h"

void Shape::update_distruibution()
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->set_pos(distribution[direction][i] + pos);
	}
;}

void Shape::init_blocks()
{
	for (int i = 0; i < 4; i++)
	{
		blocks.push_back(new Block);
	}
}

void Shape::init_distruibution()
{
}

void Shape::try_rotate_clockwise()
{
	//��ת�߼�:�鿴��һ����ת���еķ���ֲ���û�г�����Ļ���߱�ռ��,û������ת
	int next_direction = (direction + 4 - 1) % 4;
	bool flag = true;
	for (Vector relative_pos : distribution[next_direction])
	{
		Vector absolute_pos = relative_pos + pos;
		if (absolute_pos.x < 0 || absolute_pos.x > 9 || absolute_pos.y > 19)
		{
			flag = false;
			break;
		}
		if (absolute_pos.y >= 0 && stable_blocks[absolute_pos.x][absolute_pos.y] != nullptr)
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		direction = next_direction;
		update_distruibution();
	}
}

void Shape::try_rotate_anticlockwise()
{
	//��ת�߼�:�鿴��һ����ת���еķ���ֲ���û�г�����Ļ���߱�ռ��,û������ת
	int next_direction = (direction + 1) % 4;
	bool flag = true;
	for (Vector relative_pos : distribution[next_direction])
	{
		Vector absolute_pos = relative_pos + pos;
		if (absolute_pos.x < 0 || absolute_pos.x > 9 || absolute_pos.y > 19)
		{
			flag = false;
			break;
		}
		if (absolute_pos.y >= 0 &&stable_blocks[absolute_pos.x][absolute_pos.y] != nullptr)
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		direction = next_direction;
		update_distruibution();
	}
}

void Shape::try_move_left()
{
	//�ƶ��߼�: ������/����Ӧ��λ�����ޱ�ռ��
	bool flag = true;
	for (Block* block : blocks)
	{
		Vector block_pos = block->get_pos();
		if (block_pos.x < 1)
		{
			flag = false;
		}
		if (block_pos.y >= 0 && block_pos.x >= 1 && stable_blocks[block_pos.x - 1][block_pos.y] != nullptr)
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		pos.x -= 1;
		update_distruibution();
	}
}

void Shape::try_move_right()
{
	//�ƶ��߼�: ������/����Ӧ��λ�����ޱ�ռ��
	bool flag = true;
	for (Block* block : blocks)
	{
		Vector block_pos = block->get_pos();
		if (block_pos.x > 8)
		{
			flag = false;
			break;
		}
		if (block_pos.y >= 0 && block_pos.x <= 8 && stable_blocks[block_pos.x + 1][block_pos.y] != nullptr)
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		pos.x += 1;
		update_distruibution();
	}
}

bool Shape::qucik_fall()
{
	// �����Ƿ�����Ч�Ŀ����ƶ�(���Ƿ�����������1��)
	bool has_move = false;
	bool flag = true;
	while (flag)
	{
		Vector next_pos = pos;
		next_pos.y += 1;
		for (Vector relative_pos : distribution[direction])
		{
			relative_pos += next_pos;
			if (relative_pos.y > 19)
			{
				flag = false;
				break;
			}
			else if (relative_pos.y >= 0 && stable_blocks[relative_pos.x][relative_pos.y] != nullptr)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			pos = next_pos;
			has_move = true;
		}
	}
	update_distruibution();
	return has_move;
}

void Shape::draw()
{
	for (Block* block : blocks)
	{
		block->draw();
	}
}

void Shape::draw_at_preview()
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->draw_at(preview_lefttop.x + (distribution[direction][i].x * preview_block_size),
			preview_lefttop.y + (distribution[direction][i].y * preview_block_size));
	}
}

void Shape::set_blocks_color(COLORREF color)
{
	for (Block* block : blocks)
	{
		block->set_color(color);
	}
}

std::vector<Vector> Shape::get_blocks_pos()
{
	vector<Vector> result;
	for (Block* block : blocks)
	{
		result.push_back(block->get_pos());
	}
	return result;
}

void Shape::set_pos(Vector spos)
{
	pos = spos;
}

bool Shape::move_down()
{
	Vector next_pos = pos;
	next_pos.y += 1;
	for (Vector relative_pos : distribution[direction])
	{
		relative_pos += next_pos;
		if (relative_pos.y > 19 || 
			(relative_pos.y >= 0 && stable_blocks[relative_pos.x][relative_pos.y] != nullptr))
		{
			return false;
		}
	}
	pos = next_pos;
	update_distruibution();
	return true;
}

Shape::Shape()
{
}

Shape::Shape(bool is_current)
{
}

Shape::~Shape()
{
	for (Block* block : blocks)
	{
		if (block != nullptr)
		{
			delete block;
		}
	}
}

ShapeLine::ShapeLine()
{
	init_blocks();
	init_distruibution();
	pos = default_shape_spawn_pos;
	update_distruibution();
}

ShapeLine::ShapeLine(bool is_current)
{
	init_blocks();
	init_distruibution();
	if (is_current)
	{
		pos = default_shape_spawn_pos;
	}
	else
	{
		pos.x = -100;
		pos.y = -100;
	}
	update_distruibution();
}

void ShapeLine::init_distruibution()
{
	distribution[0][0].x = 0;
	distribution[0][0].y = 1;
	distribution[0][1].x = 1;
	distribution[0][1].y = 1;
	distribution[0][2].x = 2;
	distribution[0][2].y = 1;
	distribution[0][3].x = 3;
	distribution[0][3].y = 1;
	distribution[1][0].x = 2;
	distribution[1][0].y = 0;
	distribution[1][1].x = 2;
	distribution[1][1].y = 1;
	distribution[1][2].x = 2;
	distribution[1][2].y = 2;
	distribution[1][3].x = 2;
	distribution[1][3].y = 3;
	distribution[2][0].x = 0;
	distribution[2][0].y = 2;
	distribution[2][1].x = 1;
	distribution[2][1].y = 2;
	distribution[2][2].x = 2;
	distribution[2][2].y = 2;
	distribution[2][3].x = 3;
	distribution[2][3].y = 2;
	distribution[3][0].x = 1;
	distribution[3][0].y = 0;
	distribution[3][1].x = 1;
	distribution[3][1].y = 1;
	distribution[3][2].x = 1;
	distribution[3][2].y = 2;
	distribution[3][3].x = 1;
	distribution[3][3].y = 3;
}

void ShapeLine::draw_at_preview()
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->draw_at(preview_lefttop.x + (distribution[direction][i].x * preview_block_size),
			preview_lefttop.y + 12 + (distribution[direction][i].y * preview_block_size));
	}
}

ShapeL::ShapeL()
{
	init_blocks();
	init_distruibution();
	pos.x = 3;
	pos.y = -4;
	update_distruibution();
}

ShapeL::ShapeL(bool is_current)
{
	init_blocks();
	init_distruibution();
	if (is_current)
	{
		pos = default_shape_spawn_pos;
	}
	else
	{
		pos.x = -100;
		pos.y = -100;
	}
	update_distruibution();
}

void ShapeL::draw_at_preview()
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->draw_at(preview_lefttop.x + (distribution[direction][i].x * preview_block_size),
			preview_lefttop.y + 12 + (distribution[direction][i].y * preview_block_size));
	}
}

void ShapeL::init_distruibution()
{
	distribution[0][0].x = 1;
	distribution[0][0].y = 0;
	distribution[0][1].x = 1;
	distribution[0][1].y = 1;
	distribution[0][2].x = 1;
	distribution[0][2].y = 2;
	distribution[0][3].x = 2;
	distribution[0][3].y = 2;
	distribution[1][0].x = 0;
	distribution[1][0].y = 2;
	distribution[1][1].x = 1;
	distribution[1][1].y = 2;
	distribution[1][2].x = 2;
	distribution[1][2].y = 2;
	distribution[1][3].x = 2;
	distribution[1][3].y = 1;
	distribution[2][0].x = 0;
	distribution[2][0].y = 0;
	distribution[2][1].x = 1;
	distribution[2][1].y = 0;
	distribution[2][2].x = 1;
	distribution[2][2].y = 1;
	distribution[2][3].x = 1;
	distribution[2][3].y = 2;
	distribution[3][0].x = 0;
	distribution[3][0].y = 1;
	distribution[3][1].x = 0;
	distribution[3][1].y = 0;
	distribution[3][2].x = 1;
	distribution[3][2].y = 0;
	distribution[3][3].x = 2;
	distribution[3][3].y = 0;
}


ShapeLB::ShapeLB()
{
	init_blocks();
	init_distruibution();
	pos = default_shape_spawn_pos;
	update_distruibution();
}

ShapeLB::ShapeLB(bool is_current)
{
	init_blocks();
	init_distruibution();
	if (is_current)
	{
		pos = default_shape_spawn_pos;
	}
	else
	{
		pos.x = -100;
		pos.y = -100;
	}
	update_distruibution();
}

void ShapeLB::draw_at_preview()
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->draw_at(preview_lefttop.x + 25 + (distribution[direction][i].x * preview_block_size),
			preview_lefttop.y + 12 + (distribution[direction][i].y * preview_block_size));
	}
}

void ShapeLB::init_distruibution()
{
	distribution[0][0].x = 1;
	distribution[0][0].y = 0;
	distribution[0][1].x = 1;
	distribution[0][1].y = 1;
	distribution[0][2].x = 1;
	distribution[0][2].y = 2;
	distribution[0][3].x = 0;
	distribution[0][3].y = 2;
	distribution[1][0].x = 0;
	distribution[1][0].y = 1;
	distribution[1][1].x = 1;
	distribution[1][1].y = 1;
	distribution[1][2].x = 2;
	distribution[1][2].y = 1;
	distribution[1][3].x = 2;
	distribution[1][3].y = 2;
	distribution[2][0].x = 0;
	distribution[2][0].y = 0;
	distribution[2][1].x = 1;
	distribution[2][1].y = 0;
	distribution[2][2].x = 0;
	distribution[2][2].y = 1;
	distribution[2][3].x = 0;
	distribution[2][3].y = 2;
	distribution[3][0].x = 0;
	distribution[3][0].y = 0;
	distribution[3][1].x = 0;
	distribution[3][1].y = 1;
	distribution[3][2].x = 1;
	distribution[3][2].y = 1;
	distribution[3][3].x = 2;
	distribution[3][3].y = 1;
}

ShapeT::ShapeT()
{
	init_blocks();
	init_distruibution();
	pos = default_shape_spawn_pos;
	update_distruibution();
}

ShapeT::ShapeT(bool is_current)
{
	init_blocks();
	init_distruibution();
	if (is_current)
	{
		pos = default_shape_spawn_pos;
	}
	else
	{
		pos.x = -100;
		pos.y = -100;
	}
	update_distruibution();
}

void ShapeT::draw_at_preview()
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->draw_at(preview_lefttop.x + 12 + (distribution[direction][i].x * preview_block_size),
			preview_lefttop.y + 25 + (distribution[direction][i].y * preview_block_size));
	}
}

void ShapeT::init_distruibution()
{
	distribution[0][0].x = 1;
	distribution[0][0].y = 0;
	distribution[0][1].x = 0;
	distribution[0][1].y = 1;
	distribution[0][2].x = 1;
	distribution[0][2].y = 1;
	distribution[0][3].x = 2;
	distribution[0][3].y = 1;
	distribution[1][0].x = 0;
	distribution[1][0].y = 1;
	distribution[1][1].x = 1;
	distribution[1][1].y = 0;
	distribution[1][2].x = 1;
	distribution[1][2].y = 1;
	distribution[1][3].x = 1;
	distribution[1][3].y = 2;
	distribution[2][0].x = 0;
	distribution[2][0].y = 1;
	distribution[2][1].x = 1;
	distribution[2][1].y = 1;
	distribution[2][2].x = 2;
	distribution[2][2].y = 1;
	distribution[2][3].x = 1;
	distribution[2][3].y = 2;
	distribution[3][0].x = 1;
	distribution[3][0].y = 0;
	distribution[3][1].x = 1;
	distribution[3][1].y = 1;
	distribution[3][2].x = 1;
	distribution[3][2].y = 2;
	distribution[3][3].x = 2;
	distribution[3][3].y = 1;
}

ShapeZ::ShapeZ()
{
	init_blocks();
	init_distruibution();
	pos = default_shape_spawn_pos;
	update_distruibution();
}

ShapeZ::ShapeZ(bool is_current)
{
	init_blocks();
	init_distruibution();
	if (is_current)
	{
		pos = default_shape_spawn_pos;
	}
	else
	{
		pos.x = -100;
		pos.y = -100;
	}
	update_distruibution();
}

void ShapeZ::draw_at_preview()
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->draw_at(preview_lefttop.x + 12 + (distribution[direction][i].x * preview_block_size),
			preview_lefttop.y + (distribution[direction][i].y * preview_block_size));
	}
}

void ShapeZ::init_distruibution()
{
	distribution[0][0].x = 0;
	distribution[0][0].y = 1;
	distribution[0][1].x = 1;
	distribution[0][1].y = 1;
	distribution[0][2].x = 1;
	distribution[0][2].y = 2;
	distribution[0][3].x = 2;
	distribution[0][3].y = 2;
	distribution[1][0].x = 1;
	distribution[1][0].y = 1;
	distribution[1][1].x = 1;
	distribution[1][1].y = 2;
	distribution[1][2].x = 2;
	distribution[1][2].y = 0;
	distribution[1][3].x = 2;
	distribution[1][3].y = 1;
	distribution[2][0].x = 0;
	distribution[2][0].y = 0;
	distribution[2][1].x = 1;
	distribution[2][1].y = 0;
	distribution[2][2].x = 1;
	distribution[2][2].y = 1;
	distribution[2][3].x = 2;
	distribution[2][3].y = 1;
	distribution[3][0].x = 1;
	distribution[3][0].y = 0;
	distribution[3][1].x = 1;
	distribution[3][1].y = 1;
	distribution[3][2].x = 0;
	distribution[3][2].y = 1;
	distribution[3][3].x = 0;
	distribution[3][3].y = 2;
}

ShapeZB::ShapeZB()
{
	init_blocks();
	init_distruibution();
	pos = default_shape_spawn_pos;
	update_distruibution();
}

ShapeZB::ShapeZB(bool is_current)
{
	init_blocks();
	init_distruibution();
	if (is_current)
	{
		pos = default_shape_spawn_pos;
	}
	else
	{
		pos.x = -100;
		pos.y = -100;
	}
	update_distruibution();
}

void ShapeZB::draw_at_preview()
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i]->draw_at(preview_lefttop.x + 12 + (distribution[direction][i].x * preview_block_size),
			preview_lefttop.y + 25 + (distribution[direction][i].y * preview_block_size));
	}
}

void ShapeZB::init_distruibution()
{
	distribution[0][0].x = 1;
	distribution[0][0].y = 0;
	distribution[0][1].x = 2;
	distribution[0][1].y = 0;
	distribution[0][2].x = 1;
	distribution[0][2].y = 1;
	distribution[0][3].x = 0;
	distribution[0][3].y = 1;
	distribution[1][0].x = 0;
	distribution[1][0].y = 0;
	distribution[1][1].x = 0;
	distribution[1][1].y = 1;
	distribution[1][2].x = 1;
	distribution[1][2].y = 1;
	distribution[1][3].x = 1;
	distribution[1][3].y = 2;
	distribution[2][0].x = 0;
	distribution[2][0].y = 2;
	distribution[2][1].x = 1;
	distribution[2][1].y = 2;
	distribution[2][2].x = 1;
	distribution[2][2].y = 1;
	distribution[2][3].x = 2;
	distribution[2][3].y = 1;
	distribution[3][0].x = 1;
	distribution[3][0].y = 0;
	distribution[3][1].x = 1;
	distribution[3][1].y = 1;
	distribution[3][2].x = 2;
	distribution[3][2].y = 1;
	distribution[3][3].x = 2;
	distribution[3][3].y = 2;
}

ShapeBlock::ShapeBlock()
{
	init_blocks();
	init_distruibution();
	pos = default_shape_spawn_pos;
	update_distruibution();
}

ShapeBlock::ShapeBlock(bool is_current)
{
	init_blocks();
	init_distruibution();
	if (is_current)
	{
		pos = default_shape_spawn_pos;
	}
	else
	{
		pos.x = -100;
		pos.y = -100;
	}
	update_distruibution();
}

void ShapeBlock::init_distruibution()
{
	distribution[0][0].x = 1;
	distribution[0][0].y = 1;
	distribution[0][1].x = 1;
	distribution[0][1].y = 2;
	distribution[0][2].x = 2;
	distribution[0][2].y = 1;
	distribution[0][3].x = 2;
	distribution[0][3].y = 2;
	distribution[1][0].x = 1;
	distribution[1][0].y = 1;
	distribution[1][1].x = 1;
	distribution[1][1].y = 2;
	distribution[1][2].x = 2;
	distribution[1][2].y = 1;
	distribution[1][3].x = 2;
	distribution[1][3].y = 2;
	distribution[2][0].x = 1;
	distribution[2][0].y = 1;
	distribution[2][1].x = 1;
	distribution[2][1].y = 2;
	distribution[2][2].x = 2;
	distribution[2][2].y = 1;
	distribution[2][3].x = 2;
	distribution[2][3].y = 2;
	distribution[3][0].x = 1;
	distribution[3][0].y = 1;
	distribution[3][1].x = 1;
	distribution[3][1].y = 2;
	distribution[3][2].x = 2;
	distribution[3][2].y = 1;
	distribution[3][3].x = 2;
	distribution[3][3].y = 2;
}
