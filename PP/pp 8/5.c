#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kiekviena lentele[i][j] yra char* (teksto eilute). */
typedef struct {
    int n, m;
    char ***lentele;
} TextGrid;

void destroyGrid(TextGrid *g) {
    if (g == NULL) return;
    if (g->lentele != NULL) {
        for (int i = 0; i < g->n; i++) {
            if (g->lentele[i] != NULL) {
                for (int j = 0; j < g->m; j++) free(g->lentele[i][j]);
                free(g->lentele[i]);
            }
        }
        free(g->lentele);
    }
    free(g);
}

TextGrid *createGrid(int n, int m) {
    if (n <= 0 || m <= 0) return NULL;

    TextGrid *g = calloc(1, sizeof(TextGrid));
    if (g == NULL) return NULL;
    g->n = n;
    g->m = m;
    g->lentele = calloc((size_t)n, sizeof(char **));
    if (g->lentele == NULL) {
        destroyGrid(g);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        g->lentele[i] = calloc((size_t)m, sizeof(char *));
        if (g->lentele[i] == NULL) {
            destroyGrid(g);
            return NULL;
        }
    }
    return g;
}

int setString(TextGrid *g, int i, int j, const char *text) {
    if (g == NULL || text == NULL || i < 0 || j < 0 ||
        i >= g->n || j >= g->m) return -1;

    char *copy = malloc(strlen(text) + 1);
    if (copy == NULL) return -1;
    strcpy(copy, text);

    free(g->lentele[i][j]);
    g->lentele[i][j] = copy;
    return 0;
}

const char *getString(const TextGrid *g, int i, int j) {
    if (g == NULL || i < 0 || j < 0 || i >= g->n || j >= g->m)
        return NULL;
    return g->lentele[i][j];
}

int main(void) {
    TextGrid *g = createGrid(2, 3);
    if (g == NULL) return 1;

    if (setString(g, 0, 1, "Labas") != 0 ||
        setString(g, 1, 2, "Vilnius") != 0) {
        destroyGrid(g);
        return 1;
    }

    printf("%s\n", getString(g, 0, 1));
    printf("%s\n", getString(g, 1, 2));
    destroyGrid(g);
    return 0;
}
