#include "Ball.h"

Ball::Ball() {
	Ball::shape.setRadius(ballRadius);
	Ball::shape.setFillColor(Color::Yellow);
	Ball::shape.setOrigin(ballRadius, ballRadius);
}

void Ball::update() {
	shape.move(velocity);
	if (left() < 0) velocity.x = ballVelocity;
	if (right() > windowWidth) velocity.x = -ballVelocity;
	if (bottom() < 130) velocity.y = ballVelocity;
}

float Ball::x() {
	return Ball::shape.getPosition().x;
}

float Ball::y() {
	return Ball::shape.getPosition().y;
}

float Ball::left() {
	return x() - ballRadius;
}

float Ball::right() {
	return x() + ballRadius;
}

float Ball::top() {
	return y() - ballRadius;
}

float Ball::bottom() {
	return y() + ballRadius;
}