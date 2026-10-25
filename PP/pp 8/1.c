#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *createArray(int size, int low, int high) {
    if (size <= 0 || low > high) return NULL;

    int *a = malloc((size_t)size * sizeof(int));
    if (a == NULL) return NULL;

    int *p = &(*a);  /* & ir *: pirmo elemento adresas */
    for (int i = 0; i < size; i++)
        *(p + i) = low + rand() % (high - low + 1);

    return a;
}

int main(void) {
    srand((unsigned)time(NULL));
    int size = 8;
    int *a = createArray(size, 1, 20);
    if (a == NULL) return 1;

    for (int i = 0; i < size; i++) printf("%d ", *(a + i));
    printf("\n");

    free(a);
    return 0;
}
