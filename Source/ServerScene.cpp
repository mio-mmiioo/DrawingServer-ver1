#include "ServerScene.h"
#include "MyLibrary/Server.h"
#include "MyLibrary/Packet.h"

const int SERVER_PORT_NUMBER = 8888;

ServerScene::ServerScene()
{
	Packet::Init();
	server_ = new Server(SERVER_PORT_NUMBER);
	server_->Init();
}

ServerScene::~ServerScene()
{
}

void ServerScene::Update()
{
	server_->ListenSocket();
	server_->ReceiveData();
	server_->RemoveSocket();
	PACKET recvData = server_->GetRecvData();

	switch (Packet::dataName[recvData.dataType])
	{
	case END_MAKE_ROOM: // 部屋立ち上げ終了と言われたら
		server_->SendData(PACKET{ "START_PLAY", "", recvData.number });
		break;
	case MAKE_ROOM: // 部屋立ち上げ
		useNumber.push_back(recvData.number); // 使用している番号を追加
		break;
	case ENTER_ROOM: // 入室
		// 指定した部屋番号が見つかったら　入室成功

		break;


	}
}

