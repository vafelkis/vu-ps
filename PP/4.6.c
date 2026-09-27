#include <stdio.h>

int main()
{
    unsigned long long skaicius;
    unsigned long long temp;
    unsigned long long didziausias = 0;

    int skaitmenu;
    int daugiausiaiSkaitmenu = 0;
    int yraSkaiciu = 0;

    printf("Programa randa teigiama skaiciu, kuris turi daugiausiai skaitmenu.\n");
    printf("Sekos pabaiga zymima neteigiama reiksme.\n");

    while (1)
    {
        long long ivestis;

        printf("Iveskite skaiciu: ");
        scanf("%lld", &ivestis);

        if (ivestis <= 0)
            break;

        skaicius = (unsigned long long)ivestis;
        temp = skaicius;
        skaitmenu = 0;

        while (temp > 0)
        {
            skaitmenu++;
            temp /= 10;
        }

        if (!yraSkaiciu || skaitmenu > daugiausiaiSkaitmenu)
        {
            daugiausiaiSkaitmenu = skaitmenu;
            didziausias = skaicius;
        }

        yraSkaiciu = 1;
    }

    if (!yraSkaiciu)
    {
        printf("Nebuvo ivestas nei vienas teigiamas skaicius.\n");
    }
    else
    {
        printf("Daugiausiai skaitmenu turi skaicius %llu.\n", didziausias);
        printf("Skaitmenu skaicius: %d\n", daugiausiaiSkaitmenu);
    }

    return 0;
}