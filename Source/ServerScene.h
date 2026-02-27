#pragma once
#include "MyLibrary/Scene.h"
#include <vector>
#include "MyLibrary/Packet.h"

class Server;

class ServerScene : public Scene
{
public:
	ServerScene();
	~ServerScene() override;
	void Update() override;
	void GetDataUpdate(); // データを取得したときに行われる更新処理

private:
	Server* server_;
	PACKET sendData_; // 送信データ
	PACKET recvData_; // 受信データ
	std::vector<int> useNumber;
	char name[256];
	int playerCount; // 各部屋にいるプレイヤー
};