#include <stdlib.h>
#include <stdio.h>
#include "global.hpp"
#include "anime/anime.global.hpp"
#include "anime/anime.hpp"
#include "anime/anime.parser.hpp"

#define ANIME_OUT ".lexing.out"


//extern const int LireAnime(const char * filename, CBonhomme * bongarsp) {
int LireAnime(const char * dir, const char * filename, CBonhomme * bongarsp) {
  int res;
  FILE *in;

  if (filename == NULL) {
    return -1;
  }

  char * fout;
  
  fout = (char *) malloc((strlen(LOGDIR) + strlen(filename) + 1 + strlen(ANIME_OUT) + 1) * sizeof(char));

  if (fout == NULL) {
    return -2;
  }

  (void) strcat(strcat(strcpy(fout, LOGDIR), filename), ANIME_OUT);
#if 0
  fprintf(stderr, "fout = %s\n", fout);
  yyanimeout = fopen(fout, "wb");
  assert(yyanimeout != NULL);
  assert(false);
#endif

  yyanimeout = fopen(fout, "wb");
  if (yyanimeout == NULL) {
    //(void) printf("Erreur: impossible d'ouvrir le fichier \"%s\".", fout);
    return -3;
  }

  (void) fprintf(yyanimeout, "Initialisation du fichier \"%s\" de sortie réussie !\n", fout);

  filename = STRCAT2_(dir, filename);
  in = fopen(filename, "rb");
  if (in == NULL) {
    (void) fprintf(yyanimeout, "Erreur : impossible d'ouvrir le fichier \"%s\".\nFin de l'analyse.\n", filename);
    fclose(yyanimeout);
    free(fout);
    return -4;
  }
  
  (void) fprintf(yyanimeout, "Ouverture en lecture du fichier \"%s\" réussie.\nDébut de l'analyse du fichier.\n\n", filename);

  anime_restart_lexer();
  yyanimerestart(in);
  anime_parser_reset();

  bongars = bongarsp;

  res = yyanimeparse();

  (void) fprintf(yyanimeout, "\n\n\nRésultat de l'analyse : %d\n", res);
  (void) fprintf(yyanimeout, "\t=> %s\n", res ? "Analyse ratée..." : "Analyse réussie !!!");

  fclose(yyanimein);
  fclose(yyanimeout); 
  free(fout);
  
  switch (res) {
  case 0:   return 0;
  default:  return -4 + res;
  }
  
}

