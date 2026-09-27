#include <stdio.h>
int main()
{
    printf("iveskite skaiciu.\n");
    int a;
    scanf("%d", &a);
    char *text = (a % 2 != 0) ? "ne lyginis" : "lyginis";
    printf("%s\n", text);
    return 0;
}