#ifndef STR_LISTE_H
#define STR_LISTE_H

#ifndef STRUCT_STR_LISTE_T
#define STRUCT_STR_LISTE_T
struct str_liste_t {
  struct str_liste_t * cdr;
  str_t * car;
};
#endif
#ifndef STR_LISTE_T
#define STR_LISTE_T
#ifndef __cplusplus
typedef struct str_liste_t str_liste_t;
#endif
#endif


extern str_liste_t * str_liste_vide(void);
extern bool str_liste_vide_huh(const str_liste_t * l);
extern str_liste_t * str_liste_cons(const str_t * a, const str_liste_t * l);
extern str_liste_t * str_liste_cons_nocopy(str_t * a, str_liste_t * l);

extern void str_liste_free(str_liste_t * l);
extern void str_liste_free_nocopy(str_liste_t * l);

extern str_liste_t * str_liste_copy(const str_liste_t * l);
extern unsigned int str_liste_longueur(const str_liste_t * l);

extern char * str_liste_string(const str_liste_t * l);

#if 0
extern str_liste_t * str_liste_list(unsigned int n, ...);
extern str_liste_t * str_liste_vlist(unsigned int n, va_list args); 
#endif

extern bool str_liste_equal(const str_liste_t * liste1, const str_liste_t * liste2); 

extern str_liste_t * str_liste_reverse(const str_liste_t * l);

extern void str_liste_reverse_surplace(str_liste_t * * liste); 

extern str_liste_t * str_liste_append(const str_liste_t * l, const str_liste_t * m);
extern void str_liste_append_nocopy(str_liste_t * * l, str_liste_t * m);


extern bool str_liste_member(const str_t * a, const str_liste_t * liste);

extern bool str_liste_member_iteratif(const str_t * a, const str_liste_t * liste);

extern str_t * str_liste_pop(str_liste_t * * l);


extern str_liste_t * str_liste_map(str_t * (* f)(const str_t *), const str_liste_t * l);

extern str_t * str_liste_fold(str_t * (* f)(const str_t *, const str_t *), const str_t * a, const str_liste_t * l);


extern uint_t str_liste_count(const str_t * a, const str_liste_t * l);


#endif /* STR_LISTE_H */
