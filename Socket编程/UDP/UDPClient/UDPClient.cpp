// UDPClient.cpp : Defines the entry point for the console application.
//
// TCPClient.cpp : Defines the entry point for the console application.
//
/******************************************************************************
**File:			SOCKSrv.cpp
**Created:		July 30th 2009
**Author:		FreeKing
**Description:		关于socket编程基于UDP协议的客户端
*******************************************************************************/
#include "stdafx.h"
#include <Winsock2.h>
#include <stdio.h>
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
	SOCKET sockClient = socket( AF_INET,SOCK_DGRAM, 0 );
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);



	//发送数据
	sendto(sockClient, "This is Dong Liu'world", strlen( "This is Dong Liu'world" )+1, 0 ,(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	
	//关闭套接字
	closesocket(sockClient);
	WSACleanup();
	return 0;
}
