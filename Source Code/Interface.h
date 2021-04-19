#pragma once
class Interface
{
public:
	virtual ~Interface() {};
	virtual void input(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;
	virtual int run(void) = 0;
};

