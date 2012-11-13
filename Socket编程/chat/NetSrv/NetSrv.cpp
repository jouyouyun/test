// NetSrv.cpp : Defines the entry point for the console application.
//

/******************************************************************************
**File:			SOCKSrv.cpp
**Created:		July 30th 2009
**Author:		FreeKing
**Description:		����socket��̻���UDPЭ��Ŀͻ���
*******************************************************************************/
#include "stdafx.h"
#include <Winsock2.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	//�����׽��ֿ�
	WORD wVersionRequested;//WinSock��İ汾��
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if( err != 0)
	{
		return 1 ;
	}
	
	if( LOBYTE( wsaData.wVersion) != 1 || HIBYTE( wsaData.wVersion) !=1 )
	{
		WSACleanup();
		return -2;
	}
	//�����׽���
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	
	//���׽���
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	
	char recvBuf[1000];//���ܶ�����
	char sendBuf[1000];//���Ͷ�����
	char tempBuf[1000];//����������

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while(1)
	{
	//�ȴ�����������
	recvfrom(sockSrv, recvBuf ,1000, 0, (SOCKADDR*)&addrClient, &len);
	if('q' ==recvBuf[0] )
	{
		sendto(sockSrv,"q",strlen("q")+1, 0, (SOCKADDR*)&addrClient,len);
		printf("Chat end!");
		break;
	}
	sprintf(tempBuf, "%s say:%s", inet_ntoa(addrClient.sin_addr), recvBuf);

	printf("%s\n", tempBuf);
	//��������
	printf("Please input data:\n");
	gets(sendBuf);
	sendto(sockSrv,sendBuf,strlen(sendBuf)+1,0 ,(SOCKADDR*)&addrClient,len);
	}
	//�ر��׽���
	closesocket(sockSrv);
	//������Ҫ����ws2_32.lib�ļ� project--link---Object/libary modules���ws2_32.lib
	return 0;
}
