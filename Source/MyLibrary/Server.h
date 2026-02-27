#pragma once
#include <vector>
#include "Packet.h"

class Server
{
public:
	Server(int portNumber); // （ポート番号）
	~Server();		// デストラクタ
	int Init();		// 初期化
	void Update();	// 更新処理
	void SendData();						// データの送信
	void SendData(PACKET data);				// 指定したデータの送信
	void ListenSocket(); // socketの受信
	void ReceiveData();	 // データの受信
	void RemoveSocket(); // socketの削除

	void AddPeople(char name); // メンバーの追加
	PACKET GetRecvData() { return recvData_; } // 受け取ったデータの取得

private:


	int portNumber_;				// ポート番号
	SOCKET listenSocket_;			// リスンソケット
	std::vector<SOCKET> sockets_;	// クライアントのソケット配列

	PACKET sendData_; // 送信データ
	PACKET recvData_; // 受信データ


	std::vector<char> name_; // 参加者の名前
};
