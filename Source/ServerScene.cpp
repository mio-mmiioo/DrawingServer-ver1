#include "ServerScene.h"
#include "MyLibrary/Server.h"


const int SERVER_PORT_NUMBER = 8888;

ServerScene::ServerScene()
{
	Packet::Init();
	server_ = new Server(SERVER_PORT_NUMBER);
	server_->Init();
	playerCount_ = 1;
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
	std::string playerName = "プレイヤー" + std::to_string(playerCount_);
	switch (Packet::dataName[recvData_.dataType])
	{
	case END_MAKE_ROOM: // 部屋立ち上げ終了と言われたら
		// プレイヤーの人数を設定
		server_->SetPlayerLimit(server_->GetPlayerCount());
		strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "PLAYER_COUNT", _TRUNCATE);
		sendData_.number = server_->GetPlayerCount();
		phaseCount_ = sendData_.number;
		server_->SendData(sendData_);

		// ゲーム開始の指示
		strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_PLAY", _TRUNCATE);
		server_->SendData(sendData_);
		break;

	case MAKE_ROOM: // 部屋立ち上げ
		// 番号が使用済みでなかったら立ち上げ成功
		useNumber_.push_back(recvData_.number); // 使用している番号を追加
		strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_MATCHING", _TRUNCATE);
		strncpy_s(sendData_.playerName, sizeof(sendData_.playerName), playerName.c_str(), _TRUNCATE);
		server_->SendData(sendData_);
		AddPlayerName(sendData_.playerName);

		break;
	case ENTER_ROOM: // 入室
		// 指定した部屋番号が見つかったら　入室成功
		strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_MATCHING", _TRUNCATE);
		strncpy_s(sendData_.playerName, sizeof(sendData_.playerName), playerName.c_str(), _TRUNCATE);
		server_->SendData(sendData_);
		AddPlayerName(sendData_.playerName);

		break;

	case CHANGE_NAME: // 名前登録
		// 部屋番号に登録された名前の人を存在させる

	case SEND_IMAGE:
		// 今までに送られてきたimageをリストに追加
		// 参加者分そろったら、参加人数分送り返す
		// その後ゲーム再開
		if (AddRecvImage(recvData_) == server_->GetPlayerCount())
		{
			strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "SEND_IMAGE", _TRUNCATE);
			// 集めた画像を参加者全員に送る(各参加者がそれぞれの画面で画像を表示できるようにするため)
			for (int count = 0; count < hImageList_.size(); count++)
			{
				sendData_.number = hImageList_[count];
				server_->SendData(sendData_);
			}
			hImageList_.clear();
			phaseCount_ = -1;
			if (phaseCount_ <= 0) // お題入力とお絵描きを指定回数した後ならリザルトに移る指示を出す
			{
				strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_RESULT", _TRUNCATE);
				server_->SendData(sendData_);
			}
			else // 次の回答を始める指示を出す
			{
				strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_GAME", _TRUNCATE);
				server_->SendData(sendData_);
			}
		}
		break;

	case STOP_GAME: 
		if (phaseCount_ <= 0)
		{
			strncpy_s(sendData_.dataType, sizeof(sendData_.dataType), "START_RESULT", _TRUNCATE);
			server_->SendData(sendData_);
		}
		break;
	}
}

// 受け取った画像を追加する
int ServerScene::AddRecvImage(PACKET recv)
{
	auto it = std::find(hImageList_.begin(), hImageList_.end(), recv.number);

	// 見つからなかった　受信したことがない画像なので追加する
	if (it == hImageList_.end())
	{
		hImageList_.push_back(recv.number);
		return (int)hImageList_.size();
	}

	// すでに追加している画像だったなら-1を返す
	return -1;
}

int ServerScene::AddPlayerName(std::string name)
{
	// すでに同じ名前が使用されていたら、追加できない
	auto findName = std::find(playerName_.begin(), playerName_.end(), name);
	// 見つからなかった場合
	if (findName == playerName_.end())
	{
		playerName_.push_back(name);
		playerCount_ += 1;
		return 1;
	}

	return -1;
}

