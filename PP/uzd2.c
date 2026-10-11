#include <stdio.h>

/* 
stai dvylikta uzduotis, antros uzduoties.
sunku nebuvo, taciau pamirsau pasiskaityti
reikalavimas ir prideti daugiau funkciju.
galu gale, viska supratau ir viskas smagu.
*/

int neigiami(int skaic[], int n, int rez[], int j)
{
    for (int i = 0; i < n; i++) {
        if (skaic[i] < 0) {
            rez[j] = skaic[i];
            j++;
        }
    }

    return j;
}

void neneigiami(int skaic[], int n, int rez[], int *j)
{
    for (int i = 0; i < n; i++) {
        if (skaic[i] >= 0) {
            rez[*j] = skaic[i];
            (*j)++;
        }
    }
}

int main()
{
    int n, skaic[1000], rez[1000];

    printf("Iveskite n, is kuriu surikiuosime neigiamus ir teigiamas palaikant ju originalia tvarka: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 1000) {
        printf("Netinkamas n\n");
        return 1;
    }

    printf("Iveskite n[%d] - sveiku skaiciu: ", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &skaic[i]);
    }

    int j = 0;

    j = neigiami(skaic, n, rez, j);
    neneigiami(skaic, n, rez, &j);

    printf("Rezultatas: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", rez[i]);
    }

    printf("\n");

    return 0;
}