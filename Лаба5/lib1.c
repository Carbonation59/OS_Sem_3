#include <stdio.h>
#include <stdlib.h>

float E(int X){
        float x=X;
        float f=1+1/x;
        float h=1;
        while(x>0){
                x--;
                h=h*f;
        }
        return h;
}

void Sort(int *numbers, int r, int n){
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        if(numbers[j]>numbers[j+1]){
                                int y=numbers[j];
                                numbers[j]=numbers[j+1];
                                numbers[j+1]=y;
                        }
                }
        }
}
