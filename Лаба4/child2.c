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
        stat (argv[1], &buff);
        int n=buff.st_size;
        char* fd = mmap(NULL, sizeof(char)*n,PROT_WRITE|PROT_READ,MAP_SHARED,desc, 0);
        if (fd == MAP_FAILED){
                perror("mmap error\n");
                return -5;
        }
        char S[n];
        int r=0;
        for(int i=0;i<n;i++){
                if(i>0 && fd[i]==' ' && fd[i-1]==' '){
                      continue;
                }
                S[r]=fd[i];
                r++;
        }
        for(int i=0;i<r;i++){
                fd[i]=S[i];
        }
        msync(fd, sizeof(char)*r, MS_SYNC);
        munmap(fd, sizeof(char)*r);
        ftruncate(desc, sizeof(char)*r);
        close(desc);
        return 0;
}

