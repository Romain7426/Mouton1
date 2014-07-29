#include <stdlib.h>
#include <stdio.h>
#include "global.hpp"
#include "parser.hpp"
#include "../objnonanime.h"

extern FILE *yyin;
extern FILE *yyout;
const extern int yyparse(void);
extern CObjNonAnime *objet;

int CObjNonAnime::parse(char *filename) {
  int res;

  if (filename == NULL) {
    (void)fprintf(stderr, "Erreur : impossible 'filename' est le pointeur NULL.\n");
    return -1;
  }

  
  yyin = fopen(filename, "r");
  if (yyin == NULL) {
    (void)fprintf(stderr, "Erreur : impossible d'ouvrir en lecture le fichier \"%s\".\n", filename);
    return -2;
  }



  yyout = fopen("lexing.out", "w");
  if (yyout == NULL) {
    (void) fprintf(stderr, "Erreur : impossible d'ouvrir en écriture le fichier \"lexing.out\".\n");
    (void) fclose(yyin);
    return -3;
  }

  /* L'analyse elle meme. */
  objet = this;
  res = yyparse();

  /* On ferme les flux. */
  (void) fclose(yyout); 
  (void) fclose(yyin);
  
  /* On match. */
  switch (res) {
  case 0:  (void) fprintf(stdout, "Analyse réussie !!!\n"); return 0;
  default: (void) fprintf(stdout, "Analyse ratée...\n"); return res - 128;
  }
  
}

