#include <stdio.h>

#define CAPACITY 1000

int main(void)
{
    int x[CAPACITY];
    int n;
    long long s;

    printf("Programa suranda skaiciu poras, kuriu sandauga lygi s.\n");

    printf("Iveskite s ir n: ");
    scanf("%lld %d", &s, &n);

    if (n < 0 || n > CAPACITY)
    {
        printf("Netinkamas elementu skaicius.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        do
        {
            printf("Iveskite x[%d] (teigiamas skaicius): ", i);
            scanf("%d", &x[i]);

            if (x[i] <= 0)
                printf("Skaicius turi buti teigiamas.\n");

        } while (x[i] <= 0);
    }

    printf("Poros, kuriu sandauga lygi %lld:\n", s);

    int found = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if ((long long)x[i] * x[j] == s)
            {
                printf("(%d, %d)\n", x[i], x[j]);
                found = 1;
            }
        }
    }

    if (!found)
        printf("Tokiu poru nera.\n");

    return 0;
}