#include <stdio.h>
#include <limits.h>

int getFactorial(int number) {
    if (number < 0) return 0;
    if (number <= 1) return 1;

    /* Patikriname, ar rezultatas tilps i int, dar pries rekursija. */
    int product = 1;
    for (int i = 2; i <= number; i++) {
        if (product > INT_MAX / i) return 0;
        product *= i;
    }
    return number * getFactorial(number - 1);
}

int getFactorialWithoutRecursion(int number) {
    if (number < 0) return 0;
    int result = 1;
    for (int i = 2; i <= number; i++) {
        if (result > INT_MAX / i) return 0;
        result *= i;
    }
    return result;
}

int main() {
    printf("%d\n", getFactorial(5));
    printf("%d\n", getFactorialWithoutRecursion(5));
    printf("%d\n", getFactorial(13));
    return 0;
}
