#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACITY 1000

int main(void)
{
    int arr[CAPACITY];
    int a, b, c;

    printf("Programa sugeneruos c atsitiktiniu skaiciu intervale [a; b].\n");

    printf("Iveskite a, b ir c: ");
    scanf("%d %d %d", &a, &b, &c);

    if (a > b)
    {
        printf("Klaida: a negali buti didesnis uz b.\n");
        return 1;
    }

    if (c < 0 || c > CAPACITY)
    {
        printf("Klaida: c turi buti intervale [0; %d].\n", CAPACITY);
        return 1;
    }

    srand((unsigned) time(NULL));

    for (int i = 0; i < c; i++)
        arr[i] = a + rand() % (b - a + 1);

    printf("Sugeneruotas masyvas:\n");

    for (int i = 0; i < c; i++)
        printf("%d ", arr[i]);

    printf("\n");

    return 0;
}