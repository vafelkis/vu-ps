#include <stdio.h>
int main() {
    printf("iveskite n skaiciu\n");
    int n,suma = 0;
    scanf("%d", &n);
    for (int i = 0; i < n+1; i++)
    {
        suma += i*i;
    }
    printf("jusu suma: %d", suma);
    return 0;
}