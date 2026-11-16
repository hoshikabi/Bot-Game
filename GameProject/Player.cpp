#include"DxLib.h"
#include"Player.h"

namespace
{
	constexpr int SPAWN_X = 960;
	constexpr int SPAWN_Y = 540;
	constexpr float  MOVE_SPEED = 5.0f;
}

Player::Player() :posX(SPAWN_X), posY(SPAWN_Y) {}

Player::~Player()
{

}

void Player::Draw()
{
	DrawCircle(posX, posY, 32,GetColor(0, 255, 0), true);
}

void Player::Update()
{
	Draw();
	Move();
}

void Player::Move()
{
	if (CheckHitKey(KEY_INPUT_W))
	{
		posY -= MOVE_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		posY += MOVE_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		posX -= MOVE_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		posX += MOVE_SPEED;
	}
}
