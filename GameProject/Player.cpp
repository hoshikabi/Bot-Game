#include"DxLib.h"
#include"Player.h"
#include<cmath>

namespace
{
	constexpr int SPAWN_X = 960;
	constexpr int SPAWN_Y = 540;
	constexpr float  MOVE_SPEED = 2.0f;
	constexpr float DIAGONAL_FACTOR = 0.707f;

	constexpr int ENEMY_COUNT = 3;
}

Player::Player() :posX(SPAWN_X), posY(SPAWN_Y) 
{
	Img = LoadGraph("Img/Player.png");

	// ‰¼‚Ì“G‚ğİ’è
	enemy[0] = { 1100, 540, 20 };
	enemy[1] = { 800, 400, 20 };
	enemy[2] = { 1200, 700, 20 };
}

Player::~Player()
{
	DeleteGraph(Img);
}

void Player::Draw()
{
	DrawExtendGraph(posX,posY,posX + size,posY + size,Img,TRUE);
	//DrawFormatString(0, 0, GetColor(255, 255, 255),"x:%d y:%d", posX, posY);
	// “G‚Ì•`‰æ
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		int color = GetColor(0, 255, 0);

		if (enemy[i].isAttached)
		{
			color = GetColor(255, 0, 0);
		}

		DrawCircle(enemy[i].ex,enemy[i].ey,enemy[i].er,color,TRUE);
	}

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		if (enemy[i].isAttached)
		{
			DrawString(20, 20,"ATTACHED",GetColor(255, 255, 255));
			break;
		}
	}
}

void Player::Update()
{
	Draw();
	HitEnemy();
	PushEnemy();
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



bool Player::CheckHitCircle(const Player& player, const Enemy& enemy)
{
	double dx = player.posX - enemy.ex;
	double dy = player.posY - enemy.ey;
	double distance = (dx * dx) + (dy * dy);
	double r_distance = (player.r + enemy.er);
	if(distance <= r_distance * r_distance)
	{
		return true;
	}
	return false;
}

void Player::HitEnemy()
{
	float playerX = posX + size / 2.0f;
	float playerY = posY + size / 2.0f;

	for (int i = 0; i < 3; i++)
	{
		if (!enemy[i].isAttached)
		{
			if (CheckHitCircle(*this, enemy[i]))
			{
				enemy[i].isAttached = true;

				float dx = enemy[i].ex - playerX;
				float dy = enemy[i].ey - playerY;

				float distance = sqrtf(dx * dx + dy * dy);

				if (distance == 0)
				{
					dx = 1;
					dy = 0;
					distance = 1;
				}

				float attachDistance = r + enemy[i].er;

				enemy[i].offsetX =
					dx / distance * attachDistance;

				enemy[i].offsetY =
					dy / distance * attachDistance;
			}
		}

		if (enemy[i].isAttached)
		{
			enemy[i].ex =
				static_cast<int>(playerX + enemy[i].offsetX);

			enemy[i].ey =
				static_cast<int>(playerY + enemy[i].offsetY);
		}
	}
}


void Player::PushEnemy()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			// “G“¯m‚Ì‹——£‚ğŒvZ
			float dx = static_cast<float>(enemy[j].ex - enemy[i].ex);
			float dy = static_cast<float>(enemy[j].ey - enemy[i].ey);

			float distance = sqrtf(dx * dx + dy * dy);

			// “G“¯m‚ªÚG‚·‚é‹——£
			float minDistance =
				static_cast<float>(enemy[i].er + enemy[j].er);

			// d‚È‚Á‚Ä‚¢‚éê‡
			if (distance < minDistance)
			{
				// Š®‘S‚É“¯‚¶ˆÊ’u‚Ìê‡
				if (distance == 0)
				{
					dx = 1.0f;
					dy = 0.0f;
					distance = 1.0f;
				}

				// d‚È‚Á‚Ä‚¢‚é‹——£
				float overlap = minDistance - distance;

				// “G“¯m‚ğ”¼•ª‚¸‚Â‰Ÿ‚µ–ß‚·
				float pushX = dx / distance * overlap / 2.0f;
				float pushY = dy / distance * overlap / 2.0f;

				enemy[i].ex -= static_cast<int>(ceilf(pushX));
				enemy[i].ey -= static_cast<int>(ceilf(pushY));

				enemy[j].ex += static_cast<int>(ceilf(pushX));
				enemy[j].ey += static_cast<int>(ceilf(pushY));
			}
		}
	}
}
