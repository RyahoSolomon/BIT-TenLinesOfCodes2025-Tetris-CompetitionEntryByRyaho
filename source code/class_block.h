#pragma once
#include <graphics.h>
#include "class_vector.h"
#define INVALID_COLOR RGB(101, 103, 101)
#define FRAME_COLOR RGB(189, 192, 186)
#define FRAME_WIDTH 1
#define DEFAULT_COLOR RGB(204, 84, 58)

#include<iostream>
using namespace std;

extern int block_size;
extern int preview_block_size;

class Block
{
public:
	Block();
	// 根据成员变量pos绘制
	void draw();
	// 指定位置绘制,主要用于下一个方块预览
	void draw_at(int x, int y);
	void set_color(COLORREF scolor);
	void set_invalid_color();
	void set_pos(Vector target);
	Vector get_pos();
private:
	COLORREF color;
	Vector pos;
	void set_frame_color();
	void set_self_color();
};