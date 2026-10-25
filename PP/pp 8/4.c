#include <stdio.h>
#include <stdlib.h>

int splitData(const int *data, int size, int firstSize,
              int **first, int **second) {
    if (data == NULL || size < 2 || firstSize < 1 || firstSize >= size ||
        first == NULL || second == NULL || first == second ||
        *first != NULL || *second != NULL)
        return -1;

    int *a = malloc((size_t)firstSize * sizeof(int));
    int *b = malloc((size_t)(size - firstSize) * sizeof(int));
    if (a == NULL || b == NULL) {
        free(a);
        free(b);
        return -1;
    }

    for (int i = 0; i < firstSize; i++) a[i] = data[i];
    for (int i = firstSize; i < size; i++) b[i - firstSize] = data[i];

    *first = a;
    *second = b;
    return 0;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    int *a = NULL, *b = NULL;

    if (splitData(data, 5, 2, &a, &b) != 0) return 1;

    for (int i = 0; i < 2; i++) printf("%d ", a[i]);
    printf("\n");
    for (int i = 0; i < 3; i++) printf("%d ", b[i]);
    printf("\n");

    free(a);
    free(b);
    return 0;
}
