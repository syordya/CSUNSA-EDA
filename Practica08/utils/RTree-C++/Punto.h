#pragma once
class Point
{
public:
	float x;
	float y;
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	bool esigual(Point b)
	{
		if (b.x == x && b.y == y) return true;
		return false;
	}
};