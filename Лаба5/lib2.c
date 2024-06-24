#include <stdio.h>
#include <stdlib.h>

float E(int x){
        float f=1;
        float k=1;
        for(int i=1;i<=x;i++){
                k=k*i;
                f=f+1/k;
        }
        return f;
}

void Sort(int *numbers, int left, int right){
        int pivot;
        int l_hold = left;
        int r_hold = right;
        pivot = numbers[left];
        while (left < right){
                while ((numbers[right] >= pivot) && (left < right)){
                        right--;
                }
                if (left != right){
                        numbers[left] = numbers[right];
                        left++;
                }
                while ((numbers[left] <= pivot) && (left < right)){
                        left++;
                }
                if (left != right){
                        numbers[right] = numbers[left];
                        right--;
                }
        }
        numbers[left] = pivot;
        pivot = left;
        left = l_hold;
        right = r_hold;
        if (left < pivot){
                Sort(numbers, left, pivot - 1);
        }
        if (right > pivot){
                Sort(numbers, pivot + 1, right);
        }
}
