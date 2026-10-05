#include <stdio.h>

#define CAPACITY 1000

void countDigits(long long number, int count[10])
{
    for (int i = 0; i < 10; i++)
        count[i] = 0;

    if (number < 0)
        number = -number;

    if (number == 0)
    {
        count[0] = 1;
        return;
    }

    while (number > 0)
    {
        int digit = number % 10;
        count[digit]++;
        number /= 10;
    }
}

int canCreate(long long source, long long number)
{
    int sourceDigits[10];
    int numberDigits[10];

    countDigits(source, sourceDigits);
    countDigits(number, numberDigits);

    for (int i = 0; i < 10; i++)
    {
        if (numberDigits[i] > sourceDigits[i])
            return 0;
    }

    return 1;
}

int main(void)
{
    long long x;
    long long arr[CAPACITY];
    int n;

    printf("Iveskite skaiciu x: ");
    scanf("%lld", &x);

    printf("Iveskite masyvo elementu kieki: ");
    scanf("%d", &n);

    if (n < 0 || n > CAPACITY)
    {
        printf("Netinkamas masyvo dydis.\n");
        return 1;
    }

    printf("Iveskite %d skaiciu:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%lld", &arr[i]);

    int allPossible = 1;

    for (int i = 0; i < n; i++)
    {
        if (canCreate(x, arr[i]))
        {
            printf("%lld galima sudaryti is %lld skaitmenu.\n",
                   arr[i], x);
        }
        else
        {
            printf("%lld NEGALIMA sudaryti is %lld skaitmenu.\n",
                   arr[i], x);

            allPossible = 0;
        }
    }

    if (allPossible)
        printf("Visus masyvo skaicius galima sudaryti.\n");
    else
        printf("Ne visus masyvo skaicius galima sudaryti.\n");

    return 0;
}