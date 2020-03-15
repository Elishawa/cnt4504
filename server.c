#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char server_message[256] = "Connection with server has been established";

    //  creates the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the address of the server
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(50001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to the specified IP and port number
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    //call the listen function to listen for the incoming connection from client
    listen(server_socket, 5);

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    send(client_socket, server_message, sizeof(server_message), 0);

    // close the socket
    close(server_socket);

    return 0;
}
