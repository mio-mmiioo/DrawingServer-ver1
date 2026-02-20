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
	void SendData();	 // データの送信

	PACKET GetRecvData() { return recvData_; } // 受け取ったデータの取得

private:
	void ListenSocket(); // socketの受信
	void ReceiveData();	 // データの受信
	void RemoveSocket(); // socketの削除

	int portNumber_;				// ポート番号
	SOCKET listenSocket_;			// リスンソケット
	std::vector<SOCKET> sockets_;	// クライアントのソケット配列

	PACKET sendData_; // 送信データ
	PACKET recvData_; // 受信データ
};
