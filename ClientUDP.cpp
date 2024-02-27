#include "ClientUDP.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Engine/Input.h"

#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;
// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;

using std::cin;
using std::cout;
using std::endl;

// WinSock�̏�����
int InitWinSock();

int main()
{
	cout << "Chat Client" << endl;

	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		cout << "Error: InitWinSock ( ErrorCode:" << ret << " )" << endl;
		return 1;	// �I��
	}
	cout << "Success: InitWinSock" << endl;


	// UDP�\�P�b�g�̍쐬
	int sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		cout << "Error: socket ( ErrorCode:" << WSAGetLastError() << " )" << endl;
		return 1;	// ���[���I
	}
	cout << "Success: socket" << endl;


	// ����ƂȂ�T�[�o�̃\�P�b�g�A�h���X���̊��蓖��
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
		char buff[MESSAGELENGTH];			// ����M���b�Z�[�W�̊i�[�̈�
		struct sockaddr_in fromAddr;		// ���M���A�h���X�̊i�[�̈�
		int fromlen = sizeof(fromAddr);		// fromAddr�̃T�C�Y


		// ���M�p���b�Z�[�W�̓���
		cout << "Input message : ";
		cin >> buff;

		// ���M�I
		ret = sendto(sock, buff, strlen(buff), 0, (struct sockaddr*)&toAddr, sizeof(toAddr));
		if (ret != strlen(buff))
		{
			cout << "Error: sendto ( ErrorCode:" << WSAGetLastError() << " )" << endl;
			return 1;
		}

		// ��M�҂�
		cout << "wait..." << endl;

		// ��M	\0�͑����Ă��Ȃ��o�[�W����
		ret = recvfrom(sock, buff, sizeof(buff) - 1, 0, (struct sockaddr*)&fromAddr, &fromlen);
		if (ret < 0)
		{
			cout << "Error: recvfrom ( ErrorCode:" << WSAGetLastError() << " )" << endl;
			return 1;
		}
		buff[ret] = '\0';	// �I�[�L���ǉ�
		cout << "Receive message : " << buff << endl;
	}

	return 0;
}

// WinSock�̏�����
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
