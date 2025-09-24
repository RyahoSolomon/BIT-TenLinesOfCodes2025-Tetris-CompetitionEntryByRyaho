#pragma once
#include <graphics.h>

class State
{
public:
	enum StateName {home, game, end};
	// ����״̬
	virtual void on_enter() = 0;
	// �������
	virtual void input(const ExMessage& msg) = 0;
	// �˳�״̬
	virtual void on_exit() = 0;
	// ��������
	virtual void update(int delta) = 0;
	// ��Ⱦ
	virtual void draw() = 0;
};