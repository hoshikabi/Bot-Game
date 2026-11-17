#pragma once
class Enemy
{
public:
	int ex, ey;//敵の中心座標
	int er;//敵の半径

	bool isAttached = false; // くっついているか
	float offsetX = 0;       // プレイヤーの相対位置
	float offsetY = 0;
};

class Player
{
private:
	float posX, posY;
	int r = 16;//プレイヤーの半径
	int size = 32;
	int Img;
	Enemy enemy[3]; //仮の敵を保持
public:
	Player();
	~Player();
	void Draw();
	void Update();
	void Move();
	void HitEnemy(); // 敵にヒット時
	bool CheckHitCircle(const Player& player, const Enemy& enemy);
};
