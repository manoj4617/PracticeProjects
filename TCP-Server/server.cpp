#include "header_f.h"

int main(){   

    struct sockaddr_in server_address, client_address;
    char response[MAX_BUFFER_SIZE] = RESP_MSG;

    /*
    *   Creating a TCP socekt
    *   AF_INET - IPv4 addressing
    *   SOCK_STREAM - TCP protocol/connection-oriented communication
    */
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
        std::cerr << "Error in creating socket.\n";
    }

    /*
    *   Binding the socket to local IP
    */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT_NUMBER);

    if(bind(server_socket, 
            (struct sockaddr *)&server_address, 
            sizeof(server_address)) == -1)  
    {
        std::cerr << "Error in binding socket.\n";
    }

    /*
    *   Listen to incoming requests
    */
   if(listen(server_socket, MAX_PENDING_CONNECTIONS) == -1){
    std::cerr << "Error listening on socket.\n";
    return -1;
   }

    std::cout << "Server is listening on port " << PORT_NUMBER << "\n";


    while(true){
    /*
    *    Accept incoming connections
    */
        socklen_t client_address_len = sizeof(client_address);

        int client_socket = accept(server_socket, 
                                    (struct sockaddr *)&client_address, 
                                    &client_address_len);
        if(client_socket == -1){
            std::cerr << "Error in accepting client connections.\n";
            continue;
        }

        std::cout << "Client connected.\n";

        /*
        * Receive data from the client
        */
    char message[MAX_BUFFER_SIZE];
    memset(message,0,MAX_BUFFER_SIZE);
        if(recv(client_socket, message, MAX_BUFFER_SIZE, 0) == -1){
            std::cerr << "Error in receiving data from client.\n";
            continue;
        }

        std::cout << "Recieved messsage: " << message << "\n";

        /*
        *  Send data to the client
        */
       strncat(response, message, sizeof(message));
        if(send(client_socket, response, strlen(response), 0) == -1){
            std::cerr << "Error in sending data to client.\n";
            close(client_socket);
            continue;
        }
    
        std::cout << "Response sent: " << response << "\n";
        


        //Closing the connections
        close(client_socket);
        memset(response, 0, sizeof(response));
    }
    close(server_socket);

    return 0;
}
