#pragma once
#include<Novice.h>

class Player
{

private:

	int x_;
	int y_;
	int speed_;
	int r_;
	bool isAlive_;


public:

	Player();
	~Player();

	void Initalize();

	void Draw();

	void Move(char* preKeys);

	int GetPosX() { return x_; }
	int GetPosY() { return y_; }
};


