#include "Player.h"


void Player::Move(char* preKeys) {

	if (preKeys[DIK_W]) {

		y_ = y_ - speed_;
	}

	if (preKeys[DIK_S]) {

		y_ = y_ + speed_;

	}

	if (preKeys[DIK_A]) {

		x_ =  x_ - speed_;

	}

	if (preKeys[DIK_D]) {

		x_ = x_ + speed_;

	}

}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initalize()
{
	x_ = 100;
	y_ = 500;
	r_ = 50;
	speed_ = 5;
	isAlive_ = true;
}

void Player::Draw()
{
	if (isAlive_) {
		Novice::DrawBox(x_,y_,r_,r_,0.0f,RED,kFillModeSolid);
	}

}
