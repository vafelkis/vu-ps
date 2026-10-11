#ifndef VALIDATION_H
#define VALIDATION_H
#include <stddef.h>
typedef int (*Filter)(const char *, const void *);
typedef struct { Filter fn; const void *param; const char *error; } Rule;
int validate(const char *s, const Rule *rules, size_t count);
int read_line(char *s, size_t n);
int ends_with(const char *s, const char *suffix);
int filter_integer_range(const char *s, const void *p);
int filter_decimal_range(const char *s, const void *p);
int filter_decimal_places(const char *s, const void *p);
int filter_email(const char *s, const void *p);
int filter_suffix(const char *s, const void *p);
int filter_triple(const char *s, const void *p);
int filter_date(const char *s, const void *p);
int filter_nonempty(const char *s, const void *p);
typedef struct { long long min, max; } IntRange;
typedef struct { double min, max; char separator; } RealRange;
typedef struct { int maximum; char separator; } Places;
int parse_date(const char *s, int *y, int *m, int *d);
int parse_triple(const char *s, double v[3]);
#endif
