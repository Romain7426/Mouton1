#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
extern int main(void) {
  int c;
#define MPPP "ert" "tyu"
  printf("%s, %ld\n", MPPP, strlen(MPPP));

  while ((c = getc(stdin)) != EOF) {
    (void) printf("%c %c %c\n", (char) c, (char) tolower(c), (char) toupper(c));
  }

  return 0;
}

