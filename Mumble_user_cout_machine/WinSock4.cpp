// WinSock4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock.h"
#include "stdlib.h"


const WORD WINSOCK_VERSION = 0x0101;

#define DEFAULT_PROTOCOL 0
#define PORT_ADDR 80



void StartWinSock();
void StopWinSock();
void WaitSocket();
void SocketGetHostName();
void CreateSocket();
void CloseScoket();

SOCKET servsocket;


void main()
{
	StartWinSock();
	WaitSocket();
	StopWinSock();
}

void WaitSocket()
{
	SocketGetHostName();
	CreateSocket();
	SOCKADDR_IN socketaddr;
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_addr.s_addr  = INADDR_ANY; 
	socketaddr.sin_port = PORT_ADDR;

	if (bind(servsocket,(LPSOCKADDR)&socketaddr,sizeof(socketaddr)) == SOCKET_ERROR)
	{
		printf("Error bind socket");
		exit(1);
	}
	else printf("God bind socket !!!!!!\n");
	
	CloseScoket();
}

void CloseScoket()
{
	closesocket(servsocket);
}

void CreateSocket()
{
	servsocket = socket(PF_INET,SOCK_STREAM,DEFAULT_PROTOCOL);
	if (servsocket==INVALID_SOCKET) 
	{
		printf("Error create socket :-(\n");
		exit(1);
	}
}

void SocketGetHostName()
{
	char chInfo[64];

	if (gethostname(chInfo,sizeof(chInfo)))
	{
		printf("Not local host\n");
		exit(1);
	}
	else
	{	
		printf(chInfo);
		printf(" GetHostName OK !!!!!\n");
	}
}

void StopWinSock()
{
	if (WSACleanup()) printf("Error Cleapir\n");
	else printf("Cleapir Good !!!!!\n");
}

void StartWinSock()
{
	WSADATA wsaData;
	if (WSAStartup(WINSOCK_VERSION, &wsaData)) 
	{
		printf ("winsock not bi initialized !\n");
		WSACleanup();
	}
	else printf("Winsock initial OK !!!!\n");
}