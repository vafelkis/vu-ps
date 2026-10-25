#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

/* Papildytas 7.6 meniu: iskviecia pasirinkto punkto funkcija. */
void showMenu(char *menuTitle, char *menuOptions[], int menuSize,
              char *inputMsg, void (*actions[])()) {
    char line[100], *end;
    long choice;
    if (menuSize < 1 || menuOptions == NULL || actions == NULL) return;

    while (1) {
        puts(menuTitle);
        for (int i = 0; i < menuSize; i++)
            printf("%d. %s\n", i + 1, menuOptions[i]);
        printf("%s", inputMsg);

        if (!fgets(line, sizeof(line), stdin)) return;
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
            choice >= 1 && choice <= menuSize) {
            if (actions[choice - 1] != NULL) actions[choice - 1]();
            return;
        }
        puts("Neteisingas pasirinkimas.\n");
    }
}

void hello() { puts("Labas!"); }
void goodbye() { puts("Iki!"); }

int main() {
    char *options[] = {"Pasisveikinti", "Atsisveikinti"};
    void (*actions[])() = {hello, goodbye};
    showMenu("MENIU", options, 2, "Pasirinkite: ", actions);
    return 0;
}
