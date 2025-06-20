#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MaxCrops 5 // Maximum crops a Farmer can produce or a Shopowner can take
#define warehouseSize 5 // Size of the warehouse

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[] = {'R', 'W', 'P', 'S', 'M'}; // Indicating room for different crops
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'}; // Initially all the room is empty
pthread_mutex_t mutex;

void *Farmer(void *far) 
{
/*
1.Farmer harvest crops and put them in particular room. For example, room 0
for Rice(R).
2.use mutex and semaphore for critical section.
3.print which farmer is keeping which crops in which room inside the
critical section.

4.print the whole warehouse buffer outside of the critical section
*/   
    int *far_id = (int *)far; 
    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); 
        
        // Harvest a random crop
        char crop = crops[rand() % 5];
        warehouse[in] = crop; 

        printf("Farmer %d: Insert crops %c at %d\n", *far_id, crop, in);
        in = (in + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex); 
        sem_post(&full);
    }


    printf("Farmer%d: ", *far_id);
    for (int j = 0; j < warehouseSize; j++) {
        printf("%c ", warehouse[j]);
    }
    printf("\n");

    pthread_exit(NULL);
}

void *ShopOwner(void *sho) 
{ 
/*
1.Shop owner takes crops and makes that particular room empty.
2.use mutex and semaphore for critical section.
3.print which shop owner is taking which crops from which room inside the
critical section.
4.print the whole warehouse buffer outside of the critical section
*/  
    int *sho_id = (int *)sho; 

    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&full); 
        pthread_mutex_lock(&mutex); 
        
        char crop = warehouse[out];
        warehouse[out] = 'N'; //
        
        printf("Shop Owner %d: Removed crops %c from %d\n", *sho_id, crop, out);
        out = (out + 1) % warehouseSize; 
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    
    // Print warehouse state
    printf("ShopOwner%d: ", *sho_id);
    for (int j = 0; j < warehouseSize; j++) {
        printf("%c ", warehouse[j]);
    }
    printf("\n");

    pthread_exit(NULL);
}

int main() {   
/*initializing thread,mutex,semaphore
*/
    pthread_t Far[5], Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize); // when the warehouse is full, threads will wait
    sem_init(&full, 0, 0); // when the warehouse is empty, threads will wait

    int a[5] = {0, 1, 2, 3, 4}; // Just used for numbering the Farmer and ShopOwner

    /*create 5 thread for Farmer 5 thread for ShopOwner
-------------------------------------------------
-------------------------------------------------
*/
    for (int i = 0; i < 5; i++) {
        pthread_create(&Far[i], NULL, Farmer, &a[i]);
        pthread_create(&Sho[i], NULL, ShopOwner, &a[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(Far[i], NULL);
        pthread_join(Sho[i], NULL);
    }

    // Closing or destroying mutex and semaphore
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
