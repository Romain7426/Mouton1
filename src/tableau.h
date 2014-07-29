#ifndef TABLEAU_H
#define TABLEAU_H

struct tableau_t {
  size_t taille; // la taille du tableau (pour contrôler buffer overflow et cie)
  size_t nb; // le nombre de cases effectivement occupées
  void * * tab;
};
typedef struct tableau_t tableau_t;

extern tableau_t * tableau_make(size_t taille);
//extern tableau_t * tableau_make_liste(const liste_t * liste);
//extern tableau_t * tableau_make_liste_pointeur(const liste_t * liste, void * (* objet_copy)(const void *));
extern void tableau_free(tableau_t * tableau);
extern void tableau_free_pointeur(tableau_t * tableau, void (* objet_free)(void *));
extern tableau_t * tableau_copy(const tableau_t * tableau);
extern tableau_t * tableau_copy_pointeur(const tableau_t * tableau, void * (* objet_copy)(const void *));
extern tableau_t * tableau_reallouer(const tableau_t * tableau);
extern tableau_t * tableau_reallouer_pointeur(const tableau_t * tableau, void * (* objet_copy)(const void *));
extern tableau_t * tableau_map(void * (* f)(const void *), const tableau_t * tableau);
extern void * tableau_fold(void * (* f)(const void *, void *), void * a, const tableau_t * tableau);
extern void * tableau_fold_pointeur(void * (* f)(const void *, const void *), const void * a, const tableau_t * tableau, void (* objet_free)(void *), void * (* objet_copy)(const void *));
extern char * tableau_string(char * (* str_of_objet)(const void *), const tableau_t * tableau);
extern char * tableau_string2(char * (* str_of_objet)(const void *), const tableau_t * tableau);
#define str_of_tableau tableau_string
#define str_of_tableau2 tableau_string2
extern tableau_t * tableau_reverse(const tableau_t * tableau);
extern tableau_t * tableau_reverse_pointeur(const tableau_t * tableau, void * (* objet_copy)(const void *));
extern tableau_t * tableau_fusion(const tableau_t * tab1, const tableau_t * tab2);
extern tableau_t * tableau_fusion_pointeur(const tableau_t * tab1, const tableau_t * tab2, void * (* objet_copy)(const void *));
extern bool tableau_equal(const tableau_t * tab1, const tableau_t * tab2);
extern bool tableau_equal_pointeur(const tableau_t * tab1, const tableau_t * tab2, bool (* objet_equal)(const void *, const void *));



#endif /* TABLEAU_H */

