#include <stdio.h>

long long to_decimal(char *s, int base) {
    long long result = 0;
    for (int i = 0; s[i]; i++) {
        int d;
        char c = s[i];
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'A' && c <= 'Z') d = c - 'A' + 10;
        else d = c - 'a' + 10;
        result = result * base + d;
    }
    return result;
}

void from_decimal(long long n, int base) {
    if (n >= base) from_decimal(n / base, base);
    int d = n % base;
    printf("%c", d < 10 ? '0' + d : 'A' + d - 10);
}

void conv(char *value, int from, int to) {
    from_decimal(to_decimal(value, from), to);
}

int main() {
    conv("11011", 2, 10); printf("\n");
    conv("37", 10, 2);    printf("\n");
    conv("6E2", 16, 10);  printf("\n");
    conv("243", 10, 16);  printf("\n");
    conv("11011", 2, 16); printf("\n");
    conv("F3", 16, 2);    printf("\n");
    return 0;
}