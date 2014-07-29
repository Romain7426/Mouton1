#include "global.h"
#include "str_ltab.h"

//#pragma message "Compiling " __FILE__ "..."

//#pragma GCC diagnostic ignored "-Waggregate-return"


static inline str_ltab_t * str_ltab_allouer(const unsigned int taille);


static void str_ltab_reverse_aux(const str_ltab_t * l, str_ltab_t * * accu);



str_ltab_t * str_ltab_allouer(const unsigned int taille) {
  return (str_ltab_t *) malloc((taille) * (sizeof (str_ltab_t)));
}

str_ltab_t * str_ltab_make(const unsigned int taille) {
  str_ltab_t * retour;
  retour = str_ltab_allouer(taille+1);
  bzero(retour, (taille+1) * (sizeof (str_ltab_t)));
  return retour;
}

void str_ltab_free(str_ltab_t * a) {
  {
    unsigned int i = 0;
    while (a[i] != NULL) {
      str_free(a[i]);
      i++;
    }
  }
  free(a);
}

void str_ltab_free_nocopy(str_ltab_t * a) {
  free(a);
}

unsigned int str_ltab_longueur(const str_ltab_t * a) {
  unsigned int i = 0;
  while (a[i] != NULL) i++;
  return i;
}

str_ltab_t * str_ltab_copy(const str_ltab_t * a) {
  if (a == NULL) return NULL;
  
  str_ltab_t * retour;
  unsigned int taille;
  taille = str_ltab_longueur(a);
  retour = str_ltab_make(taille);
  unsigned int nb_elts;
  nb_elts = taille;
  for (unsigned int i = 0; i < nb_elts; i++)
    retour[i] = str_copy(a[i]);
  return retour;
}



bool str_ltab_equal(const str_ltab_t * array1, const str_ltab_t * array2) {
  unsigned int nb_elts1;
  nb_elts1 = str_ltab_longueur(array1);

  unsigned int nb_elts2;
  nb_elts2 = str_ltab_longueur(array2);

  if (nb_elts1 != nb_elts2) return false;

  for (unsigned int i = 0; i < nb_elts1; i++)
    if (not(str_equal(array1[i], array2[i]))) return false;

  return true;
}



bool str_ltab_member_huh(const str_t * a, const str_ltab_t * array) {
  {
    unsigned int i = 0; 
    while (array[i] != NULL) {
      if (a == array[i]) return true;
      i++;
    }
  }
  
  return false;
}




str_ltab_t * str_ltab_map(str_t * (* f)(const str_t *), const str_ltab_t * array) {
  str_ltab_t * retour;

  unsigned int taille;
  taille = str_ltab_longueur(array);

  retour = str_ltab_make(taille);

  for (unsigned int i = 0; i < taille; i++)
    retour[i] = f(array[i]);

  return retour;
}


str_t * str_ltab_fold(str_t * (* f)(const str_t *, const str_t *), const str_t * a, const str_ltab_t * array) {
  str_t * temp;

  temp = str_copy(a);
  
  {
    unsigned int i = 0; 
    while (array[i] != NULL) {
      temp = f(array[i], temp);
      i++;
    }
  }

  return temp;
}


char * str_ltab_string(const str_ltab_t * array) {
  char * retour;
  
  if (array == NULL) 
    return strcopy("(null)");

  retour = strcopy("array [");

  {
    unsigned int i = 0; 
    while (array[i] != NULL) {
      stradd2(&retour, str_string(array[i]));
      if (array[i+1] != NULL)
	stradd2(&retour, ", ");
      i++;
    }
  }

  stradd2(&retour, "]");

  return retour;
}



str_ltab_t * str_ltab_reverse(const str_ltab_t * array) {
  str_ltab_t * retour;

  retour = str_ltab_copy(array);
  
  str_ltab_reverse_surplace(retour);

  return retour;
}



void str_ltab_reverse_surplace(str_ltab_t * array) {
  str_t * temp;

  unsigned int nb_elts;
  nb_elts = str_ltab_longueur(array);

  for (unsigned int i = 0; i < (nb_elts / 2); i++) {
    temp = array[i];
    array[i] = array[nb_elts - i - 1];
    array[nb_elts - i - 1] = temp;
  }
}



str_ltab_t * str_ltab_append(const str_ltab_t * array1, const str_ltab_t * array2) {
  str_ltab_t * retour;

  unsigned int taille1;
  taille1 = str_ltab_longueur(array1);
  unsigned int taille2;
  taille2 = str_ltab_longueur(array2);

  retour = str_ltab_make(taille1 + taille2);

  unsigned int nb_elts1;
  nb_elts1 = taille1;
  unsigned int nb_elts2;
  nb_elts2 = taille2;

  for (unsigned int i = 0; i < nb_elts1; i++) 
    retour[i] = str_copy(array1[i]);

  for (unsigned int i = 0; i < nb_elts2; i++) 
    retour[nb_elts1 + i] = str_copy(array2[i]);

  return retour;
}

str_ltab_t * str_ltab_append_nocopy(str_ltab_t * array1, str_ltab_t * array2) {
  str_ltab_t * retour;

  unsigned int taille1;
  taille1 = str_ltab_longueur(array1);
  unsigned int taille2;
  taille2 = str_ltab_longueur(array2);

  retour = str_ltab_make(taille1 + taille2);
  
  unsigned int nb_elts1;
  nb_elts1 = taille1;
  unsigned int nb_elts2;
  nb_elts2 = taille2;

  for (unsigned int i = 0; i < nb_elts1; i++) 
    retour[i] = array1[i];

  for (unsigned int i = 0; i < nb_elts2; i++) 
    retour[nb_elts1 + i] = array2[i];

  return retour;
}



uint_t str_ltab_count(const str_t * a, const str_ltab_t * array) {
  uint_t count;

  count = 0;

  {
    unsigned int i = 0; 
    while (array[i] != NULL) {
      if (a == array[i]) count++;
      i++;
    }
  }

  return count;
}
