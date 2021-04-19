#pragma once
#include <SDL.h>
#include "Screen.h"
#include "Field.h"
class Ball : public Field
{
public:
	SDL_Rect ball;
	int speed;
	int direction;
	int dx;
	int dy;
public:
	Ball();
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void draw(void);
	void serve();
	void setSpeed(int speed);
	~Ball();
};

