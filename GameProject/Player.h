#pragma once
class Player
{
private:
	int posX, posY;
public:
	Player();
	~Player();
	void Draw();
	void Update();
	void Move();
	void sample();
};