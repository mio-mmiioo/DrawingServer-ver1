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
	CHANGE_NAME,	// 名前の登録
	START_PLAY,     // プレイ画面開始
	PLAYER_COUNT,	// プレイヤーの人数
	START_GAME,		// ゲーム再開
	STOP_GAME,      // ゲーム停止中
	START_RESULT,	// リザルト画面開始
	SEND_IMAGE,		// 回答・お題の画像
	START_MATCHING, // マッチング画面開始
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

