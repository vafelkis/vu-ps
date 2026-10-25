#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

/* Binariame faile saugomi int skaiciai; indeksai prasideda nuo 0. */
static long countValues(FILE *file) {
    if (file == NULL || fseek(file, 0, SEEK_END) != 0) return -1;
    long bytes = ftell(file);
    if (bytes < 0 || bytes % (long)sizeof(int) != 0) return -1;
    return bytes / (long)sizeof(int);
}

static int goTo(FILE *file, long index) {
    return fseek(file, index * (long)sizeof(int), SEEK_SET);
}

/* Nesekmes atveju grazina -1 (taip pat -1 gali buti ir faile). */
int getValue(FILE *file, int index) {
    long count = countValues(file);
    int value;
    if (index < 0 || count < 0 || index >= count || goTo(file, index) != 0)
        return -1;
    if (fread(&value, sizeof(int), 1, file) != 1) return -1;
    return value;
}

int setValue(FILE *file, int index, int value) {
    long count = countValues(file);
    if (index < 0 || count < 0 || index >= count || goTo(file, index) != 0)
        return -1;
    if (fwrite(&value, sizeof(int), 1, file) != 1) return -1;
    return fflush(file) == 0 ? 0 : -1;
}

int addValue(FILE *file, int index, int value) {
    long count = countValues(file);
    if (index < 0 || count < 0 || index > count) return -1;

    for (long i = count; i > index; i--) {
        int temp;
        if (goTo(file, i - 1) != 0 || fread(&temp, sizeof(int), 1, file) != 1)
            return -1;
        if (goTo(file, i) != 0 || fwrite(&temp, sizeof(int), 1, file) != 1)
            return -1;
    }
    if (goTo(file, index) != 0 || fwrite(&value, sizeof(int), 1, file) != 1)
        return -1;
    return fflush(file) == 0 ? 0 : -1;
}

int remValue(FILE *file, int index) {
    long count = countValues(file);
    if (index < 0 || count < 0 || index >= count) return -1;

    for (long i = index; i < count - 1; i++) {
        int temp;
        if (goTo(file, i + 1) != 0 || fread(&temp, sizeof(int), 1, file) != 1)
            return -1;
        if (goTo(file, i) != 0 || fwrite(&temp, sizeof(int), 1, file) != 1)
            return -1;
    }
    if (fflush(file) != 0) return -1;

    long newSize = (count - 1) * (long)sizeof(int);
#ifdef _WIN32
    return _chsize_s(_fileno(file), (long long)newSize) == 0 ? 0 : -1;
#else
    return ftruncate(fileno(file), newSize) == 0 ? 0 : -1;
#endif
}

int main() {
    /* Reikia ir skaitymo, ir rasymo teisiu: w+b arba r+b. */
    FILE *file = fopen("numbers.bin", "w+b");
    if (file == NULL) return 1;

    int data[] = {10, 20, 30};
    if (fwrite(data, sizeof(int), 3, file) != 3 || fflush(file) != 0) {
        fclose(file);
        return 1;
    }

    printf("Pradinis antras: %d\n", getValue(file, 1));
    printf("Pakeitimas: %d\n", setValue(file, 1, 25));
    printf("Iterpimas: %d\n", addValue(file, 1, 15));
    printf("Trynimas: %d\n", remValue(file, 2));

    long count = countValues(file);
    for (long i = 0; i < count; i++) printf("%d ", getValue(file, (int)i));
    puts("");
    fclose(file);
    remove("numbers.bin");
    return 0;
}
