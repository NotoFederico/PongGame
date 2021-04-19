#include "Game.h"
#include <iostream>

#define LEFTPLAYER 0
#define RIGHTPLAYER 1

using namespace std;

Game::Game() {
	cout << "Game object initialization" << endl;
	this->keyDown = this->keyUp = this->keyW = this->keyS = 0;
	this->normalize = this->relative = this->angle = 0;
	this->testPoint = { NULL };
	this->collision = { 0 };
	this->event = { 0 };
	this->state = 1;
	this->winnerScore = 5;
	paddle.speed = 20;

	//Author
	this->author.text = "Made by F. Noto";
	this->author.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->author.setColor(0xFF, 0xFF, 0xFF, 0xFF);
	this->author.setContainer(1090, 690, 150, 25);
	//-Pong
	this->pong.text = "- PONG";
	this->pong.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->pong.setColor(0x69, 0x69, 0x69, 0xFF);
	this->pong.setContainer(Screen::getInstance()->defaultWidth / 2 - 250 - 10, 30, 250, 75);
	//Game -
	this->game.text = "GAME -";
	this->game.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->game.setColor(0xFF, 0xD0, 0x00, 0xFF);
	this->game.setContainer(Screen::getInstance()->defaultWidth / 2 + 10, 30, 250, 75);
	//Winner
	this->winnerMessage.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	this->winnerMessage.setColor(0xFF, 0xFF, 0xFF, 0xFF);
	this->winnerMessage.centerX(345, 800, 200);
	//Play/Pause music button
	this->musicButton.setContainer(1000, this->pong.container.y + this->pong.container.h / 2 - 25, 40, 40);
	this->musicButton.path = "images/music.png";
	//reset game button
	this->resetGameButton.setContainer(1000 + 50 + 50, this->pong.container.y + this->pong.container.h / 2 - 25, 40, 40);
	this->resetGameButton.path = "images/reset.png";
	//Home button
	this->homeButton.setContainer(1000 + 50 + 50 + 100, this->pong.container.y + this->pong.container.h / 2 - 25, 40, 40);
	this->homeButton.path = "images/home.png";
	//Score
	score.leftScore.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	score.leftScore.setColor(0x69, 0x69, 0x69, 0xFF);
	score.leftScore.setContainer(Screen::getInstance()->defaultWidth / 2 - 100, 140, 50, 50);
	score.rightScore.setFont(Font::getInstance()->fonts["fonts/ExpressaBold.ttf"].first);
	score.rightScore.setColor(0xFF, 0xD0, 0x00, 0xFF);
	score.rightScore.setContainer(Screen::getInstance()->defaultWidth / 2 + 50, 140, 50, 50);
	//serve
	randomServe();
}

void Game::update(void) {
	Screen::getInstance()->gameBackgroundColor();
	author.write();
	pong.write();
	game.write();
	drawButtons();
	field.draw();
	paddle.draw();
	moveBall();
	ball.draw();
	detectColision();
	score.leftScore.write();
	score.rightScore.write();
	checkWinner();

}

void Game::render(void) {
	SDL_RenderPresent(Screen::getInstance()->renderer);
}

