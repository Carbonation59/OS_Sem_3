#include <stdio.h>
#include "functions.h"

int main(){
        printf("1 + float x - calculation of exponent with accuracy of x\n");
        printf("2 + int n + int A[n] - number of members of array and array\n");
        int command;
        while(scanf("%d", &command) != EOF){
                if(command==2){
                        int n;
                        if(scanf("%d", &n) != 1){
                                printf("Wrong arguements!\n");
                                continue;
                        }
                        int A[n];
                        for(int i=0;i<n;i++){
                                if(scanf("%d", &A[i]) != 1){
                                        printf("Wrong arguements!\n");
                                        continue;
                                }
                        }
                        Sort(A, 0, n-1);
                        for(int i=0;i<n;i++){
                                printf("%d ",A[i]);
                        }
                        printf("\n");
                } else if(command==1){
                        float x;
                        if(scanf("%f", &x) != 1){
                                printf("Wrong arguements!\n");
                                continue;
                        }
                        printf("%f\n", E(x));
                } else{
                        printf("Wrong command!\n");
                }
        }
}
