#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.hpp"
#include "carte/carte.global.hpp"
#include "carte/carte.hpp"
#include "carte/carte.parser.hpp"


#define CARTE_OUT_SUFFIXE ".lexing.out"

/* Valeur de retour.
   0 : OK
   < 0 : erreur
   -1 : filename est NULL
   -2 : impossible d'ouvrir en écriture le fichier de sortie.
   -3 : impossible d'ouvrir en lecture le fichier d'entrée.
   < -128 : erreur lors du parsing.
   regarder dans carte/carte.parse.y et chercher l'erreur (res + 128).
*/

//int CMap::parse(const char * filename) {
int CMap::parse(const char * dir, const char * filename) {
  int res;
  FILE *cartein;
  char *carte_out;
  size_t taille;

  message("On entre dans la fonction CMap::parse.");

  message("Teste si filename est NULL.");
  if (filename == NULL) {
    messerr("CMap::parse: filename est le pointeur NULL. On quitte.");
    return -1;
  }
  message("Test reussi.");


  //nonanime_out = strcat(strcpy(new char[strlen(filename) + strlen(SUFF_NONANIMEOUT) + 1], filename), SUFF_NONANIMEOUT);
  carte_out = STRCAT3_(LOGDIR,filename,CARTE_OUT_SUFFIXE);
#if 0
  fprintf(stderr, "fout = %s\n", nonanime_out);
  yynonanimeout = fopen(nonanime_out, "wb");
  assert(yynonanimeout != NULL);
  assert(false);
#endif

#if 0
  message("On essaye de créer le fichier de sortie pour l'analyse.");
  (void) (taille = strlen(filename) + strlen(CARTE_OUT_SUFFIXE));
  (void) (carte_out = new char[taille + 1]);
  (void) strcat(strcpy(carte_out, filename), CARTE_OUT_SUFFIXE);
  message("Création du fichier \"%s\".", carte_out);
  message("On essaye de l'ouvrir en écriture.");
#endif

  (void) (yycarteout = fopen(carte_out, "wb"));
  if (yycarteout == NULL) {
    messerr("CMap::parse: impossible d'ouvrir en écriture le fichier \"%s\". On arrête l'analyse du fichier.", carte_out);
    delete[] carte_out;
    return -2;
  }
  carte_mess("Ouverture en écriture réussie du fichier \"%s\" !", carte_out);


  filename = STRCAT2_(dir, filename);
  carte_mess("On essaye d'ouvrir en lecture le fichier \"%s\".", filename);
  (void) (cartein = fopen(filename, "rb"));
  if (cartein == NULL) {
    carte_err("Impossible d'ouvrir en lecture le fichier \"%s\" ! On arrête l'analyse.", filename);
    (void) fclose(yycarteout);
    delete[] carte_out;
    return -3;
  }

  carte_mess("Ouverture en lecture du fichier \"%s\" réussie.", filename);
  carte_mess("Initialisation du lexer et parser.");
  carte_parser_reset();
  carte_restart_lexer();
  yycarterestart(cartein);
  carte = this;

  carte_mess("Démarrage de l'analyse.");

  (void) (res = yycarteparse());
  switch (res) {
  case 0: 
    carte_mess("Analyse réussie du fichier \"%s\".", filename);
    break;
  default:
    carte_err("Analyse raté du fichier \"%s\".", filename);
    res -= 128;
  }

  carte_mess("Fermeture des flots d'entrée et de sortie.");
  (void) fclose(cartein);
  (void) fclose(yycarteout);
  message("Flots fermés.");
  message("On quitte CMap::parse avec comme argument \"%s\".", filename);
  delete[] carte_out;
  return res;
  
}

