#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "Socket.h"
#include "Server.h"
#include "send_int.c"


int main (int argc, char **argv)
{
    if ((listen_fd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
        perror("Problem in creating the socket");
        exit(2);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);
    
    bind (listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    
    listen (listen_fd, MAX_CONNECTION);
    
    printf("%s\n","Server running! Waiting for connections...");
    
    for (; ;) {   // run forever
        
        client_len = sizeof(client_addr);
        conn_fd = accept (listen_fd, (struct sockaddr *) &client_addr, &client_len);
        
        // Create a child process
        if ( (child_pid = fork ()) == 0 ) {     // child_pid == 0 represents a child process
            
            printf ("%s\n","Child process responds client.");
            close (listen_fd);
            
            // send hash request times
            if (read(conn_fd, &hash_times, sizeof(hash_times) > 0)) {
                printf("Hash time: %d \n", hash_times);
            }
            
            // Respond client
            len_hashrespond = 36 * hash_times;
            write(conn_fd, &len_hashrespond, sizeof(len_hashrespond));
            
           /*
            
            
            
             while ( (msg_length = recv(conn_fd, &buf, sizeof(buf), 0)) > 0)  {
             hash_times = ntohl(buf);
             printf("%d","Int from client: ", hash_times);
             
             }
             
             if (msg_length < 0)      // did not receive data
             printf("%s\n", "Read error");
             */
            // CHILD TERMINATED
            exit(0);
        }
        
        //STEP 6: PARENT closed!
        close(conn_fd);
    }
}
