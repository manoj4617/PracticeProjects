#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE (49152)

class TCPListener;


//callback to message handler
typedef void (*MessageRecievedHandler)(TCPListener *listener, int socketID, std::string message);

class TCPListener {

public:
	TCPListener(std::string ip_address, int port, MessageRecievedHandler handler);

	~TCPListener();

	//Send a message to the specified client
	void Send(int clientSocket, std::string);

	//Initialize winsock
	bool Init();

	//the main process loop
	void Run();
	
	//Revcieve loop
	//Send back message

	//cleanup
	void Cleanup();

	void ErrorHandler(std::string error_message);

private:

	//Create a Socket
	SOCKET CreateSocket();

	//Wait for connection
	SOCKET WaitForConnection(SOCKET listening);

	std::string				m_ipAddress;
	int						m_port;
	MessageRecievedHandler	m_messageRecieveHandler;
};