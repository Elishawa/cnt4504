#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Client: Attempting to connect with the server\n");
    // Create a socket
    int network_socket;
    // SOCK_STREAM specifies that we are using byte stream and not datagram network fucntionality (used by TCP)
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify the address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    // pass the port number you want to connect to remotely to htons which converts it to the right format to read 
    server_address.sin_port = htons(50001);
    // specify network address
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Call connect function to connect to a separate socket
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    // value of 0 = connection ok, -1 = something went wrong
    if (connection_status == -1){
        printf("Client: Error connecting to server socket\n\n");
    }

    // retrieve network_socket
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print the data returned from server
    printf("Server: %s\n", server_response);

    char buffer[512];

    FILE *f;
    int words = 0;

    char c;

    f = fopen(argv[1], "r");
    while((c = getc(f)) != EOF) {
        fscanf(f, "%s", buffer);
        if(isspace(c) || c == '\t'){
            words++;
        }
    }

    write(network_socket, &words, sizeof(int));
    // takes the file pointer back to the beginning of the file
    rewind(f);

    char ch;
    while(ch != EOF){
        fscanf(f, "%s", buffer);
        write(network_socket, buffer, 512);
        ch = fgetc(f);
    }
    printf("Client: file sent to server \n");

    // close the socket
    close(network_socket);
    
    return 0;
}