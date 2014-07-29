#ifndef COEURS_HPP
#define COEURS_HPP

#include "text.hpp"
#include "texture.hpp"


/*******************************************************************************
 Affichage des coeurs
 (animés et tout...)
 ******************************************************************************/

#define nb_Etape_Animation 64


class CAffichageCoeur;
//enum TCoeurTypeAnimation;


enum TCoeurTypeAnimation {caONNEFAITRIEN, caECLATERGROSCOEUR, caPERDREGROSCOEUR, caPERDREPETITSCOEURS};



class CAffichageCoeur {
  CTexture * texcoeur;
  float temps;
  int pv;
  int iAnimation;
  int nbpetitscoeursperdus;
  
  TCoeurTypeAnimation TypeAnimation;
  bool JeSuisEnTrainDEtreAnimeDsl;
    
    
public:
  CAffichageCoeur();
  ~CAffichageCoeur();
  
  /*il faut informer l'objet du nombre de pv du héros à chaque tour 
    via un appel du genre : InformerNbPV(Hero->GetPV())*/
  void InformerNbPV(int inpv);  
  
  // affiche dans le coin supérieur gauche des coeurs
  void Render(void) const;

  void Life(void);
};




// TODO bad
extern CAffichageCoeur * AffichageCoeur; 


#endif

