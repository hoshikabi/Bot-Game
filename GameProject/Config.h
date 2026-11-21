#pragma once
class Config
{
private:

	const int Width = 1920;//PC画面の横の画面サイズ
	const int Height = 1080;//PC画面の縦の画面サイズ

	//一応作っとるけど使わんなら消していいよ(使うPCの拡大率次第でステージの描画のサイズを変える用)
	const int DPI = 96;//画面の拡大率100%時のDPI
	const int dpi = GetDpiForSystem();//画面の拡大率


public:

	static Config& GetInstance();

	int GetSCREEN_Width() { return Width; }
	int GetSCREEN_Height() { return Height; }

	int GetDPI();
};