void Game::input(void) {

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
			if (SDL_PointInRect(&testPoint, &(resetGameButton.container))) {
				cout << "Hay interseccion con reset!" << endl;
				this->state = PLAY;
				score.reset();
				randomServe();
			}
			if (SDL_PointInRect(&testPoint, &(musicButton.container))) {
				cout << "Hay interseccion con music button!" << endl;
				if (Mix_PlayingMusic()) {
					Mix_HaltMusic();
					this->musicButton.path = "images/silence.png";
				}
				else {
					Mix_PlayMusic(Music::getInstance()->game, -1);
					this->musicButton.path = "images/music.png";
				}
			}
			break;

		case SDL_KEYDOWN:

			//Captura cuando se ha presionado una tecla
			keysym = event.key.keysym;
			cout << "SDL keysym: " << keysym.sym << " - ";
			cout << "Key name: " << SDL_GetKeyName(keysym.sym) << endl;
			detectControl();
			movePaddle();
			paddle.checkPlayableArea();

			if (keysym.sym == SDLK_ESCAPE) {
				cout << "Cerrando..." << endl;
				exit(0);
			}

			if (keysym.sym == SDLK_RETURN) {
				cout << " Toque enter" << endl;
			}

			if (keysym.sym == SDLK_F11) {
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

void Game::serve()
{
	paddle.serve();
	ball.serve();
}

void Game::randomServe(void)
{
	do {
		ball.direction = rand() % 3 - 1;
	} while (ball.direction == 0);
	serve();
}

void Game::detectColision(void)
{
	if (SDL_IntersectRect(&ball.ball, &paddle.left, &this->collision)) {
		cout << "Collision detected with left pad" << endl;
		ball.direction = 1;
		ball.speed++;

		relative = (paddle.left.y + (double)(paddle.height / 2)) - collision.y;
		normalize = relative / (paddle.height / 2);
		angle = normalize * (5 * M_PI / 12);
		ball.dx = ball.speed * cos(angle);
		ball.dy = ball.speed * (-sin(angle));

		Mix_PlayChannel(-1, Music::getInstance()->ping, 0);
	}

	if (SDL_IntersectRect(&ball.ball, &paddle.right, &this->collision)) {
		cout << "Collision detected with rigth pad" << endl;
		ball.direction = -1;
		ball.speed++;

		relative = (paddle.right.y + (double)(paddle.height / 2)) - collision.y;
		normalize = relative / (paddle.height / 2);
		angle = normalize * (5 * M_PI / 12);
		ball.dx = ball.speed * cos(angle);
		ball.dy = ball.speed * (-sin(angle));

		Mix_PlayChannel(-1, Music::getInstance()->pong, 0);
	}

	if (SDL_IntersectRect(&ball.ball, &field.upRightHalf, &this->collision) ||
		SDL_IntersectRect(&ball.ball, &field.downRightHalf, &this->collision) ||
		SDL_IntersectRect(&ball.ball, &field.upLeftHalf, &this->collision) ||
		SDL_IntersectRect(&ball.ball, &field.downLeftHalf, &this->collision)) {
		cout << "Collision detected with field" << endl;
		ball.dy *= -1;
	}

	if (SDL_IntersectRect(&ball.ball, &field.left, &this->collision)) {
		cout << "Collision detected with left field" << endl;
		score.update(RIGHTPLAYER);
		ball.direction = 1;
		serve();
	}

	if (SDL_IntersectRect(&ball.ball, &field.right, &this->collision)) {
		cout << "Collision detected with right field" << endl;
		score.update(LEFTPLAYER);
		ball.direction = -1;
		serve();
	}
}

void Game::checkWinner(void)
{

	if (score.leftPlayer == this->winnerScore) {
		winnerMessage.text = "LEFT PLAYER WINS!";
		winnerMessage.setColor(0xFF, 0xD0, 0x00, 0xFF);

		this->state = WINNER;
	}
	else if ((score.rightPlayer == this->winnerScore)) {
		winnerMessage.text = "RIGHT PLAYER WINS!";
		winnerMessage.setColor(0x69, 0x69, 0x69, 0xFF);
		this->state = WINNER;
	}
}

void Game::drawButtons(void)
{
	homeButton.draw();
	resetGameButton.draw();
	musicButton.draw();
}

void Game::winner(void)
{
	Screen::getInstance()->blackRectAlpha(10);
	drawButtons();
	SDL_Delay(25);
	winnerMessage.write();
}

void Game::movePaddle(void)
{
	//toma de decisiones
	if (keyW && keyUp) {
		paddle.left.y -= paddle.speed;
		paddle.right.y -= paddle.speed;
	}
	else if (keyW && keyDown) {
		paddle.left.y -= paddle.speed;
		paddle.right.y += paddle.speed;
	}
	else if (keyS && keyUp) {
		paddle.left.y += paddle.speed;
		paddle.right.y -= paddle.speed;
	}
	else if (keyS && keyDown) {
		paddle.left.y += paddle.speed;
		paddle.right.y += paddle.speed;
	}
	else if (keyW) {
		paddle.left.y -= paddle.speed;
	}
	else if (keyS) {
		paddle.left.y += paddle.speed;
	}
	else if (keyUp) {
		paddle.right.y -= paddle.speed;
	}
	else if (keyDown) {
		paddle.right.y += paddle.speed;
	}
}

void Game::detectControl(void)
{
	this->keyState = SDL_GetKeyboardState(NULL);

	//keyUp
	if (this->keyState[SDL_SCANCODE_UP])
	{
		this->keyUp = true;
	}
	else {
		this->keyUp = false;
	}

	//keyDown
	if (this->keyState[SDL_SCANCODE_DOWN])
	{
		this->keyDown = true;
	}
	else {
		this->keyDown = false;
	}

	//keyW
	if (this->keyState[SDL_SCANCODE_W])
	{
		this->keyW = true;
	}
	else {
		this->keyW = false;
	}

	//keyS
	if (this->keyState[SDL_SCANCODE_S])
	{
		this->keyS = true;
	}
	else {
		this->keyS = false;
	}
}

void Game::moveBall() {

	ball.ball.x += ball.dx * ball.direction;
	ball.ball.y += ball.dy;
}


int Game::run(void) {

	switch (this->state) {
	case MENU:
		this->state = PLAY;
		Screen::getInstance()->setWindowTitle("Pong Menu");
		Mix_HaltMusic();
		Mix_PlayMusic(Music::getInstance()->menu, -1);
		//puedo agregar fade in y fade out pero me ralentiza el cambio de vista
		//Mix_FadeOutMusic(1500);
		//Mix_FadeInMusic(Music::getInstance()->menu, -1, 1500);
		return MENU;
		break;

	case PLAY:
		this->state = PLAY;
		input();
		update();
		render();
		return PLAY;
		break;

	case QUIT:
		this->state = PLAY;
		return QUIT;
		break;

	case WINNER:
		input();
		winner();
		render();
		return PLAY; //sigo en el modo juego
		break;

	default:
		return PLAY;
		break;
	}
}

Game::~Game() {
	cout << "Destroying Game object" << endl;
}
