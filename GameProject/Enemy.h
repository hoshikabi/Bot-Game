#pragma once

class Player;

class Enemy 
{
public:
    //コンストラクタ
    Enemy(float x, float y);
    //Enemyの更新
    void Update(const Player& player);
    //座標取得
    float x;
    float y;

private:
    //移動速度
    float speed;
    //Playerが一定の距離に来ると逃げる
    float Runaway;
    //Enemyの移動方向
    float moveX;
    float moveY;
};