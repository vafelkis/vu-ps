#include <stdio.h>

#define MAX_N 30

int findSum(
    int arr[],
    int n,
    long long target,
    int index,
    long long sum,
    int chosen[],
    int chosenCount)
{
    if (index == n)
        return sum == target && chosenCount > 0;

    chosen[index] = 1;

    if (findSum(
        arr,
        n,
        target,
        index + 1,
        sum + arr[index],
        chosen,
        chosenCount + 1))
    {
        return 1;
    }

    chosen[index] = 0;

    if (findSum(
        arr,
        n,
        target,
        index + 1,
        sum,
        chosen,
        chosenCount))
    {
        return 1;
    }

    return 0;
}

int main(void)
{
    int arr[MAX_N];
    int chosen[MAX_N] = {0};

    int n;
    long long x;

    printf("Iveskite masyvo elementu kieki: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_N)
    {
        printf("Netinkamas masyvo dydis.\n");
        return 1;
    }

    printf("Iveskite %d skaiciu:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Iveskite x: ");
    scanf("%lld", &x);

    if (findSum(arr, n, x, 0, 0, chosen, 0))
    {
        printf("%lld galima sudaryti:\n", x);

        long long sum = 0;

        int first = 1;

        for (int i = 0; i < n; i++)
        {
            if (chosen[i])
            {
                if (!first)
                    printf(" + ");

                printf("%d", arr[i]);

                sum += arr[i];
                first = 0;
            }
        }

        printf(" = %lld\n", sum);
    }
    else
    {
        printf("%lld negalima sudaryti is masyvo elementu.\n", x);
    }

    return 0;
}