#pragma once
class Enemy
{
public:
	int ex, ey;//敵の中心座標
	int er;//敵の半径
};

class Player
{
private:
	int posX, posY;
	int r;//プレイヤーの半径
	int size = 32;
	int Img;
public:
	Player();
	~Player();
	void Draw();
	void Update();
	void Move();
	bool CheckHitCircle(const Player& player, const Enemy& enemy);
};
