#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_BLOCKS 100

typedef struct {
    void *ptr;
    size_t size;
    void **owner;       /* Kintamasis, kuriame laikoma rodykle */
    int inArena;        /* Ar blokas yra bendrame bloke? */
} Block;

static Block blocks[MAX_BLOCKS];
static void *arena = NULL;

static int findBlock(void *p) {
    for (int i = 0; i < MAX_BLOCKS; i++)
        if (p != NULL && blocks[i].ptr == p) return i;
    return -1;
}

static int freeSlot(void) {
    for (int i = 0; i < MAX_BLOCKS; i++)
        if (blocks[i].ptr == NULL) return i;
    return -1;
}

void *myMalloc(size_t size) {
    if (size == 0) return NULL;
    int i = freeSlot();
    if (i == -1) return NULL;
    void *p = malloc(size);
    if (p != NULL) blocks[i] = (Block){p, size, NULL, 0};
    return p;
}

void *myCalloc(size_t count, size_t size) {
    if (count == 0 || size == 0 || count > SIZE_MAX / size) return NULL;
    int i = freeSlot();
    if (i == -1) return NULL;
    void *p = calloc(count, size);
    if (p != NULL) blocks[i] = (Block){p, count * size, NULL, 0};
    return p;
}

void myFree(void *p) {
    int i = findBlock(p);
    if (i == -1) return;
    if (!blocks[i].inArena) free(p);
    if (blocks[i].owner != NULL && *blocks[i].owner == p)
        *blocks[i].owner = NULL;
    blocks[i] = (Block){0};
}

void *myRealloc(void *p, size_t size) {
    if (p == NULL) return myMalloc(size);
    int i = findBlock(p);
    if (i == -1) return NULL;
    if (size == 0) {
        myFree(p);
        return NULL;
    }

    void *newPtr;
    if (blocks[i].inArena) {
        newPtr = malloc(size);
        if (newPtr == NULL) return NULL;
        size_t n = size < blocks[i].size ? size : blocks[i].size;
        memcpy(newPtr, p, n);
        blocks[i].inArena = 0;
    } else {
        newPtr = realloc(p, size);
        if (newPtr == NULL) return NULL;
    }

    if (blocks[i].owner != NULL) *blocks[i].owner = newPtr;
    blocks[i].ptr = newPtr;
    blocks[i].size = size;
    return newPtr;
}

size_t getMallocSize(void) {
    size_t total = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) total += blocks[i].size;
    return total;
}

void freeAll(void) {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (blocks[i].ptr != NULL && !blocks[i].inArena)
            free(blocks[i].ptr);
        if (blocks[i].owner != NULL) *blocks[i].owner = NULL;
        blocks[i] = (Block){0};
    }
    free(arena);
    arena = NULL;
}

/* Uzregistruojame rodykles KINTAMAJI, kad ji galetume atnaujinti. */
int watchPointer(void **owner) {
    if (owner == NULL) return -1;
    int i = findBlock(*owner);
    if (i == -1) return -1;
    blocks[i].owner = owner;
    return 0;
}

/* Visus blokus perkelia i viena vientisa atminties bloka.
   Visi blokai privalo tureti uzregistruotas rodykles! */
int defragmentMemory(void) {
    size_t total = getMallocSize();
    if (total == 0) {
        free(arena);
        arena = NULL;
        return 0;
    }

    for (int i = 0; i < MAX_BLOCKS; i++)
        if (blocks[i].ptr != NULL &&
            (blocks[i].owner == NULL || *blocks[i].owner != blocks[i].ptr))
            return -1;

    unsigned char *newArena = malloc(total);
    if (newArena == NULL) return -1;

    size_t offset = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (blocks[i].ptr == NULL) continue;
        memcpy(newArena + offset, blocks[i].ptr, blocks[i].size);
        offset += blocks[i].size;
    }

    offset = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (blocks[i].ptr == NULL) continue;
        if (!blocks[i].inArena) free(blocks[i].ptr);
        blocks[i].ptr = newArena + offset;
        blocks[i].inArena = 1;
        *blocks[i].owner = blocks[i].ptr;
        offset += blocks[i].size;
    }

    free(arena);
    arena = newArena;
    return 0;
}

int main(void) {
    void *a = myMalloc(3 * sizeof(int));
    void *b = myCalloc(2, sizeof(int));
    void *c = myMalloc(2 * sizeof(int));
    if (a == NULL || b == NULL || c == NULL) {
        freeAll();
        return 1;
    }

    if (watchPointer(&a) != 0 || watchPointer(&b) != 0 || watchPointer(&c) != 0) {
        freeAll();
        return 1;
    }

    ((int *)a)[0] = 10;
    ((int *)a)[1] = 20;
    ((int *)a)[2] = 30;
    ((int *)c)[0] = 99;

    myFree(b);              /* Atlaisviname vidurini bloka */
    if (defragmentMemory() != 0) {
        freeAll();
        return 1;
    }
    printf("Po sutankinimo: %zu baitu\n", getMallocSize());
    printf("a[1]=%d, c[0]=%d\n", ((int *)a)[1], ((int *)c)[0]);

    void *newA = myRealloc(a, 4 * sizeof(int));
    if (newA == NULL) {
        freeAll();
        return 1;
    }
    a = newA;
    ((int *)a)[3] = 40;
    printf("Po realloc: %zu baitu, a[3]=%d\n",
           getMallocSize(), ((int *)a)[3]);

    freeAll();
    printf("Po freeAll: %zu baitu\n", getMallocSize());
    return 0;
}
