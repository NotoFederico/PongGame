#pragma once
#include "Header.h"

#define WINNER 4
class Game : public Interface
{
public:
	Ball ball;
	Image homeButton;
	Image resetGameButton;
	Image musicButton;
	Field field;
	Paddles paddle;
	Score score;
	SDL_Event event;
	SDL_Keysym keysym;
	SDL_Point testPoint;
	SDL_Rect collision;
	Text author;
	Text pong;
	Text game;
	Text winnerMessage;

	bool keyUp;
	bool keyDown;
	bool keyW;
	bool keyS;
	const Uint8* keyState;
	double relative;
	double normalize;
	double angle;
	int state;
	int flag;
	int winnerScore;

public:
	Game();
	void serve(void);
	void randomServe(void);
	void detectColision(void);
	void checkWinner(void);
	void drawButtons(void);
	void winner(void);
	void movePaddle(void);
	void detectControl(void);
	void moveBall();
	void input(void);
	void update(void);
	void render(void);
	int run(void);
	~Game();
};

