#include <stdio.h>

int conv_2_dec(char *text) {
    int result = 0;
    int i = 0;

    while (text[i] != '\0') {
        int bit = text[i] - '0';
        result = result * 2 + bit;
        i++;
    }

    return result;
}

int conv_16_dec(char *text) {
    int result = 0;
    int i = 0;

    while (text[i] != '\0') {
        int digit;
        char c = text[i];

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else {
            digit = c - 'A' + 10;
        }

        result = result * 16 + digit;
        i++;
    }

    return result;
}

void conv_dec_2(int number) {
    if (number > 1) {
        conv_dec_2(number / 2);
    }
    printf("%d", number % 2);
}

void conv_dec_16(int number) {
    if (number > 15) {
        conv_dec_16(number / 16);
    }
    printf("%X", number % 16);
}

int main() {
    printf("%d\n", conv_2_dec("11011"));
    printf("%d\n", conv_2_dec("10010100"));
    printf("%d\n", conv_2_dec("11001011010101"));

    conv_dec_2(37);
    printf("\n");
    conv_dec_2(241);
    printf("\n");
    conv_dec_2(2487);
    printf("\n");

    printf("%d\n", conv_16_dec("6E2"));
    printf("%d\n", conv_16_dec("ED33"));
    printf("%d\n", conv_16_dec("123456"));

    printf("0x");
    conv_dec_16(243);
    printf("\n");
    printf("0x");
    conv_dec_16(2483);
    printf("\n");
    printf("0x");
    conv_dec_16(4612);
    printf("\n");

    return 0;
}