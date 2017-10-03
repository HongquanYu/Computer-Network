#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "Socket.h"

int main (int argc, char **argv)
{
    int listen_fd;                      // Listen socket descriptor
    int conn_fd;                        // Connection socket descriptor
    int msg_length;                     // Message length of writing received data to buffer
    pid_t child_pid;                    // Children process to handle clients' request
    socklen_t client_len;               //
    char buf[MAX_TEXT_LENGTH];          // Buffer for storing received data
    struct sockaddr_in client_addr;     // Client address
    struct sockaddr_in server_addr;     // Server address
    
    // STEP 0: Create a socket for the soclet
    if ((listen_fd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
        perror("Problem in creating the socket");
        exit(2);
    }
    
    //STEP 1: Preparation of the socket address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);
    
    //STEP 2: Bind the socket to specified address and port
    bind (listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    
    //STEP 3: listen to the socket by creating a connection queue, then wait for clients
    listen (listen_fd, MAX_CONNECTION);
    
    printf("%s\n","Server running! Waiting for connections...");
    
    for ( ; ; ) {   // run forever
        
        client_len = sizeof(client_addr);
        
        //STEP 4: Accept a connection
        conn_fd = accept (listen_fd, (struct sockaddr *) &client_addr, &client_len);
        
        printf("%s\n","Received request...");
        
        // CREATE A CHILD PROCESS TO DEAL WITH CLIENT'S REQUEST
        if ( (child_pid = fork ()) == 0 ) {     //if child_pid == 0, it’s child process
            
            printf ("%s\n","Child created for dealing with client requests");
            
            //STEP 5: close listening socket
            close (listen_fd);
            
            while ( (msg_length = recv(conn_fd, buf, MAX_TEXT_LENGTH, 0)) > 0)  {
                printf("%s","String received from and resent to the client: ");
                puts(buf);                              // store the received data to buffer
                send(conn_fd, buf, msg_length, 0);       // Send it back
            }
            
            if (msg_length < 0)      // did not receive data
                printf("%s\n", "Read error");
            
            // CHILD TERMINATED
            exit(0);
        }
        
        //STEP 6: PARENT closed!
        close(conn_fd);
    }
}
