#pragma once
#include "Header.h"

class Instructions : public Interface
{
public:

	Image homeButton;
	//Image keyboard;
	SDL_Event event;
	SDL_Keysym keysym;
	SDL_Point testPoint;
	Text title;
	Text line1;
	Text line2;
	Text line3;
	Text line4;
	Text line5;
	Text line6;
	Text rightControls;
	int state;

public:
	Instructions();
	void input(void);
	void update(void);
	void render(void);
	int run(void);
	~Instructions();
};

