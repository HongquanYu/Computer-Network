//
//  readFile.c
//  TCP
//
//  Created by YuAlex on 10/3/17.
//  Copyright © 2017 YuAlex. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int readFileIntoBuffer(char *path, char *buffer[], int num) {
    FILE * infile;
    long numbytes;
    
    if (infile = fopen(path, "r") == NULL) {
        perror("open file failed ");
        return -1;
    }
    
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    fseek(infile, 0L, SEEK_SET);
    
    int chk = numbytes / num;
    for (int i = 0; i < num; ++i) {
        if (buffer[i] = (char*)calloc(chk, sizeof(char)) == NULL) {
            perror("alloc space failed ");
            return -2;
        }
    }
    
    char * t = buffer;
    for (int i = 0; i < num; ++i) {
        fread(t, sizeof(char), chk, infile);
        t += chk;
    }
    
    fclose(infile);
    
    printf("The file called test.dat contains this text\n\n%s", buffer);
    
    return numbytes;
}
