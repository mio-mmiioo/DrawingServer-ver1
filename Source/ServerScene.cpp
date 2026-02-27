#include "ServerScene.h"
#include "MyLibrary/Server.h"


const int SERVER_PORT_NUMBER = 8888;

ServerScene::ServerScene()
{
	Packet::Init();
	server_ = new Server(SERVER_PORT_NUMBER);
	server_->Init();
	playerCount = 1;
}

ServerScene::~ServerScene()
{
}

void ServerScene::Update()
{
	server_->ListenSocket();
	if (server_->ReceiveData() == true)
	{
		GetDataUpdate(); // データを取得した場合に行われる処理
	}
	server_->RemoveSocket();
}

void ServerScene::GetDataUpdate()
{
	recvData_ = server_->GetRecvData();
	sendData_ = recvData_;
	//const char* playerName = "プレイヤー" + playerCount;
	std::string playerName = "プレイヤー" + std::to_string(playerCount);
	switch (Packet::dataName[recvData_.dataType])
	{
	case END_MAKE_ROOM: // 部屋立ち上げ終了と言われたら
		strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_PLAY", _TRUNCATE);
		server_->SendData(sendData_);
		break;

	case MAKE_ROOM: // 部屋立ち上げ
		// 番号が使用済みでなかったら立ち上げ成功
		useNumber.push_back(recvData_.number); // 使用している番号を追加
		strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_MATCHING", _TRUNCATE);
		strncpy_s(sendData_.playerName, sizeof(sendData_.playerName), playerName.c_str(), _TRUNCATE);
		server_->SendData(sendData_);

		break;
	case ENTER_ROOM: // 入室
		// 指定した部屋番号が見つかったら　入室成功
		strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_MATCHING", _TRUNCATE);
		strncpy_s(sendData_.playerName, sizeof(sendData_.playerName), playerName.c_str(), _TRUNCATE);
		server_->SendData(sendData_);

		// 成功したら
		playerCount += 1;

		break;

	case CHANGE_NAME: // 名前登録
		// 部屋番号に登録された名前の人を存在させる
		// 

		break;
	}
}

