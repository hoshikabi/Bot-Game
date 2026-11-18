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
	int r = 32;//プレイヤーの半径
	int size = 64;
	int Img;
	Enemy enemy[3]; //仮の敵を保持
public:
	/// <summary>
	/// インスタンス
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	/// Enemyに触れているか
	/// </summary>
	void HitEnemy(); // 敵にヒット時
	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="player">Playerオブジェクト</param>
	/// <param name="enemy">Enemyオブジェクト</param>
	/// <returns></returns>
	bool CheckHitCircle(const Player& player, const Enemy& enemy);
	/// <summary>
/// 当たり判定可視化
/// </summary>
/// <param name="color">色</param>
/// <param name="isFill">塗りつぶし</param>
	void DrawRect(unsigned int color,bool isFill);
};
