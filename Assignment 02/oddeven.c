#include <stdio.h>
#include <stdlib.h>
void oddeven(int arr[], int n){
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

int main(int argc, char *argv[]) {
if (argc < 2) {
printf("%s \n", argv[0]);
return 1;}

int n = argc - 1;
int arr[n];

for (int i = 0; i < n; i++){
arr[i] = atoi(argv[i+1]);
}
oddeven(arr, n);
return 0;
}
