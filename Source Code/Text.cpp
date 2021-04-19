#include "Text.h"
#include "Screen.h"
#include <iostream>

using namespace std;

Text::Text() {
	this->text = NULL;
	this->color = { NULL };
	this->container = { NULL };
	this->font = { NULL };
}


void Text::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	this->color = { r, g, b, a };
}

void Text::write(void) {

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->font, this->text, this->color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Screen::getInstance()->renderer, surfaceMessage);
	SDL_RenderCopy(Screen::getInstance()->renderer, Message, NULL, &(this->container));
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

Text::~Text() {
	cout << "Destroying text object" << endl;
}

void Text::setContainer(int x, int y, int w, int h)
{
	this->container = { x, y, w , h };
}

void Text::setFont(TTF_Font* font)
{
	this->font = font;
}

void Text::centerX(int y, int w, int h)
{
	this->container.h = h;
	this->container.w = w;
	this->container.y = y;
	this->container.x = Screen::getInstance()->defaultWidth / 2 - this->container.w / 2;
}

void Text::centerY(int x, int w, int h) {
	this->container.h = h;
	this->container.w = w;
	this->container.x = x;
	this->container.y = Screen::getInstance()->defaultHeight / 2 - this->container.h / 2;
}

void Text::centerXY(int w, int h) {

	this->container.h = h;
	this->container.w = w;
	this->container.x = Screen::getInstance()->defaultWidth / 2 - this->container.w / 2;
	this->container.y = Screen::getInstance()->defaultHeight / 2 - this->container.h / 2;
}
