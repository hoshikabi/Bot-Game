#include"Dxlib.h"
#include"Config.h"


Config& Config::GetInstance()
{
	static Config instance;

	return instance;
}

//DPIを計算する関数(いらんなら消す)
int Config::GetDPI()
{
	int SCREENDPI = 0;
	SCREENDPI = (2 - dpi / DPI);

	return SCREENDPI;
}