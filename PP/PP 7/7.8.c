#include <stdio.h>
#include <stdlib.h>

static int median3(int a, int b, int c) {
    if ((a <= b && b <= c) || (c <= b && b <= a)) return b;
    if ((b <= a && a <= c) || (c <= a && a <= b)) return a;
    return c;
}

static int partition(int a[], int left, int right) {
    int pivot = median3(a[left], a[left + (right-left)/2], a[right]);
    int i = left, j = right;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            int temp = a[i]; a[i] = a[j]; a[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

static void sortRec(int a[], int left, int right) {
    if (left >= right) return;
    int split = partition(a, left, right);
    if (left < split - 1) sortRec(a, left, split - 1);
    if (split < right) sortRec(a, split, right);
}

void quickSortRecursive(int a[], int size) {
    if (a != NULL && size > 1) sortRec(a, 0, size-1);
}

typedef struct { int left, right; } Range;

void quickSortIterative(int a[], int size) {
    if (a == NULL || size <= 1) return;
    Range *stack = malloc((size_t)size * sizeof(Range));
    if (stack == NULL) return;

    int top = 0;
    stack[top++] = (Range){0, size-1};
    while (top > 0) {
        Range current = stack[--top];
        int split = partition(a, current.left, current.right);
        if (current.left < split - 1)
            stack[top++] = (Range){current.left, split-1};
        if (split < current.right)
            stack[top++] = (Range){split, current.right};
    }
    free(stack);
}

int main(void) {
    int a[] = {9, 4, 1, 7, 3, 3, 8};
    int b[] = {9, 4, 1, 7, 3, 3, 8};
    int size = sizeof(a)/sizeof(a[0]);
    quickSortRecursive(a, size);
    quickSortIterative(b, size);
    for (int i = 0; i < size; i++) printf("%d ", a[i]);
    puts("");
    for (int i = 0; i < size; i++) printf("%d ", b[i]);
    puts("");
    return 0;
}
