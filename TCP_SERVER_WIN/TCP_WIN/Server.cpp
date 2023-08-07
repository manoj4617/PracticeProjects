

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

	fd_set master;
	FD_ZERO(&master);

	FD_SET(server_socket, &master);

	bool running = true;

	while (running) {
		fd_set master_cpy = master;

		int socket_count = select(0, &master_cpy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socket_count; i++) {
			SOCKET sock = master_cpy.fd_array[i];

			if (sock == server_socket) {
				//the socket select is the listening one, meaning the server
				int client_size = sizeof(client_addr);
				SOCKET client = accept(server_socket, (sockaddr*)&client_addr, &client_size);

				if (client == INVALID_SOCKET) {
					socket_error("Error accepting client connections", client);
				}
				char host[NI_MAXHOST];
				char service[NI_MAXSERV];

				ZeroMemory(host, NI_MAXHOST);
				ZeroMemory(service, NI_MAXSERV);

				if (getnameinfo((sockaddr*)&client_addr,
					sizeof(client_addr),
					host,
					NI_MAXHOST,
					service,
					NI_MAXSERV,
					0) == 0) {
					cout << host << " connected on port: " << service << "\n";
				}
				else {
					inet_ntop(AF_INET, &client_addr.sin_addr, host, NI_MAXHOST);
					cout << host << " connected on port " <<
							ntohs(client_addr.sin_port) << "\n";
				}
				
				//add the new connection to the list of connected clients
				FD_SET(client, &master);

				//send a welcome message to the clint
				string welcomeMsg = "Welcome to awesome chat server!!!!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			}
			else {
				//accept a new message
				char buf[MAX_BUFFER];
				ZeroMemory(buf, MAX_BUFFER);

				int bytes_recieved = recv(sock, buf, MAX_BUFFER, 0);

				if (bytes_recieved <= 0) {
					//drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else {
					//send massage to other clients not the listening 
					if (buf[0] == '\\') {
						string cmd = string(buf, bytes_recieved);
						if (cmd == "\\quit") {
							running = false;
							break;
						}
						continue;
					}

					for (int i = 0; i < master.fd_count; ++i) {
						SOCKET outSock = master.fd_array[i];
						if ((outSock != server_socket) && (outSock != sock)) {
							ostringstream ss;
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							string strOut = ss.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}

			}
		}
	}


	//shutdown winsock
	WSACleanup();
	return;
}