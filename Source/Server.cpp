#include "Server.h"
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include "DxLib.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

unsigned long cmdarg = 0x01;

Server::Server(int portNumber)
{
    portNumber_ = portNumber;
}

Server::~Server()
{

}

int Server::Init()
{
    // WinSock2.2 初期化
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printfDx("Error : WSAStartup\n");
        return -1;
    }
    printfDx("Success : WSAStartup\n");

    // TCPリスンソケットの作成
    listenSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket_ == INVALID_SOCKET)
    {
        printfDx("Error : socket\n");
        return -1;
    }
    printfDx("Success : socket\n");

    // ノンブロッキング設定
    ioctlsocket(listenSocket_, FIONBIO, &cmdarg);

    // 固定アドレスの割り当て
    SOCKADDR_IN bindSocketAddress;
    memset(&bindSocketAddress, 0, sizeof(bindSocketAddress));
    bindSocketAddress.sin_family = AF_INET;
    bindSocketAddress.sin_port = htons(portNumber_);
    bindSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenSocket_, (SOCKADDR*)&bindSocketAddress, sizeof(bindSocketAddress)) == SOCKET_ERROR)
    {
        printfDx("Error : bind\n");
        return -1;
    }
    printfDx("Success : bind\n");

    // リスン状態に設定
    if (listen(listenSocket_, SOMAXCONN) == SOCKET_ERROR)
    {
        printfDx("Error : listen");
        return -1;
    }
    printfDx("Success : listen\n");

    return 0;
}

void Server::Update()
{
    ListenSocket();
    ReceiveData();
    RemoveSocket();
}

void Server::ListenSocket()
{
    // 接続受け入れ
    SOCKADDR_IN clientAddr;
    int addressLength = sizeof(SOCKADDR_IN);
    int tmpSocket = accept(listenSocket_, (SOCKADDR*)&clientAddr, &addressLength);
    if (tmpSocket > 0)
    {
        ioctlsocket(listenSocket_, FIONBIO, &cmdarg);
        sockets_.push_back(tmpSocket);
    }
}

void Server::SendData()
{
    for (auto s : sockets_)
    {
        if (s == -1) continue;
        // 送信
        int sendRet = send(s, (char*)&sendData_, sizeof(sendData_), 0);
        if (sendRet == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                continue;
            }
        }
    }
}

void Server::ReceiveData()
{
    // 受信処理
    for (auto s : sockets_)
    {
        int ret = recv(s, (char*)&recvData_, sizeof(PACKET), 0);
        if (ret > 0)
        {
            recvData_ = ByteSwapPacket(recvData_);
            printfDx(recvData_.str);
            printfDx(" : %d\n", recvData_.hImage);
            sendData_ = ByteSwapPacket(recvData_);
            SendData();
        }
        else
        {
            if (WSAGetLastError() == WSAECONNRESET)
            {
                printfDx("shutdown\n");
                shutdown(s, SD_BOTH);
                closesocket(s);
                s = -1;
            }
        }
    }
}

void Server::RemoveSocket()
{
    // 切断されたソケットの削除
    sockets_.erase(
        remove_if(sockets_.begin(), sockets_.end(), [](SOCKET sock)
            { return sock == -1; }),
        sockets_.end());
}
