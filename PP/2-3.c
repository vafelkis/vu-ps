#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/*
stai trecioji uzduotis, kurios kurybos
metu teko pasikartoti rodykles [pointerius] 
ir tt, taciau viskas suprantama ir neblogai
sekesi atlikti uzduoti.

planuojama laiko buvo apie 30min,
taciau uztruko apie 80-90min
klaidu tiketasi mazai,
kas ir pasiteisino,
taciau teko perdaryti
uzduoti pagal salyga.
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
        if (!isspace((unsigned char)text[i]))
        {
            if (word_start == -1)
                word_start = i;
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
        reversuoti(text, word_start, i - 1);
}
void apdoroti_teksta(char **tekstas, int eiluciu_kiekis)
{
    for (int i = 0; i < eiluciu_kiekis; i++)
    {
        reversuoti_zodzius(tekstas[i]);
    }
}
int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 3)
    {
        printf("Naudojimas: %s <ivesties_failas> <isvesties_failas>\n", argv[0]);
        return 1;
    }
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("Klaida: ivesties failas neegzistuoja!\n");
        return 1;
    }
    FILE *fout = fopen(argv[2], "w");
    if (fout == NULL)
    {
        printf("Klaida: negalima sukurti isvesties failo!\n");
        fclose(fin);
        return 1;
    }
    int talpa = 10;
    int eiluciu_kiekis = 0;
    char **tekstas = malloc(talpa * sizeof(char *));
    if (tekstas == NULL)
    {
        fclose(fin);
        fclose(fout);
        return 1;
    }
    char line[99999];
    while (fgets(line, sizeof(line), fin) != NULL)
    {
        if (eiluciu_kiekis >= talpa)
        {
            talpa += 5;
            char **temp = realloc(tekstas, talpa * sizeof(char *));
            if (temp == NULL)
                break;
            tekstas = temp;
        }
        tekstas[eiluciu_kiekis] = malloc((strlen(line) + 1) * sizeof(char));
        if (tekstas[eiluciu_kiekis] != NULL)
        {
            strcpy(tekstas[eiluciu_kiekis], line);
            eiluciu_kiekis++;
        }
    }
    fclose(fin);
    apdoroti_teksta(tekstas, eiluciu_kiekis);
    for (int i = 0; i < eiluciu_kiekis; i++)
    {
        fputs(tekstas[i], fout);
        free(tekstas[i]);
    }
    free(tekstas);
    fclose(fout);
    printf("Atlikta!\n");
    return 0;
}