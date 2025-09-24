#include "class_vector.h"

Vector::Vector(int x, int y) : x(x), y(y) {}

bool Vector::operator==(Vector& b)
{
	return (x == b.x && y == b.y);
}

Vector Vector::operator+(Vector& b)
{
	return Vector(x + b.x, y + b.y);
}

Vector Vector::operator-(Vector& b)
{
	return Vector(x - b.x, y - b.y);
}

void Vector::operator+=(Vector& b)
{
	x += b.x;
	y += b.y;
}

void Vector::operator-=(Vector& b)
{
	x -= b.x;
	y -= b.y;
}

void Vector::operator=(Vector& b)
{
	x = b.x;
	y = b.y;
}
