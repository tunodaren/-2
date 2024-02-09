#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initalize()
{

		x_ = 300;
		y_ = 100;
		r_ = 100;
		speed_ = 4;
		isAlive_ = true;
		x2_ = 0;
		y2_ = 0;

}

void Enemy::Update()
{
	x2_ = x_ + r_;
	y2_ = y_ + r_;

	if (isAlive_ == true) {
		x_ += speed_;
		if (x_ <= 16 || x_ >= 1280 - r_)
		{
			speed_ *= -1;
		}
	}
}

void Enemy::Draw()
{
	if (isAlive_) {
		Novice::DrawBox(x_, y_, r_, r_, 0.0f, BLACK, kFillModeSolid);
	}
}


