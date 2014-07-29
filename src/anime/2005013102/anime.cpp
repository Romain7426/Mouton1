#include <stdlib.h>
#include <stdio.h>
#include "anime.global.hpp"
#include "anime.hpp"
#include "anime.parser.hpp"

#define ANIME_OUT ".lexing.out"

extern const  int LireAnime(const char * filename, CBonhomme* bongarsp) {
  int res;
  FILE *in;

  if (filename == NULL) {
    return -1;
  }

  char *fout;
  
  fout = (char *) malloc((strlen(filename) + 1 + strlen(ANIME_OUT) + 1) * sizeof(char));

  if (fout == NULL) {
    return -2;
  }

  (void) strcat(strcpy(fout, filename), ANIME_OUT);

  yyout = fopen(fout, "w");
  if (yyout == NULL) {
    //(void) printf("Erreur : impossible d'ouvrir le fichier \"%s\".", fout);
    return -3;
  }

  (void) fprintf(yyout, "Initialisation du fichier \"%s\" de sortie réussie !\n", fout);


  in = fopen(filename, "r");
  if (in == NULL) {
    (void) fprintf(yyout, "Erreur : impossible d'ouvrir le fichier \"%s\".\nFin de l'analyse.\n", filename);
    fclose(yyout);
    free(fout);
    return -4;
  }
  
  (void) fprintf(yyout, "Ouverture en lecture du fichier \"%s\" réussie.\nDébut de l'analyse du fichier.\n\n", filename);
  yyrestart(in);


  bongars = bongarsp;

  res = yyparse();

  (void) fprintf(yyout, "\n\n\nRésultat de l'analyse : %d\n", res);
  (void) fprintf(yyout, "\t=> %s\n", res ? "Analyse ratée..." : "Analyse réussie !!!");

  fclose(yyin);
  fclose(yyout); 
  free(fout);
  
  switch (res) {
  case 0:   return 0;
  default:  return -4 + res;
  }
  
}

