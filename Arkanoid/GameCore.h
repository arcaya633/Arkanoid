#pragma once
#include "Parametrs.h"
#include "Ball.h"
#include "Platform.h"
#include "Brick.h"
#include <fstream>
#include <sstream>

class Game {
public:
	Game();
	void initUI();
	void checkEvent();
	void checkState();
	RenderWindow window = { VideoMode(windowWidth, windowHeight), gameTitle };

private:
	void initLevel(int level);
	void loadFiles();
	void mergeBall();
	void restart();
	void loadData();
	void saveData();
	void findHighscore();
	int getState();
	void setState(int state);
	template<class T1, class T2> bool isInteracting(T1&, T2&);
	void checkCollision(Platform& platform, Ball& ball, bool isBallMerged);
	void checkCollision(Brick& brick, Ball& ball);
	void checkCollision(Sprite& bonus, Platform& platform);

	Event event;

	Ball ball;
	Platform platform;

	Text lifesText;
	Text scoreText;
	Text highscoreText;
	Text levelText;
	Text controllerText;
	Text soundText;

	Font font;

	Texture backgroundInGameTexture;
	Texture backgroundTexture;
	Texture menuTexture;
	Texture winScreenTexture;
	Texture loseScreenTexture;
	Texture pointerTexture;
	Texture heartTexture;
	Texture settingsTexture;

	Sprite backgroundInGameSprite;
	Sprite backgroundSprite;
	Sprite menuSprite;
	Sprite winScreenSprite;
	Sprite loseScreenSprite;
	Sprite pointerSprite;
	Sprite heartSprite;
	Sprite bonusSprite;
	Sprite settingsSprite;

	SoundBuffer blipSoundBuffer;
	SoundBuffer breakBlipSoundBuffer;

	Sound blipSound;
	Sound breakBlipSound;

	vector<Brick> bricks;
	int state;
	int lifes;
	int pointerPosition;
	int level;
	int score;
	int highscore;
	bool isSoundOn;
	bool controllerType;
	bool isBallMerged;
	bool isBonusInit;
};