#include "global.h"
#include "str_liste.h"


static inline str_liste_t * str_liste_allouer(void);


static void str_liste_reverse_aux(const str_liste_t * l, str_liste_t * * accu);



str_liste_t * str_liste_vide(void) {
  return NULL;
}

bool str_liste_vide_huh(const str_liste_t * l) {
  return (NULL == l);
}

str_liste_t * str_liste_allouer(void) {
  return (str_liste_t *) malloc(sizeof (str_liste_t));
}

str_liste_t * str_liste_cons(const str_t * a, const str_liste_t * l) {
  return str_liste_cons_nocopy(str_copy(a), str_liste_copy(l));
}

str_liste_t * str_liste_cons_nocopy(str_t * a, str_liste_t * l) {
  str_liste_t * retour;
  retour = str_liste_allouer();
  retour -> car = a;
  retour -> cdr = l;
  return retour;
}

void str_liste_free(str_liste_t * l) {
  if (l == NULL) return;
  str_free(l -> car);
  str_liste_free(l -> cdr);
  free(l);
}

void str_liste_free_nocopy(str_liste_t * l) {
  if (l == NULL) return;
  str_liste_free_nocopy(l -> cdr);
  free(l);
}

str_liste_t * str_liste_copy(const str_liste_t * l) {
  if (l == NULL) 
    return NULL;
  
  return str_liste_cons(l -> car, l -> cdr);
}

unsigned int str_liste_longueur(const str_liste_t * l) {
  if (l == NULL) {
    return 0;
  }
  
  return 1 + str_liste_longueur(l -> cdr);
}


#if 0
str_liste_t * str_liste_vlist(unsigned int n, va_list args) {
  unsigned int i;
  str_liste_t * retour;
  str_liste_element_t temp;

  retour = str_liste_vide();
  
  for (i = 0; i < n; i++) {
    temp = va_arg(args, str_liste_element_t);
    retour = str_liste_cons_element(temp, retour);
  }

  str_liste_reverse_surplace(&retour);

  return retour;
}

str_liste_t * str_liste_list(unsigned int n, ...) {
  va_list args;
  str_liste_t * retour;

  va_start(args, n);
  retour = str_liste_vlist(n, args);
  va_end(args);

  return retour;
}
#endif


bool str_liste_equal(const str_liste_t * l1, const str_liste_t * l2) {
  bool b1;
  bool b2;
  bool b3;

  b1 = str_liste_vide_huh(l1);
  b2 = str_liste_vide_huh(l2);
 
  if (b1) {
    return b2;
  }

  if (b2) {
    return false;
  }

  b3 = str_equal(l1 -> car, l2 -> car);
  if (b3) {
    return str_liste_equal(l1 -> cdr, l2 -> cdr);
  }
  else {
    return false;
  }

  assert(false);
  return false;
}



bool str_liste_member(const str_t * a, const str_liste_t * liste) {
  bool b;

  b = str_liste_vide_huh(liste);

  if (b) return false;

  b = str_equal(a, liste -> car);

  if (b) return true;

  return str_liste_member(a, liste -> cdr);
}


bool str_liste_member_iteratif(const str_t * a, const str_liste_t * liste) {
  while (not(str_liste_vide_huh(liste))) {
    if (str_equal(a, liste -> car)) return true; 

    liste = liste -> cdr;
  }

  return false;
}
 
 
str_t * str_liste_pop(str_liste_t * * l) {
  assert(l != NULL);
  assert(*l != NULL);

  str_t * a;
  str_liste_t * p;

  a = (*l) -> car;
  p = (*l) -> cdr;
  
  free(*l);

  *l = p;

  return a;
}


str_liste_t * str_liste_map(str_t * (* f)(const str_t *), const str_liste_t * l) {
  if (l == NULL) return NULL;

  return str_liste_cons_nocopy(f(l -> car), str_liste_map(f, l -> cdr));
}


str_t * str_liste_fold(str_t * (* f)(const str_t *, const str_t *), const str_t * a, const str_liste_t * l) {
  if (l == NULL) return str_copy(a);
  
  return f(l -> car, str_liste_fold(f, a, l -> cdr));
}


char * str_liste_string(const str_liste_t * l) {
  char * retour;
  unsigned int n;
  unsigned int i;
  char * prec;
  char * str;

  n = str_liste_longueur(l);

  if (n == 0) {
    const char * const u = "list []";
    //retour = strcopy("list []");
    return strcpy(malloc(strlen(u)+1), u);
  }

  retour = strcopy("list [");

  assert(n >= 1);
  for (i = 0; i < n - 1; i++) {
    prec = retour;
    str = str_string(l -> car);
    retour = strconcat3(prec, str, ", ");
    strfree(str);
    strfree(prec);
    l = l -> cdr;
  }

  prec = retour;

  str = str_string(l -> car);
  retour = strconcat2(prec, str);
  strfree(str);
  strfree(prec);
  prec = retour;

  retour = strconcat2(prec, "]");
  strfree(prec);

  return retour;
}





str_liste_t * str_liste_reverse(const str_liste_t * l) {
  str_liste_t * retour;

  retour = NULL;
  str_liste_reverse_aux(l, &retour);

  return retour;
}

void str_liste_reverse_aux(const str_liste_t * l, str_liste_t * * accu) {
  if (l == NULL) {
    return;
  }

  *accu = str_liste_cons_nocopy(str_copy(l -> car), *accu);

  str_liste_reverse_aux(l -> cdr, accu);
}


void str_liste_reverse_surplace(str_liste_t * * liste) {
  assert(liste != NULL);
  str_liste_t * precedent;
  str_liste_t * courant;
  str_liste_t * suivant;

  if (str_liste_vide_huh(*liste)) return;

  precedent = str_liste_vide();
  courant = *liste;
  suivant = courant -> cdr;

  while (not(str_liste_vide_huh(suivant))) {
    courant -> cdr = precedent;

    precedent = courant;
    courant = suivant;
    suivant = suivant -> cdr;
  }

  courant -> cdr = precedent;

  *liste = courant;
}



str_liste_t * str_liste_append(const str_liste_t * l, const str_liste_t * m) {
  if (l == NULL) return str_liste_copy(m);

  return str_liste_cons_nocopy(str_copy(l -> car), str_liste_append(l -> cdr, m));
}

void str_liste_append_nocopy(str_liste_t * * l, str_liste_t * m) {
  if (*l == NULL) {
    *l = m;
    return;
  }
  
  str_liste_append_nocopy(&((*l) -> cdr), m);
}


uint_t str_liste_count(const str_t * a, const str_liste_t * l) {
  if (l == NULL) return 0;
  uint_t s, t;
  s = (str_equal(a, l->car)) ? 1 : 0;
  t = str_liste_count(a, l -> cdr);
  return s + t;
}

