// TCPServer.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define MAX_BUFFER 4096

using namespace std;

SOCKET client_socket;
SOCKET server_socket;

sockaddr_in client_addr;
sockaddr_in server_addr;

void socket_error(string error_message, SOCKET sock) {
	cerr << error_message << ": " << WSAGetLastError() << "\n";
	closesocket(sock);
	WSACleanup();
	return;
}

