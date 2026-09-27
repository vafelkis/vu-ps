#include <stdio.h>
#include <math.h>
int main()
{
    double x,y,z;
    printf("iveskite x reiksme.\n");
    scanf("%lf", &x);
    printf("iveskite y reiksme.\n");
    scanf("%lf", &y);
    printf("iveskite z reiksme.\n");
    scanf("%lf", &z);
    printf("%lf\n", x+4*y+powf(z,3));
    printf("%lf\n", (x+sqrtf(y))*(powf(z,4)-abs(z)+46.3));
    return 0;
}