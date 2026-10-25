#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int a = 5, b = 10;
    printf("Pries: %d %d\n", a, b);
    swap(&a, &b);
    printf("Po:    %d %d\n", a, b);
    return 0;
}
