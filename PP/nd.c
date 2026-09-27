#include <stdio.h>

int main()
{
    printf("Iveskite skaiciu seka (nuliui ivestam - pabaiga):\n");
    
    int temp, index = 0, nar = 0; 

    scanf("%d", &temp);

    while (temp != 0)
    {
        if (temp < 0)
        {
            printf("Galima tik TEIGIAMUS skaicius, bandykite dar karta\n");
        }
        else
        {
            if (index % 2 == 1)
            {
                nar++;
            }
            index++;
        }
        
        scanf("%d", &temp);
    }

    printf("Galinis lyginiu nariu skaicius: %d\n", nar);

    return 0;
}