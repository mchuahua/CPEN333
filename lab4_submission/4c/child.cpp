//child
//taken from docs.microsoft.com
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <vector>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;

int __cdecl main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	const char *yescansee = "yes can see";
	const char *nocansee = "no cant see";
	const char *fourtwenty = "420";
	const char *numbers = "5138008";
	const char *imfine = "yes im doing good";

		

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);
	int count = 0;
	vector<char> temp;
	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			//printf("recieved test: %s\n", recvbuf);
			temp.clear();
			if (count == 0) {
				for (int i = 0; i < 14; ++i) {
					temp.push_back(recvbuf[i]);
				}
				count++;
			}
			/*else if (count == 1) {
				for (int i = 0; i < 3; ++i) {
					temp.push_back(recvbuf[i]);
				}
				count++;
			}*/
			else if (count == 1) {
				for (int i = 0; i < 5; ++i) {
					temp.push_back(recvbuf[i]);
				}
				count++;
			}
			else if (count == 2) {
				for (int i = 0; i < 15; ++i) {
					temp.push_back(recvbuf[i]);
				}
				count++;
			}
			temp.push_back('\0');
			printf("Received this text: %s\n", temp.data());

			// Echo the buffer back to the sender
			if (!strcmp(temp.data(), "can u see this")) {

				iSendResult = send(ClientSocket, yescansee, iResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}
				printf("Sent: %s\n", yescansee);
			}
			else if (!strcmp(temp.data(), "421")) {
				recvbuf[2] -= 1;
				recvbuf[3] = ' ';
				recvbuf[4] = ' ';
				recvbuf[5] = '\0';
				iSendResult = send(ClientSocket, recvbuf, iResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}
				printf("Sent: %s\n", recvbuf);
				

			}
			else if (!strcmp(temp.data(), "58008")) {
				recvbuf[0] = 'n';
				recvbuf[1] = 'o';
				recvbuf[2] = 'o';
				recvbuf[3] = 'o';
				recvbuf[4] = '!';
				recvbuf[5] = '\0';
				iSendResult = send(ClientSocket, recvbuf, iResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}
				printf("Sent: %s\n", recvbuf);


			}
			else if (!strcmp(temp.data(), "how are u doing")) {
				
				iSendResult = send(ClientSocket, imfine, iResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}
				printf("Sent: %s\n", imfine);


			}
			else {
				iSendResult = send(ClientSocket, nocansee, iResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				
				}
				printf("Sent: %s\n", nocansee);
			}
			printf("Bytes sent: %d\n", iSendResult);
			
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
		Sleep(2000);
	} while (iResult > 0);
	
	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	getchar();


	return 0;
}