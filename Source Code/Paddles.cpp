#include "Paddles.h"


Paddles::Paddles()
{
	//init values
	this->left = { 0 };
	this->right = { 0 };

	this->width = 16;
	this->height = 120;
	this->xOffset = 20;

	this->left.w = this->right.w = this->width;
	this->left.h = this->right.h = this->height;

	//set paddle coordinates
	this->left.x = Field::xOffset + Field::thickness + this->xOffset;
	this->left.y = Field::yOffset + Field::thickness + 10;
	this->right.x = (Field::xOffset + Field::width) - Field::thickness - this->width - this->xOffset;
	this->right.y = Field::yOffset + Field::thickness + 10;

	this->speed = 5;

}

void Paddles::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(Screen::getInstance()->renderer, r, g, b, a);
}

void Paddles::setSpeed(int speed)
{
	this->speed = speed;
}

void Paddles::serve(void)
{
	this->left.y = this->right.y = (Field::upperLimit + Field::lowerLimit) / 2 - this->left.h / 2;
}

void Paddles::checkPlayableArea(void)
{
	if (this->left.y < Field::upperLimit) {
		this->left.y = Field::upperLimit;
	}
	else if (((this->left.y + this->height) > Field::lowerLimit))
		this->left.y = Field::lowerLimit - this->height;

	if (this->right.y < Field::upperLimit) {
		this->right.y = Field::upperLimit;
	}
	else if (((this->right.y + this->height) > Field::lowerLimit))
		this->right.y = Field::lowerLimit - this->height;

}

void Paddles::draw(void) {
	setColor(0x69, 0x69, 0x69, 0xFF);
	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->left));
	setColor(0xFF, 0xD0, 0x00, 0xFF);
	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->right));
}

Paddles::~Paddles()
{
}
