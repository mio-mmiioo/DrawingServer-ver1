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
	int AddRecvImage(PACKET recv); // 受信した画像データを配列に追加する -1 → 追加できなかった
	
	Server* server_;
	PACKET sendData_; // 送信データ
	PACKET recvData_; // 受信データ
	std::vector<int> useNumber_;
	//char name[256];
	int playerCount_; // 各部屋にいるプレイヤー
	int phaseCount_; // 各部屋のフェーズの回数
	
	std::vector<int> hImageList_; // 受信した画像データを保存する配列
};