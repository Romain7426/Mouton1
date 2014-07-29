#include "global.h"
#include "main.h"
#include "programme.h"
#include "lexer_for_c_language.h"

int main(const int argc, const char * argv[]) {
  int retour;
  retour = 0;
  
  srandomdev();
  //srandom();
  
  biglib_structures_base_test();
  
#if 1
  programme_boucle(argc, argv);
#else
  if (2 != argc) {
    put_string("usage: ");
    put_string(argv[0]);
    put_string(" name-of-a-C-file.c\n");
    return -1;
  }
#endif

  
  
  
  
#ifdef WINDOWS_DEV_CPP
  system("pause");
#endif
  
  return retour;
}






