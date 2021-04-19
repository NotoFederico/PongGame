#include "Instructions.h"
#include <iostream>

using namespace std;

Instructions::Instructions()
{
	this->state = HOWTOPLAY;
	//Home button
	this->homeButton.setContainer(1200, 50, 40, 40);
	this->homeButton.path = "images/home.png";
	//title
	this->title.text = "How to Play";
	this->title.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->title.setColor(0xFF, 0xD0, 0x00, 0xFF);
	this->title.centerX(30, 300, 100);
	//line1
	this->line1.text = "                          Rules                          ";
	this->line1.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->line1.setColor(0xFF, 0xFF, 0xFF, 0xFF);
	this->line1.centerX(150, 840, 80);
	//line2
	this->line2.text = "The first player to score 5 points wins!";
	this->line2.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->line2.setColor(0xFF, 0xD0, 0x00, 0xFF);
	this->line2.centerX(230, 600, 80);
	//line3
	this->line3.text = "                     Controls                     ";
	this->line3.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->line3.setColor(0xFF, 0xFF, 0xFF, 0xFF);
	this->line3.centerX(350, 900, 80);
	//line4
	this->line4.text = "        The left player moves with 'W' Key and 'S' Key         ";
	this->line4.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->line4.setColor(0xFF, 0xD0, 0x00, 0xFF);
	this->line4.centerX(450, 800, 80);
	//line5
	this->line5.text = "The right playes moves with 'UP Arrow' Key and 'Down Arrow' Key";
	this->line5.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->line5.setColor(0xFF, 0xD0, 0x00, 0xFF);
	this->line5.centerX(530, 800, 80);
	//line6
	this->line6.text = "                            Have fun!                          ";
	this->line6.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->line6.setColor(0xFF, 0xFF, 0xFF, 0xFF);
	this->line6.centerX(630, 800, 80);

}

void Instructions::input(void)
{
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{

		case SDL_MOUSEBUTTONDOWN:
			//Captura cuando un boton del mouse ha sido presionado
			cout << "Se ha presionado el boton ";
			cout << event.button.button << " en la posicion (";
			cout << event.button.x << "," << event.button.y << ")" << endl;
			testPoint = { event.button.x, event.button.y };
			if (SDL_PointInRect(&testPoint, &(homeButton.container))) {
				cout << "Hay interseccion con home!" << endl;
				this->state = MENU;
			}
			break;

		case SDL_QUIT:
			cout << "Cerrando..." << endl;
			//Captura cuando presionamos el boton para cerrar una ventana
			exit(0);
			break;

		}
	}
}

void Instructions::update(void)
{
	Screen::getInstance()->instructBackgroundColor(0x69, 0x69, 0x69, 0xFF);
	homeButton.draw();
	title.write();
	line1.write();
	line2.write();
	line3.write();
	line4.write();
	line5.write();
	line6.write();
}

void Instructions::render(void)
{
	SDL_RenderPresent(Screen::getInstance()->renderer);
}

int Instructions::run(void)
{
	switch (this->state) {
	case MENU:
		this->state = HOWTOPLAY;
		Screen::getInstance()->setWindowTitle("Pong Menu");
		return MENU;
		break;

	case HOWTOPLAY:
		this->state = HOWTOPLAY;
		input();
		update();
		render();
		return HOWTOPLAY;
		break;

	default:
		return HOWTOPLAY;
		break;
	}

	return 0;
}

Instructions::~Instructions()
{
}
