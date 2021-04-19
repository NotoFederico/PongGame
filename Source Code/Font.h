#pragma once
#include <SDL_ttf.h>
#include <map>
using namespace std;

class Font
{
public:
	std::map<const char*, std::pair<TTF_Font*, int> > fonts;
public:
	static Font* getInstance();
	void addFont(const char* fontPath, int fontSize);
	~Font();
private:
	static Font* instance;
	Font();
};

