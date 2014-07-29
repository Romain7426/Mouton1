#include "global.h"
#include "str_tableau.h"


static str_tableau_t * str_tableau_allouer(void);

str_tableau_t * str_tableau_allouer(void) {
  return (str_tableau_t *) malloc(sizeof (str_tableau_t));
}

str_tableau_t * str_tableau_make(const int taille) {
  str_tableau_t * retour;
  
  retour = str_tableau_allouer();
  
  retour -> taille = taille;
  
  retour -> nb = 0;
  
  retour -> tab = malloc(taille * (sizeof (void *)));
  
  assert(retour -> tab != NULL);
  
  return retour;
}

void str_tableau_free(str_tableau_t * str_tableau) {
  for (int i = 0; i < str_tableau -> nb; i++) {
    strfree(str_tableau -> tab[i]);
  }
  
  free(str_tableau -> tab);
  free(str_tableau);
}

str_tableau_t * str_tableau_copy(const str_tableau_t * str_tableau) {
  str_tableau_t * retour;

  retour = str_tableau_make(str_tableau -> taille);

  retour -> nb = str_tableau -> nb;

  for (int i = 0; i < str_tableau -> nb; i++) {
    retour -> tab[i] = strcopy(str_tableau -> tab[i]);
  }
  
  return retour;
}

str_tableau_t * str_tableau_map(str_t * (* f)(const str_t *), const str_tableau_t * str_tableau) {
  str_tableau_t * retour;
  
  retour = str_tableau_make(str_tableau -> taille);

  retour -> nb = str_tableau -> nb;

  for (int i = 0; i < str_tableau -> nb; i++) {
    retour -> tab[i] = f(str_tableau -> tab[i]);
  }

  return retour;
}

void * str_tableau_fold(void * (* f)(const str_t *, const void *), const void * a, const str_tableau_t * str_tableau, void (* objet_free)(void *), void * (* objet_copy)(const void *)) {
  void * b;
  void * temp;

  b = objet_copy(a);

  for (int i = 0; i < str_tableau -> nb; i++) {
    temp = f(str_tableau -> tab[i], b);
    
    objet_free(b);

    b = temp;
  }

  return b;
}


//char * str_of_str_tableau(const str_tableau_t * str_tableau) {
char * str_tableau_string(const str_tableau_t * str_tableau) {
  const str_tableau_t * p;
  char * retour;
  char * temp;
  
  if (str_tableau -> taille == 0) return strcopy("[]");
  
  
  p = str_tableau;

  retour = strcopy("[");

  for (int i = 0; i < (str_tableau -> nb - 1); i++) {
    temp = strconcat3(retour, p -> tab[i], ", ");

    strfree(retour);

    retour = temp;
  }

  temp = strconcat3(retour, p -> tab[str_tableau -> nb], "]");
  
  strfree(retour);
  
  retour = temp;
  
  return retour;
}



str_tableau_t * str_tableau_reverse(const str_tableau_t * str_tableau) {
  str_tableau_t * retour;
  int nb;

  nb = str_tableau -> nb;

  retour = str_tableau_make(str_tableau -> taille);

  nb --;

  for (int i = 0; i < str_tableau -> nb; i++) {
    retour -> tab[i] = strcopy(str_tableau -> tab[nb - i]);
  }

  return retour;
}


str_tableau_t * str_tableau_fusion(const str_tableau_t * tab1, const str_tableau_t * tab2) {
  str_tableau_t * retour;

  retour = str_tableau_make((tab1 -> taille) + (tab2 -> taille));

  retour -> nb = tab1 -> nb + tab2 -> nb;

  for (int i = 0; i < tab1 -> nb; i++) {
    retour -> tab[i] = strcopy(tab1 -> tab[i]);
  }

  for (int i = 0; i < tab2 -> nb; i++) {
    retour -> tab[(tab1 -> nb) + i] = strcopy(tab2 -> tab[i]);
  }

  return retour;
}


bool str_tableau_equal(const str_tableau_t * tab1, const str_tableau_t * tab2) {
  if (tab1 -> nb != tab2 -> nb)
    return false;

  for (int i = 0; i < tab1 -> nb; i++) {
    if (not(strequal(tab1 -> tab[i], tab2 -> tab[i])))
      return false;
  }

  return true;
}







