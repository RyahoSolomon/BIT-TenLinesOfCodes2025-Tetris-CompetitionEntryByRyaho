#pragma once
class Vector
{
public:
	int x = 0, y = 0;
	
public:
	Vector() = default;
	Vector(int x, int y);

	bool operator==(Vector& b);

	Vector operator+(Vector& b);

	Vector operator-(Vector& b);

	void operator+=(Vector& b);

	void operator-=(Vector& b);

	void operator=(Vector& b);
};