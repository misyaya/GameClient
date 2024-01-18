#include "ClientUDP.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;
// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;

// WinSock�̏�����
int InitWinSock();

int main()
{
	std::cout << "Chat Client" << std::endl;

	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		std::cout << "Error: InitWinSock ( ErrorCode:" << ret << " )" << std::endl;
		return 1;	// ���[���I
	}
	std::cout << "Success: InitWinSock" << std::endl;


	// UDP�\�P�b�g�̍쐬
	int sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		std::cout << "Error: socket ( ErrorCode:" << WSAGetLastError() << " )" << std::endl;
		return 1;	// ���[���I
	}
	std::cout << "Success: socket" << std::endl;


	// ����ƂȂ�T�[�o�̃\�P�b�g�A�h���X���̊��蓖��
	std::string serverIpv4Address;
	std::cout << "Input Server IPv4 Address : ";
	std::cin >> serverIpv4Address;
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
		std::cout << "Input message : ";
		std::cin >> buff;

		// ���M�I
		ret = sendto(sock, buff, strlen(buff), 0, (struct sockaddr*)&toAddr, sizeof(toAddr));
		if (ret != strlen(buff))
		{
			std::cout << "Error: sendto ( ErrorCode:" << WSAGetLastError() << " )" << std::endl;
			return 1;
		}

		// ��M�҂�
		std::cout << "wait..." << std::endl;

		// ��M	\0�͑����Ă��Ȃ��o�[�W����
		ret = recvfrom(sock, buff, sizeof(buff) - 1, 0, (struct sockaddr*)&fromAddr, &fromlen);
		if (ret < 0)
		{
			std::cout << "Error: recvfrom ( ErrorCode:" << WSAGetLastError() << " )" << std::endl;
			return 1;
		}
		buff[ret] = '\0';	// �I�[�L���ǉ�
		std::cout << "Receive message : " << buff << std::endl;
	}

	return 0;
}

// WinSock�̏�����
int InitWinSock()
{
	WSADATA wsaData;
	return WSAStartup(MAKEWORD(2, 2), &wsaData);
}