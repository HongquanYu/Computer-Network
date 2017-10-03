#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include "Socket.h"
#include "Client.h"
#include "read_file.c"
#include "send_int.c"

int main(int argc, char **argv)
{
    if (argc != 2) {
        perror("Usage: TCPClient <IP address of the server");
        exit(1);
    }

    if ((socket_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Problem in creating the socket");
        exit(2);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr= inet_addr(argv[1]);
    serv_addr.sin_port =  htons(SERV_PORT);     //convert to big-endian order
    
    if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Problem in connecting to the server");
        exit(3);
    }
    
    write(socket_fd, &hash_req, sizeof(hash_req));
    
    if (read(socket_fd, &len_HashRespond, sizeof(len_HashRespond)) > 0)
        printf("Hash Respond = %d \n", len_HashRespond);
    
    char *buf[hash_req];
    int filesize = readFileIntoBuffer(FILE_PATH, buf, hash_req);
    int chunk = filesize / hash_req;
    struct HashRequest hs;
    hs.ID = 0x0417;
    hs.length = chunk;

    hs.payload = buf[0];
    
    free(buf);
    
    exit(0); // exit
}
