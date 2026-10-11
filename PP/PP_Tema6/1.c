#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_ERRORS 5
int main(void) {
    char s[256]; int errors=0;
    const IntRange range={1,20}; /* 20! telpa i unsigned long long */
    const Rule rules[]={{filter_integer_range,&range,"Reikia sveiko teigiamo skaiciaus nuo 1 iki 20 (didesnio faktorialas netilptu)."}};
    puts("Programa apskaiciuoja teigiamo sveiko skaiciaus faktoriala ir ji iraso i out.txt.");
    while (errors<MAX_ERRORS) {
        puts("Iveskite viena sveika skaiciu nuo 1 iki 20:");
        int status=read_line(s,sizeof s);
        if (!status) return 1;
        if (status<0 || !validate(s,rules,1)) {if(status<0) puts("Klaida: per ilga eilute."); errors++; continue;}
        unsigned n=(unsigned)strtoul(s,NULL,10); unsigned long long result=1;
        for(unsigned i=2;i<=n;i++) result*=i;
        FILE *f=fopen("out.txt","w");
        if(!f) {perror("Nepavyko atidaryti out.txt"); return 1;}
        printf("%u! = %llu\n",n,result);
        fprintf(f,"%u! = %llu\n",n,result);
        if(fclose(f)!=0) {perror("Failo uzdarymo klaida"); return 1;}
        puts("Rezultatas irasytas i out.txt."); return 0;
    }
    puts("Virsyta klaidu riba."); return 1;
}
