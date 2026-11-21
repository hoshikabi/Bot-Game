#pragma once
#include<vector>
//とりあえず５用意しとく
enum class Stage
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5
};

class StageMap
{
private:
	std::vector<std::vector<int>>MAP1;

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//試運転変数
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	int MAP_HIGHT;
	int OneBlockSize;//読み込んだマップのサイズ次第で一マスの大きさを変える
	
	int GroundColor = GetColor(206, 230, 193);
	int WallColor = GetColor(150, 75, 0);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

public:

	void Init();
	void Draw();
};

