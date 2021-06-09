#pragma comment(lib, "ws2_32.lib")
#define HAVE_STRUCT_TIMESPEC
#define _CRT_SECURE_NO_WARNINGS
#include <winsock.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void* ReceiveFromServer(void* param)
{
	int bytes;
	SOCKET server = (SOCKET)param;
	char* receive = (char*)calloc(1024, sizeof(char));
	while (1)
	{
		bytes = recv(server, receive, 1024, 0);
		if (bytes > 0)
		{
			receive[bytes] = 0;
			printf("%s\n", receive);
		}
	}
	return (void*)0;
}

void StartChatting()
{
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (client == INVALID_SOCKET)
	{
		printf("Error create socket\n");
		return;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(1111); //the same as in server
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //special look-up address
	if (connect(client, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Can't connect to server\n");
		closesocket(client);
		return;
	}
	
	char* transmit = (char*)calloc(1024, sizeof(char));
	char* receive = (char*)calloc(1024, sizeof(char));

	pthread_t mythread;
	int status = pthread_create(&mythread, NULL, ReceiveFromServer, (void*)client);
	pthread_detach(mythread);

	while (1)
	{
		fgets(transmit, 1024, stdin);

		fflush(stdin);
		Sleep(500);
	}

	closesocket(client);
}

int main()
{
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(1, 1), &wsd) != 0)
	{
		printf("Can't connect to socket lib");
		return 1;
	}
	
	StartChatting();

	return 0;
}

