#include "Screen.h"
#include <iostream>
#include <SDL.h>


using namespace std;

Screen* Screen::instance = 0;

Screen* Screen::getInstance()
{
	if (instance == 0) {
		instance = new Screen(1280, 720);
	}
	return instance;
}

Screen::Screen(int width, int height)
{
	this->defaultHeight = height;
	this->defaultWidth = width;
	this->renderer = NULL;
	this->window = NULL;

	this->leftHalf.x = 0;
	this->leftHalf.y = 0;
	this->leftHalf.w = this->defaultWidth / 2;
	this->leftHalf.h = this->defaultHeight;

	this->rightHalf.x = this->defaultWidth / 2;
	this->rightHalf.y = 0;
	this->rightHalf.w = this->defaultWidth / 2;
	this->rightHalf.h = this->defaultHeight;

	this->blackRect.x = this->blackRect.y = 0;
	this->blackRect.w = this->defaultWidth;
	this->blackRect.h = this->defaultHeight;

	cout << "Initialization of all SDL2 modules" << endl;
	SDL_Init(SDL_INIT_EVERYTHING) == 0 ? cout << "SDL2 Init OK" << endl : cout << "SDL2 Init ERROR = " << SDL_GetError() << endl;


	cout << "Creating window of " << this->defaultWidth << "x" << this->defaultHeight << " and the renderer" << endl;
	if (SDL_CreateWindowAndRenderer(this->defaultWidth, this->defaultHeight, SDL_WINDOW_ALLOW_HIGHDPI, &(this->window), &(this->renderer)) == 0)
		cout << "Renderer create OK \nWindow create OK" << endl;
	else
		cout << "Renderer create ERROR \nWindow create ERROR" << endl;

	SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

	cout << "-Initialization of extra modules-" << endl;

	//Initialize SDL TTF 
	TTF_Init() == 0 ? cout << "TTF module init OK" : cout << " TTF module ERROR"; cout << endl;

	//Initialize SDL IMAGE 
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
		cout << "IMAGE module init OK [ PNG and JPG ONLY]" << endl;
	else
		cout << "IMAGE module ERROR" << endl;

	//Initialize SDL MIXER 
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == 0 ? std::cout << "MIXER module init OK" : std::cout << "MIXER module ERROR";
	std::cout << std::endl;

}

void Screen::fullscreen(void)
{
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_RenderPresent(this->renderer);
}

void Screen::windowed(void)
{
	SDL_SetWindowFullscreen(window, 0);
	SDL_RenderPresent(this->renderer);
}

void Screen::setWindowTitle(const char* title)
{
	SDL_SetWindowTitle(this->window, title);
}


void Screen::gameBackgroundColor(void) {
	SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xD0, 0x00, 0xFF);
	SDL_RenderFillRect(this->renderer, &(this->leftHalf));
	SDL_SetRenderDrawColor(this->renderer, 0x69, 0x69, 0x69, 0xFF);
	SDL_RenderFillRect(this->renderer, &(this->rightHalf));
}

void Screen::instructBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
	SDL_RenderClear(this->renderer);
}

void Screen::blackRectAlpha(uint8_t a)
{
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 10);
	SDL_RenderFillRect(this->renderer, &(this->blackRect));
}

void Screen::menuBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
	SDL_RenderClear(this->renderer);
}

void Screen::hide(void)
{
	SDL_HideWindow(this->window);
}

void Screen::show(void)
{
	SDL_ShowWindow(this->window);
}

void Screen::raise(void)
{
	SDL_RaiseWindow(this->window);
}

Screen::~Screen()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}
