#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "asprintf.h"

#ifdef WIN

// fait en gros comme printf mais ecrit dans la chaine strp (elle l'alloue)
// retourne le nombre de caracteres ecrits (ex : "bon" --> 3)
// en cas d'erreur, ça retourne -1 et *strp = NULL
int asprintf(char * * strp, const char * format, ...) {
  va_list args;
  int len;
    
  // realise un premier appel pour avoir la taille de la chaine a allouer
  va_start(args, format);
  len = vsnprintf(NULL, 0, format, args);
  va_end(args);
    
  if(len == -1) {
    *strp = NULL; 
    return -1;
  }
    
  // on alloue la chaîne
  *strp = (char *) malloc(sizeof(char) * (len+1));
    
  va_start(args, format);
  retour = vsnprintf(*strp, retour, format, args);
  va_end(args);
    
  return len;
}

#endif
