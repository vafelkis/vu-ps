#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 25

long long bestDifference = LLONG_MAX;

int current[MAX_N];
int best[MAX_N];

void findBestPartition(
    int arr[],
    int n,
    int index,
    long long sumA,
    long long total)
{
    if (index == n)
    {
        long long sumB = total - sumA;

        long long difference = llabs(sumA - sumB);

        if (difference < bestDifference)
        {
            bestDifference = difference;

            for (int i = 0; i < n; i++)
                best[i] = current[i];
        }

        return;
    }

    current[index] = 1;

    findBestPartition(
        arr,
        n,
        index + 1,
        sumA + arr[index],
        total
    );

    current[index] = 0;

    findBestPartition(
        arr,
        n,
        index + 1,
        sumA,
        total
    );
}

int main(void)
{
    int arr[MAX_N];
    int n;

    printf("Iveskite masyvo elementu kieki: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_N)
    {
        printf("Netinkamas masyvo dydis.\n");
        return 1;
    }

    long long total = 0;

    printf("Iveskite %d skaiciu:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        total += arr[i];
    }

    findBestPartition(arr, n, 0, 0, total);

    long long sumA = 0;
    long long sumB = 0;

    printf("Pirma dalis: ");

    for (int i = 0; i < n; i++)
    {
        if (best[i])
        {
            printf("%d ", arr[i]);
            sumA += arr[i];
        }
    }

    printf("\nAntra dalis: ");

    for (int i = 0; i < n; i++)
    {
        if (!best[i])
        {
            printf("%d ", arr[i]);
            sumB += arr[i];
        }
    }

    printf("\n");

    printf("Pirmos dalies suma: %lld\n", sumA);
    printf("Antros dalies suma: %lld\n", sumB);
    printf("Skirtumas: %lld\n", llabs(sumA - sumB));

    return 0;
}