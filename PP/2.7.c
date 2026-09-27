#include <stdio.h>

int main() {
    long n;
    printf("prasome ivesti kazkoki numeri, ir bus surikiuota.\njusu skaicius: ");
    scanf("%lld", &n);

    long result = 0;

    for (int d = 9; d >= 0; d--) {
        long temp = n;
        while (temp > 0) {
            if (temp % 10 == d)
                result = result * 10 + d;
            temp /= 10;
        }
    }

    printf("%lld\n", result);
    return 0;
}