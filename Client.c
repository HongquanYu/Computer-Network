#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include "Socket.h"

int main(int argc, char **argv)
{
    int socket_fd;                      // Socket socket descriptor
    struct sockaddr_in serv_addr;       // Server address structure
    char send_line[MAX_TEXT_LENGTH];    // Buffer for storing send data
    char recv_line[MAX_TEXT_LENGTH];    // Buffer for storing received data
    
    //STEP 0: Arguments checking!
    
    if (argc != 2) {
        perror("Usage: TCPClient <IP address of the server");
        exit(1);
    }
    
    //STEP 1: Create a socket for the client
    
    if ((socket_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Problem in creating the socket");
        exit(2);
    }
    
    //STEP 2: Prepare address
    
    memset(&serv_addr, 0, sizeof(serv_addr));   // initialize the structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr= inet_addr(argv[1]);
    serv_addr.sin_port =  htons(SERV_PORT); //convert to big-endian order
    
    //STEP 3: Establish connection
    if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Problem in connecting to the server");
        exit(3);
    }
    
    // Read a line from specified stream into send_line
    
    while (fgets(send_line, MAX_TEXT_LENGTH, stdin) != NULL) {
        
        send(socket_fd, send_line, strlen(send_line), 0);
        
        if (recv(socket_fd, recv_line, MAX_TEXT_LENGTH,0) == 0){
            perror("The server terminated prematurely");
            exit(4);
        }
        
        printf("%s", "String received from the server: ");
        fputs(recv_line, stdout);
    }
    
    exit(0); // exit
}
