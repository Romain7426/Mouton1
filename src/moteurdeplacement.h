#include "bonhomme.h"
#include "liste.h"
//#include "


struct COrdresDeplacement {
#if 0
  COrdresDeplacement(void);
  ~COrdresDeplacement(void);
#endif
  
  void (* AjouterOrdreDeplacement)(struct COrdresDeplacement * this, TPoint3D pos);
  void (* AppliquerOrdresA)(struct COrdresDeplacement * this, struct CBonhomme * b);
};

