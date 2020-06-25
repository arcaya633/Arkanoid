#include "GameCore.h"
#include <cmath>

Game::Game() {
    window.setFramerateLimit(60);
    window.setTitle("Arkanoid");
    lifes = 3;
    state = 1;
    level = 1;
    score = 0;
    pointerPosition = 1;
    pointerSprite.setPosition(535, 555);
    isSoundOn = true;
    controllerType = true;
    isBonusInit = false;
    mergeBall();
    loadFiles();
    loadData();
    initLevel(level);
}

void Game::initUI() {
    window.clear(Color::Black);
    if (getState() == 1) { //In menu state
        window.draw(backgroundSprite);
        window.draw(menuSprite);
        window.draw(pointerSprite);
    }
    else if (getState() == 2) { //In game state
        scoreText.setPosition(0, 0);
        scoreText.setCharacterSize(70);
        window.draw(backgroundInGameSprite);
        window.draw(ball.shape);
        window.draw(platform.shape);
        window.draw(lifesText);
        window.draw(bonusSprite);
        window.draw(scoreText);
        window.draw(heartSprite);
        window.draw(levelText);
        pointerSprite.setPosition(535, 880);
        levelText.setString("Level: " + to_string(level));
        lifesText.setString(to_string(lifes) + "x");
        scoreText.setString("Score: " + to_string(score));
        if (!isBallMerged) ball.update();
        else mergeBall();
        for (auto& brick : bricks) window.draw(brick.shape);
        platform.update();
    }
    else if (getState() == 3) { //In victory screen
        scoreText.setPosition(950, 508);
        scoreText.setCharacterSize(90);
        scoreText.setString(to_string(score));
        highscoreText.setString(to_string(highscore));
        window.draw(backgroundSprite);
        window.draw(winScreenSprite);
        window.draw(pointerSprite);
        window.draw(scoreText);
        window.draw(highscoreText);
    }
    else if (getState() == 4) { //In lose screen
        scoreText.setPosition(950, 508);
        scoreText.setCharacterSize(90);
        window.draw(backgroundSprite);
        window.draw(loseScreenSprite);
        window.draw(pointerSprite);
        window.draw(scoreText);
        window.draw(highscoreText);
        scoreText.setString(to_string(score));
        highscoreText.setString(to_string(highscore));
    }
    else if (getState() == 5) { //In settings screen
        window.draw(backgroundSprite);
        window.draw(settingsSprite);
        window.draw(pointerSprite);
        window.draw(controllerText);
        window.draw(soundText);
        if (controllerType)
            controllerText.setString("Mouse");
        else
            controllerText.setString("Keyboard");

        if (isSoundOn)
            soundText.setString("On");
        else
            soundText.setString("Off");
    }
    window.display();
}

