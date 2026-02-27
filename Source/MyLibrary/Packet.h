#pragma once
#include <WinSock2.h>
#include <vector>
#include <string>
#include <map>

// 受信したデータの種類
enum PACKET_DATA_TYPE
{
	MAKE_ROOM,		// 部屋立ち上げ
	ENTER_ROOM,		// 入室
	END_MAKE_ROOM,	// 部屋作成完了
	REGISTER_NAME,	// 名前の登録
	MAX_PACKET_TYPE
};

// 受信したいデータの中身
struct PACKET
{
	char dataType[256];
	char playerName[256];
	int number;
};

namespace Packet
{
	void Init(); // 初期化

	// バイトオーダーを変換する関数
	// PACKET内を書き換えたら書き換える必要がある
	PACKET ByteSwapPacket(PACKET data);

	// 追加されたプレイヤーの名前を保存しておく配列
	// 追加できた場合 → 1, 追加できなかった場合 → -1
	int AddPlayerName(std::string name);

	extern std::map<std::string, PACKET_DATA_TYPE> dataName;	// データの名前, データの種類
}

