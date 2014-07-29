#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  printf("%d", strlen(NULL)); // seg fault
  return 0;
}
