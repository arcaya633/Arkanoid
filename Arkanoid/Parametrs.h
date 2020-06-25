#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

const int windowWidth{ 1600 }, windowHeight{ 1200 };
const string gameTitle{ "Arkanoid" };
const float ballRadius{ 20.f }, ballVelocity{ 16.f };
const float platformWidth{ 240.f }, platformHeight{ 40.f }, platformVelocity{ 34.f };

const float brickWidth{ 120.f }, brickHeight{ 40.f };