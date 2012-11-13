// UDPSrv.cpp : Defines the entry point for the console application.
//

// TCPsrv.cpp : Defines the entry point for the console application.
//
/******************************************************************************
**File:			SOCKSrv.cpp
**Created:		July 30th 2009
**Author:		FreeKing
**Description:		关于socket编程基于UDP协议的服务器端
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
		return 1 ;
	}
	
	if( LOBYTE( wsaData.wVersion) != 1 || HIBYTE( wsaData.wVersion) !=1 )
	{
		WSACleanup();
		return -2;
	}
	//创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	
	//绑定套接字
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	
	//等待并接受数据
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[100];
	recvfrom(sockSrv, recvBuf ,100, 0, (SOCKADDR*)&addrClient, &len);
	printf("%s\n", recvBuf);
	
	//关闭套接字
	closesocket(sockSrv);
	
	
	//程序需要连接ws2_32.lib文件 project--link---Object/libary modules添加ws2_32.lib
	return 0;
}
