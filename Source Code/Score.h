#pragma once
#include "Text.h"
class Score
{
public:
	int leftPlayer;
	int rightPlayer;
	Text leftScore;
	Text rightScore;
	char bufferScore1[4] = { NULL };
	char bufferScore2[4] = { NULL };
public:
	Score();
	void reset(void);
	void update(int scored);
	~Score();
};

