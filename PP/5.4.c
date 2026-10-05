#include <stdio.h>

#define CAPACITY 1000

int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main(void)
{
    int arr[CAPACITY];
    int size = 0;
    int value;

    printf("Iveskite teigiamus skaicius.\n");
    printf("Ivedus neteigiama skaiciu, ivedimas bus baigtas.\n");

    while (size < CAPACITY)
    {
        printf("Iveskite skaiciu: ");
        scanf("%d", &value);

        if (value <= 0)
            break;

        arr[size] = value;
        size++;
    }

    if (size == CAPACITY)
        printf("Pasiekta maksimali masyvo talpa.\n");

    printf("Pirminiai skaiciai:\n");

    for (int i = 0; i < size; i++)
    {
        if (isPrime(arr[i]))
        {
            int alreadyPrinted = 0;

            for (int j = 0; j < i; j++)
            {
                if (arr[i] == arr[j])
                {
                    alreadyPrinted = 1;
                    break;
                }
            }

            if (!alreadyPrinted)
                printf("%d ", arr[i]);
        }
    }

    printf("\n");

    return 0;
}