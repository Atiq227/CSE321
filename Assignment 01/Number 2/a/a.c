#include <stdio.h>
int main(){
int value1,value2;
printf("Enter value 1:- \n");
scanf("%d",&value1);
printf("Enter value 2:- \n");
scanf("%d",&value2);
if (value1>value2){
int result=value1-value2;
printf("The result is :- %d\n",result);
}
else if (value1<value2){
int result=value2+value1;
printf("The result is:- %d\n",result);
}
else{
int result=value1*value2;
printf("The result is:- %d\n",result);
}
return 0;
}
