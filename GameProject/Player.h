#pragma once
#include<vector>
class Enemy
{
public:
	int ex, ey;//敵の中心座標
	int er;//敵の半径

	bool isAttached = false; // くっついているか
	float offsetX = 0;       // プレイヤーの相対位置
	float offsetY = 0;
	int EnemyColor;
};

class Player
{
private:
	float posX, posY;
	int r = 32;//プレイヤーの半径
	int size = 64;
	int Img;

	//マウス入力関係
	int choice = 0;
	int prevMouse = 0;
	int currentMouse = 0;
	int dragStartX, dragStartY;//開始位置
	int dragStartTime = 0;//ドラッグ開始時間
	int dragDuration = 0;//ドラッグ時間
	bool isDragging = false; // ドラッグ中かどうか

	float vx, vy;//引っ張った時の移動速度


	Enemy enemy[3]; //仮の敵を保持
	std::vector<int>playerhand; // プレイヤーが持っている敵を保持
	int handCount = 0;
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

	void PushEnemy();
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
	/// <summary>
	/// Enemyの選択
	/// </summary>
	void ChoiceEnemy();
	void ShotEnemy();
};
