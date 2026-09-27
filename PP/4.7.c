#include <stdio.h>
#include <limits.h>

int main()
{
    printf("C sveikuju duomenu tipu reziai:\n\n");
    //taciau teoriskai galima tiesiog for loop'e padaryti kad ziuro ar neivyko overflow, ir taip gaunam rezius.
    printf("signed char:\n");
    printf("min = %d\n", SCHAR_MIN);
    printf("max = %d\n\n", SCHAR_MAX);

    printf("unsigned char:\n");
    printf("min = 0\n");
    printf("max = %u\n\n", UCHAR_MAX);

    printf("short:\n");
    printf("min = %d\n", SHRT_MIN);
    printf("max = %d\n\n", SHRT_MAX);

    printf("unsigned short:\n");
    printf("min = 0\n");
    printf("max = %u\n\n", USHRT_MAX);

    printf("int:\n");
    printf("min = %d\n", INT_MIN);
    printf("max = %d\n\n", INT_MAX);

    printf("unsigned int:\n");
    printf("min = 0\n");
    printf("max = %u\n\n", UINT_MAX);

    printf("long:\n");
    printf("min = %ld\n", LONG_MIN);
    printf("max = %ld\n\n", LONG_MAX);

    printf("unsigned long:\n");
    printf("min = 0\n");
    printf("max = %lu\n\n", ULONG_MAX);

    printf("long long:\n");
    printf("min = %lld\n", LLONG_MIN);
    printf("max = %lld\n\n", LLONG_MAX);

    printf("unsigned long long:\n");
    printf("min = 0\n");
    printf("max = %llu\n", ULLONG_MAX);

    return 0;
}