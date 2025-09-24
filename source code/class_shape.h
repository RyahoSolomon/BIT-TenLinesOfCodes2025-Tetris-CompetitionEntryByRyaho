#pragma once
#include "class_block.h"
#include <vector>

#include <iostream>
using namespace std;

extern Vector default_shape_spawn_pos;

extern Vector preview_lefttop;
extern int preview_block_size;

extern Block* stable_blocks[10][20];

class Shape
{
protected:
	Vector distribution[4][4];
	int direction = 0;
	std::vector<Block*> blocks;
	Vector pos;

	void update_distruibution();
	void init_blocks();
	// 初始化形状
	virtual void init_distruibution();

public:
	// 玩家操作
	void try_rotate_clockwise();
	void try_rotate_anticlockwise();
	void try_move_left();
	void try_move_right();
	bool qucik_fall();
	
	// 渲染
	void draw();
	virtual void draw_at_preview();

	void set_blocks_color(COLORREF color);

	std::vector<Vector> get_blocks_pos();
	void set_pos(Vector spos = default_shape_spawn_pos);

	// 下落
	bool move_down();
	Shape();
	Shape(bool is_current);
	~Shape();
};

class ShapeLine : public Shape
{
public:
	ShapeLine();
	ShapeLine(bool is_current);
	void draw_at_preview();
private:
	void init_distruibution();
};

class ShapeL : public Shape
{
public:
	ShapeL();
	ShapeL(bool is_current);
	void draw_at_preview();
private:
	void init_distruibution();
};

class ShapeLB : public Shape
{
public:
	ShapeLB();
	ShapeLB(bool is_current);
	void draw_at_preview();
private:
	void init_distruibution();
};

class ShapeT : public Shape
{
public:
	ShapeT();
	ShapeT(bool is_current);
	void draw_at_preview();
private:
	void init_distruibution();
};

class ShapeZ : public Shape
{
public:
	ShapeZ();
	ShapeZ(bool is_current);
	void draw_at_preview();
private:
	void init_distruibution();
};

class ShapeZB : public Shape
{
public:
	ShapeZB();
	ShapeZB(bool is_current);
	void draw_at_preview();
private:
	void init_distruibution();
};

class ShapeBlock : public Shape
{
public:
	ShapeBlock();
	ShapeBlock(bool is_current);
private:
	void init_distruibution();
};