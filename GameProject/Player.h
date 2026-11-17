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
	bool Collision(int px, int py, int pw, int ph, int ex, int ey, int ew, int eh);
};