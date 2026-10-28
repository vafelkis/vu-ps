#include <stdio.h>
#include <stdlib.h>

void uzpildom(int masyvas[], int dydis);
int* sukurtiruzpildyt(int dydis);
void pildomparams(int **masyvas_ptr, int dydis);
int main()
{
    int dydis = 10;
    int arr1[10];
    uzpildom(arr1, dydis);
    int *arr2 = sukurtiruzpildyt(dydis);
    int *arr3 = NULL;
    pildomparams(&arr3, dydis);
    printf("1. ");
    for (int i = 0; i < dydis; i++) printf("%d ", arr1[i]);
    printf("\n2. ");
    for (int i = 0; i < dydis; i++) printf("%d ", arr2[i]);
    printf("\n3. ");
    for (int i = 0; i < dydis; i++) printf("%d ", arr3[i]);
    free(arr2);
    free(arr3);
    return 0;
}
void uzpildom(int masyvas[], int dydis)
{
    for (int i = 0; i < dydis; i++)
    {
        masyvas[i] = i + 1;
    }
}
int* sukurtiruzpildyt(int dydis)
{
    int *masyvas = malloc(dydis * sizeof(int));
    for (int i = 0; i < dydis; i++)
    {
        masyvas[i] = i + 1;
    }
    return masyvas;
}
void pildomparams(int **masyvas_ptr, int dydis)
{
    *masyvas_ptr = malloc(dydis * sizeof(int));
    for (int i = 0; i < dydis; i++)
    {
        (*masyvas_ptr)[i] = i + 1;
    }
}