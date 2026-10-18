#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateArray(int data[], int size, int low, int high) {
    if (size < 0 || low > high || (size > 0 && data == NULL)) return;

    unsigned long long range = (unsigned long long)((long long)high - low) + 1;
    unsigned long long base = (unsigned long long)RAND_MAX + 1;

    for (int i = 0; i < size; i++) {
        unsigned long long r = 0;
        for (int j = 0; j < 3; j++)
            r = (r * base + (unsigned long long)rand()) % range;
        data[i] = (int)((long long)low + (long long)r);
    }
}

int main(void) {
    int data[10];
    srand((unsigned)time(NULL));
    generateArray(data, 10, 1, 20);
    for (int i = 0; i < 10; i++) printf("%d ", data[i]);
    puts("");
    return 0;
}
