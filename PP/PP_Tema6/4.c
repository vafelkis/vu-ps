#include "validation.h"
#include <stdio.h>
#include <string.h>
#define MAX_ERRORS 5
/* Sakamoto formule: 0 = sekmadienis, 1 = pirmadienis */
static int weekday(int y,int m,int d) {
    static const int t[]={0,3,2,5,0,3,5,1,4,6,2,4};
    if(m<3)y--;
    return (y+y/4-y/100+y/400+t[m-1]+d)%7;
}
int main(void) {
    char s[256], days[7][128];int errors=0,y,m,d;
    const Rule rules[]={{filter_date,NULL,"Netaisyklinga data. Naudokite YYYY-MM-DD, tikra kalendorine data."}};
    puts("Programa nustato ivestos datos savaites diena pagal week.txt pavadinimus.");
    while(errors<MAX_ERRORS) {
        puts("Iveskite data formatu YYYY-MM-DD:");
        int st=read_line(s,sizeof s);if(!st)return 1;
        if(st<0 || !validate(s,rules,1)) {if(st<0)puts("Klaida: per ilga eilute.");errors++;continue;}
        parse_date(s,&y,&m,&d);puts("Data nuskaityta sekmingai.");
        FILE *f=fopen("week.txt","r");
        if(!f) {perror("Nepavyko atidaryti week.txt");return 1;}
        int ok=1;
        for(int i=0;i<7;i++) {
            if(!fgets(days[i],sizeof days[i],f)) {ok=0;break;}
            size_t len=strlen(days[i]);
            if(len && days[i][len-1]=='\n') days[i][--len]=0;
            if(len && days[i][len-1]=='\r')days[i][--len]=0;
            if(!len)ok=0;
        }
        if(ok && fgetc(f)!=EOF)ok=0;
        fclose(f);
        if(!ok) {puts("Klaida: week.txt privalo tureti lygiai 7 netuscias eilutes (nuo pirmadienio iki sekmadienio).");return 1;}
        printf("Savaites diena: %s\n",days[(weekday(y,m,d)+6)%7]);return 0;
    }
    puts("Virsyta klaidu riba.");return 1;
}
