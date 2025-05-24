#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *threadfunc(void *arg);
int number = 0;
int a = 1;
int main(){
    pthread_t b[5];
    for (int i = 0 ; i < 5 ; i++){
        pthread_create(&b[i],NULL,threadfunc,NULL);
        pthread_join(b[i],NULL);
    }
    return 0;
}

void *threadfunc(void *arg){
for (int i = 0 ; i < 5 ; i++){
   printf("Thread %d prints %d\n",number,a);
   a++;
   //sleep(1)//;
}
   number++;
}
