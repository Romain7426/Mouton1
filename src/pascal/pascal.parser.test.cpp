#include <stdlib.h>
#include <stdio.h>
#include "pascal.tools.hpp"
#include "pascal.expr.hpp"
#include "pascal.parser.hpp"
#include "pascal.prog.hpp"

extern FILE *yypascalout;
extern FILE *yypascalin;
extern int yypascallex(void);
extern int yypascalparse(void);
extern void yypascalrestart(FILE *new_file);
extern void yypascallexerinit(void);

extern CPprog *prog;

int main(void) {
  int ret;

  pmessinit("pascal.test.pml");

  yypascalout = fopen("pascal.lexer.out", "w");
  yypascalin = fopen("pascal.test.pml", "r");

  //while (yypascallex() != TOKEN_EOF) continue;
  pmesserr("DTC");
  printf("HERE\n");
  ret = yypascalparse();
  printf("%d\n", ret);
  fclose(yypascalin);
  fclose(yypascalout);
  if (prog == NULL) {
    printf("prog est NULL.\n");
    return -1;
  }
  printf("C bon\n");
  printf("Affichage du programme:\n");
  printf("-----------------------\n\n");
  fflush(NULL);
  printf("%s", prog->toString());
  //scanf("a");
  //printf("-----------------------\n\n");
  //fflush(NULL);
  //printf(prog->toString());
  printf("\n-----------------------\n");
  printf("Maintenant, exécution du programme.\n");
  printf("-----------------------\n\n");
  fflush(NULL);
  prog->execute();
  printf("\n-----------------------\n");
  printf("Fin de l'exécution.");
  printf("@+    Romain");

  pmessend();

  return 0;
}
  





