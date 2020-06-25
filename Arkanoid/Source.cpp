#include "GameCore.h"

int main() {
	Game game;
	while (game.window.isOpen()) {
		game.initUI();
		game.checkEvent();
		game.checkState();
	}

	return EXIT_SUCCESS;
}