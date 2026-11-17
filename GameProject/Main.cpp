#include"DxLib.h"
#include"Player.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)	return -1;

	SetGraphMode(1920, 1080, 32);

	SetDrawScreen(DX_SCREEN_BACK);
Player* player = new Player;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		player->Update();
		ScreenFlip();
	}

	DxLib_End();
	return 0;

}