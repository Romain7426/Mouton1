#include "pascal.tools.hpp"
#include "pascal.hpp"
#include "pascal.mem.hpp"


int main(void) {
  pmessinit("essai");

  pmessage("\nEssai de la fonction %s | %d %p", "pmessage", 54, &main);
  pmesserr("\nEssai de la fonction %s | %d %p", "pmesserr", 54, &main);

  pmessage("\nPASCAL_MEM_SIZE %u", PASCAL_MEM_SIZE);
  pmessage("\nPASCAL_MEM_SIZE2 %u", PASCAL_MEM_SIZE2);
  pmessage("\nPASCAL_MEM_SIZE3 %u", PASCAL_MEM_SIZE3);
  pmessage("\nPASCAL_MEM_SIZE4 %u", PASCAL_MEM_SIZE4);

  pmessend();
  return 0;
}
