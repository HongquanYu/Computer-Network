//
//  Client.c
//  TCP
//
//  Created by YuAlex on 9/25/17.
//  Copyright © 2017 YuAlex. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#define DATA "Half a league, half a league . . ."

/*
main(argc, argv)
int argc;
char *argv[];
{
    int sock;
    struct sockaddr_un server;
    char buf[1024];
    
    
    if (argc < 2) {
        printf("usage:%s <pathname>", argv[0]);
        exit(1);
    }
    
    
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("opening stream socket");
    }
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, argv[1]);
    
    
    if (connect(sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0) {
        close(sock);
        perror("connecting stream socket");
        exit(1);
    }
        close(sock);
        }

*/
