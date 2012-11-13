// TCPsrv.cpp : Defines the entry point for the console application.
//
/******************************************************************************
**File:			SOCKSrv.cpp
**Created:		July 30th 2009
**Author:		FreeKing
**Description:		关于socket编程基于TCP/IP协议的服务器端
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
	//创建用于监听的套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	
	//绑定套接字
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	//将套接字设为监听模式，准备接受客户请求
	listen(sockSrv, 5);//5为等待连续队列的最大值
	
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	
	while(1)
	{
		//等待客户请求到来
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//sockConn建立连接的套接字
		char sendBuf[100];
		sprintf( sendBuf, "Welcome %s to the FreeKing World", inet_ntoa(addrClient.sin_addr));
		
		//发送数据
		send( sockConn, sendBuf, strlen(sendBuf)+1, 0 );
		char recvBuf[100];
		//接受数据
		recv( sockConn, recvBuf, 100, 0 );
		//打印接受的数据
		printf( "%s\n", recvBuf);
		//关闭套接字
		closesocket(sockConn);
	}
	
	//程序需要连接ws2_32.lib文件 project--link---Object/libary modules添加ws2_32.lib
	return 0;
}
