#include "Header.h"
#include "Menu.h"
#include <iostream>
#include <SDL.h>

using namespace std;

Menu::Menu() {

	cout << "Menu object initialization" << endl;

	Screen::getInstance()->setWindowTitle("Pong Menu");

	this->fullscreen = 0;
	this->event = { 0 };
	this->menuOption = PLAYTEXT;
	this->state = MENU;

	//Play button
	play.text = " > Play Pong < ";
	play.setFont(Font::getInstance()->fonts["fonts/Peepo.ttf"].first);
	play.setColor(0xAA, 0xAA, 0xAA, 0xFF);
	play.centerX(250, 300, 100);
	//Controls button
	instructions.text = "  How to Play  ";
	instructions.setFont(Font::getInstance()->fonts["fonts/Peepo.ttf"].first);
	instructions.setColor(0xAA, 0xAA, 0xAA, 0xFF);
	instructions.centerX(350, 300, 100);
	//Quit button
	quit.text = "   Quit Pong   ";
	quit.setFont(Font::getInstance()->fonts["fonts/Peepo.ttf"].first);
	quit.setColor(0xAA, 0xAA, 0xAA, 0xFF);
	quit.centerX(450, 300, 100);
	//Fox image
	fox.centerX(600, 200, 100);
	fox.path = "images/fox.png";
	//Background image
	background.fill();
	background.path = "images/pongPressStart.svg";
	//Music
	Mix_PlayMusic(Music::getInstance()->menu, -1);
}

void Menu::input(void) {
	while (SDL_PollEvent(&event)) {
		switch (event.type) //miembro tipo de la union evento
		{
		case SDL_MOUSEMOTION:
			//Captura del movimiento del mouse
			//cout << "El puntero se ha movido ";
			//Posición actual del puntero
			//cout << "La posicion nueva es: (";
			//cout << event.motion.x << "," << event.motion.y << ")." << endl;
			//Posición relativa
			//cout << "Posicion relativa: (";
			//cout << event.motion.xrel << "," << event.motion.yrel << ")" << endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//Captura cuando un boton del mouse ha sido presionado
			//cout << "Se ha presionado el boton ";
			//cout << event.button.button << " en la posicion (";
			//cout << event.button.x << "," << event.button.y << ")" << endl;
			break;
		case SDL_KEYDOWN:
			//Captura cuando se ha presionado una tecla
			keysym = event.key.keysym;
			cout << "SDL keysym: " << keysym.sym << " - ";
			cout << SDL_GetKeyName(keysym.sym) << endl;
			/*Podemos identificar si tenemos teclas como el shift presionadas
			y entonces escribir en mayúscula*/
			if (event.key.keysym.mod & KMOD_LSHIFT)
				cout << "El shift izquierdo esta siendo presionado" << endl;
			else
				cout << "El shift izquierdo no esta presionado" << endl;
			//Podría identificar alguna letra en especial, por ejemplo ESC para salir
			if (keysym.sym == SDLK_ESCAPE) {
				cout << "Cerrando..." << endl;
				exit(0);
			}
			if (keysym.sym == SDLK_UP || keysym.sym == SDLK_DOWN) {

				if (keysym.sym == SDLK_DOWN) {
					this->menuOption++;
				}
				else if (keysym.sym == SDLK_UP) {
					this->menuOption--;
				}

				if (this->menuOption < PLAYTEXT)
					this->menuOption = QUITTEXT;
				else if (this->menuOption > QUITTEXT) {
					this->menuOption = PLAYTEXT;
				}

				switch (this->menuOption) {
				case PLAYTEXT:
					play.text = " > Play Pong < ";
					instructions.text = "  How to Play  ";
					quit.text = "   Quit Pong   ";
					break;
				case HOWTOPLAYTEXT:
					play.text = "   Play Pong   ";
					instructions.text = "> How to Play <";
					quit.text = "   Quit Pong   ";
					break;
				case QUITTEXT:
					play.text = "   Play Pong   ";
					instructions.text = "  How to Play  ";
					quit.text = " > Quit Pong < ";
					break;
				}
			}
			if (keysym.sym == SDLK_RETURN) {

				switch (this->menuOption) {
				case PLAYTEXT:
					this->state = PLAY;
					break;
				case HOWTOPLAYTEXT:
					this->state = HOWTOPLAY;
					break;
				case QUITTEXT:
					this->state = QUIT;
					break;
				}
			}
			if (keysym.sym == SDLK_F11) {
				fullscreen = !fullscreen;
				switch (fullscreen) {
				case 0:
					Screen::getInstance()->windowed();
					break;
				case 1:
					Screen::getInstance()->fullscreen();
					break;
				}
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

void Menu::update(void) {
	Screen::getInstance()->menuBackgroundColor(0xF9, 0x64, 0x00, 0xFF);
	//title.setColors(0xF9, 0x64, 0x00, 0xFF); //naranja
	//title.setContainer(Screen::getInstance()->defaultWidth / 2 - 200, 10, 400, 100);
	background.draw();
	play.write();
	instructions.write();
	quit.write();
	fox.draw();

}

void Menu::render(void) {
	SDL_RenderPresent(Screen::getInstance()->renderer);
}

int Menu::run(void) {

	switch (this->state) {
	case MENU:
		input();
		update();
		render();
		return MENU;
		break;

	case PLAY:
		Screen::getInstance()->setWindowTitle("Pong Game");
		Mix_HaltMusic();
		Mix_PlayMusic(Music::getInstance()->game, -1);
		//puedo agregar fade in y fade out pero me ralentiza el cambio de vista
		//Mix_FadeOutMusic(1500);
		//Mix_FadeInMusic(Music::getInstance()->game, -1, 1500);
		this->state = MENU;
		return PLAY;
		break;

	case HOWTOPLAY:
		this->state = MENU;
		return HOWTOPLAY;
		break;

	case QUIT:
		this->state = MENU;
		return QUIT;
		break;

	default:
		return MENU;
		break;
	}

}

Menu::~Menu() {
	cout << "Destroying Menu object" << endl;
	TTF_Quit();
	IMG_Quit();
}
