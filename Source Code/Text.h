#pragma once
#include <SDL.h>
#include "Font.h"
class Text
{
public:

	SDL_Color color;
	SDL_Rect container;
	TTF_Font* font;
	const char* text;

public:
	Text();
	void setContainer(int x, int y, int w, int h);
	void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void centerX(int y, int w, int h);
	void centerY(int x, int w, int h);
	void centerXY(int w, int h);
	void setFont(TTF_Font* font);
	void write(void);
	~Text();
};

