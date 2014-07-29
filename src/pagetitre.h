#ifndef CPageTitre_HPP
#define CPageTitre_HPP


#include "global.hpp"
#include "texture.hpp"
#include "text.hpp"

/******************************************************************************
     page de titre
******************************************************************************/
class CPageTitre {
#define NB_ETAPE_FADING 64
  private:  
     enum TPageTitreAction {ptFADEIN, ptTITRE, ptFADEOUT};
     TPageTitreAction Action;
     CTexture* DessineMoiUnMouton;
     CTexture* Titre;
     int t;
     int fade;
     float Ligne_Courante;
     
  public:
     CPageTitre();
     ~CPageTitre();

  void Render(void) const;
  bool Life(void);
       
       
};


#endif
