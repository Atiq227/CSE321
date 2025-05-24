#include <stdio.h>
#include <string.h>

int main() {
FILE *source = NULL, *destination = NULL;
char src[] = "/home/atiq/input.txt";
char desti[] = "/home/atiq/output.txt";
char st[1024];
char *st1;

source = fopen(src, "r");
destination = fopen(desti, "w");

while (fgets(st, sizeof(st), source) != NULL) {
st1 = strtok(st, " ");
while (st1 != NULL)
{fputs(st1, destination);
st1 = strtok(NULL, " ");
if (st1 != NULL) {
fputc(' ', destination);
}
}
}
fclose(source);
fclose(destination);
return 0;
}

