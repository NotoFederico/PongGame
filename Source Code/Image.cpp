#include "Image.h"
#include <iostream>

using namespace std;
Image::Image()
{
	this->path = NULL;
	this->container = { NULL };
}

void Image::draw(void)
{
	SDL_Surface* image = IMG_Load(this->path);
	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(Screen::getInstance()->renderer, image);
	SDL_RenderCopy(Screen::getInstance()->renderer, imageTexture, NULL, &(this->container));
	SDL_DestroyTexture(imageTexture);
	SDL_FreeSurface(image);
}

void Image::setContainer(int x, int y, int w, int h)
{
	this->container = { x,y,w,h };
}

void Image::centerX(int y, int w, int h)
{
	this->container.h = h;
	this->container.w = w;
	this->container.y = y;
	this->container.x = Screen::getInstance()->defaultWidth / 2 - this->container.w / 2;
}

void Image::centerY(int x, int w, int h) {
	this->container.h = h;
	this->container.w = w;
	this->container.x = x;
	this->container.y = Screen::getInstance()->defaultHeight / 2 - this->container.h / 2;
}

void Image::centerXY(int w, int h) {

	this->container.h = h;
	this->container.w = w;
	this->container.x = Screen::getInstance()->defaultWidth / 2 - this->container.w / 2;
	this->container.y = Screen::getInstance()->defaultHeight / 2 - this->container.h / 2;
}

void Image::fill(void) {
	this->container.x = 0;
	this->container.y = 0;
	this->container.w = Screen::getInstance()->defaultWidth;
	this->container.h = Screen::getInstance()->defaultHeight;
}

Image::~Image()
{
	cout << "Destroying image object" << endl;
}
