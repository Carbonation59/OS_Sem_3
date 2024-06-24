#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main(){
        int fd1[2], fd2[2], fd3[2];
        pipe(fd1);
        pipe(fd2);
        pipe(fd3);
        int id1 = fork();
        if (id1 == -1) {
                perror("fork error");
                return -1;
        } else if (id1 == 0){
                if (dup2(fd1[0], STDIN_FILENO) < 0) {
                        perror("Can't redirect stdin for child process");
                }
                if (dup2(fd2[1], STDOUT_FILENO) < 0) {
                     perror("Can't redirect stdout for child process");
                }
                close(fd1[0]);
                close(fd2[1]);
                execl("child1.out", "", NULL);
        } else{
                int id2 = fork();
                if (id2 == -1) {
                        perror("fork error");
                        return -1;
                } else if(id2==0){
                        if (dup2(fd2[0], STDIN_FILENO) < 0) {
                                perror("Can't redirect stdin for child process");
                        }
                        if (dup2(fd3[1], STDOUT_FILENO) < 0) {
                                perror("Can't redirect stdout for child process");
                        }
                        close(fd2[0]);
                        close(fd3[1]);
                        execl("child2.out", "", NULL);
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
                        char S[n];
                        read(0,&S,sizeof(char)*n);
                        write(fd1[1],&n,sizeof(int));
                        write(fd1[1], &S, sizeof(char)*n);
                        read(fd3[0], &n, sizeof(int));
                        read(fd3[0], &S, sizeof(char)*n);
                        write(1, &S, sizeof(char)*n);
                        p='\n';
                        write(1, &p, sizeof(char));
                        close(fd1[1]);
                        close(fd3[0]);
                }
        }
        return 0;
}
