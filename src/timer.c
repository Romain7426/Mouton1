#include "global.h"
#include "timer.h"


extern int main(const int argc, const char * argv[]); 
extern void timer_hello(void) { 
  fprintf(stderr, "Hello World!\n"); 
  fprintf(stderr, "Addr of 'main' = %p " "\n", main); 
}; 





