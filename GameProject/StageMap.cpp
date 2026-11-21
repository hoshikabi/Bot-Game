#include"Dxlib.h"
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include"StageMap.h"
#include"Config.h"
void StageMap::Init()
{
	//std::ifstream 適当な変数名("CSVの保存場所");←これでファイルを読み込む
	std::ifstream stage1("StageMap/Stage1.csv");
	

	//ステージ1のCSVファイルを読み込む
	std::string line;
	for (; std::getline(stage1, line);)//Stage1の中身をlineが読み取れなくなるまでループ
	{
		std::stringstream ss(line);//lineの中身をssにストリームとして保存
		std::vector<int>Line_X;
		std::string MapData;

		for (;std::getline(ss, MapData, ',');)//ssの数字を,区切りで1つずつ読み取っていく
		{
			Line_X.push_back(std::stoi(MapData));//数字を1つずつ入れていく
		}
		MAP1.emplace_back(Line_X);//mapに保存（次の列に保存）
	}

	stage1.close();//読み込んだファイルを閉じる
	MAP_HIGHT = MAP1.size();
	OneBlockSize = Config::GetInstance().GetSCREEN_Height() / MAP_HIGHT;//一マスの大きさを計算
}

void StageMap::Draw()
{
	for (int y = 0; y < MAP1.size(); y++)
	{
		for (int x = 0; x < MAP1[y].size(); x++)
		{
			switch (MAP1[y][x])
			{
			case 0://空気（仮）
			{
				break;
			}
			case 1://地面（仮）
			{
				DrawBox(((Config::GetInstance().GetSCREEN_Width() - MAP1[y].size() * OneBlockSize) / 2) + x * OneBlockSize,
					y * OneBlockSize,
					((Config::GetInstance().GetSCREEN_Width() - MAP1[y].size() * OneBlockSize) / 2) + x * OneBlockSize + OneBlockSize,
					y * OneBlockSize + OneBlockSize,
					GroundColor, TRUE);
				break;
			}
			case 2://壁（仮）
			{
				DrawBox(((Config::GetInstance().GetSCREEN_Width() - MAP1[y].size() * OneBlockSize) / 2) + x * OneBlockSize,
					y * OneBlockSize,
					((Config::GetInstance().GetSCREEN_Width() - MAP1[y].size() * OneBlockSize) / 2) + x * OneBlockSize + OneBlockSize,
					y * OneBlockSize + OneBlockSize,
					WallColor, TRUE);
				break;
			}
			}
		}
	}
}