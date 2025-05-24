#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define num_threads 5
void *thread_func(void *arg) {
    int thread_id=*((int*) arg);
    printf("thread-%d running\n",thread_id);
    printf("thread-%d closed\n",thread_id);
}
int main(){
    pthread_t thread[num_threads];
    int thread_ids[num_threads];
    for (int i=0;i<num_threads;i++){
        thread_ids[i]=i+1;
        pthread_create(&thread[i],NULL, thread_func, (void*) &thread_ids[i]);
        pthread_join(thread[i],NULL);
    }
    return 0;
}
