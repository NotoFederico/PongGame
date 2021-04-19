#include "Music.h"
#include <iostream>

using namespace std;

Music* Music::instance = 0;

Music* Music::getInstance()
{
	if (instance == 0) {
		instance = new Music();
	}
	return instance;
}

Music::Music() {

	this->ping = NULL;
	this->pong = NULL;
	this->game = NULL;
	this->menu = NULL;

	this->ping = Mix_LoadWAV("ost/ping.ogg");
	this->pong = Mix_LoadWAV("ost/pong.ogg");
	this->menu = Mix_LoadMUS("ost/menu.wav");
	this->game = Mix_LoadMUS("ost/game.wav");

	musicVolume(10);
}


void Music::effectVolume(Mix_Chunk* effect, int amplitude) { //puede que no funcione correctamente, es necesario testear este metodo
	Mix_VolumeChunk(effect, amplitude);
}

void Music::musicVolume(int amplitude) {
	Mix_VolumeMusic(amplitude);
}

void Music::generalVolume(int amplitude) {
	Mix_Volume(-1, amplitude);
}

Music::~Music() {
	Mix_FreeMusic(this->game);
	Mix_FreeMusic(this->menu);
	Mix_FreeChunk(this->ping);
	Mix_FreeChunk(this->pong);
	Mix_CloseAudio();
}