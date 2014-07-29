#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "asprintf.hpp"

#ifdef WIN

// fait en gros comme printf mais ecrit dans la chaine strp (elle l'alloue)
// retourne le nombre de caracteres ecrits (ex : "bon" --> 3)
// en cas d'erreur, ça retourne -1 et *strp = NULL
int asprintf(char * * strp, const char * format, ...) {
  va_list args;
  int retour;
    
  // realise un premier appel pour avoir la taille de la chaine a allouer
  va_start(args, format);
  retour = vsnprintf(NULL, 0, format, args);
  va_end(args);
    
  if(retour == -1) {
    *strp = NULL; 
    return -1;
  }
    
  // retour designe ici la taille du buffer (le '\0' final compris)
  retour ++;
    
  // on alloue la chaîne
  *strp = (char *) malloc(retour);
    
  va_start(args, format);
  retour = vsnprintf(*strp, retour, format, args);
  va_end(args);
    
  return retour-1;
}

#endif
