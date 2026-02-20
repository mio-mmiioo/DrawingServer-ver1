#define WIN32_LEAN_AND_MEAN
#include "DxLib.h"
#include "Scene.h"

const int WINDOW_WIDTH = 1000; // ウィンドウの横幅
const int WINDOW_HEIGHT = 700; // ウィンドウの高さ

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DxLib初期化まわり
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	SceneMaster::Init();

	while (1)
	{
		// 更新処理
		SceneMaster::Update();
		
		// 描画処理
		ScreenFlip();
		ClearDrawScreen();
		SceneMaster::Draw();

		if (ProcessMessage() == -1) 
		{
			break;
		}
	}

	return 0;
}
