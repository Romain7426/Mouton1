struct CMenu;
#include "menu.h"




#define MAX_LONGUEUR_BUFFER 16

struct CMenuEntreeNom /* : public CMenu */ {
  CMenu parent;
  
  //private:
  int poscur;
  char buffer[MAX_LONGUEUR_BUFFER];
  
  
  
  void (* RetArr)(struct CMenuEntreeNom * this);
  
  //public:
#if 0
  CMenuEntreeNom();
  ~CMenuEntreeNom();
#endif
  
  void (* Init)(struct CMenuEntreeNom * this);
  
  bool (* InputAndRender)(struct CMenuEntreeNom * this); 
};


