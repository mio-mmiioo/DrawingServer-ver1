#include "ServerScene.h"
#include "MyLibrary/Server.h"

const int SERVER_PORT_NUMBER = 8888;

ServerScene::ServerScene()
{
	server_ = new Server(SERVER_PORT_NUMBER);
	server_->Init();
	state_ = MAKE_ROOM;
}

ServerScene::~ServerScene()
{
}

void ServerScene::Update()
{
	// これだと融通が利かない
	server_->Update();

	switch (state_)
	{
	case MAKE_ROOM:
		server_->ListenSocket();
		server_->ReceiveData();

		PACKET recvData = server_->GetRecvData();
		// ここで受信したデータが
		// 1回目　MAKE_ROOM, 111111
		// 2回目以降  ENTER_ROOM 1回目で送られてきた数字
		// 完了ボタンが押された END_MAKE_ROOM
		// 参加者にMAKE_NAMEを送る



		break;
	case MAKE_NAME:

		break;
	case WAIT_ANSWER:

		break;
	case SEND_ANSWER:
		break;
	}
}

