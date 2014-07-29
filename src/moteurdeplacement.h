#include "bonhomme.hpp"
#include "liste.hpp"
//#include "


class COrdresDeplacement {
private:
 
public:
  COrdresDeplacement(void);
  ~COrdresDeplacement(void);
  
  void AjouterOrdreDeplacement(TPoint3D pos);
  void AppliquerOrdresA(CBonhomme * b);
};

