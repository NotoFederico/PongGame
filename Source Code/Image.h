#pragma once
#include "Screen.h"
#include <SDL.h>
#include <SDL_image.h>
class Image
{
public:
	const char* path;
	SDL_Rect container;
public:
	Image();
	void draw(void);
	void setContainer(int x, int y, int w, int h);
	void centerX(int y, int w, int h);
	void centerY(int x, int w, int h);
	void centerXY(int w, int h);
	void fill(void);
	~Image();
};

