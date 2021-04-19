#include "Field.h"
#include "Screen.h"
#include <iostream>

Field::Field() {
	//init variables
	this->upLeftHalf = this->upRightHalf = this->downLeftHalf = this->downRightHalf = { 0 };
	this->left = this->right = this->dashedLine = { 0 };

	//set field parameters
	this->xOffset = 40;
	this->yOffset = 200;
	this->thickness = 10;
	this->height = Screen::getInstance()->defaultHeight;
	this->width = Screen::getInstance()->defaultWidth - 2 * this->xOffset;

	//set field coordinates
	this->upLeftHalf.x = this->xOffset;
	this->upLeftHalf.y = this->yOffset;
	this->upLeftHalf.w = Screen::getInstance()->defaultWidth / 2 - this->xOffset;
	this->upLeftHalf.h = this->thickness;

	this->upRightHalf.x = this->upLeftHalf.x + this->upLeftHalf.w;
	this->upRightHalf.y = this->yOffset;
	this->upRightHalf.w = this->upLeftHalf.w;
	this->upRightHalf.h = this->thickness;

	this->downLeftHalf.x = this->xOffset;
	this->downLeftHalf.y = this->height - this->thickness - this->xOffset;
	this->downLeftHalf.w = this->upLeftHalf.w;
	this->downLeftHalf.h = this->thickness;

	this->downRightHalf.x = this->downLeftHalf.x + this->downLeftHalf.w;
	this->downRightHalf.y = this->downLeftHalf.y;
	this->downRightHalf.w = this->downLeftHalf.w;
	this->downRightHalf.h = this->thickness;

	this->left.x = this->xOffset;
	this->left.y = this->yOffset;
	this->left.w = this->thickness;
	this->left.h = this->height - this->yOffset - this->xOffset;

	this->right.x = this->width + this->xOffset - this->thickness;
	this->right.y = this->yOffset;
	this->right.w = this->thickness;
	this->right.h = this->height - this->yOffset - this->xOffset;

	this->dashedLine.w = 2 * this->thickness;
	this->dashedLine.h = this->thickness;
	this->dashedLine.y = this->yOffset + this->thickness;
	this->dashedLine.x = Screen::getInstance()->defaultWidth / 2 - this->dashedLine.w / 2;

	this->upperLimit = this->yOffset + this->thickness;
	this->lowerLimit = this->height - this->thickness - this->xOffset;

	std::cout << "Upper limit : " << this->upperLimit << std::endl;
	std::cout << "Lower limit : " << this->lowerLimit << std::endl;
}

void Field::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(Screen::getInstance()->renderer, r, g, b, a);
}

void Field::draw(void) {
	setColor(0x69, 0x69, 0x69, 0xFF);
	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->upLeftHalf));
	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->downLeftHalf));
	setColor(0xFF, 0xD0, 0x00, 0xFF);
	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->upRightHalf));
	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->downRightHalf));
	setColor(0x69, 0x69, 0x69, 0xFF);
	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->left));
	setColor(0xFF, 0xD0, 0x00, 0xFF);
	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->right));
	//La altura del interior de la cancha es de 450 px
	setColor(0x69, 0x69, 0x69, 0xFF);
	this->dashedLine.y = this->yOffset + this->thickness + this->thickness / 2;
	for (int i = 0; i < (this->downRightHalf.y - this->yOffset - this->thickness) / (2 * this->thickness); i++) {
		SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->dashedLine));
		this->dashedLine.y += 2 * this->thickness; //So actually a line with holes in it
	}
}

Field::~Field() {
}
