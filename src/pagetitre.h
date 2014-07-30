#ifndef CPageTitre_H
#define CPageTitre_H


#include "global.h"
#include "texture.h"
#include "text.h"

/******************************************************************************
     page de titre
******************************************************************************/

enum TPageTitreAction {ptFADEIN, ptTITRE, ptFADEOUT};
TYPEDEF_TYPENAME_WITHOUT_ENUM(TPageTitreAction);

struct CPageTitre {
#define NB_ETAPE_FADING 64
  //private:  
  TPageTitreAction Action;
  CTexture* DessineMoiUnMouton;
  CTexture* Titre;
  int t;
  int fade;
  float Ligne_Courante;
  
  //public:
#if 0
  CPageTitre();
  ~CPageTitre();
#endif

  void (* Render)(const struct CPageTitre * this);
  bool (* Life)(struct CPageTitre * this);
};


#endif
