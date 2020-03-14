#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a socket
    int network_socket;
    // SOCK_STREAM specifies that we are using byte stream and not datagram network fucntionality (used by TCP)
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify the address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    // pass the port number you want to connect to remotely to htons which converts it to the right format to read 
    server_address.sin_port = htons(9002);
    // specify network address
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Call connect function to connect to a separate socket
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    // value of 0 = connection ok, -1 = something went wrong
    if (connection_status == -1){
        printf("Error connecting to server socket\n\n");
    }

    // retrieve network_socket
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print the data returned from server
    printf("The server returned the data: %s", server_response);

    // close the socket
    close(network_socket);
    
    return 0;
}