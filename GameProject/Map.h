#pragma once
#include<vector>
class Map
{
private:
	//マップ
	std::vector<std::vector<int>> mapData; // CSVのデータを保持
	int chipSize = 64; // マップチップ1枚の大きさ（32など）
	bool LoadCsv(const char*fileName);

public:
    Map(const char* fileName);
	bool IsHit(int x, int y, int width, int height) const;
};

