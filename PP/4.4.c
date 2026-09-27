#include <stdio.h>

unsigned long long dbd(unsigned long long a, unsigned long long b)
{
    unsigned long long liekana;

    while (b != 0)
    {
        liekana = a % b;
        a = b;
        b = liekana;
    }

    return a;
}

int main()
{
    unsigned long long a, b, c;

    unsigned long long dbd_ab;
    unsigned long long dbd_abc;

    unsigned long long mbk_ab;
    unsigned long long mbk_abc;

    printf("Programa skaiciuoja triju naturaliuju skaiciu DBD ir MBK.\nIveskite a, b ir c: ");

    scanf("%llu %llu %llu", &a, &b, &c);

    printf("\nDuomenys nuskaityti sekmingai.\n");

    if (a == 0 || b == 0 || c == 0)
    {
        printf("Klaida: reikia ivesti naturaliuosius skaicius (> 0).\n");
        return 0;
    }

    dbd_ab = dbd(a, b);
    dbd_abc = dbd(dbd_ab, c);

    mbk_ab = a / dbd(a, b) * b;
    mbk_abc = mbk_ab / dbd(mbk_ab, c) * c;

    printf("DBD = %llu\n", dbd_abc);
    printf("MBK = %llu\n", mbk_abc);

    return 0;
}