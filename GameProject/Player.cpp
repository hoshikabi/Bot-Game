#include"DxLib.h"
#include"Player.h"

namespace
{
	constexpr int SPAWN_X = 960;
	constexpr int SPAWN_Y = 540;
	constexpr float  MOVE_SPEED = 5.0f;
	constexpr float DIAGONAL_FACTOR = 0.707f;
}

Player::Player() :posX(SPAWN_X), posY(SPAWN_Y) 
{
	Img = LoadGraph("Img/sample.png");
}

Player::~Player()
{
	DeleteGraph(Img);
}

void Player::Draw()
{
	DrawExtendGraph(posX,posY,posX + size,posY + size,Img,TRUE);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "x:%d y:%d", posX, posY);
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
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		DrawString(20, 20, "ƒNƒŠƒbƒN‚³‚ê‚Ä‚¢‚Ü‚·", GetColor(255, 0, 0));
	}

	if (posX < 32) posX = 32;
	if (posX > 1888) posX = 1888;

	if (posY < 32) posY = 32;
	if (posY > 1048) posY = 1048;
}

bool Player::Collision(int px, int py, int pw, int ph, int ex, int ey, int ew, int eh)
{
	if (px < ex + ew &&
		px + pw >  ex &&
		py < ey + eh &&
		py + ph > ey)
	{
		return true;
	}
	return false;
}
