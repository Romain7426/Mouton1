class CMenu;
#include "menu.hpp"




#define MAX_LONGUEUR_BUFFER 16

class CMenuEntreeNom : public CMenu
{
private:
     int poscur;
     void RetArr();
     
public:
     char buffer[MAX_LONGUEUR_BUFFER];
     
     CMenuEntreeNom();
     ~CMenuEntreeNom();
     
     void Init();
         
     bool InputAndRender(); 
};


