#include <stdio.h>
#include <string.h>

int main(){
char input[1024];
int upper = 0, lower = 0, special = 0, number = 0;
printf("Enter the password:- \n");
scanf("%s", input);
for (int i = 0; i < strlen(input); i++) 
{
if (input[i] >= 'a' && input[i] <= 'z') 
{
lower = 1;
}
if (input[i] >= 'A' && input[i] <= 'Z') 
{
upper = 1;
}
if (input[i] >= '0' && input[i] <= '9') 
{
number = 1;
}
if (input[i]=='!' || input[i]=='_' || input[i]=='@' || input[i]=='#' || input[i]=='$' || input[i]=='%' ||input[i]=='^' ||input[i]=='&' ||input[i]=='*' || input[i]=='(' ||input[i]==')') {
special = 1;
}
}
if (upper && lower && special && number) {
printf("OK");
} 
else 
{
int status = 1;
if (!upper) 
{
if (!status) printf(", ");
printf("Uppercase character missing");
status = 0;
}
if (!lower) 
{
if (!status) printf(", ");
printf("Lowercase character missing");
status = 0;
}
if (!number) {
if (!status) printf(", ");
printf("Digit missing");
status = 0;
}
if (!special) 
{
if (!status) printf(", ");
printf("Special character missing");
status = 0;
}
}
printf("\n");
return 0;
}
