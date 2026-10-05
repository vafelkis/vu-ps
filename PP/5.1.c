#include <stdio.h>

#define CAPACITY 10
void printarr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main(void)
{
    int arr[CAPACITY] = {0};
    int size = CAPACITY;

    printf("Programa atlieka operacijas su 10 elementu masyvu.\n");

    printf("Pradinis masyvas:\n");
    printarr(arr, size);

    arr[0] = 1;
    arr[3] = 2;
    arr[9] = 3;

    for (int i = 2; i < size - 1; i++)
        arr[i] = arr[i + 1];

    size--;

    if (size < CAPACITY)
    {
        for (int i = size; i > 6; i--)
            arr[i] = arr[i - 1];

        arr[6] = 4;
        size++;
    }

    printf("Masyvas po pradinių operaciju:\n");
    printarr(arr, size);

    int x, y;

    printf("Iveskite indeksa x ir nauja reiksme y: ");
    scanf("%d %d", &x, &y);

    if (x >= 0 && x < size)
    {
        arr[x] = y;
        printf("Reiksme pakeista sekmingai.\n");
    }
    else
    {
        printf("Klaida: toks indeksas neegzistuoja.\n");
    }

    printf("Iveskite elemento, kuri norite istrinti, indeksa x: ");
    scanf("%d", &x);

    if (x >= 0 && x < size)
    {
        for (int i = x; i < size - 1; i++)
            arr[i] = arr[i + 1];

        size--;
        printf("Elementas istrintas sekmingai.\n");
    }
    else
    {
        printf("Klaida: toks indeksas neegzistuoja.\n");
    }

    printf("Iveskite indeksa x ir iterpiama reiksme y: ");
    scanf("%d %d", &x, &y);

    if (size >= CAPACITY)
    {
        printf("Klaida: masyvas pilnas.\n");
    }
    else if (x < 0 || x > size)
    {
        printf("Klaida: netinkamas indeksas.\n");
    }
    else
    {
        for (int i = size; i > x; i--)
            arr[i] = arr[i - 1];

        arr[x] = y;
        size++;

        printf("Elementas iterptas sekmingai.\n");
    }

    printf("Galutinis masyvas:\n");
    printarr(arr, size);

    return 0;
}