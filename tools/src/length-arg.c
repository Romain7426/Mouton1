#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 
#include "lib.ci" 
int main(const int argc, const char *argv[]) { 
  for (int i = 1; i < argc; i++) { 
    const int len = cstrlen(argv[i]); 
#if 0 
    write_long_long_int_old(STDOUT_FILENO, len); 
    write_eol(STDOUT_FILENO); 
#else 
    write_llint_ln(STDOUT_FILENO, len); 
#endif 
  }; 
  return 0; 
}; 