void Game::checkEvent() {
    srand(time(NULL));
    if (ball.y() > windowHeight) {
        lifes--;
        mergeBall();
    }

    checkCollision(platform, ball, isBallMerged);
    checkCollision(bonusSprite, platform);
    bonusSprite.move(0, 3.f);
    for (auto& brick : bricks) checkCollision(brick, ball);
    for (auto i = 0; i < bricks.size(); i++) {
        if (bricks[i].isDestroyed) {
            if (isSoundOn)
                breakBlipSound.play();
            if (bricks[i].shape.getFillColor() == Color::Blue) {
                score += 10;
                if (!isBonusInit) {
                    if (rand() % 100 > 0 && rand() % 100 <= 10) {
                        if (rand() % 100 > 0 && rand() % 100 <= 30) {
                            bonusSprite = heartSprite;
                            bonusSprite.setPosition(bricks[i].shape.getPosition().x, bricks[i].shape.getPosition().y);
                            isBonusInit = true;
                        }
                    }
                }
                bricks.erase(bricks.begin() + i);
            }
            else if (bricks[i].shape.getFillColor() == Color::Green) {
                score += 15;
                if (!isBonusInit) {
                    if (rand() % 100 > 0 && rand() % 100 <= 10) {
                        if (rand() % 100 > 0 && rand() % 100 <= 30) {
                            bonusSprite = heartSprite;
                            bonusSprite.setPosition(bricks[i].shape.getPosition().x, bricks[i].shape.getPosition().y);
                            isBonusInit = true;

                        }
                    }
                }
                bricks.erase(bricks.begin() + i);
            }
            else if (bricks[i].shape.getFillColor() == Color::Red) {
                score += 20;
                if (!isBonusInit) {
                    if (rand() % 100 > 0 && rand() % 100 <= 10) {
                        if (rand() % 100 > 0 && rand() % 100 <= 30) {
                            bonusSprite = heartSprite;
                            bonusSprite.setPosition(bricks[i].shape.getPosition().x, bricks[i].shape.getPosition().y);
                            isBonusInit = true;
                        }
                    }
                }
                bricks.erase(bricks.begin() + i);
            }
            else if (bricks[i].shape.getFillColor() == Color::Cyan) {
                bricks[i].shape.setFillColor(Color::Blue);
                score += 5;
            }
        }
    }

    while (window.pollEvent(event)) {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {

            window.close();
        }

        //MARK: Menu controller
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down && getState() == 1) {
            if (pointerPosition == 1) {
                pointerSprite.setPosition(535, 650);
                pointerPosition = 2;
                if (isSoundOn)
                    blipSound.play();
            }
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up && getState() == 1) {
            if (pointerPosition == 2) {
                pointerSprite.setPosition(535, 555);
                pointerPosition = 1;
                if (isSoundOn)
                    blipSound.play();
            }
        }

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && getState() == 1) {
            if (pointerPosition == 1) {
                state = 2;
                if (isSoundOn)
                    blipSound.play();
            }
            else if (pointerPosition == 2) {
                pointerPosition = 1;
                pointerSprite.setPosition(15, 295);
                state = 5;
                if (isSoundOn)
                    blipSound.play();
            }
        }

        //MARK: Game controller
        if (getState() == 2) {
            if (!controllerType) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left && platform.left() > 0) {
                    platform.velocity.x = -platformVelocity;
                    if (isBallMerged) ball.velocity.x = platform.velocity.x;
                }
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right && platform.right() < windowWidth) {
                    platform.velocity.x = platformVelocity;
                    if (isBallMerged) ball.velocity.x = platform.velocity.x;
                }
                else {
                    platform.velocity.x = 0;
                    if (isBallMerged) ball.velocity.x = 0;
                }
            }
            else {
                platform.velocity.x = 0;
                if (event.type == Event::MouseMoved)
                    platform.shape.setPosition(event.mouseMove.x, windowHeight - 50);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && getState() == 2 && isBallMerged) {
                ball.velocity.y = -ballVelocity;
                ball.velocity.x = 0;
                isBallMerged = false;
            }
        }
        //MARK: Lose screen controller
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down && getState() == 4) {
            if (pointerPosition == 1) {
                pointerSprite.setPosition(535, 980);
                pointerPosition = 2;
                if (isSoundOn)
                    blipSound.play();
            }
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up && getState() == 4) {
            if (pointerPosition == 2) {
                pointerSprite.setPosition(535, 880);
                pointerPosition = 1;
                if (isSoundOn)
                    blipSound.play();
            }
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && getState() == 4 && pointerPosition == 1) {
            restart();
            setState(2);
            if (isSoundOn)
                blipSound.play();
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && getState() == 4 && pointerPosition == 2) {
            pointerPosition = 1;
            pointerSprite.setPosition(535, 555);
            setState(1);
            restart();
            if (isSoundOn)
                blipSound.play();
        }
        //MARK: Win screen controller
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down && getState() == 3) {
            if (pointerPosition == 1) {
                pointerSprite.setPosition(535, 980);
                pointerPosition = 2;
                if (isSoundOn)
                    blipSound.play();
            }
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up && getState() == 3) {
            if (pointerPosition == 2) {
                pointerSprite.setPosition(535, 880);
                pointerPosition = 1;
                if (isSoundOn)
                    blipSound.play();
            }
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && getState() == 3) {
            if (pointerPosition == 1) {
                restart();
                setState(2);
                if (isSoundOn)
                    blipSound.play();
            }
            else if (pointerPosition == 2) {
                setState(1);
                if (isSoundOn)
                    blipSound.play();
                restart();
                pointerSprite.setPosition(535, 555);
                pointerPosition = 1;
            }
        }

        //MARK: Settings screen controller
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down && getState() == 5) {
            if (pointerPosition == 1) {
                pointerSprite.setPosition(15, 390);
                pointerPosition = 2;
                if (isSoundOn)
                    blipSound.play();
            }
            else if (pointerPosition == 2) {
                pointerPosition = 3;
                pointerSprite.setPosition(15, 765);
                if (isSoundOn)
                    blipSound.play();
            }
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up && getState() == 5) {
            if (pointerPosition == 3) {
                pointerPosition = 2;
                pointerSprite.setPosition(15, 390);
                if (isSoundOn)
                    blipSound.play();

            }
            else if (pointerPosition == 2) {
                pointerPosition = 1;
                pointerSprite.setPosition(15, 295);
                if (isSoundOn)
                    blipSound.play();
            }
        }

        if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right) && getState() == 5) {
            if (pointerPosition == 1) {
                controllerType = !controllerType;
                if (isSoundOn)
                    blipSound.play();
            }
            else if (pointerPosition == 2) {
                isSoundOn = !isSoundOn;
                if (isSoundOn)
                    blipSound.play();
            }
        }

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && getState() == 5) {
            if (pointerPosition == 3) {
                saveData();
                pointerPosition = 1;
                pointerSprite.setPosition(535, 555);
                setState(1);
                if (isSoundOn)
                    blipSound.play();
            }
        }
    }
}

