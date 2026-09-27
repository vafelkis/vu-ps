#include <stdio.h>

int main()
{
    int n;
    int i;

    double skaicius;
    double suma = 0.0;
    double vidurkis;
    double minimumas;
    double maksimumas;

    printf("Programa apskaiciuoja n realiuju skaiciu suma, vidurki,\nminimuma ir maksimuma.\n");

    printf("Iveskite skaiciu kieki n: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Klaida: n turi buti teigiamas.\n");
        return 0;
    }

    printf("Iveskite %d realiuju skaiciu:\n", n);

    scanf("%lf", &skaicius);

    suma = skaicius;
    minimumas = skaicius;
    maksimumas = skaicius;

    for (i = 1; i < n; i++)
    {
        scanf("%lf", &skaicius);

        suma += skaicius;

        if (skaicius < minimumas)
            minimumas = skaicius;

        if (skaicius > maksimumas)
            maksimumas = skaicius;
    }

    vidurkis = suma / n;

    printf("Duomenys nuskaityti sekmingai.\n");

    printf("Suma = %.2f\n", suma);
    printf("Vidurkis = %.2f\n", vidurkis);
    printf("Minimumas = %.2f\n", minimumas);
    printf("Maksimumas = %.2f\n", maksimumas);

    return 0;
}