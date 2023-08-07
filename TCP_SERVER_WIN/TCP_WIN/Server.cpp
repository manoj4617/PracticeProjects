

// TCPServer.cpp : Defines the entry point for the application.
//

#include "TCPServer.h"

using namespace std;

void main()
{
	//Initialize winsock  
	WSADATA wsData;
	WORD version = MAKEWORD(2, 2);

	int wsOK = WSAStartup(version, &wsData);
	if (wsOK != 0) {
		cerr << "WINSOCK initialization failed!" << "\n";
		return;
	}

	//create a socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == INVALID_SOCKET) {
		cerr << "Can't create a socket!" << "\n";
		return;
	}

	//Bind the IP and port to the socket
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080); //hton = host to network short
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		socket_error("Error Binding to socket", server_socket);
	}

	//Tell winsock the socket is for listening
	if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
		socket_error("Error in listening for connections", server_socket);
	}

	cout << "Server listening on port 8080..." << "\n\n";

	//wait for the connection
	int clientSize = sizeof(client_addr);

	client_socket = accept(server_socket, (sockaddr*)&client_addr, &clientSize);
	if (client_socket == INVALID_SOCKET) {
		socket_error("Error accepting client connections", client_socket);
	}
	char host[NI_MAXHOST];				//client's remote name
	char service[NI_MAXHOST];			//Service (port) the client is connected on

	ZeroMemory(host, NI_MAXHOST);		//memset
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client_addr,
		sizeof(client_addr),
		host,
		NI_MAXHOST,
		service,
		NI_MAXSERV,
		0) == 0) {
		cout << host << " connected on port " << service << "\n";
	}
	else {
		inet_ntop(AF_INET, &client_addr.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client_addr.sin_port) << "\n";
	}

	//close listening socket
	closesocket(server_socket);

	//while loop: accept and echo message back to client
	char buff[MAX_BUFFER];

	while (true) {
		ZeroMemory(buff, MAX_BUFFER);

		//Wait for client to send data
		int bytes_recv = recv(client_socket, buff, MAX_BUFFER, 0);
		if (bytes_recv == SOCKET_ERROR) {
			socket_error("Error in recieving data", client_socket);
		}

		if (bytes_recv == 0) {
			cout << "Client disconnected " << "\n";
			break;
		}

		//echo message back to client
		send(client_socket, buff, bytes_recv + 1, 0);


	}
	//close the socket
	closesocket(client_socket);

	//shutdown winsock
	WSACleanup();
	return;
}