void Game::loadFiles() {
    if (!backgroundInGameTexture.loadFromFile("res/images/background-ingame.png")) return;
    if (!backgroundTexture.loadFromFile("res/images/background.png")) return;
    if (!menuTexture.loadFromFile("res/images/main.png")) return;
    if (!winScreenTexture.loadFromFile("res/images/winscreen.png")) return;
    if (!loseScreenTexture.loadFromFile("res/images/losescreen.png")) return;
    if (!pointerTexture.loadFromFile("res/images/pointer.png")) return;
    if (!heartTexture.loadFromFile("res/images/heart.png")) return;
    if (!settingsTexture.loadFromFile("res/images/settings.png")) return;

    if (!font.loadFromFile("res/fonts/Baloo.ttf")) return;

    if (!blipSoundBuffer.loadFromFile("res/sounds/blip.wav")) return;
    if (!breakBlipSoundBuffer.loadFromFile("res/sounds/breakBlip.wav")) return;

    backgroundInGameSprite.setTexture(backgroundInGameTexture);
    backgroundSprite.setTexture(backgroundTexture);
    menuSprite.setTexture(menuTexture);
    winScreenSprite.setTexture(winScreenTexture);
    loseScreenSprite.setTexture(loseScreenTexture);
    pointerSprite.setTexture(pointerTexture);
    heartSprite.setTexture(heartTexture);
    heartSprite.setPosition(1500, 15);
    settingsSprite.setTexture(settingsTexture);

    blipSound.setBuffer(blipSoundBuffer);
    breakBlipSound.setBuffer(breakBlipSoundBuffer);

    lifesText.setFont(font);
    lifesText.setCharacterSize(70);
    lifesText.setPosition(1400, 0);
    scoreText.setFont(font);
    scoreText.setCharacterSize(70);
    scoreText.setPosition(0, 0);
    highscoreText.setFont(font);
    highscoreText.setCharacterSize(90);
    highscoreText.setPosition(950, 608);
    levelText.setFont(font);
    levelText.setCharacterSize(70);
    levelText.setPosition(windowWidth / 2 - 140, 0);
    controllerText.setFont(font);
    controllerText.setCharacterSize(80);
    controllerText.setPosition(590, 260);
    soundText.setFont(font);
    soundText.setCharacterSize(80);
    soundText.setPosition(590, 360);

}

void Game::mergeBall() {
    ball.shape.setPosition(platform.x(), platform.y() - 45);
    ball.velocity.x = 0;
    ball.velocity.y = 0;
    isBallMerged = true;
}

