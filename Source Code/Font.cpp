#include "Font.h"
#include <iostream>

Font* Font::instance = 0;

Font* Font::getInstance()
{
	if (instance == 0) {
		instance = new Font();
	}
	return instance;
}

Font::Font()
{
	this->addFont("fonts/Peepo.ttf", 200);
	this->addFont("fonts/Helvetica.ttf", 200);
	this->addFont("fonts/FreeSans.ttf", 200);
	this->addFont("fonts/ExpressaBold.ttf", 200);

}

void Font::addFont(const char* fontPath, int fontSize) {
	this->fonts[fontPath] = make_pair(TTF_OpenFont(fontPath, fontSize), fontSize);
	if (this->fonts[fontPath].first != NULL)
		cout << "Font " << fontPath << " added and opened OK with font size = " << this->fonts[fontPath].second << endl;
	else
		cout << "Font " << fontPath << "opening ERROR" << endl;
}

Font::~Font()
{
}
