#include "ClientUDP.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Engine/Input.h"

#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVERPORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;

using std::cin;
using std::cout;
using std::endl;

// WinSockの初期化
int InitWinSock();

int main()
{
	cout << "Chat Client" << endl;

	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		cout << "Error: InitWinSock ( ErrorCode:" << ret << " )" << endl;
		return 1;	// 終了
	}
	cout << "Success: InitWinSock" << endl;


	// UDPソケットの作成
	int sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		cout << "Error: socket ( ErrorCode:" << WSAGetLastError() << " )" << endl;
		return 1;	// おーわり！
	}
	cout << "Success: socket" << endl;


	// 宛先となるサーバのソケットアドレス情報の割り当て
	std::string serverIpv4Address;
	cout << "Input Server IPv4 Address : ";
	cin >> serverIpv4Address;
	struct sockaddr_in toAddr;
	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(SERVERPORT);
	inet_pton(AF_INET, serverIpv4Address.c_str(), &toAddr.sin_addr.s_addr);


	while (true)
	{
		char buff[MESSAGELENGTH];			// 送受信メッセージの格納領域
		struct sockaddr_in fromAddr;		// 送信元アドレスの格納領域
		int fromlen = sizeof(fromAddr);		// fromAddrのサイズ


		// 送信用メッセージの入力
		cout << "Input message : ";
		cin >> buff;

		// 送信！
		ret = sendto(sock, buff, strlen(buff), 0, (struct sockaddr*)&toAddr, sizeof(toAddr));
		if (ret != strlen(buff))
		{
			cout << "Error: sendto ( ErrorCode:" << WSAGetLastError() << " )" << endl;
			return 1;
		}

		// 受信待ち
		cout << "wait..." << endl;

		// 受信	\0は送ってこないバージョン
		ret = recvfrom(sock, buff, sizeof(buff) - 1, 0, (struct sockaddr*)&fromAddr, &fromlen);
		if (ret < 0)
		{
			cout << "Error: recvfrom ( ErrorCode:" << WSAGetLastError() << " )" << endl;
			return 1;
		}
		buff[ret] = '\0';	// 終端記号追加
		cout << "Receive message : " << buff << endl;
	}

	return 0;
}

// WinSockの初期化
int InitWinSock()
{
	WSADATA wsaData;
	return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

void ClientUDP::GamePlay()
{
	for(int i = 0; i< 5; i++)
	{
		//
		if (Input::IsKeyDown(DIK_UP))
		{
			number[i] = 1;
		}

		if (Input::IsKeyDown(DIK_DOWN))
		{
			number[i] = 2;
		}

		if (Input::IsKeyDown(DIK_DOWN))
		{
			number[i] = 3;
		}

		if (Input::IsKeyDown(DIK_DOWN))
		{
			number[i] = 4;
		}

	}
}
