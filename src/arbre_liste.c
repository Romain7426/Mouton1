#include "global.h"
#include "arbre.h"
#include "arbre_liste.h"

//#pragma message "Compiling " __FILE__ "..."

//#pragma GCC diagnostic ignored "-Waggregate-return"


static inline arbre_liste_t * arbre_liste_allouer(void);


static void arbre_liste_reverse_aux(const arbre_liste_t * l, arbre_liste_t * * accu);



arbre_liste_t * arbre_liste_vide(void) {
  return NULL;
}

bool arbre_liste_vide_huh(const arbre_liste_t * l) {
  return (NULL == l);
}

arbre_liste_t * arbre_liste_allouer(void) {
  return (arbre_liste_t *) malloc(sizeof (arbre_liste_t));
}

arbre_liste_t * arbre_liste_cons(const arbre_t * a, const arbre_liste_t * l) {
  return arbre_liste_cons_nocopy(arbre_copy(a), arbre_liste_copy(l));
}

arbre_liste_t * arbre_liste_cons_nocopy(arbre_t * a, arbre_liste_t * l) {
  arbre_liste_t * retour;
  retour = arbre_liste_allouer();
  retour -> car = a;
  retour -> cdr = l;
  return retour;
}

void arbre_liste_free(arbre_liste_t * l) {
  if (l == NULL) return;
  arbre_free(l -> car);
  arbre_liste_free(l -> cdr);
  free(l);
}

void arbre_liste_free_nocopy(arbre_liste_t * l) {
  if (l == NULL) return;
  arbre_liste_free_nocopy(l -> cdr);
  free(l);
}

arbre_liste_t * arbre_liste_copy(const arbre_liste_t * l) {
  if (l == NULL) 
    return NULL;
  
  return arbre_liste_cons(l -> car, l -> cdr);
}

unsigned int arbre_liste_longueur(const arbre_liste_t * l) {
  if (l == NULL) {
    return 0;
  }
  
  return 1 + arbre_liste_longueur(l -> cdr);
}


#if 0
arbre_liste_t * arbre_liste_vlist(unsigned int n, va_list args) {
  unsigned int i;
  arbre_liste_t * retour;
  arbre_liste_element_t temp;

  retour = arbre_liste_vide();
  
  for (i = 0; i < n; i++) {
    temp = va_arg(args, arbre_liste_element_t);
    retour = arbre_liste_cons_element(temp, retour);
  }

  arbre_liste_reverse_surplace(&retour);

  return retour;
}

arbre_liste_t * arbre_liste_list(unsigned int n, ...) {
  va_list args;
  arbre_liste_t * retour;

  va_start(args, n);
  retour = arbre_liste_vlist(n, args);
  va_end(args);

  return retour;
}
#endif


bool arbre_liste_equal(const arbre_liste_t * l1, const arbre_liste_t * l2) {
  bool b1;
  bool b2;
  bool b3;

  b1 = arbre_liste_vide_huh(l1);
  b2 = arbre_liste_vide_huh(l2);
 
  if (b1) {
    return b2;
  }

  if (b2) {
    return false;
  }

  b3 = arbre_equal(l1 -> car, l2 -> car);
  if (b3) {
    return arbre_liste_equal(l1 -> cdr, l2 -> cdr);
  }
  else {
    return false;
  }

  assert(false);
  return false;
}



bool arbre_liste_member(const arbre_t * a, const arbre_liste_t * liste) {
  bool b;

  b = arbre_liste_vide_huh(liste);

  if (b) return false;

  b = arbre_equal(a, liste -> car);

  if (b) return true;

  return arbre_liste_member(a, liste -> cdr);
}


bool arbre_liste_member_iteratif(const arbre_t * a, const arbre_liste_t * liste) {
  while (not(arbre_liste_vide_huh(liste))) {
    if (arbre_equal(a, liste -> car)) return true; 

    liste = liste -> cdr;
  }

  return false;
}
 
 
arbre_t * arbre_liste_pop(arbre_liste_t * * l) {
  assert(l != NULL);
  assert(*l != NULL);

  arbre_t * a;
  arbre_liste_t * p;

  a = (*l) -> car;
  p = (*l) -> cdr;
  
  free(*l);

  *l = p;

  return a;
}


arbre_liste_t * arbre_liste_map(arbre_t * (* f)(const arbre_t *), const arbre_liste_t * l) {
  if (l == NULL) return NULL;

  return arbre_liste_cons_nocopy(f(l -> car), arbre_liste_map(f, l -> cdr));
}


arbre_t * arbre_liste_fold(arbre_t * (* f)(const arbre_t *, const arbre_t *), const arbre_t * a, const arbre_liste_t * l) {
  if (l == NULL) return arbre_copy(a);
  
  return f(l -> car, arbre_liste_fold(f, a, l -> cdr));
}


char * arbre_liste_string(const arbre_liste_t * l) {
  char * retour;
  unsigned int n;
  unsigned int i;
  char * prec;
  char * str;

  n = arbre_liste_longueur(l);

  if (n == 0) {
    const char * const u = "list []";
    //retour = strcopy("list []");
    return strcpy(malloc(strlen(u)+1), u);
  }

  retour = strcopy("list [");

  assert(n >= 1);
  for (i = 0; i < n - 1; i++) {
    prec = retour;
    str = arbre_string(l -> car);
    retour = strconcat3(prec, str, ", ");
    strfree(str);
    strfree(prec);
    l = l -> cdr;
  }

  prec = retour;

  str = arbre_string(l -> car);
  retour = strconcat2(prec, str);
  strfree(str);
  strfree(prec);
  prec = retour;

  retour = strconcat2(prec, "]");
  strfree(prec);

  return retour;
}





arbre_liste_t * arbre_liste_reverse(const arbre_liste_t * l) {
  arbre_liste_t * retour;

  retour = NULL;
  arbre_liste_reverse_aux(l, &retour);

  return retour;
}

void arbre_liste_reverse_aux(const arbre_liste_t * l, arbre_liste_t * * accu) {
  if (l == NULL) {
    return;
  }

  *accu = arbre_liste_cons_nocopy(arbre_copy(l -> car), *accu);

  arbre_liste_reverse_aux(l -> cdr, accu);
}


void arbre_liste_reverse_surplace(arbre_liste_t * * liste) {
  assert(liste != NULL);
  arbre_liste_t * precedent;
  arbre_liste_t * courant;
  arbre_liste_t * suivant;

  if (arbre_liste_vide_huh(*liste)) return;

  precedent = arbre_liste_vide();
  courant = *liste;
  suivant = courant -> cdr;

  while (not(arbre_liste_vide_huh(suivant))) {
    courant -> cdr = precedent;

    precedent = courant;
    courant = suivant;
    suivant = suivant -> cdr;
  }

  courant -> cdr = precedent;

  *liste = courant;
}



arbre_liste_t * arbre_liste_append(const arbre_liste_t * l, const arbre_liste_t * m) {
  if (l == NULL) return arbre_liste_copy(m);

  return arbre_liste_cons_nocopy(arbre_copy(l -> car), arbre_liste_append(l -> cdr, m));
}

