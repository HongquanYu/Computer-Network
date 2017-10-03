//
//  int_transfer.c
//  TCP
//
//  Created by YuAlex on 10/3/17.
//  Copyright © 2017 YuAlex. All rights reserved.
//

#include <stdio.h>
#include <errno.h>

// function declarations

ssize_t	 write(int __fd, const void * __buf, size_t __nbyte);
ssize_t	 read(int, void *, size_t);

int send_int(int num, int fd) {
    int32_t trans = htonl(num);
    
    if (write(fd, &trans, sizeof(trans) == -1)) {
        printf("send fails.\n");
        return -1;
    }
    
    
    return 0;
}

int receive_int(int *num, int fd) {
    int32_t received_bytes;
    
    if (read(fd, &received_bytes, sizeof(received_bytes) == -1)) {
        printf("receive fails.\n");
        return -1;
    }
    
    *num = ntohl(received_bytes);
    
    return 0;
}
