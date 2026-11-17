#pragma once
class Player
{
private:
	int posX, posY;
	int size = 32;
	int Img;
public:
	Player();
	~Player();
	void Draw();
	void Update();
	void Move();
};