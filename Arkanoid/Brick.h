#pragma once
#include "Parametrs.h"

struct Brick {
	Brick(float mX, float mY, Color color);
	Brick();
	RectangleShape shape;
	bool isDestroyed{ false };
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};