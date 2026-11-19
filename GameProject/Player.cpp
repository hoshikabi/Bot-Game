#include"DxLib.h"
#include"Player.h"
#include<cmath>
#include<vector>

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

	// 敵（仮）の配置位置
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
	// 敵の描画
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		enemy[i].EnemyColor = GetColor(0, 255, 0);

		if (enemy[i].isAttached)
		{
			enemy[i].EnemyColor = GetColor(255, 0, 0);
		}
		if (!playerhand.empty())
		{
			int selectEnemy = playerhand[choice];
			enemy[selectEnemy].EnemyColor = GetColor(255, 255, 255);
		}

		DrawCircle(enemy[i].ex,enemy[i].ey,enemy[i].er,enemy[i].EnemyColor,TRUE);
	}

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		if (enemy[i].isAttached)
		{
			DrawString(20, 20,"ATTACHED",GetColor(255, 255, 255));
			break;
		}
	}

#ifdef _DEBUG
	DrawRect(0x0000ff, false);
#endif // 

}

void Player::Update()
{
	currentMouse = GetMouseInput();
	HitEnemy();
	PushEnemy();
	ChoiceEnemy();
	ShotEnemy();
	Move();
	Draw();
	prevMouse = currentMouse;
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
	if (posX < 32) posX = 32;
	if (posX > 1888) posX = 1888;

	if (posY < 32) posY = 32;
	if (posY > 1048) posY = 1048;
}



bool Player::CheckHitCircle(const Player& player, const Enemy& enemy)
{
	double dx = enemy.ex - (player.posX + player.size/2);
	double dy = enemy.ey - (player.posY + player.size/2);
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
	handCount = 0;
	for (int i = 0; i < 3; i++)
	{
		if (!enemy[i].isAttached)
		{
			if (CheckHitCircle(*this, enemy[i]))
			{
				enemy[i].isAttached = true;
				playerhand.push_back(i);

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
			/*ChoiceEnemy();*/
		}
	}
}


void Player::PushEnemy()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			// 中心座標の差
			float dx = static_cast<float>(enemy[j].ex - enemy[i].ex);
			float dy = static_cast<float>(enemy[j].ey - enemy[i].ey);
			//二点間の距離
			float distance = sqrtf(dx * dx + dy * dy);

			//最小距離 
			float minDistance =
				static_cast<float>(enemy[i].er + enemy[j].er);

			//重なっている場合
			if (distance < minDistance)
			{
				//同じ座標にいる場合
				if (distance == 0)
				{
					dx = 1.0f;
					dy = 0.0f;
					distance = 1.0f;
				}

				//重なっている距離
				float overlap = minDistance - distance;

				//押し戻し
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
void Player::DrawRect(unsigned int color,bool isFill)
{
	DrawCircle(static_cast<int>(posX + size/2), static_cast<int>(posY + size/2), static_cast<int>(r), color, isFill);
}

void Player::ChoiceEnemy()
{
	handCount = static_cast<int>(playerhand.size());
	// マウスの状態を取得
	/*currentMouse = GetMouseInput();*/
	if ((currentMouse & MOUSE_INPUT_RIGHT) != 0 && (prevMouse & MOUSE_INPUT_RIGHT) == 0 && handCount > 0)
	{
		// 敵を選択するロジック
		choice = (choice + 1) % handCount;
		
	}
	DrawFormatString(20, 40, GetColor(255,0,0),"choice: %d", choice+1);
	/*prevMouse = currentMouse;*/

}

void Player::ShotEnemy()
{
	if (playerhand.empty())return;
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	/*currentMouse = GetMouseInput();*/
	if ((currentMouse & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT))
	{
		isDragging = true;
		dragStartX = mouseX;
		dragStartY = mouseY;
		// ドラッグ開始時間を記録
		dragStartTime = GetNowCount();
		dragDuration = 0;
	}
	if (isDragging)
	{
		dragDuration = GetNowCount() - dragStartTime;
	}
	if (!(currentMouse & MOUSE_INPUT_LEFT) && (prevMouse & MOUSE_INPUT_LEFT))
	{
		if (isDragging)
		{
			isDragging = false;
			dragDuration = GetNowCount() - dragStartTime;
			vx = (dragStartX - mouseX) * 0.1f;
			vy = (dragStartY - mouseY) * 0.1f;
		}

	}
	if (isDragging)
	{
		DrawLine(dragStartX, dragStartY, mouseX, mouseY, GetColor(255, 0, 0));
	}
	//prevMouse = currentMouse;
}
