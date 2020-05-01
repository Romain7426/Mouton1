#include "global.h"
#include "timer.h"



static int t;


void DebutDePasse(void) {
  t = SDL_GetTicks();    
};



void FinDePasse(void) { 
  const int diff = SDL_GetTicks() - t; 
  
enum { nb_microsec_in_passe = 20 }; 
#if 1 
  if (diff < nb_microsec_in_passe) { 
    SDL_Delay(nb_microsec_in_passe - diff); 
  }; 
#endif 
  
}; 





