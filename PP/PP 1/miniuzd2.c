#include <stdio.h>

int rastimax(int skaic[], int n)
{
    int max = skaic[0];
    for (int i = 1; i < n; i++) {
        if (skaic[i] > max)
            max = skaic[i];
    }
    return max;
}

void rastimin(int skaic[], int n, int *min)
{
    *min = skaic[0];
    for (int i = 1; i < n; i++) {
        if (skaic[i] < *min)
            *min = skaic[i];
    }
}

int main()
{
    int n, skaic[1000];

    printf("iveskite n: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 1000) {
        printf("netinkamas n\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &skaic[i]);
    }

    int min;
    printf("max: %d\n", rastimax(skaic, n));

    rastimin(skaic, n, &min);
    printf("min: %d\n", min);

    return 0;
}