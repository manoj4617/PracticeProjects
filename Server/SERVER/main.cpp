#include "TCPListener.h"

#define LOCALHOST "127.0.0.1"
#define PORT 8080

void Listener_MessageRecieved(TCPListener *listener,
	int sockerID,
	std::string message);

void main() {

	TCPListener server(LOCALHOST, PORT, Listener_MessageRecieved);

	if (server.Init()) {
		server.Run();
	}
}

void Listener_MessageRecieved(TCPListener *listener,
	int socketID,
	std::string message) {
	listener->Send(socketID, message);
}