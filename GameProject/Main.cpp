#include"DxLib.h"
#include"StageMap.h"
#include"Config.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)	return -1;

	SetGraphMode(1920, 1080, 32);

	SetDrawScreen(DX_SCREEN_BACK);
	StageMap stagemap;
	stagemap.Init();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		stagemap.Draw();

		ScreenFlip();
	}

	DxLib_End();
	return 0;

}