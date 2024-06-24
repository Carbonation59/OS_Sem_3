#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char* argv[]){
        int desc = open(argv[1], O_RDWR);
        if(desc < 0){
        perror("Tmp file not created\n");
                return -6;
        }
        struct stat buff;
        stat(argv[1], &buff);
        int n=buff.st_size;
        char* fd = mmap(NULL, sizeof(char)*n,PROT_WRITE|PROT_READ,MAP_SHARED,desc, 0);
        if (fd == MAP_FAILED){
                perror("mmap error\n");
                return -5;
        }
        for(int i=0;i<n;i++){
                fd[i]=tolower(fd[i]);
        }
        msync(fd, sizeof(char)*n, MS_SYNC);
        munmap(fd, sizeof(char)*n);
        close(desc);
        return 0;
}
