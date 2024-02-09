#pragma once
#include<Novice.h>
class Enemy
{
private:

	int x_;
	int y_;
	int speed_;
	int r_;
	bool isAlive_;
	int x2_;
	int y2_;


public:
	Enemy();
	~Enemy();

	void Initalize();

	void Update();

	void Draw();

	int GetPosX() { return x_; }
	int GetPosY() { return y_; }
	int GetPosX_2() { return x2_; }
	int GetPosY_2() { return y2_; }
	bool GetisAlive() { return isAlive_; }
	/*int GetR() { return r_; }*/
};
