#pragma once

class Player;

class Enemy 
{
public:
    //コンストラクタ
    Enemy(float x, float y);
    //Enemyの更新
    void Update(float playerX, float playerY);
    //座標取得
    float x;
    float y;
    //描画
    void Draw() const;
    //Enemyの座標を返す
    bool IsAttached() const;
    //CPU 同士の当たり判定の関数を作る
    void CheckHitEnemy(const Enemy &other, float playerX, float playerY);

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
    //鬼またはCPUにくっついているか判断する
    bool isAttached = false;
   

    int imageHandle;
        
};