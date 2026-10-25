#include <stdio.h>

const char *largestFile(int argc, char *argv[]) {
    const char *largest = NULL;
    long biggest = -1;

    for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "rb");
        if (f == NULL) continue;

        if (fseek(f, 0, SEEK_END) == 0) {
            long size = ftell(f);
            if (size > biggest) {
                biggest = size;
                largest = argv[i];
            }
        }
        fclose(f);
    }
    return largest;
}

int main(int argc, char *argv[]) {
    const char *name = largestFile(argc, argv);
    if (name == NULL) {
        printf("Nera tinkamu failu.\n");
        return 1;
    }
    printf("Didziausias failas: %s\n", name);
    return 0;
}
