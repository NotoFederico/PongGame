#pragma once
#include <SDL.h>

class Field
{
public:
	SDL_Rect upLeftHalf;
	SDL_Rect upRightHalf;
	SDL_Rect downLeftHalf;
	SDL_Rect downRightHalf;
	SDL_Rect left;
	SDL_Rect right;
	SDL_Rect dashedLine;
	int xOffset;
	int yOffset;
	int width;
	int height;
	int thickness;
	int upperLimit;
	int lowerLimit;

public:
	Field();
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void draw(void);
	~Field();
};

