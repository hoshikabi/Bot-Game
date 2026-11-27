#include"DxLib.h"
#include"Enemy.h"
#include"Vector"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)	return -1;

	SetGraphMode(1920, 1080, 32);

	SetDrawScreen(DX_SCREEN_BACK);

	float playerX = 960;
	float playerY = 540;
	//vectorでEnemyを作る
	std::vector<Enemy> enemyis;
	enemyis.push_back(Enemy(300, 300));
	enemyis.push_back(Enemy(200, 200));
	enemyis.push_back(Enemy(400, 400));

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//動くかの確認
		ClearDrawScreen();
		
		if (CheckHitKey(KEY_INPUT_UP))
		{
			playerY -= 5;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			playerY += 5;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			playerX -= 5;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			playerX += 5;
		}


		//呼び出す
		for (int i = 0; i < enemyis.size(); i++)
		{
			enemyis[i].Update(playerX, playerY);
		}


		//CPU同士の当たり判定
		for (int i = 0; i < enemyis.size(); i++)
		{
			for (int j = 0; j < enemyis.size(); j++)
			{
				if (i != j)
				{
					enemyis[i].CheckHitEnemy(enemyis[j], playerX, playerY);
				}
			}
		}

		//描画
		DrawCircle(playerX, playerY, 32, GetColor(255, 0, 0));
		for (int i = 0; i < enemyis.size(); i++)
		{
			enemyis[i].Draw();
		}
		

		


		ScreenFlip();
	}

	DxLib_End();
	return 0;

}