#ifndef STR_TABLEAU_H
#define STR_TABLEAU_H


extern str_tableau_t * str_tableau_make(const int taille);
extern char * str_tableau_string(const str_tableau_t * tableau);
extern void str_tableau_free(str_tableau_t * tableau);
extern str_tableau_t * str_tableau_copy(const str_tableau_t * tableau);
extern str_tableau_t * str_tableau_reverse(const str_tableau_t * tableau);
extern str_tableau_t * str_tableau_fusion(const str_tableau_t * tab1, const str_tableau_t * tab2);
extern bool str_tableau_equal(const str_tableau_t * tab1, const str_tableau_t * tab2);

extern str_tableau_t * str_tableau_map(str_t * (* f)(const str_t *), const str_tableau_t * str_tableau);
extern void * str_tableau_fold(void * (* f)(const str_t *, const void *), const void * a, const str_tableau_t * str_tableau, void (* objet_free)(void *), void * (* objet_copy)(const void *));

struct str_tableau_t {
  int taille;
  int nb;
  str_t * * tab;
};


#endif /* STR_TABLEAU_H */

