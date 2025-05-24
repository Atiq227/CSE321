#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
pid_t pidp;
printf("1. Parent process ID: %d\n", getpid());
pidp=fork();
if (pidp>0){
wait(NULL);}
else if (pidp==0){
  printf("2. Child process ID: %d\n",getpid());
  pid_t pidc;
  pidc=fork();
  if (pidc==0){
    printf("3. Grandchild process ID: %d\n",getpid());}
  else if (pidc>0){
    wait(NULL);
    pid_t pidg1;
    pidg1=fork();
    if (pidg1==0){
      printf("4. Grandchild process ID: %d\n",getpid());}
    else if (pidg1>0){
      wait(NULL);
      pid_t pidg2;
      pidg2=fork();
      if (pidg2==0){
        printf("5. Grandchild process ID: %d\n",getpid());}
      else if (pidg2>0){
        wait(NULL);
        exit(0);}
      else {
        printf("Fork failed");
        exit(1);}
        }
   else {
      printf("Fork failed");
      exit(1);}
      }
      }
else {
printf("Fork failed");
exit(1);}
return 0;
} 