void Game::checkState() {
    if (lifes == 0) {
        findHighscore();
        saveData();
        setState(4);
    }

    if (bricks.empty()) {
        if (level != 4) {
            level++;
            initLevel(level);
        }
        else {
            findHighscore();
            saveData();
            setState(3);
        }
    }
}

int Game::getState() {
    return state;
}

void Game::setState(int state) {
    Game::state = state;
}

template<class T1, class T2> bool Game::isInteracting(T1& object1, T2& object2) {
    return object1.right() > object2.left() && object1.left() < object2.right() && object1.bottom() > object2.top() && object1.top() < object2.bottom();
}

void Game::checkCollision(Platform& platform, Ball& ball, bool isBallMerged) {
    if (!isBallMerged) {
        if (!isInteracting(platform, ball)) return;
        else ball.velocity.y = -ballVelocity;
        if (ball.x() <= platform.x() * 2.f / 5.f) ball.velocity.x = -ballVelocity;
        else if (ball.x() < platform.x() - 6.f && ball.x() > platform.x() / 2.f) ball.velocity.x = -ballVelocity / 2;
        else if (ball.x() > platform.x() + 6.f && ball.x() <

            platform.x() * 2.f) ball.velocity.x = ballVelocity / 2;
        else if (ball.x() >= platform.x() * 2.f / 5.f * 4.f) ball.velocity.x = ballVelocity;
        else ball.velocity.x = 0;
    }
}

