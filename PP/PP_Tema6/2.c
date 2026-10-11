#include "validation.h"
#include <stdio.h>
#include <string.h>
#define MAX_ERRORS 5
int main(void) {
    int errors=0; char filename[256]="in.txt", line[256];
    const RealRange range={10,1000,','};
    const Places places={3,','};
    const Rule rules[]={
        {filter_decimal_range,&range,"Reikia realaus skaiciaus nuo 10 iki 1000, su kableliu kaip skirtuku."},
        {filter_decimal_places,&places,"Po kablelio leidziama daugiausia 3 skaitmenys."}
    };
    puts("Programa tikrina skaiciu is failo (10..1000, iki 3 skaitmenu po kablelio) ir isveda jo ilgi.");
    while(errors<MAX_ERRORS) {
        printf("Nuskaitomas failas: %s\n",filename);
        FILE *f=fopen(filename,"r");
        int ok=0;
        if (!f) puts("Klaida: failas neegzistuoja arba jo negalima atidaryti.");
        else {
            if (fgets(line,sizeof line,f)) {
                size_t len=strlen(line);
                if(len && line[len-1]=='\n') line[--len]=0;
                if(len && line[len-1]=='\r') line[--len]=0;
                int c=fgetc(f);
                if(c!=EOF || (len==sizeof line-1 && line[len-1]!='\0')) puts("Klaida: faile turi buti tik vienas skaicius vienoje eiluteje.");
                else if (validate(line,rules,2)) {printf("Skaicius nuskaitytas sekmingai. Ilgis: %zu simboliai.\n",strlen(line)); ok=1;}
            } else puts("Klaida: failas tuscias.");
            fclose(f);
        }
        if(ok) return 0;
        errors++; if(errors==MAX_ERRORS) break;
        puts("Iveskite kito duomenu failo varda:");
        int st=read_line(filename,sizeof filename);
        if(!st) return 1;
        if(st<0 || !filename[0]) {puts("Klaida: netinkamas failo vardas."); errors++; strcpy(filename,"in.txt");}
    }
    puts("Virsyta klaidu riba."); return 1;
}
