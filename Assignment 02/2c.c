#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main () {
pid_t a,b,c;
int counter=1;
a=fork();
if (a>0){
counter++;
wait(NULL);
}
else if(a==0){
if (getpid()%2!=0){
pid_t newa;
newa=fork();
if (newa==0){
counter++;}
exit(0);}
exit(0);
}
else{
printf("Fork failed\n");
exit(1);}

b=fork();
if (b>0){
counter++;
wait(NULL);
}
else if(b==0){
if (getpid()%2!=0){
pid_t newb;
newb=fork();
if (newb==0){
counter++;}
exit(0);}
}
else{
printf("Fork failed\n");
exit(1);}

c=fork();
if (c>0){
counter++;
wait(NULL);
}
else if(c==0){
if (getpid()%2!=0){
pid_t newc;
newc=fork();
if (newc==0){
counter++;}
exit(0);}
exit(0);
}
else{
printf("Fork failed\n");
exit(1);}
printf("Number of total process: %d\n",counter);
return 0;
}
