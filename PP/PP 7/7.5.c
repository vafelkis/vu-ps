#include <stdio.h>

long getFileSize(char *fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) return -1;

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return -1;
    }

    long size = ftell(file);
    if (fclose(file) != 0) return -1;
    return size;
}

int main() {
    FILE *file = fopen("example.bin", "wb");
    if (file == NULL) return 1;
    int ok = fwrite("Hello", 1, 5, file) == 5;
    if (fclose(file) != 0) ok = 0;
    if (!ok) return 1;

    printf("Failo dydis: %ld\n", getFileSize("example.bin"));
    printf("Nera failo: %ld\n", getFileSize("nera.bin"));
    remove("example.bin");
    return 0;
}
