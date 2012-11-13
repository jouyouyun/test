// TCPsrv.cpp : Defines the entry point for the console application.
//
/******************************************************************************
**File:			SOCKSrv.cpp
**Created:		July 30th 2009
**Author:		FreeKing
**Description:		����socket��̻���TCP/IPЭ��ķ�������
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
	//�������ڼ������׽���
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	
	//���׽���
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	//���׽�����Ϊ����ģʽ��׼�����ܿͻ�����
	listen(sockSrv, 5);//5Ϊ�ȴ��������е����ֵ
	
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	
	while(1)
	{
		//�ȴ��ͻ�������
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//sockConn�������ӵ��׽���
		char sendBuf[100];
		sprintf( sendBuf, "Welcome %s to the FreeKing World", inet_ntoa(addrClient.sin_addr));
		
		//��������
		send( sockConn, sendBuf, strlen(sendBuf)+1, 0 );
		char recvBuf[100];
		//��������
		recv( sockConn, recvBuf, 100, 0 );
		//��ӡ���ܵ�����
		printf( "%s\n", recvBuf);
		//�ر��׽���
		closesocket(sockConn);
	}
	
	//������Ҫ����ws2_32.lib�ļ� project--link---Object/libary modules���ws2_32.lib
	return 0;
}
