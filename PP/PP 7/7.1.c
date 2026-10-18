#include <stdio.h>

int isInRange(int number, int low, int high) {
    return low <= high && number >= low && number <= high;
}

int main(void) {
    printf("%d\n", isInRange(5, 1, 10));
    printf("%d\n", isInRange(15, 1, 10));
    return 0;
}
