#include <stdio.h>

int perfect(int num){
int sum=0;
for (int i =1; i<num; i++){
	if (num%i==0){
	sum+=i;
	}
     }
     return sum==num;
}
void perfect_num(int i,int j){
     for (i;i<=j;i++){
     	if (perfect(i)){
     	  printf("%d\n",i);
          }
        }
}

int main(){
int i,j;
scanf("%d",&i);
scanf("%d",&j);
perfect_num(i,j);
return 0;
}
