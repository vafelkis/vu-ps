#include "validation.h"
#include <stdio.h>
#define MAX_ERRORS 5
int main() {
    int errors=0; char s[256],name[256]; double v[3];
    const Rule numbers[]={{filter_triple,NULL,"Tiksliai 3 skaiciai be tarpu, atskirti kabliataskiais, pvz. -2;3.5;1."}};
    const Rule file_rules[]={{filter_nonempty,NULL,"Failo vardas negali buti tuscias."},{filter_suffix,".txt","Failo vardas privalo baigtis .txt."}};
    puts("Programa randa vidurini pagal reiksme is triju skaiciu ir ji iraso i pasirinkta .txt faila.");
    while(errors<MAX_ERRORS) {
        puts("Iveskite 3 skaicius viena eilute be tarpu, atskirkite ';' (desimtainis skirtukas '.'): ");
        int st=read_line(s,sizeof s); if(!st) return 1;
        if(st<0 || !validate(s,numbers,1)) {if(st<0) puts("Klaida: per ilga eilute.");errors++;continue;}
        parse_triple(s,v); puts("Skaiciai nuskaityti sekmingai."); break;
    }
    if(errors>=MAX_ERRORS) {puts("Virsyta klaidu riba.");return 1;}
    double middle=v[0]+v[1]+v[2];
    double low=v[0],high=v[0];
    for(int i=1;i<3;i++) {if(v[i]<low)low=v[i];if(v[i]>high)high=v[i];}
    middle-=low+high;
    while(errors<MAX_ERRORS) {
        puts("Iveskite rezultato failo varda, kuris baigiasi .txt:");
        int st=read_line(name,sizeof name); if(!st) return 1;
        if(st<0 || !validate(name,file_rules,2)) {if(st<0)puts("Klaida: per ilgas pavadinimas.");errors++;continue;}
        FILE *f=fopen(name,"w");
        if(!f) {perror("Klaida atidarant faila");errors++;continue;}
        fprintf(f,"Vidurinis skaicius: %.15g\n",middle);
        fclose(f);
        printf("Vidurinis skaicius %.15g irasytas i %s.\n",middle,name);
        return 0;
    }
    puts("Virsyta klaidu riba.");return 1;
}
