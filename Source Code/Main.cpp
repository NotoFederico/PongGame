#include "Header.h"
#include "Menu.h"
#include "Game.h"
#include "Instructions.h"
#include <iostream>

using namespace std;


int main(int argc, char* args[]) {
	bool running = true;
	int state = 0;
	cout << "-Application running-" << endl;
	Screen::getInstance();
	Music::getInstance();
	Menu menu;
	Game game;
	Instructions howToPlay;

	while (running) {
		switch (state) {
		case MENU:
			state = menu.run();
			break;
		case PLAY:
			state = game.run();
			break;
		case HOWTOPLAY:
			state = howToPlay.run();
			break;
		case QUIT:
			cout << "-Application terminate-" << endl;
			running = false;
			SDL_Quit();
			break;
		}
	}
	//menu.~Menu(); Se origina una excepcion...
	//game.~Game();
	return 0;
}

