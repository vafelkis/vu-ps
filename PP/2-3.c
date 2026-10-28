#include <stdio.h>
#include <ctype.h>
#include <string.h>
/*
stai trecioji uzduotis, kurios kurybos
metu teko pasikartoti rodykles [pointerius] 
ir tt, taciau viskas suprantama ir neblogai
sekesi atlikti uzduoti.
*/
void reversuoti(char *str, int start, int end)
{
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
void reversuoti_zodzius(char *text)
{
    int i = 0;
    int word_start = -1;
    while (text[i] != '\0')
    {
        if (!isspace((unsigned char)text[i]) && text[i] != '\0')
        {
            if (word_start == -1)
            {
                word_start = i;
            }
        }
        else
        {
            if (word_start != -1)
            {
                reversuoti(text, word_start, i - 1);
                word_start = -1; 
            }
        }
        i++;
    }
    if (word_start != -1)
    {
        reversuoti(text, word_start, i - 1);
    }
}
int main()
{
    FILE *fptr = fopen("2-3.txt", "r");
    if (fptr == NULL)
    {
        perror("Nepavyko atidaryti failo");
        return 1;
    }
    char mystr[99999];
    while (fgets(mystr, sizeof(mystr), fptr) != NULL)
    {
        printf("Originalus: %s\n", mystr);

        reversuoti_zodzius(mystr);

        printf("Perdirbtas: %s", mystr);
    }
    fclose(fptr);
    return 0;
}