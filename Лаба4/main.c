#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "unistd.h"

int main(){
        char template[] = "/tmp/tmpXXXXXX";
        int desc = mkstemp(template);
        if(desc < 0){
                perror("Tmp file not created\n");
                return -6;
        }
        printf("%s\n", template);
        int id1 = fork();
        if (id1 == -1) {
                perror("fork error");
                return -1;
        } else if (id1 == 0){
                sleep(10);
                execl("child1.out", "child1.out", template, NULL);
        } else{
                int id2 = fork();
                if (id2 == -1) {
                        perror("fork error");
                        return -1;
                } else if(id2==0){
                        sleep(10);
                        execl("child2.out", "child2.out", template,  NULL);
                } else {
                        int n=0;
                        char p;
                        read(0,&p,sizeof(char));
                        while(p!='\n'){
                                if(p<'0' || p>'9'){
                                        printf("Wrong values\n");
                                        while(read(0,&p,sizeof(char))){
                                        }
                                        return -1;
                                }
                                n=n*10+p-'0';
                                read(0,&p,sizeof(char));
                        }
                        ftruncate(desc, sizeof(char)*n);
                        char S[n];
                        read(0,&S,sizeof(char)*n);
                        char* fd = mmap(NULL, sizeof(char)*n, PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);
                        if (fd == MAP_FAILED){
                                perror("mmap error\n");
                                return -5;
                        }
                        for(int i=0;i<n;i++){
                                fd[i]=S[i];
                        }
                        msync(fd, sizeof(char)*n, MS_SYNC);
                        munmap(fd, sizeof(char)*n);
                        int status;
                        waitpid(id2, &status,WUNTRACED);
                        if(WEXITSTATUS(status)){
                                return -1;
                        }
                        struct stat buff;
                        fstat (desc, &buff);
                        n=buff.st_size;
                        fd = mmap(NULL, sizeof(char)*n, PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);
                        for(int i=0;i<n;i++){
                                printf("%c",fd[i]);
                        }
                }
        }
        return 0;
}

