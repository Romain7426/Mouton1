#ifndef ANIME_H
#define ANIME_H

//#include "../bonhomme.h"

/* Penser � regarder lexing.out
   Valeur de retour :
    -  0 : OK
    - -1 : filename est NULL
    - -2 : allocation rat� de m�moire
    - -3 : ouverture en �criture impossible du fichier "lexing.out"
    - -4 : ouverture en lecture de filename impossible
    - < -4 : erreur de parsing (syntaxe).
    - ...
*/
extern const int LireAnime(const char *, CBonhomme *);

#endif /* ANIME_H */
