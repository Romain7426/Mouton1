#include <stdlib.h>
#include <stdio.h>
#include "anime.h"
#include "global.h"
#include "parser.hpp"

extern FILE *yyin;
extern FILE *yyout;
extern const  int get_nb_lignes(void);
extern const  int get_nb_chars(void);
extern const  int get_nb_chars_tot(void);
extern const  int get_yyleng(void);
extern const  char * get_yytext(void);
extern const  int yyparse(void);


extern const  int LireAnime(const char * filename, CBonhomme* bongarsp) {
  int res;
  FILE *in;

  in = fopen(filename, "r");
  if (in == NULL) {
    //(void)printf("Erreur : impossible d'ouvrir le fichier \"%s\".", filename);
    return -1;
  }
  yyrestart(in);



  yyout = fopen("lexing.out", "w");
  if (yyout == NULL) {
    //(void) printf("Erreur : impossible d'ouvrir le fichier \"lexing.out\".");
    fclose(yyin);
    return -2;
  }

  bongars = bongarsp;

  res = yyparse();

  fclose(yyout); 
  fclose(yyin);
  
  switch (res) {
  case 0:  /*(void) printf("Analyse réussie !!!\n");*/ return 0;
  default: /*(void) printf("Analyse ratée...\n");*/ return -3;
  }
  
}

