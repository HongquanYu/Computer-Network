//
//  Server.h
//  TCP
//
//  Created by YuAlex on 10/3/17.
//  Copyright © 2017 YuAlex. All rights reserved.
//

#ifndef Server_h
#define Server_h

int listen_fd;                      // Listen socket descriptor
int conn_fd;                        // Connection socket descriptor
int msg_length;                     // Message length of writing received data to buffer

pid_t child_pid;                    // Children process to handle clients' request

socklen_t client_len;               //
char buf[MAX_TEXT_LENGTH];          // Buffer for storing received data
struct sockaddr_in client_addr;     // Client address
struct sockaddr_in server_addr;     // Server address

int hash_times;
int len_hashrespond;

struct HashResponce{
    int index;
    char hash[32];
};

#endif /* Server_h */
