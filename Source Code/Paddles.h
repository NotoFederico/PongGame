#pragma once
#include <SDL.h>
#include "Screen.h"
#include "Field.h"

class Paddles : public Field
{
public:
	SDL_Rect left;
	SDL_Rect right;
	int speed;
	int xOffset;
	int width;
	int height;

public:
	Paddles();
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void draw(void);
	void setSpeed(int speed);
	void serve(void);
	void checkPlayableArea(void);
	~Paddles();
};

