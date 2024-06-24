#include <pthread.h>
#include <stdlib.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

pthread_mutex_t mutex;

typedef struct{
        __uint128_t value;
        int cnt;
        FILE* f;
} pthrData;

bool status=false;

#define memory 692
#define thread_size 12                          //704-692

void* threadFunc(void* thread_data){
        pthrData *data = (pthrData*) thread_data;
        while(true){
                if(status){
                        break;
                }
                pthread_mutex_lock(&mutex);
                char s[33];
                int k=0;
                if(fscanf(data->f,"%c",&s[k])==-1){
                        break;
                }
                while(s[k]==' ' || s[k]=='\n' || s[k]=='\t'){
                        if(fscanf(data->f,"%c",&s[k])==-1){
                                status=true;
                                break;
                        }
                }
                if(status){
                        break;
                }
                while(s[k]!=' ' && s[k]!='\n' && s[k]!='\t'){
                        k++;
                        if(k>31){
                                return (void*)-1;
                        }
                        if(fscanf(data->f,"%c",&s[k])==-1){
                                status=true;
                                break;
                        }
                }
                __uint128_t a=0;
                for(int i=0;i<k;i++){
                        if(s[i]>='0' && s[i]<='9'){
                                a=a*16+(s[i]-'0');
                        }else if(s[i]>='A' && s[i]<='F'){
                                a=a*16+(s[i]-'A'+10);
                        } else {
                                return (void*)-1;
                        }
                }
                /*while(true){
                }*/
                data->value=data->value+a;
                data->cnt++;
                if(status){
                        break;
                }
                pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_unlock(&mutex);
        return NULL;
}

int main(int argc, char * argv[]){
        int n=1;
        if(argc!=2 && argc!=3){
                fprintf(stderr, "Неверное количество аргументов\n");
                return 1;
        }
        if(argc==2){
                n=1;
        } else {
                long long p=atoi(argv[2]);
                if(p<1){
                        fprintf(stderr, "Количество памяти не может быть меньше единицы\n");
                        return 2;
                }
                p=p-memory;
                if(p<0){
                        fprintf(stderr, "Количество памяти слишком мало\n");
                        return 3;
                }
                n=n+p/thread_size;
        }
        __uint128_t sum=0;
        int count=0;
        FILE *in = fopen(argv[1], "r");
        if(in==NULL){
                fprintf(stderr, "Что-то не так с файлом '%s'\n", argv[1]);
                return 3;
        }
        pthread_t threads[n];
        pthread_mutex_init(&mutex, NULL);
        pthrData threadData[n];
        for(int i=0;i<n;i++){
                threadData[i].value=0;
                threadData[i].cnt=0;
                threadData[i].f=in;
                pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
        }
        for(int i=0;i<n;i++){
                void* r;
                pthread_join(threads[i], &r);
                if(r==(void*)-1){
                        fprintf(stderr, "Неправильные данные\n");
                        return 4;
                }
        }
        for(int i=0;i<n;i++){
                sum=sum+threadData[i].value;
                count=count+threadData[i].cnt;
        }
        sum=sum/count;
        long long g=(sum>>64);
        long long q=sum&0xFFFFFFFFFFFFFFFF;
        if(g>0){
                printf("%llx\n",g);
        }
        printf("%llx\n",q);
        pthread_mutex_destroy(&mutex);
}
