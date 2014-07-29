#include "global.h"
#include "token.h"
#include "token_liste.h"

//#pragma message "Compiling " __FILE__ "..."

//#pragma GCC diagnostic ignored "-Waggregate-return"


static inline token_liste_t * token_liste_allouer(void);


static void token_liste_reverse_aux(const token_liste_t * l, token_liste_t * * accu);



token_liste_t * token_liste_vide(void) {
  return NULL;
}

bool token_liste_vide_huh(const token_liste_t * l) {
  return (NULL == l);
}

token_liste_t * token_liste_allouer(void) {
  return (token_liste_t *) malloc(sizeof (token_liste_t));
}

token_liste_t * token_liste_cons(const token_t * a, const token_liste_t * l) {
  return token_liste_cons_nocopy(token_copy(a), token_liste_copy(l));
}

token_liste_t * token_liste_cons_nocopy(token_t * a, token_liste_t * l) {
  token_liste_t * retour;
  retour = token_liste_allouer();
  retour -> car = a;
  retour -> cdr = l;
  return retour;
}

void token_liste_free(token_liste_t * l) {
  if (l == NULL) return;
  token_liste_free(l -> cdr);
  free(l);
}

token_liste_t * token_liste_copy(const token_liste_t * l) {
  if (l == NULL) 
    return NULL;
  
  return token_liste_cons(l -> car, l -> cdr);
}

unsigned int token_liste_longueur(const token_liste_t * l) {
  if (l == NULL) {
    return 0;
  }
  
  return 1 + token_liste_longueur(l -> cdr);
}


#if 0
token_liste_t * token_liste_vlist(unsigned int n, va_list args) {
  unsigned int i;
  token_liste_t * retour;
  token_liste_element_t temp;

  retour = token_liste_vide();
  
  for (i = 0; i < n; i++) {
    temp = va_arg(args, token_liste_element_t);
    retour = token_liste_cons_element(temp, retour);
  }

  token_liste_reverse_surplace(&retour);

  return retour;
}

token_liste_t * token_liste_list(unsigned int n, ...) {
  va_list args;
  token_liste_t * retour;

  va_start(args, n);
  retour = token_liste_vlist(n, args);
  va_end(args);

  return retour;
}
#endif


bool token_liste_equal(const token_liste_t * l1, const token_liste_t * l2) {
  bool b1;
  bool b2;
  bool b3;

  b1 = token_liste_vide_huh(l1);
  b2 = token_liste_vide_huh(l2);
 
  if (b1) {
    return b2;
  }

  if (b2) {
    return false;
  }

  b3 = token_equal(l1 -> car, l2 -> car);
  if (b3) {
    return token_liste_equal(l1 -> cdr, l2 -> cdr);
  }
  else {
    return false;
  }

  assert(false);
  return false;
}



bool token_liste_member(const token_t * a, const token_liste_t * liste) {
  bool b;

  b = token_liste_vide_huh(liste);

  if (b) return false;

  b = token_equal(a, liste -> car);

  if (b) return true;

  return token_liste_member(a, liste -> cdr);
}


bool token_liste_member_iteratif(const token_t * a, const token_liste_t * liste) {
  while (not(token_liste_vide_huh(liste))) {
    if (token_equal(a, liste -> car)) return true; 

    liste = liste -> cdr;
  }

  return false;
}
 
 
token_t * token_liste_pop(token_liste_t * * l) {
  assert(l != NULL);
  assert(*l != NULL);

  token_t * a;
  token_liste_t * p;

  a = (*l) -> car;
  p = (*l) -> cdr;
  
  free(*l);

  *l = p;

  return a;
}


token_liste_t * token_liste_map(token_t * (* f)(const token_t *), const token_liste_t * l) {
  if (l == NULL) return NULL;

  return token_liste_cons_nocopy(f(l -> car), token_liste_map(f, l -> cdr));
}


token_t * token_liste_fold(token_t * (* f)(const token_t *, const token_t *), const token_t * a, const token_liste_t * l) {
  if (l == NULL) return token_copy(a);
  
  return f(l -> car, token_liste_fold(f, a, l -> cdr));
}


char * token_liste_string(const token_liste_t * l) {
  char * retour;
  unsigned int n;
  unsigned int i;
  char * prec;
  char * str;

  n = token_liste_longueur(l);

  if (n == 0) {
    const char * const u = "list []";
    //retour = strcopy("list []");
    return strcpy(malloc(strlen(u)+1), u);
  }

  retour = strcopy("list [");

  assert(n >= 1);
  for (i = 0; i < n - 1; i++) {
    prec = retour;
    str = token_string(l -> car);
    retour = strconcat3(prec, str, ", ");
    strfree(str);
    strfree(prec);
    l = l -> cdr;
  }

  prec = retour;

  str = token_string(l -> car);
  retour = strconcat2(prec, str);
  strfree(str);
  strfree(prec);
  prec = retour;

  retour = strconcat2(prec, "]");
  strfree(prec);

  return retour;
}





token_liste_t * token_liste_reverse(const token_liste_t * l) {
  token_liste_t * retour;

  retour = NULL;
  token_liste_reverse_aux(l, &retour);

  return retour;
}

void token_liste_reverse_aux(const token_liste_t * l, token_liste_t * * accu) {
  if (l == NULL) {
    return;
  }

  *accu = token_liste_cons_nocopy(token_copy(l -> car), *accu);

  token_liste_reverse_aux(l -> cdr, accu);
}


void token_liste_reverse_surplace(token_liste_t * * liste) {
  assert(liste != NULL);
  token_liste_t * precedent;
  token_liste_t * courant;
  token_liste_t * suivant;

  if (token_liste_vide_huh(*liste)) return;

  precedent = token_liste_vide();
  courant = *liste;
  suivant = courant -> cdr;

  while (not(token_liste_vide_huh(suivant))) {
    courant -> cdr = precedent;

    precedent = courant;
    courant = suivant;
    suivant = suivant -> cdr;
  }

  courant -> cdr = precedent;

  *liste = courant;
}



token_liste_t * token_liste_append(const token_liste_t * l, const token_liste_t * m) {
  if (l == NULL) return token_liste_copy(m);

  return token_liste_cons_nocopy(token_copy(l -> car), token_liste_append(l -> cdr, m));
}

