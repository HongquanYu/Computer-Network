//
//  Client.h
//  TCP
//
//  Created by YuAlex on 10/3/17.
//  Copyright © 2017 YuAlex. All rights reserved.
//

#ifndef Client_h
#define Client_h

#define FILE_PATH "/Users/Yu/Desktop/reviews.txt"

int socket_fd;                      // Socket socket descriptor
struct sockaddr_in serv_addr;       // Server address structure

int hash_req = 8;
int len_HashRespond;

struct HashRequest {
    short ID;
    int length;
    char * payload;
};

#endif /* Client_h */
