#pragma once
#include "Header.h"

class Menu : public Interface
{
public:
	SDL_Event event;
	SDL_Keysym keysym;
	Text play;
	Text quit;
	Text instructions;
	Image fox;
	Image background;
	int fullscreen;
	int menuOption;
	int state;
public:
	Menu();
	void input(void);
	void update(void);
	void render(void);
	int run(void);
	~Menu();
};

