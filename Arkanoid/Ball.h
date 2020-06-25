#pragma once
#include "Parametrs.h"

struct Ball
{
	Ball();
	CircleShape shape;
	Vector2f velocity;

	void update();

	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};

