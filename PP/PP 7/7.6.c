#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

int showMenu(char *menuTitle, char *menuOptions[], int menuSize, char *inputMsg) {
    char line[100], *end;
    long choice;
    if (menuSize < 1 || menuOptions == NULL) return -1;

    while (1) {
        puts(menuTitle);
        for (int i = 0; i < menuSize; i++)
            printf("%d. %s\n", i + 1, menuOptions[i]);
        printf("%s", inputMsg);

        if (!fgets(line, sizeof(line), stdin)) return -1;
        if (!strchr(line, '\n') && strlen(line) == sizeof(line) - 1) {
            int ch = getchar();
            if (ch != '\n' && ch != EOF) {
                while ((ch = getchar()) != '\n' && ch != EOF) { }
                puts("Neteisingas pasirinkimas.\n");
                continue;
            }
        }
        errno = 0;
        choice = strtol(line, &end, 10);
        while (isspace((unsigned char)*end)) end++;
        if (end != line && *end == '\0' && errno == 0 &&
            choice >= 1 && choice <= menuSize)
            return (int)choice;
        puts("Neteisingas pasirinkimas.\n");
    }
}

int main() {
    char *options[] = {"Pirmas", "Antras", "Baigti"};
    int choice = showMenu("MENIU", options, 3, "Pasirinkite: ");
    printf("Pasirinkote: %d\n", choice);
    return 0;
}
