#include "global.h"
#include "tableau.h"



static tableau_t * tableau_allouer(void);

tableau_t * tableau_allouer(void) {
  return (tableau_t *) malloc(sizeof (tableau_t));
}

tableau_t * tableau_make(size_t taille) {
  tableau_t * retour;

  retour = tableau_allouer();

  retour -> taille = taille;

  retour -> nb = 0;

  retour -> tab = malloc(taille * (sizeof (void *)));

  assert(retour -> tab != NULL);

  return retour;
}

void tableau_free(tableau_t * tableau) {
  free(tableau -> tab);
  free(tableau);
}

void tableau_free_pointeur(tableau_t * tableau, void (* objet_free)(void *)) {
  unsigned int i;

  for (i = 0; i < tableau -> nb; i++) {
    objet_free(tableau -> tab[i]);
  }

  tableau_free(tableau);
}

tableau_t * tableau_copy(const tableau_t * tableau) {
  tableau_t * retour;
  unsigned int i;

  retour = tableau_make(tableau -> taille);

  retour -> nb = tableau -> nb;

  for (i = 0; i < tableau -> taille; i++) {
    retour -> tab[i] = tableau -> tab[i];
  }

  return retour;
}

tableau_t * tableau_copy_pointeur(const tableau_t * tableau, void * (* objet_copy)(const void *)) {
  tableau_t * retour;
  unsigned int i;

  retour = tableau_make(tableau -> taille);

  retour -> nb = tableau -> nb;

  for (i = 0; i < tableau -> nb; i++) {
    retour -> tab[i] = objet_copy(tableau -> tab[i]);
  }

  return retour;
}

tableau_t * tableau_map(void * (* f)(const void *), const tableau_t * tableau) {
  tableau_t * retour;
  unsigned int i;

  retour = tableau_make(tableau -> taille);

  retour -> nb = tableau -> nb;

  for (i = 0; i < tableau -> nb; i++) {
    retour -> tab[i] = f(tableau -> tab[i]);
  }

  return retour;
}

void * tableau_fold(void * (* f)(const void *, void *), void * a, const tableau_t * tableau) {
  unsigned int i;

  for (i = 0; i < tableau -> nb; i++) {
    a = f(tableau -> tab[i], a);
  }

  return a;
}

void * tableau_fold_pointeur(void * (* f)(const void *, const void *), const void * a, const tableau_t * tableau, void (* objet_free)(void *), void * (* objet_copy)(const void *)) {
  unsigned int i;
  void * b;
  void * temp;

  b = objet_copy(a);

  for (i = 0; i < tableau -> nb; i++) {
    temp = f(tableau -> tab[i], b);
    
    objet_free(b);

    b = temp;
  }

  return b;
}


//char * str_of_tableau2(char * (* str_of_objet)(const void *), const tableau_t * tableau) {
char * tableau_string2(char * (* str_of_objet)(const void *), const tableau_t * tableau) {
  tableau_t * p;
  char * retour;

  p = tableau_map((void * (*)(const void *)) str_of_objet, tableau);

  retour = tableau_fold_pointeur((void * (*)(const void *, const void *)) strconcat, "", p, (void (*)(void *)) strfree, (void * (*)(const void *)) strcopy);

  tableau_free_pointeur(p, (void (*)(void *)) strfree);

  return retour;
}

//char * str_of_tableau(char * (* str_of_objet)(const void *), const tableau_t * tableau) {
char * tableau_string(char * (* str_of_objet)(const void *), const tableau_t * tableau) {
  tableau_t * p;
  char * retour;
  char * temp;
  unsigned int i;

  if (tableau -> taille == 0) return strcopy("[]");


  p = tableau_map((void * (*)(const void *)) str_of_objet, tableau);

  retour = strcopy("[");

  for (i = 0; i < (tableau -> nb - 1); i++) {
    temp = strconcat3(retour, p -> tab[i], ", ");

    strfree(retour);

    retour = temp;
  }

  temp = strconcat3(retour, p -> tab[i], "]");
  
  strfree(retour);
  
  retour = temp;


  tableau_free_pointeur(p, (void (*)(void *)) strfree);


  return retour;
}



tableau_t * tableau_reverse(const tableau_t * tableau) {
  tableau_t * retour;
  unsigned int i;
  unsigned int nb;

  nb = tableau -> nb;

  retour = tableau_make(tableau -> taille);

  nb --;

  for (i = 0; i < tableau -> nb; i++) {
    retour -> tab[i] = tableau -> tab[nb - i];
  }

  return retour;
}


tableau_t * tableau_reverse_pointeur(const tableau_t * tableau, void * (* objet_copy)(const void *)) {
  tableau_t * retour;
  unsigned int i;
  unsigned int nb;

  nb = tableau -> nb;

  retour = tableau_make(tableau -> taille);

  nb --;

  for (i = 0; i < tableau -> nb; i++) {
    retour -> tab[i] = objet_copy(tableau -> tab[nb - i]);
  }

  return retour;
}


tableau_t * tableau_fusion(const tableau_t * tab1, const tableau_t * tab2) {
  tableau_t * retour;
  unsigned int i;

  retour = tableau_make((tab1 -> taille) + (tab2 -> taille));

  retour -> nb = tab1 -> nb + tab2 -> nb;

  for (i = 0; i < tab1 -> nb; i++) {
    retour -> tab[i] = tab1 -> tab[i];
  }

  for (i = 0; i < tab2 -> nb; i++) {
    retour -> tab[(tab1 -> nb) + i] = tab2 -> tab[i];
  }

  return retour;
}

tableau_t * tableau_fusion_pointeur(const tableau_t * tab1, const tableau_t * tab2, void * (* objet_copy)(const void *)) {
  tableau_t * retour;
  unsigned int i;

  retour = tableau_make((tab1 -> taille) + (tab2 -> taille));

  retour -> nb = tab1 -> nb + tab2 -> nb;

  for (i = 0; i < tab1 -> nb; i++) {
    retour -> tab[i] = objet_copy(tab1 -> tab[i]);
  }

  for (i = 0; i < tab2 -> nb; i++) {
    retour -> tab[(tab1 -> nb) + i] = objet_copy(tab2 -> tab[i]);
  }

  return retour;
}


bool tableau_equal(const tableau_t * tab1, const tableau_t * tab2) {
  unsigned int i;

  if (tab1 -> nb != tab2 -> nb)
    return false;

  for (i = 0; i < tab1 -> nb; i++) {
    if (tab1 -> tab[i] != tab2 -> tab[i])
      return false;
  }

  return true;
}


bool tableau_equal_pointeur(const tableau_t * tab1, const tableau_t * tab2, bool (* objet_equal)(const void *, const void *)) {
  unsigned int i;

  if (tab1 -> nb != tab2 -> nb)
    return false;

  for (i = 0; i < tab1 -> nb; i++) {
    if (not(objet_equal(tab1 -> tab[i], tab2 -> tab[i])))
      return false;
  }

  return true;
}



