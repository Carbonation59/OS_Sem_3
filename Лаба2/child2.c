#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main(){
        int n;
        read(0, &n, sizeof(int));
        char S[n];
        char K[n];
        int r=1;
        read(0, &S, sizeof(char)*n);
        K[0]=S[0];
        for(int i=1;i<n;i++){
                if(S[i]==' ' && S[i-1]==' '){
                      continue;
                }
                K[r]=S[i];
                r++;
        }
        write(1, &r, sizeof(int));
        write(1, &K, sizeof(char)*r);
        return 0;
}
