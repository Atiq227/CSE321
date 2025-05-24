#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int result;
void *asciival(void *arg);
int main() {
    int val[3];
    pthread_t a[3];
    for (int i= 0; i<3;i++) {
        pthread_create(&a[i], NULL, asciival, NULL);
        pthread_join(a[i], NULL);
        val[i] = result;
    }
   
    int counter = 1;
    for(int i=0; i<3; i++)
    {
        for(int j=i+1; j<3; j++)
        {
            if(val[i] == val[j])
            {
                counter++;
                break;
            }
        }
    }
    if (counter == 3){
    printf("Youreka\n");
    }
    else if (counter == 2){
    printf("Miracle\n");
    }
    else{
    printf("Hasta la vista\n");
    }
   
    return 0;
   
}


void *asciival(void *arg) {
    char name[50];
    int sum = 0;
    printf("Please enter your name: \n");
    scanf("%s", name);
    int j;
    for (j=0;name[j]!='\0';j++) {
        sum=sum+name[j];
    }
    result = sum;
    printf("sum: %d\n", result);
}
