
#include <stdio.h>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#include <conio.h>


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wsock32.lib")



void sweety_output(char* res, int i, int ii){
	int num_flag = 0;
	for (; i < ii; i++)
	{
		if (res[i] != 0 || num_flag == 1)
		{
			std::cout << static_cast<int> (res[i]);
			num_flag = 1;
		}
	}
	std::cout << std::endl;
}


void ress_(char* res)
{
	std::cout << "Version \x0\x1\x2\x3: ";
	for (int i = 0; i < 4; i++)
	{
		std::cout << "/x" << static_cast<int> (res[i]); //¬от здесь € использую €вное преобразование типа
	}
	std::cout << std::endl;


	std::cout << "Ident: ";
	for (int i = 4; i < 12; i++)
	{
		std::cout << (int) res[i] << "."; // ј вот здесь просто вывожу как int
	}
	std::cout << std::endl;


	std::cout << "Currently connected users count: ";
	sweety_output(res, 12, 16);

	std::cout << "Maximum users (slot count): ";
	sweety_output(res, 16, 20);

	std::cout << "Allowed bandwidth: ";
	sweety_output(res, 20, 24);
}

int main()
{
	WSADATA ws; 
	WSAStartup(MAKEWORD(2, 0), &ws); 

	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM - UDP сокет 

	std::cout << "Server's address: ";
	char addr[256];
	std::cin.getline(addr, 256, '\n');
	std::cout << "Server's port: ";
	int port;
	std::cin >> port;
	//standart 64738

	//std::cin >> addr;
	sockaddr_in s_a;
	//std::string host = "domenname";
	hostent *name = gethostbyname(addr); // THIS

	ZeroMemory(&s_a, sizeof(s_a));
	s_a.sin_family = AF_INET;
	s_a.sin_addr = *(struct in_addr *) name->h_addr_list[0];  // AND THIS
	//s_a.sin_addr.s_addr = inet_addr("ip addr");
	s_a.sin_port = htons(port);

	connect(s, (sockaddr *)&s_a, sizeof (s_a));


	char buf[12] = { 0, 0, 0, 0, 122, 0, 120, 7, 111, 1, 120, 0, };

	send(s, buf, 12, 0);


	int actual_len;

	char mdaa[24];
	
	if ((actual_len = recv(s, mdaa, sizeof(mdaa), 0)) == 0)  { std::cout << "No no no"; }

	std::cout << "";

	ress_(mdaa);
	_getch();

	return 0;
}
