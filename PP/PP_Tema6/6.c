/* 6a + 6b: failo zodziai tikrinami pagal surikiuota zodyna naudojant dvejetaine paieska.
   Nauji zodziai iterpiami islaikant rikiavima ir issaugomi baigus darba. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD 127
#define MAX_ERRORS 5

typedef struct {char **items; size_t n,cap;} Dictionary;
static void die(const char *msg){perror(msg);exit(1);}
static char *copyword(const char *s){char *p=malloc(strlen(s)+1);if(!p)die("malloc");strcpy(p,s);return p;}
static size_t position(const Dictionary *d,const char *s,int *found){
    size_t lo=0,hi=d->n;while(lo<hi){size_t mid=lo+(hi-lo)/2;int cmp=strcmp(d->items[mid],s);if(cmp<0)lo=mid+1;else hi=mid;}
    *found=(lo<d->n && strcmp(d->items[lo],s)==0);return lo;
}
static void insert(Dictionary *d,const char *s){
    int found;size_t pos=position(d,s,&found);if(found)return;
    if(d->n==d->cap){size_t c=d->cap?d->cap*2:16;char **a=realloc(d->items,c*sizeof *a);if(!a)die("realloc");d->items=a;d->cap=c;}
    memmove(d->items+pos+1,d->items+pos,(d->n-pos)*sizeof *d->items);
    d->items[pos]=copyword(s);d->n++;
}
static void lower(char *s){for(;*s;s++)*s=(char)tolower((unsigned char)*s);}
static void process_word(char *word,size_t line,size_t word_no,Dictionary *dict,FILE *errors){
    lower(word);int found;position(dict,word,&found);if(found)return;
    printf("Nezinomas zodis '%s' (%zu eilute, %zu zodis). [k] klaida / [p] prideti: ",word,line,word_no);
    char answer[64];
    while(1){
        if(!fgets(answer,sizeof answer,stdin)){puts("Ivestis nutraukta.");exit(1);}
        if(answer[0]=='k' || answer[0]=='K'){fprintf(errors,"%zu eilute, %zu zodis: %s\n",line,word_no,word);break;}
        if(answer[0]=='p' || answer[0]=='P'){insert(dict,word);break;}
        puts("Iveskite 'k' arba 'p':");
    }
}
int main(){
    Dictionary dict={0};char word[MAX_WORD+1],input[256];
    puts("6a/6b: programa tikrina teksto zodzius, klaidas fiksuoja errors.txt, naujus zodzius prideda i dictionary.txt.");
    FILE *d=fopen("dictionary.txt","r");
    if(!d)die("dictionary.txt");
    while(fgets(input,sizeof input,d)){
        if(!strchr(input,'\n') && !feof(d)){int c;while((c=fgetc(d))!='\n' && c!=EOF){};puts("Zodyne per ilgas zodis.");return 1;}
        input[strcspn(input,"\r\n")]=0;lower(input);if(*input)insert(&dict,input);
    }
    fclose(d);
    FILE *in=fopen("text.txt","r");if(!in)die("text.txt");
    FILE *err=fopen("errors.txt","w");if(!err)die("errors.txt");
    size_t line=1,word_no=0,len=0;int ch,too_long=0;
    while((ch=fgetc(in))!=EOF){
        if(isalpha((unsigned char)ch) || (unsigned char)ch>=128){
            if(len<MAX_WORD)word[len++]=(char)ch;else too_long=1;
        } else {
            if(len || too_long){word_no++;word[len]=0;
                if(too_long)fprintf(err,"%zu eilute, %zu zodis: per ilgas zodis\n",line,word_no);
                else process_word(word,line,word_no,&dict,err);
                len=0;too_long=0;
            }
            if(ch=='\n'){line++;word_no=0;}
        }
    }
    if(len || too_long){word_no++;word[len]=0;
        if(too_long)fprintf(err,"%zu eilute, %zu zodis: per ilgas zodis\n",line,word_no);
        else process_word(word,line,word_no,&dict,err);
    }
    fclose(in);fclose(err);
    d=fopen("dictionary.txt","w");if(!d)die("dictionary.txt write");
    for(size_t i=0;i<dict.n;i++){fprintf(d,"%s\n",dict.items[i]);free(dict.items[i]);}
    free(dict.items);fclose(d);
    puts("Baigta. Klaidos: errors.txt; zodynas: dictionary.txt (surikiuotas dvejetainei paieskai).");return 0;
}
