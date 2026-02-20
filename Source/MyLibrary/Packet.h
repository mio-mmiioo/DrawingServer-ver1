#pragma once
#include <WinSock2.h>
#include <string>

// 受信したいデータの中身
static struct PACKET
{
    char str[256];
    int hImage;
};

// バイトオーダーを変換する関数
// PACKET内を書き換えたら書き換える必要がある
static PACKET ByteSwapPacket(PACKET data)
{
    PACKET ret;
    memcpy(ret.str, data.str, sizeof(ret.str));
    ret.hImage = htonl(data.hImage);
    return ret;
}

