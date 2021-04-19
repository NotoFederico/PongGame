#pragma once
#include <SDL_mixer.h>

class Music
{
public:
	//Sound effects objects
	Mix_Chunk* ping = NULL;
	Mix_Chunk* pong = NULL;
	//Music objects
	Mix_Music* menu = NULL;
	Mix_Music* game = NULL;

public:
	void effectVolume(Mix_Chunk* effect, int amplitude);
	void musicVolume(int amplitude);
	void generalVolume(int amplitude);
	static Music* getInstance();
	~Music();

private:
	static Music* instance;
	Music();
};

