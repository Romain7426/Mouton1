#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
const extern int main(void) {
  int c;

  while ((c = getc(stdin)) != EOF) {
    (void) printf("%c %c %c\n", (char) c, (char) tolower(c), (char) toupper(c));
  }

  return 0;
}

