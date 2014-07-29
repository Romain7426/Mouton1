#ifndef TOKEN_LISTE_H
#define TOKEN_LISTE_H

#ifndef TOKEN_LISTE_T
#define TOKEN_LISTE_T
struct token_liste_t {
  struct token_liste_t * cdr;
  token_t * car;
};
#ifndef __cplusplus
typedef struct token_liste_t token_liste_t;
#endif
#endif


extern token_liste_t * token_liste_vide(void);
extern bool token_liste_vide_huh(const token_liste_t * l);
extern token_liste_t * token_liste_cons(const token_t * a, const token_liste_t * l);
extern token_liste_t * token_liste_cons_nocopy(token_t * a, token_liste_t * l);

extern void token_liste_free(token_liste_t * l);

extern token_liste_t * token_liste_copy(const token_liste_t * l);
extern unsigned int token_liste_longueur(const token_liste_t * l);

extern char * token_liste_string(const token_liste_t * l);

#if 0
extern token_liste_t * token_liste_list(unsigned int n, ...);
extern token_liste_t * token_liste_vlist(unsigned int n, va_list args); 
#endif

extern bool token_liste_equal(const token_liste_t * liste1, const token_liste_t * liste2); 

extern token_liste_t * token_liste_reverse(const token_liste_t * l);

extern void token_liste_reverse_surplace(token_liste_t * * liste); 

extern token_liste_t * token_liste_append(const token_liste_t * l, const token_liste_t * m);


extern bool token_liste_member(const token_t * a, const token_liste_t * liste);

extern bool token_liste_member_iteratif(const token_t * a, const token_liste_t * liste);

extern token_t * token_liste_pop(token_liste_t * * l);


extern token_liste_t * token_liste_map(token_t * (* f)(const token_t *), const token_liste_t * l);

extern token_t * token_liste_fold(token_t * (* f)(const token_t *, const token_t *), const token_t * a, const token_liste_t * l);


#endif /* TOKEN_LISTE_H */
