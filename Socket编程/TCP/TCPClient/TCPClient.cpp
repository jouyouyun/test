// TCPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Winsock2.h>
#include <stdio.h>


/******************************************************************************
**File:			SOCKSrv.cpp
**Created:		July 30th 2009
**Author:		FreeKing
**Description:		关于socket编程基于TCP/IP协议的客户端端
*******************************************************************************/

int main(int argc, char* argv[])
{
	
	//加载套接字库
	WORD wVersionRequested;//WinSock库的版本号
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
	//创建套接字
	SOCKET sockClient = socket( AF_INET,SOCK_STREAM, 0 );
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	//向服务器发出连接请求
	connect( sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//接受数据
	char recvBuf[100];
	recv( sockClient, recvBuf, 100, 0 );
	printf( "%s\n", recvBuf );

	//发送数据
	send(sockClient, "This is Dong Liu", strlen( "This is Dong Liu" )+1, 0 );
	
	//关闭套接字
	closesocket(sockClient);
	WSACleanup();
	return 0;
}
