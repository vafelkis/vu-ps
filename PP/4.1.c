#include <stdio.h>
#include <math.h>

int main()
{
    int a, b, c;
    double d, x1, x2;

    printf("Programa sprendzia kvadratine lygti ax^2 + bx + c = 0.\nIveskite tris sveikuosius skaicius a, b ir c: ");

    scanf("%d %d %d", &a, &b, &c);

    printf("Duomenys nuskaityti sekmingai.\n");

    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
                printf("Lygtis turi begalybe sprendiniu.\n");
            else
                printf("Lygtis sprendiniu neturi.\n");
        }
        else
        {
            x1 = -(double)c / b;
            printf("Lygtis turi viena sprendini: x = %.6f\n", x1);
        }

        return 0;
    }

    d = (double)b * b - 4.0 * a * c;

    if (d > 0)
    {
        x1 = (-b + sqrt(d)) / (2.0 * a);
        x2 = (-b - sqrt(d)) / (2.0 * a);

        printf("Lygtis turi du sprendinius.\n");
        printf("x1 = %.6f\n", x1);
        printf("x2 = %.6f\n", x2);
    }
    else if (d == 0)
    {
        x1 = -(double)b / (2.0 * a);

        printf("Lygtis turi viena sprendini.\n");
        printf("x = %.6f\n", x1);
    }
    else
    {
        printf("Lygtis realiuju sprendiniu neturi.\n");
    }

    return 0;
}