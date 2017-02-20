// socktest.cpp : Defines the entry point for the console application.
//
// Самій простейший Сервер, если это можно так назвать... :)


#include "stdafx.h"
#include "winsock2.h"

#define		MAX_CONN	10
#define		MSG_LEN		128

int main(int argc, char* argv[])
{
	SOCKET		s, new_conn;
	WSADATA		ws;
	sockaddr_in	sock_bind, new_ca;
	int			new_len, i = 0;
	char		buff [MSG_LEN];

	// Init 
	if (FAILED (WSAStartup (0x0002, &ws) ) ) return E_FAIL;
	
	// Создаём сокет
	if (INVALID_SOCKET == (s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP) ) )

	// Выполняем привязку
	ZeroMemory (&sock_bind, sizeof (sock_bind));
	sock_bind.sin_family			= PF_INET;
	sock_bind.sin_addr.S_un.S_addr	= htonl (INADDR_ANY);		// Любой адрес расчитываем на "прямую видимость" :)
																// Можете указать адрес непосредственно
	sock_bind.sin_port				= htons (1234);				// Порт 1234
	if (SOCKET_ERROR == bind (s, (sockaddr* ) &sock_bind, sizeof (sock_bind) ) )
	{
		return E_FAIL;
	}

	// Устанавливаем "слушающий" режим для сокета
	if (FAILED (listen (s, MAX_CONN) ) )
	{
		return E_FAIL;
	}	

	printf ("Wait for incoming connections...\n");

	while (i < MAX_CONN)
	{
		ZeroMemory (&new_ca, sizeof (new_ca));
		new_len = sizeof (new_ca);

		if (FAILED (new_conn = accept (s, (sockaddr* ) &new_ca, &new_len) ) )
		{
			// Error
			printf ("\n Accept failed on %d", i);
			return E_FAIL;
		}
		else 
			{
				// Выводим онформацию о клиенте
				printf ("New Cilent... Numba %d\n", i);
				printf ("Client IP %s, Client Port %d\n", inet_ntoa ((in_addr) new_ca.sin_addr), ntohs (new_ca.sin_port) );
				
				// Получаем сообщение от клиента
				int msg_len;
				if (FAILED (msg_len = recv (new_conn, (char* ) &buff, MSG_LEN, 0) ) )
					return E_FAIL;
				
				// Печатем сообщение.
				for (int c = 0; c<msg_len; c++)
					printf ("%c", buff [c]);

				// Зкарываем соединение (пока таким вот макаром :) )
				closesocket (new_conn);
			}

		i++;

	}

	printf ("\n\nDone!");

	return 0;
}

