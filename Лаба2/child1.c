#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main(){
        int n;
        read(0,&n,sizeof(int));
        char S[n];
        read(0, &S, sizeof(char)*n);
        for(int i=0;i<n;i++){
                S[i]=tolower(S[i]);
        }
        write(1, &n, sizeof(int));
        write(1, &S, sizeof(char)*n);
        return 0;
}