void Game::checkCollision(Brick& brick, Ball& ball) {
    if (!isInteracting(brick, ball)) return;
    if (brick.shape.getFillColor() != Color::Cyan)
        brick.isDestroyed = true;
    else brick.shape.setFillColor(Color::Blue);

    float overlapLeft{ ball.right() - brick.left() };
    float overlapRight{ brick.right() - ball.left() };
    float overlapTop{ ball.bottom() - brick.top() };
    float overlapBottom{ brick.bottom() - ball.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
        ball.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
    else
        ball.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}

void Game::checkCollision(Sprite& bonus, Platform& platform) {
    if (bonus.getPosition().x < platform.right() && bonus.getPosition().x > platform.left() && bonus.getPosition().y > platform.top() && bonus.getPosition().y < platform.bottom()) {
        bonus.setPosition(-100, -100);
        isBonusInit = false;
        Game::lifes++;
    }
    else if (bonus.getPosition().y > windowHeight) isBonusInit = false;
}

void Game::initLevel(int level) {
    mergeBall();
    if (level == 1) {
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 6 / 3; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) - 58, (iY + 2) * (brickHeight + 3) + 70, Color::Red);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 6 / 3; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) - 58, (iY + 2) * (brickHeight + 3) + 156, Color::Green);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 6 / 3; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) - 58, (iY + 2) * (brickHeight + 3) + 244, Color::Blue);
            }
        }
    }
    else if (level == 2) {
        for (int iX = 0; iX < 4; iX++) {
            for (int iY = 0; iY < 4; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) - 58, (iY + 2) * (brickHeight + 3) + 70, Color::Red);
            }
        }
        for (int iX = 0; iX < 4; iX++) {
            for (int iY = 0; iY < 4; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) - 58, (iY + 2) * (brickHeight + 3) + 244, Color::Green);
            }
        }
        for (int iX = 0; iX < 4; iX++) {
            for (int iY = 0; iY < 4; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) - 58, (iY + 2) * (brickHeight + 3) + 418, Color::Blue);
            }
        }
        for (int iX = 0; iX < 4; iX++) {
            for (int iY = 0; iY < 4; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) + 1044, (iY + 2) * (brickHeight + 3) + 70, Color::Red);
            }
        }
        for (int iX = 0; iX < 4; iX++) {
            for (int iY = 0; iY < 4; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) + 1044, (iY + 2) * (brickHeight + 3) + 244, Color::Green);
            }
        }
        for (int iX = 0; iX < 4; iX++) {
            for (int iY = 0; iY < 4; iY++) {
                bricks.emplace_back((iX + 1) * (brickWidth + 3) + 1044, (iY + 2) * (brickHeight + 3) + 418, Color::Blue);
            }
        }
    }
    else if (level == 3) {
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 1; iY++) {
                if (iX == 6) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 2) * (brickHeight + 3) + 70, Color::Cyan);
                else bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 2) * (brickHeight + 3) + 70, Color::Red);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 1; iY++) {
                if (iX == 5 || iX == 7) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 3) * (brickHeight + 3) + 70, Color::Cyan);
                else if (iX == 6) continue;
                else bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 3) * (brickHeight + 3) + 70, Color::Red);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 1; iY++) {
                if (iX == 4 || iX == 8) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 4) * (brickHeight + 3) + 70, Color::Cyan);
                else if (iX >= 5 && iX <= 7) continue;
                else bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 4) * (brickHeight + 3) + 70, Color::Green);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 1; iY++) {
                if (iX == 3 || iX == 9) bricks.emplace_back((iX + 1) * (brickWidth + 3)

                    - 50, (iY + 5) * (brickHeight + 3) + 70, Color::Cyan);
                else if (iX >= 4 && iX <= 8) continue;
                else bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 5) * (brickHeight + 3) + 70, Color::Green);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 1; iY++) {
                if (iX == 2 || iX == 10) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 6) * (brickHeight + 3) + 70, Color::Cyan);
                else if (iX >= 3 && iX <= 9) continue;
                else bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 6) * (brickHeight + 3) + 70, Color::Blue);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 1; iY++) {
                if (iX == 1 || iX == 11) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 7) * (brickHeight + 3) + 70, Color::Cyan);
                else if (iX >= 2 && iX <= 10) continue;
                else {
                    if (iX == 0 || iX == 12) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 8) * (brickHeight + 3) + 70, Color::Cyan);
                    bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 7) * (brickHeight + 3) + 70, Color::Blue);
                }
            }
        }
    }
    else if (level == 4) {
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 1; iY++) {
                if (iX >= 2 && iX <= 10) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 7) * (brickHeight + 3) + 70, Color::Cyan);
                else if (iX >= 2 && iX <= 10) continue;
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 3; iY++) {
                if (iX >= 3 && iX <= 9 && iY != 1) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 6) * (brickHeight + 3) + 70, Color::Red);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 5; iY++) {
                if (iX >= 4 && iX <= 8 && (iY == 0 || iY == 4)) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 5) * (brickHeight + 3) + 70, Color::Green);
            }
        }
        for (int iX = 0; iX < 13; iX++) {
            for (int iY = 0; iY < 7; iY++) {
                if (iX >= 5 && iX <= 7 && (iY == 0 || iY == 6)) bricks.emplace_back((iX + 1) * (brickWidth + 3) - 50, (iY + 4) * (brickHeight + 3) + 70, Color::Blue);
            }
        }
    }
}

void Game::restart() {
    score = 0;
    lifes = 3;
    level = 1;
    bricks.clear();
    initLevel(level);
    platform.shape.setPosition(windowWidth / 2, windowHeight - 50);
}

void Game::loadData() {
    string scoreString;
    ifstream scoreFile("score.txt");
    scoreFile >> scoreString;
    stringstream scoreStream(scoreString);
    scoreStream >> highscore;
    scoreFile.close();

    string settingsString;
    ifstream settingsFile("settings.txt");
    getline(settingsFile, settingsString);
    if (settingsString == "1")
        controllerType = true;
    else
        controllerType = false;

    getline(settingsFile, settingsString);
    if (settingsString == "1")
        isSoundOn = true;
    else
        isSoundOn = false;
    settingsFile.close();
}

void Game::saveData() {
    // ofstream scoreFile("/Users/rykvlv/MyTona/Arkanoid/score.txt");
    ofstream scoreFile("score.txt");
    scoreFile << to_string(highscore);
    scoreFile.close();

    ofstream settingsFile("settings.txt");
    settingsFile << controllerType << endl;
    settingsFile << isSoundOn << endl;
}

void Game::findHighscore() {
    if (highscore < score)
        highscore = score;
}