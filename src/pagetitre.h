#ifndef CPageTitre_H
#define CPageTitre_H

/******************************************************************************
     Page de titre
******************************************************************************/

enum TPageTitreAction {ptFADEIN, ptTITRE, ptFADEOUT};
TYPEDEF_TYPENAME_WITHOUT_ENUM(TPageTitreAction);

struct CPageTitre {
#define NB_ETAPE_FADING 64
  //private:  
  TPageTitreAction Action;
  CTexture * DessineMoiUnMouton;
  CTexture * Titre;
  int t;
  int fade;
  float Ligne_Courante;
  
  void (* Render)(const struct CPageTitre * this);
  bool (* Life)(struct CPageTitre * this);
};
extern CPageTitre * CPageTitre_make(void);
extern void CPageTitre_delete(CPageTitre * this);
extern void CPageTitre__Render(const CPageTitre * this);
extern bool CPageTitre__Life(CPageTitre * this);


#endif
