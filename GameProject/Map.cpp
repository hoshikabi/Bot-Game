#include "Map.h"
#include<fstream>
#include<string>
#include <sstream>

//CSVファイルを読み込んで、mapDataに入れる
//読み込めたらtrue、失敗したらfalseを返す
bool Map::LoadCsv(const char* fileName)
{
	//CSVファイルを開く
	std::ifstream file(fileName);
	//開けなかったら失敗
	if (file.is_open() == false)
	{
		return false;
	}

	//1行分の文字を入れる
	std::string mapLine;
	//1マス分の文字を入れる
	std::string cell;

	//ファイルから1行ずつ読む（最後の行まで）
	while (std::getline(file, mapLine))
	{
		//1行をgetlineで読めるようにする
		std::stringstream lineStream(mapLine);
		//1行分の数字をためる（行ごとに空から始まる）
		std::vector<int> rowData;
		//カンマごとに1マスずつ読む
		while (std::getline(lineStream,cell, ','))
		{
			//文字を数字にして、1行分に追加する
			rowData.push_back(std::stoi(cell));
		}
		//1行分をマップ全体に追加する
		mapData.push_back(rowData);
	}

	//最後まで読めたら成功
	return true;
}

//マップを作るときに、CSVを読み込む
Map::Map(const char* fileName)
{
	LoadCsv(fileName);
}


bool Map::IsHit(int x, int y, int width, int height) const
{
	return false;
}
