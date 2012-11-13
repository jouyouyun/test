// TCPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Winsock2.h>
#include <stdio.h>


/******************************************************************************
**File:			SOCKSrv.cpp
**Created:		July 30th 2009
**Author:		FreeKing
**Description:		����socket��̻���TCP/IPЭ��Ŀͻ��˶�
*******************************************************************************/

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
		return -1 ;
	}
	
	if( LOBYTE( wsaData.wVersion) != 1 || HIBYTE( wsaData.wVersion) !=1 )
	{
		WSACleanup();
		return -2;
	}
	//�����׽���
	SOCKET sockClient = socket( AF_INET,SOCK_STREAM, 0 );
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	//�������������������
	connect( sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//��������
	char recvBuf[100];
	recv( sockClient, recvBuf, 100, 0 );
	printf( "%s\n", recvBuf );

	//��������
	send(sockClient, "This is Dong Liu", strlen( "This is Dong Liu" )+1, 0 );
	
	//�ر��׽���
	closesocket(sockClient);
	WSACleanup();
	return 0;
}
