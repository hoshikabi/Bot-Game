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
    //円の半径
    float radius = 32.0f;
    //移動速度
    float speed;
    //Playerが一定の距離に来ると逃げる
    float Runaway;
    //Enemyの移動方向
    float moveX;
    float moveY;
    //移動前の座標
    float prevX;
    float prevY;
    //鬼の中心から見た、くっついた位置
    float offsetX;
    float offsetY;
        
};