#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("'%s' is oppened.\n", argv[1]);
    printf("Enter strings. Type '-1' to end.\n");

    char input[256];

    while (1) {
        printf("Write something: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "-1") == 0) {
            printf("'%s' closed\n", argv[1]);
            break;
        }

        fprintf(file, "%s\n", input);
        printf("'%s' is written.\n", input);
    }

    fclose(file);

    return 0;
}
