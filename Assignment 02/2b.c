#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
pid_t pid;
pid=fork();
if (pid>0) {
wait(NULL);
printf("I am parent\n");}
else if (pid==0){
pid_t pidg;
pidg=fork();
if (pidg>0){
wait(NULL);
printf("I am child\n");}
else if (pidg==0){
printf("I am grandchild\n");
exit(0);
}
else{
printf("Fork failed\n");
exit(1);
}
}
return 0;
}
