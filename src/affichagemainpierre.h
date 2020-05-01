#ifndef CAffichageMainPierre_H
#define CAffichageMainPierre_H

/*******************************************************************************
 Affichage de la main et de la pierre (qui indique l'heure)
 ******************************************************************************/

struct CAffichageMainPierre {
  CTexture * main;
  CTexture * pierre;

  void (* Render)(const struct CAffichageMainPierre * this, const float y, const float FacteurCompression); //const CMap * Map);
};    
extern CAffichageMainPierre * CAffichageMainPierre_make(void); 
extern void CAffichageMainPierre_delete(CAffichageMainPierre * this); 
extern void CAffichageMainPierre__Render(const CAffichageMainPierre * this, const float y, const float FacteurCompression); //const CMap * Map); 



#endif

