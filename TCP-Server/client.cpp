#include "header_f.h"

int main(){

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        std::cerr << "Error creating a socket.\n";
    }

    struct sockaddr_in server_address {};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(LOCALHOST);
    server_address.sin_port = htons(PORT_NUMBER);

    if(connect(client_socket,
                (struct sockaddr *)&server_address,
                sizeof(server_address)) == -1)
                {
                    std::cerr << "Error in connecting to server.\n";
                    return -1;
                }

    std::string message;
    std::cout << "Enter a message to send to the server: ";
    std::getline(std::cin,  message);

    ssize_t bytes_sent = send(client_socket, message.c_str(), message.length(), 0);
    if(bytes_sent == -1){
        std::cerr << "Error sending data to server.\n";
        close(client_socket);
        return -1;
    }

    // Receive response from the server
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
    if (bytes_received == -1) {
        std::cerr << "Failed to receive response from server\n";
        close(client_socket);
        return 1;
    }

    // Print the response received from the server
    buffer[bytes_received] = '\0';
    std::cout << "Response from server: " << buffer << "\n";

    close(client_socket);
    return 0;
}