#include <stdio.h>
#include <string.h>

int main() {
char email[1024];
int j;
printf("Please enter the email: ");
scanf("%s", email);    
for (int i = 0; i < strlen(email); i++) {
if (email[i] == '@') 
{
j = i + 1;
break;
}
}
if (strcmp(email + j, "sheba.xyz")==0) 
{
printf("Email address is ok\n");
} 
else 
{
printf("Email address is outdated\n");
}
return 0;
}

