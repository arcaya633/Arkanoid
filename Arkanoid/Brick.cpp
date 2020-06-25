#include "Brick.h"

Brick::Brick(float mX, float mY, Color color) {
	Brick::shape.setPosition(mX, mY);
	Brick::shape.setSize({ brickWidth, brickHeight });
	Brick::shape.setFillColor(color);
	Brick::shape.setOrigin(brickWidth / 2.f, brickHeight / 2.f);
}
Brick::Brick() {

}

float Brick::x() {
	return Brick::shape.getPosition().x;
}
float Brick::y() {
	return Brick::shape.getPosition().y;
}
float Brick::left() {
	return x() - shape.getSize().x / 2.f;
}
float Brick::right() {
	return x() + shape.getSize().x / 2.f;
}
float Brick::top() {
	return y() - shape.getSize().y / 2.f;
}
float Brick::bottom() {
	return y() + shape.getSize().y / 2.f;
}