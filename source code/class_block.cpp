#include "class_block.h"

Block::Block()
{
	color = DEFAULT_COLOR;
}

void Block::draw()
{
	set_frame_color();
	solidrectangle(pos.x * block_size, pos.y * block_size, (pos.x + 1) * block_size, (pos.y + 1) * block_size);
	set_self_color();
	solidrectangle(pos.x * block_size + FRAME_WIDTH, pos.y * block_size + FRAME_WIDTH,
		(pos.x + 1) * block_size - FRAME_WIDTH, (pos.y + 1) * block_size - FRAME_WIDTH);
}

void Block::draw_at(int x, int y)
{
	set_frame_color();
	solidrectangle(x, y, x + preview_block_size, y + preview_block_size);
	set_self_color();
	solidrectangle(x + FRAME_WIDTH, y + FRAME_WIDTH,
		x + preview_block_size - FRAME_WIDTH, y + preview_block_size - FRAME_WIDTH);
}

void Block::set_pos(Vector target)
{
	pos = target;
}

Vector Block::get_pos()
{
	return pos;
}

void Block::set_color(COLORREF scolor)
{
	color = scolor;
}

void Block::set_invalid_color()
{
	color = INVALID_COLOR;
}

void Block::set_frame_color()
{
	setfillcolor(FRAME_COLOR);
}

void Block::set_self_color()
{
	setfillcolor(color);
}

