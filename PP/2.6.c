#include <stdio.h>
int main()
{
    int sk[3], min, max;
    for (int i = 0; i < 3; i++)
    {
        printf("iveskite %d-aji skaiciu.\n", i+1);
        scanf("%d", &sk[i]);
        min = (min > sk[i] || i == 0) ? sk[i] : min;
        max = (max < sk[i] || i == 0) ? sk[i] : max;
    }
    
    printf("%min: %d; max: %d;\n", min, max);
    return 0;
}