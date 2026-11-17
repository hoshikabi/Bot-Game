#include "Enemy.h"
//#include"Player.h"
#include <cmath>
#include <cstdlib>

using namespace std;
//Enemyの初期化
Enemy::Enemy(float startX, float startY)
    : x(startX), y(startY),speed(2.0f), Runaway(100.0f),moveX(0.0f), moveY(0.0f)
{
}
//フレーム更新
void Enemy::Update(const Player& player)
{
    //Playerとの距離
    float dx = x;//- player.x;
    float dy = y;//- player.y;
    //PlayerとEnemyの距離を二乗する
    float distances = dx * dx + dy * dy;
    //
    if (distances < Runaway * Runaway && distances > 0.001f) 
    {
        //Playerから離れる方向へ移動
        float distance = sqrt(distances);
        moveX = dx / distance;
        moveY = dy / distance;
    }
    else 
    {
        //通常時はランダムな方向を選ぶ
        moveX = static_cast<float>(std::rand() % 3 - 1);
        moveY = static_cast<float>(std::rand() % 3 - 1);

        // 斜め移動が速くならないように方向をそろえる
        float length = sqrt(moveX * moveX + moveY * moveY);
        if (length > 0.001f) 
        {
            moveX /= length;
            moveY /= length;
        }
    }
    //speedを掛けて逃げる
    x += moveX * speed;
    y += moveY * speed;
}