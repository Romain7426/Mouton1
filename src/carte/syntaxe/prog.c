#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "parser.h"

extern FILE *yyin;
extern FILE *yyout;
const extern int yyparse(void);

const extern int main(int argc, char *argv[]) {
  int res;

  if (argc > 1) {
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
      (void)printf("Erreur : impossible d'ouvrir le fichier \"%s\".", argv[1]);
      return -1;
    }
  }

  else {
    yyin = stdin;
  }


  yyout = fopen("lexing.out", "w");
  if (yyout == NULL) {
    (void) printf("Erreur : impossible d'ouvrir le fichier \"lexing.out\".");
    fclose(yyin);
    return -2;
  }

  res = yyparse();

  fclose(yyout); 
  fclose(yyin);
  
  switch (res) {
  case 0:  (void) printf("Analyse réussie !!!\n"); return 0;
  default: (void) printf("Analyse ratée...\n"); return -3;
  }
  
}

