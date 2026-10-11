#include "validation.h"
#include <stdio.h>
#include <string.h>
#define MAX_ERRORS 5
int main(void) {
    char s[256];int errors=0;
    const Rule rules[]={{filter_email,NULL,"Reikia vieno @, bent vieno tasko po jo ir netusciu daliu pries @, tarp @ ir tasko, bei po tasko."}};
    puts("Programa tikrina el. pasto adresa, isveda domena ir kaupia teisingus adresus emails.txt.");
    while(errors<MAX_ERRORS) {
        puts("Iveskite el. pasto adresa:");
        int st=read_line(s,sizeof s);if(!st)return 1;
        if(st<0 || !validate(s,rules,1)) {if(st<0)puts("Klaida: per ilga eilute.");errors++;continue;}
        FILE *f=fopen("emails.txt","a");
        if(!f){perror("Negaliu papildyti emails.txt");return 1;}
        fprintf(f,"%s\n",s);
        if(fclose(f)!=0){perror("Nepavyko issaugoti");return 1;}
        printf("Adresas teisingas. Domenas: %s\n",strchr(s,'@')+1);
        puts("Adresas pridetas i emails.txt.");return 0;
    }
    puts("Virsyta klaidu riba.");return 1;
}
