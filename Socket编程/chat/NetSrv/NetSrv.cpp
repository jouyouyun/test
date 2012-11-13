// NetSrv.cpp : Defines the entry point for the console application.
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
	
	char recvBuf[1000];//接受端数据
	char sendBuf[1000];//发送端数据
	char tempBuf[1000];//交换区数据

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while(1)
	{
	//等待并接受数据
	recvfrom(sockSrv, recvBuf ,1000, 0, (SOCKADDR*)&addrClient, &len);
	if('q' ==recvBuf[0] )
	{
		sendto(sockSrv,"q",strlen("q")+1, 0, (SOCKADDR*)&addrClient,len);
		printf("Chat end!");
		break;
	}
	sprintf(tempBuf, "%s say:%s", inet_ntoa(addrClient.sin_addr), recvBuf);

	printf("%s\n", tempBuf);
	//发送数据
	printf("Please input data:\n");
	gets(sendBuf);
	sendto(sockSrv,sendBuf,strlen(sendBuf)+1,0 ,(SOCKADDR*)&addrClient,len);
	}
	//关闭套接字
	closesocket(sockSrv);
	//程序需要连接ws2_32.lib文件 project--link---Object/libary modules添加ws2_32.lib
	return 0;
}
