#pragma once
#pragma once
#include "Parametrs.h"

struct Platform {
	Platform();
	RectangleShape shape;
	Vector2f velocity;

	//Updating status of platform, changing velocity
	void update();

	//Getting coordinats of platform
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};