#define WIN32_LEAN_AND_MEAN
#include "DxLib.h"
#include "Server.h"

const int WINDOW_WIDTH = 1000; // ウィンドウの横幅
const int WINDOW_HEIGHT = 700; // ウィンドウの高さ

Server* server = new Server(8888);

int hRecvImage = -1;


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

	if (server->Init() == -1)
	{
		return -1;
	}

	while (1)
	{
		// 更新処理
		server->Update();
		if (server->GetRecvData().hImage > 0)
		{
			hRecvImage = server->GetRecvData().hImage;
		}

		// 描画処理
		ScreenFlip();
		ClearDrawScreen();


		if (ProcessMessage() == -1) 
		{
			break;
		}
	}

	return 0;
}
