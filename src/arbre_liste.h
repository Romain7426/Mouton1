#ifndef ARBRE_LISTE_H
#define ARBRE_LISTE_H

#ifndef ARBRE_LISTE_T
#define ARBRE_LISTE_T
struct arbre_liste_t {
  struct arbre_liste_t * cdr;
  arbre_t * car;
};
#ifndef __cplusplus
typedef struct arbre_liste_t arbre_liste_t;
#endif
#endif


extern arbre_liste_t * arbre_liste_vide(void);
extern bool arbre_liste_vide_huh(const arbre_liste_t * l);
extern arbre_liste_t * arbre_liste_cons(const arbre_t * a, const arbre_liste_t * l);
extern arbre_liste_t * arbre_liste_cons_nocopy(arbre_t * a, arbre_liste_t * l);

extern void arbre_liste_free(arbre_liste_t * l);
extern void arbre_liste_free_nocopy(arbre_liste_t * l);

extern arbre_liste_t * arbre_liste_copy(const arbre_liste_t * l);
extern unsigned int arbre_liste_longueur(const arbre_liste_t * l);

extern char * arbre_liste_string(const arbre_liste_t * l);

#if 0
extern arbre_liste_t * arbre_liste_list(unsigned int n, ...);
extern arbre_liste_t * arbre_liste_vlist(unsigned int n, va_list args); 
#endif

extern bool arbre_liste_equal(const arbre_liste_t * liste1, const arbre_liste_t * liste2); 

extern arbre_liste_t * arbre_liste_reverse(const arbre_liste_t * l);

extern void arbre_liste_reverse_surplace(arbre_liste_t * * liste); 

extern arbre_liste_t * arbre_liste_append(const arbre_liste_t * l, const arbre_liste_t * m);


extern bool arbre_liste_member(const arbre_t * a, const arbre_liste_t * liste);

extern bool arbre_liste_member_iteratif(const arbre_t * a, const arbre_liste_t * liste);

extern arbre_t * arbre_liste_pop(arbre_liste_t * * l);


extern arbre_liste_t * arbre_liste_map(arbre_t * (* f)(const arbre_t *), const arbre_liste_t * l);

extern arbre_t * arbre_liste_fold(arbre_t * (* f)(const arbre_t *, const arbre_t *), const arbre_t * a, const arbre_liste_t * l);


#endif /* ARBRE_LISTE_H */
