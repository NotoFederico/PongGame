#include "Ball.h"

Ball::Ball()
{
	this->ball.h = 14;
	this->ball.w = 14;
	this->ball.x = Screen::getInstance()->defaultWidth / 2 - this->ball.w / 2;
	this->ball.y = (Field::upperLimit + Field::lowerLimit) / 2 - this->ball.h / 2;
	this->direction = 1;
	this->speed = 1;
	this->dx = 1;
	this->dy = 0;
}

void Ball::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(Screen::getInstance()->renderer, r, g, b, a);
}

void Ball::draw()
{
	if (this->ball.x < Screen::getInstance()->defaultWidth / 2)
		setColor(0x69, 0x69, 0x69, 0xFF);
	else
		setColor(0xFF, 0xD0, 0x00, 0xFF);

	SDL_RenderFillRect(Screen::getInstance()->renderer, &(this->ball));
}

void Ball::serve()
{
	this->ball.x = Screen::getInstance()->defaultWidth / 2 - this->ball.w / 2;
	this->ball.y = (Field::upperLimit + Field::lowerLimit) / 2 - this->ball.h / 2;
	this->dy = 0;
	this->dx = 4;
	this->speed = 4;
}


void Ball::setSpeed(int speed)
{
	this->speed = speed;
}

Ball::~Ball()
{

}

