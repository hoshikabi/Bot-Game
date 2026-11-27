#include "Enemy.h"
#include"Dxlib.h"
//#include"Player.h"
#include <cmath>
#include <cstdlib>

using namespace std;
//Enemyの初期化
Enemy::Enemy(float startX, float startY)
    : x(startX), y(startY),speed(2.0f), Runaway(100.0f),moveX(0.0f), moveY(0.0f),
    imageHandle(LoadGraph("image/Enemy.png"))
{
}
//敵の描画
void Enemy::Draw() const
{
    DrawRotaGraph(static_cast<int>(x), static_cast<int>(y), 0.167 ,0,imageHandle, TRUE);
}

bool Enemy::IsAttached() const
{
    return isAttached;
}

void Enemy::CheckHitEnemy(const Enemy &other, float playerX, float playerY)
{
    if (isAttached == true || other.IsAttached() == false)
    {
        //くっつかなくていいので終わる
        return;
    }

    // 移動後のCPUとCPU同氏の座標の差
    const float diffX = x - other.x;
    const float diffY = y - other.y;
    const float distanceSquared = diffX * diffX + diffY * diffY;//三平方の定理からそれぞれの中心からの距離を出す

    const float touchDistance = radius + other.radius;
    //中心からの距離が半径の合計以下だったら
    if (distanceSquared <= touchDistance * touchDistance)
    {
        // ここまで来たら、2つの円が触れているか、重なっている
        if (distanceSquared == 0)
        {
            x = other.x + touchDistance;
            y = other.y;
        }
        else
        {
            //Xの過ぎた分の押し戻し
            x += diffX / sqrt(distanceSquared) * (touchDistance - sqrt(distanceSquared));
            //Yの過ぎた文の押し戻し
            y += diffY / sqrt(distanceSquared) * (touchDistance - sqrt(distanceSquared));
        }
        //押し戻した後、鬼の中心から見たCPUの位置を保存する
        offsetX = x - playerX;
        offsetY = y - playerY;

        isAttached = true;
    }
}

//フレーム更新
void Enemy::Update(float playerX, float playerY)
{
    //くっついているなら
    if (isAttached == true)
    {
        x = playerX + offsetX;
        y = playerY + offsetY;
        //updateを終わらせる
        return;
    }
   
    //Playerとの距離
    float dx = x - playerX;
    float dy = y - playerY;

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

    //移動前のX座標とY座標を取得する
    prevX = x;
    prevY = y;
    //speedを掛けて逃げる
    x += moveX * speed;
    y += moveY * speed;

   // 仮のプレイヤーの中心と半径
   const float playerRadius = 32.0f;

   // 移動後のCPUとプレイヤーの中心座標の差
   const float diffX = x - playerX;
   const float diffY = y - playerY;
   const float distanceSquared = diffX * diffX + diffY * diffY;//三平方の定理からそれぞれの中心からの距離を出す

   const float touchDistance = radius + playerRadius;
   //中心からの距離が半径の合計以下だったら
   if (distanceSquared <= touchDistance * touchDistance)
   {
       // ここまで来たら、2つの円が触れているか、重なっている
       if (distanceSquared == 0)
       {
           x = playerX + touchDistance;
           y = playerY;
       }
       else
       {
           //Xの過ぎた分の押し戻し
           x += diffX / sqrt(distanceSquared) * (touchDistance - sqrt(distanceSquared));
           //Yの過ぎた文の押し戻し
           y += diffY / sqrt(distanceSquared) * (touchDistance - sqrt(distanceSquared));
       }
       //押し戻した後、鬼の中心から見たCPUの位置を保存する
       offsetX = x - playerX;
       offsetY = y - playerY;

       isAttached = true;
   }



}