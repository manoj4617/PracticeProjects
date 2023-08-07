#include "TCPListener.h"

TCPListener::TCPListener(std::string ip_address, int port, MessageRecievedHandler handler)
	:	m_ipAddress(ip_address),
		m_port(port),
		m_messageRecieveHandler(handler)
{

}

TCPListener::~TCPListener() {
	Cleanup();
}

//Send a message to the specified client
void TCPListener::Send(int clientSocket, std::string message) {
	send(clientSocket, message.c_str(), message.size() + 1, 0);
}

//Initialize winsock
bool TCPListener::Init() {

	WSADATA wsData;

	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
		ErrorHandler("Error in initialization");
		return false;
	}

	return true;
}

//the main process loop
void TCPListener::Run() {

	char buf[MAX_BUFFER_SIZE];

	while (true) {
		//create a listening socket
		SOCKET listening = CreateSocket();
		if (listening == INVALID_SOCKET) {
			break;
		}

		SOCKET client = WaitForConnection(listening);

		if (client != INVALID_SOCKET) {
			closesocket(listening);

			int bytes_recieved = 0;
			
			do {
				ZeroMemory(buf, MAX_BUFFER_SIZE);

				bytes_recieved = recv(client, buf, MAX_BUFFER_SIZE, 0);

				if (bytes_recieved > 0) {
					if (m_messageRecieveHandler != nullptr) {
						m_messageRecieveHandler(this, client, std::string(buf, 0, bytes_recieved));
					}
				}
			} while (bytes_recieved > 0);

			closesocket(client);
		}
	}

}


//cleanup
void TCPListener::Cleanup() {
	WSACleanup();
}

//Create a Socket
SOCKET TCPListener::CreateSocket() {

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening != INVALID_SOCKET) {
		sockaddr_in hint;
		
		hint.sin_family		= AF_INET;
		hint.sin_port		= htons(m_port);
		
		inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

		if (bind(listening, (sockaddr*)&hint, sizeof(hint)) != 0) {
			ErrorHandler("Binding Error");
			return -1;
		}

		if (listen(listening, SOMAXCONN) == SOCKET_ERROR) {
			ErrorHandler("Failed to listen to connections");
			return -1;
		}
	}

	return listening;
}

//Wait for connection
SOCKET TCPListener::WaitForConnection(SOCKET listening){

	SOCKET client = accept(listening, NULL, NULL);
	return client;
}

void TCPListener::ErrorHandler(std::string error_message) {
	std::cerr << error_message << " : " << "\n";
}

