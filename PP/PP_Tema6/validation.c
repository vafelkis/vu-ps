#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

int read_line(char *s, size_t n) {
    if (!fgets(s, (int)n, stdin)) return 0;
    size_t len = strlen(s);
    if (len && s[len-1] == '\n') s[--len] = 0;
    else if (!feof(stdin)) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return -1; /* per ilga eilute */
    }
    if (len && s[len-1] == '\r') s[len-1] = 0;
    return 1;
}
int validate(const char *s, const Rule *rules, size_t count) {
    for (size_t i=0; i<count; ++i)
        if (!rules[i].fn(s, rules[i].param)) {
            printf("Klaida: %s\n", rules[i].error);
            return 0;
        }
    return 1;
}
int ends_with(const char *s, const char *suffix) {
    size_t a=strlen(s), b=strlen(suffix);
    return a>=b && strcmp(s+a-b,suffix)==0;
}
int filter_nonempty(const char *s, const void *p) { (void)p; return *s!='\0'; }
int filter_suffix(const char *s, const void *p) { return ends_with(s,(const char *)p); }
int filter_integer_range(const char *s, const void *p) {
    const IntRange *r=p; char *end; errno=0;
    if (!*s) return 0;
    for (const char *c=s; *c; ++c) if (!isdigit((unsigned char)*c)) return 0;
    long long v=strtoll(s,&end,10);
    return errno==0 && *end==0 && v>=r->min && v<=r->max;
}
static int decimal_format(const char *s, char sep, int *digits) {
    int before=0, after=0, seen=0;
    if (*s=='-' || *s=='+') s++;
    for (; *s; ++s) {
        if (isdigit((unsigned char)*s)) { if (seen) after++; else before++; }
        else if (*s==sep && !seen) seen=1;
        else return 0;
    }
    *digits=after;
    return before>0 && (!seen || after>0);
}
static int parse_real(const char *s, char sep, double *v) {
    int digits;
    if (!decimal_format(s,sep,&digits)) return 0;
    char temp[256]; if (strlen(s)>=sizeof temp) return 0;
    strcpy(temp,s);
    for (char *c=temp; *c; ++c) if (*c==sep) *c='.';
    char *end; errno=0; *v=strtod(temp,&end);
    return errno==0 && *end==0 && isfinite(*v);
}
int filter_decimal_range(const char *s, const void *p) {
    const RealRange *r=p; double v;
    return parse_real(s,r->separator,&v) && v>=r->min && v<=r->max;
}
int filter_decimal_places(const char *s, const void *p) {
    const Places *r=p; int digits;
    return decimal_format(s,r->separator,&digits) && digits<=r->maximum;
}
int filter_email(const char *s, const void *p) {
    (void)p;
    const char *at=strchr(s,'@');
    if (!at || at==s || strchr(at+1,'@')) return 0;
    const char *dot=strchr(at+1,'.');
    return dot && dot>at+1 && dot[1]!=0;
}
int parse_triple(const char *s, double v[3]) {
    const char *p=s;
    for (int i=0;i<3;i++) {
        const char *start=p;
        if (*p=='+' || *p=='-') ++p;
        int digits=0;
        while (isdigit((unsigned char)*p)) { p++; digits++; }
        if (*p=='.') { p++; while(isdigit((unsigned char)*p)) {p++; digits++;} }
        if (!digits) return 0;
        size_t len=(size_t)(p-start);
        if (len>=128) return 0;
        char buf[128]; memcpy(buf,start,len); buf[len]=0;
        char *end; errno=0; v[i]=strtod(buf,&end);
        if (errno || *end || !isfinite(v[i])) return 0;
        if (i<2) { if (*p!=';') return 0; p++; }
    }
    return *p==0;
}
int filter_triple(const char *s, const void *p) { (void)p; double v[3]; return parse_triple(s,v); }
static int leap(int y) {return y%4==0 && (y%100!=0 || y%400==0);}
int parse_date(const char *s, int *y, int *m, int *d) {
    if (strlen(s)!=10 || s[4]!='-' || s[7]!='-') return 0;
    for (int i=0;i<10;i++) if (i!=4 && i!=7 && !isdigit((unsigned char)s[i])) return 0;
    *y=(s[0]-'0')*1000+(s[1]-'0')*100+(s[2]-'0')*10+s[3]-'0';
    *m=(s[5]-'0')*10+s[6]-'0'; *d=(s[8]-'0')*10+s[9]-'0';
    const int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    return *y>=1 && *m>=1 && *m<=12 && *d>=1 && *d<=days[*m]+(*m==2 && leap(*y));
}
int filter_date(const char *s, const void *p) {(void)p; int y,m,d;return parse_date(s,&y,&m,&d);}
