#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
char pal[400];
char *start, *finish;
scanf("%s",pal);
start=pal;
finish=start+strlen(pal)-1;
int status=1;
while (start<finish)
{
if (tolower(*start)!=tolower(*finish)){
printf("Not Pallindrome\n");
status = 0;
break;
}
start++;
finish--;
}
if (status) printf("Pallindrome\n");
return 0;
}
