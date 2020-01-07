#include <stdlib.h>
#include <stdio.h>
#include "pascal.parser.hpp"

extern FILE *yypascalout;
extern FILE *yypascalin;
extern int yypascallex(void);

int main(int argc, char *argv[]) {
  yypascalout = fopen("pascal.lexer.out", "w");
  yypascalin = fopen("pascal.test.pml", "r");
  while (yypascallex() != TOKEN_EOF) continue;

  return 0;
}


