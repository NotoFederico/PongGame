#include "Score.h"
#include <iostream>

Score::Score() {
	reset();
}

void Score::reset(void) {
	this->leftPlayer = this->rightPlayer = 0;
	snprintf(bufferScore1, sizeof bufferScore1, "%d", this->leftPlayer);
	this->leftScore.text = bufferScore1;
	snprintf(bufferScore2, sizeof bufferScore2, "%d", this->rightPlayer);
	this->rightScore.text = bufferScore2;
}

void Score::update(int scored) {

	if (scored == 0) {
		this->leftPlayer++;
		snprintf(bufferScore1, sizeof bufferScore1, "%d", this->leftPlayer);
		this->leftScore.text = bufferScore1;
	}

	else if (scored == 1) {
		this->rightPlayer++;
		snprintf(bufferScore2, sizeof bufferScore2, "%d", this->rightPlayer);
		this->rightScore.text = bufferScore2;
	}

}

Score::~Score() {
}