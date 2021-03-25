#ifndef __UTILS_H__
#define __UTILS_H__

#define forn(n) for (unsigned int i = 0; i < n; i++)

#define blank(k) forn(k) printf("\n")

#define error 4294967295

#define section(msg) printf("\n\n\n============================%s=============================\n\n\n",msg)

void print_in_red           (char*);
void print_in_green         (char*);
void check_cond             (char,char*,char*);
void check_bipartito        (char);
void check_sc               (char);
void check_coloreo_propio   (char);
void check_chicogrande      (char);
void check_wp               (char);
void check_alv              (char);

#endif