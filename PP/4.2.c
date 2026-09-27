#include <stdio.h>

int main()
{
    int a, b, c;
    int i;
    int rasta = 0;

    printf("Programa randa teigiamus sveikuosius skaicius intervale (a; b],\nkurie dalijant is c duoda liekana 1.\n");

    printf("Iveskite a, b ir c: ");
    scanf("%d %d %d", &a, &b, &c);

    printf("Duomenys nuskaityti sekmingai.\n");

    if (c == 0)
    {
        printf("Klaida: dalyba is nulio negalima.\n");
        return 0;
    }

    if (a >= b)
    {
        printf("Klaida: intervalas (a; b] yra tuscias.\n");
        return 0;
    }

    printf("Tinkami skaiciai: ");

    for (i = a + 1; i <= b; i++)
    {
        if (i > 0 && i % c == 1)
        {
            printf("%d ", i);
            rasta = 1;
        }
    }

    if (!rasta)
        printf("nera");

    printf("\n");

    return 0;
}