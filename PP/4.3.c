#include <stdio.h>

int main()
{
    unsigned long long a, b;
    unsigned int c;
    unsigned int i;

    unsigned long long ankstesnis;
    unsigned long long dabartinis;
    unsigned long long kitas;

    printf("Programa skaiciuoja sekos c-aji nari.\nf0 = a, f1 = b, fc = f(c-1) + f(c-2).\n");

    printf("Iveskite neneigiamus a, b ir c: ");
    scanf("%llu %llu %u", &a, &b, &c);

    printf("Duomenys nuskaityti sekmingai.\n");

    if (c == 0)
    {
        printf("f%u = %llu\n", c, a);
        return 0;
    }

    if (c == 1)
    {
        printf("f%u = %llu\n", c, b);
        return 0;
    }

    ankstesnis = a;
    dabartinis = b;

    for (i = 2; i <= c; i++)
    {
        kitas = ankstesnis + dabartinis;

        ankstesnis = dabartinis;
        dabartinis = kitas;
    }

    printf("f%u = %llu\n", c, dabartinis);

    return 0;
}