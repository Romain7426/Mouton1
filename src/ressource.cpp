#include "global.hpp"
#include "ressource.hpp"



void metacollecter(void) {
  gestion3DS.collecter();
  gestionTexture.collecter();
}


gestionnaire<C3DS> gestion3DS;
gestionnaire<CTexture> gestionTexture;
gestionnaire<CPascal> gestionPascal;
