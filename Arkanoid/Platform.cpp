#include "Platform.h"

Platform::Platform() {
	Platform::shape.setPosition(windowWidth / 2, windowHeight - 50);
	Platform::shape.setFillColor(Color::Black);
	Platform::shape.setSize({ platformWidth, platformHeight });
	Platform::shape.setOrigin(platformWidth / 2, platformHeight / 2);
	Platform::velocity = { 0, 0 };
}

void Platform::update() {
	Platform::shape.move(velocity);
}

float Platform::x() {
	return Platform::shape.getPosition().x;
}
float Platform::y() {
	return Platform::shape.getPosition().y;
}
float Platform::left() {
	return x() - shape.getSize().x / 2;
}
float Platform::right() {
	return x() + shape.getSize().x / 2;
}
float Platform::top() {
	return y() - shape.getSize().y / 2;
}
float Platform::bottom() {
	return y() + shape.getSize().y / 2;
}