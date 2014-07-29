#ifndef ANIME_H
#define ANIME_H

#include "../bonhomme.h"

/* Penser à regarder lexing.out
   Valeur de retour :
    -  0 : OK
    - -1 : lecture impossible du fichier
    - -2 : ouverture en écriture impossible du fichier "lexing.out"
    - -3 : erreur de parsing (syntaxe).
    - ...
*/
extern const int LireAnime(const char *, CBonhomme *);

#endif /* ANIME_H */
