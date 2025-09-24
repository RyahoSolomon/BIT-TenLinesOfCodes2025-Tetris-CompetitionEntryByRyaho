#pragma once
#include <graphics.h>

class State
{
public:
	enum StateName {home, game, end};
	// 进入状态
	virtual void on_enter() = 0;
	// 输入控制
	virtual void input(const ExMessage& msg) = 0;
	// 退出状态
	virtual void on_exit() = 0;
	// 更新数据
	virtual void update(int delta) = 0;
	// 渲染
	virtual void draw() = 0;
};