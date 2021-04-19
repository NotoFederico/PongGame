#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class Screen
{
public:
	int defaultWidth;
	int defaultHeight;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Rect leftHalf;
	SDL_Rect rightHalf;
	SDL_Rect blackRect;
public:
	static Screen* getInstance();
	void fullscreen(void);
	void windowed(void);
	void setWindowTitle(const char* title);
	void menuBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void gameBackgroundColor(void);
	void instructBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void blackRectAlpha(uint8_t a);
	void hide(void);
	void show(void);
	void raise(void);
	~Screen();

private:
	static Screen* instance;
	Screen(int width, int height);
};

