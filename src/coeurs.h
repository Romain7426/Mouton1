#ifndef COEURS_H
#define COEURS_H

#include "text.h"
#include "texture.h"


/*******************************************************************************
 Affichage des coeurs
 (animés et tout...)
 ******************************************************************************/

#define nb_Etape_Animation 64


struct CAffichageCoeur;
//enum TCoeurTypeAnimation;


enum TCoeurTypeAnimation {caONNEFAITRIEN, caECLATERGROSCOEUR, caPERDREGROSCOEUR, caPERDREPETITSCOEURS};



struct CAffichageCoeur {
  CTexture * texcoeur;
  float temps;
  int pv;
  int iAnimation;
  int nbpetitscoeursperdus;
  
  TCoeurTypeAnimation TypeAnimation;
  bool JeSuisEnTrainDEtreAnimeDsl;
    
    
  //public:
#if 0
  struct CAffichageCoeur();
  ~struct CAffichageCoeur();
#endif
  
  /*il faut informer l'objet du nombre de pv du héros à chaque tour 
    via un appel du genre : InformerNbPV(Hero->GetPV())*/
  void (* InformerNbPV)(struct CAffichageCoeur * this, int inpv);  
  
  // affiche dans le coin supérieur gauche des coeurs
  void (* Render)(const struct CAffichageCoeur * this);
  
  void (* Life)(struct CAffichageCoeur * this);
};




// TODO bad
extern struct CAffichageCoeur * AffichageCoeur; 


#endif

