#include <stdio.h>
#include <dlfcn.h>

int main(){
        int version = 1;
        int command;
        float (*E)(int) = NULL;
        int (*Sort)(int*, int, int) = NULL;
        void *lib1_handler = dlopen("./lib1.so",RTLD_LAZY);
        if (!lib1_handler){
            fprintf(stderr,"dlopen() error: %s\n", dlerror());
            return -1;
        }
        void *lib2_handler = dlopen("./lib2.so",RTLD_LAZY);
        if (!lib2_handler){
            fprintf(stderr,"dlopen() error: %s\n", dlerror());
            return -1;
        }
        E = dlsym(lib1_handler,"E");
        Sort = dlsym(lib1_handler,"Sort");
        printf("0 - to switch realizations\n");
        printf("1 + float x - calculation of exponent with accuracy of x\n");
        printf("2 + int n + int A[n] - number of members of array and array\n");
        while(scanf("%d", &command) != EOF){
                if(command==0){
                        if(version==2){
                                E = dlsym(lib1_handler,"E");
                                Sort = dlsym(lib1_handler,"Sort");
                                version=1;
                        } else{
                                E = dlsym(lib2_handler,"E");
                                Sort = dlsym(lib2_handler,"Sort");
                                version=2;
                        }
                        printf("Switched to realization %d\n", version);
                } else if(command==1){
                        float x;
                        if(scanf("%f", &x) != 1){
                                printf("Wrong arguements!\n");
                                continue;
                        }
                        printf("%f\n", E(x));
                } else if(command==2){
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
                } else{
                        printf("Wrong command!\n");
                }
        }
        dlclose(lib1_handler);
        dlclose(lib2_handler);
}

