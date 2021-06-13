#define _CRT_SECURE_NO_WARNINGS
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#define MAX_CLIENTS 11
#include "funcs.h"

pthread_mutex_t mutex;
pthread_mutex_t mutex_file;

CLIENT clients[MAX_CLIENTS];
CHAT rooms[MAX_CLIENTS];
int clientsNum = 0;
int roomsNum = 0;

int FindClient(int id)
{
	for (int i = 0; i < clientsNum; i++)
	{
		if (clients[i].id == id)
			return i;
	}
	return -1;
}

void CreateRoom(const char* name, int client)
{
	strcpy(rooms[roomsNum].name, name);
	sprintf(rooms[roomsNum].filename, "%s.txt", name);
	if (client > -1)
		strcpy(rooms[roomsNum].admin, clients[client].name);
	else
		strcpy(rooms[roomsNum].admin, "\0");
	roomsNum++;
}

int SignIn(SOCKET client)
{
	int bytes;
	char* login = (char*)calloc(256, sizeof(char));
	char* password = (char*)calloc(256, sizeof(char));

	send(client, "WELCOME TO THE SERVER!\n", strlen("WELCOME TO THE SERVER!\n"), 0);
	int flag;

	while (1)
	{
		int flag = 0;
		send(client, "Enter your login: ", strlen("Enter your login: "), 0);
		bytes = recv(client, login, 256, 0);
		login[bytes] = 0;

		send(client, "Enter your password: ", strlen("Enter your password: "), 0);
		bytes = recv(client, password, 256, 0);
		password[bytes] = 0;

		if (bytes > 0)
		{
			int rows;
			char** base = ReadData("clientbase.txt", &rows);
			char* login_format = (char*)calloc(strlen(login) + 10, sizeof(char));
			char* password_format = (char*)calloc(strlen(login) + 10, sizeof(char));

			sprintf(login_format, "login:%s\n", login);
			sprintf(password_format, "password:%s\n", password);

			for (int i = 0; i < rows; i++)
			{
				if (strcmp(base[i], login_format) == 0)
				{
					if (strcmp(base[i + 1], password_format) == 0)
					{
						int index = FindClient(i);
						clients[index].status = 1;
						clients[index].socket = client;
						clients[index].curChat = 0;
						send(client, "Welcome to the main chat!\n", strlen("Welcome to the main chat!\n"), 0);
						
						pthread_mutex_lock(&mutex);
						printf("%s logged in\n", clients[index].name);
						pthread_mutex_unlock(&mutex);

						return index;
					}
					else
					{
						flag = 1;
						send(client, "Wrong password. Try again!", strlen("Wrong password. Try again!"), 0);
						break;
					}
				}
			}
			
			if (flag < 1)
			{
				clients[clientsNum].id = rows - 1;
				clients[clientsNum].socket = client;
				clients[clientsNum].friendsNum = 0;
				clients[clientsNum].status = 1;
				clients[clientsNum].curChat = 0;
				clients[clientsNum].chatsNum++;
				strcpy(clients[clientsNum].name, login);
				clientsNum++;

				pthread_mutex_lock(&mutex);
				printf("%s registered\n", clients[clientsNum - 1].name);
				pthread_mutex_unlock(&mutex);

				AddData(base, login_format, &rows);
				AddData(base, password_format, &rows);
				AddData(base, "\n", &rows);
				
				pthread_mutex_lock(&mutex_file);
				WriteData("clientbase.txt", rows, base);
				pthread_mutex_unlock(&mutex_file);

				send(client, "Welcome to the main chat!\n", strlen("Welcome to the main chat!\n"), 0);

				return (clientsNum - 1);
			}
		}
	}
}

void* ClientService(void* param)
{
	SOCKET client = (SOCKET)param;

	int index = SignIn(client);

	char* receive = (char*)calloc(1024, sizeof(char));
	char* transmit = (char*)calloc(1024, sizeof(char));
	char* date = (char*)calloc(50, sizeof(char));
	int bytes;

	sprintf(transmit, "%s joined\n", clients[index].name);
	for (int i = 0; i < clientsNum; i++)
		if (i != index && clients[i].curChat == clients[index].curChat && clients[i].status == 1)
			send(clients[i].socket, transmit, strlen(transmit), 0);

	char* hist = ReadHistory(rooms[clients[index].curChat].filename);
	send(client, hist, strlen(hist), 0);

	while (1)
	{
		bytes = recv(client, receive, 1024, 0);

		if (bytes > 0)
		{
			receive[bytes] = 0;

			int size;
			char** history = ReadData(rooms[clients[index].curChat].filename, &size);

			time_t seconds = time(NULL);
			tm* info = localtime(&seconds);

			sprintf(date, "Delivered on (%d:%d, %d.%d.%d)\n", info->tm_hour, info->tm_min,
				info->tm_mday, info->tm_mon + 1, info->tm_year + 1900);

			sprintf(transmit, "%s: %s%s", clients[index].name, receive, date);
			AddData(history, transmit, &size);
			AddData(history, "\n", &size);

			pthread_mutex_lock(&mutex_file);
			WriteData(rooms[clients[index].curChat].filename, size, history);
			pthread_mutex_unlock(&mutex_file);

			for (int i = 0; i < clientsNum; i++)
			{
				if (i != index && clients[i].curChat == clients[index].curChat && clients[i].status == 1)
					send(clients[i].socket, transmit, strlen(transmit), 0);
				if (i == index)
					send(clients[index].socket, date, strlen(date), 0);
			}
		}
	}

	return (void*)0;
}

int CreateServer()
{
	SOCKET server, client;
	sockaddr_in localaddr, clientaddr;
	int size;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (server == INVALID_SOCKET)
	{
		printf("Error create server\n");
		return 1;
	}
	localaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(1111);//port number is for example, must be more than 1024
	if (bind(server, (sockaddr*)&localaddr, sizeof(localaddr)) == SOCKET_ERROR)
	{
		printf("Can't start server\n");
		return 2;
	} else
	{
		printf("Server is started\n");
	}
	
	listen(server, MAX_CLIENTS);
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex_file, NULL);

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		clients[i].id = -1;
		clients[i].curChat = -1;
		clients[i].friendsList = (int*)calloc(MAX_CLIENTS, sizeof(int));
		clients[i].name = (char*)calloc(30, sizeof(char));
		clients[i].friendsNum = 0;
		clients[i].availableChats = (int*)calloc(MAX_CLIENTS, sizeof(int));
		clients[i].chatsNum = 0;

		rooms[i].name = (char*)calloc(30, sizeof(char));
		rooms[i].admin = (char*)calloc(30, sizeof(char));
		rooms[i].filename = (char*)calloc(30, sizeof(char));
	}

	CreateRoom("main", -1);

	while (1)
	{
		size = sizeof(clientaddr);
		client = accept(server, (sockaddr*)&clientaddr, &size);

		if (client == INVALID_SOCKET)
		{
			printf("Error accept client\n");
			continue; 
		} else
		{
			printf("Client is accepted\n");
		}
		pthread_t mythread;
		int status = pthread_create(&mythread, NULL, ClientService, (void*)client);
		pthread_detach(mythread);
	}
	pthread_mutex_destroy(&mutex_file);
	pthread_mutex_destroy(&mutex);
	printf("Server is stopped\n");
	closesocket(server);
	return 0;
}

int main()
{
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(1, 1), &wsd) == 0)
	{
		printf("Connected to socket lib\n");
	} else
	{
		return 1;
	}
	return CreateServer();
}

