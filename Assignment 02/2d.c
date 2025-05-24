#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubblesort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) { 
        for (j = 0; j < n-i-1; j++) { 
            if (arr[j] < arr[j+1]) { 
                temp = arr[j]; 
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
if (argc<2){
printf("%s \n",argv[0]);
return 1;
}
int arr[argc-1];
for (int i=0; i<argc-1;i++){
arr[i]=atoi(argv[i+1]);
}
int n=argc-1;
pid_t pid;
pid=fork();
if (pid>0){
wait(NULL);
printf("Status according to the parent process: ");
for (int i=0;i<n;i++){
if (arr[i]%2==0){
printf("Even ");
}
else {
printf("Odd ");
}
}
printf("\n");
}

else if (pid==0){
bubblesort(arr,n);
printf("Sorted array in child: ");
for (int i=0;i<n;i++){
printf("%d ",arr[i]);
}
printf("\n");
return 0;
}
}
