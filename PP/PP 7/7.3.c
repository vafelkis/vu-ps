#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

int getPositiveNumber(char *msg) {
    char line[128], *end;
    long number;

    while (1) {
        printf("%s", msg);
        if (!fgets(line, sizeof(line), stdin)) return 0;

        if (!strchr(line, '\n') && strlen(line) == sizeof(line) - 1) {
            int ch = getchar();
            if (ch != '\n' && ch != EOF) {
                while ((ch = getchar()) != '\n' && ch != EOF) { }
                puts("Per ilga eilute.");
                continue;
            }
        }

        errno = 0;
        number = strtol(line, &end, 10);
        while (isspace((unsigned char)*end)) end++;
        if (end != line && *end == '\0' && errno == 0 &&
            number > 0 && number <= INT_MAX)
            return (int)number;

        puts("Iveskite viena teigiama sveika skaiciu.");
    }
}

int main(void) {
    int number = getPositiveNumber("Iveskite teigiama skaiciu: ");
    printf("Gauta: %d\n", number);
    return 0;
}
