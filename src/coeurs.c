#include "global.h"
#include "coeurs.h"

CAffichageCoeur * AffichageCoeur = NULL;

#define JeSuisEnTrainDEtreAnimeDsl (this -> JeSuisEnTrainDEtreAnimeDsl)
#define texcoeur                   (this -> texcoeur)
#define pv                         (this -> pv)
#define temps                      (this -> temps)
#define TypeAnimation              (this -> TypeAnimation)
#define nbpetitscoeursperdus       (this -> nbpetitscoeursperdus)
#define iAnimation                 (this -> iAnimation)

CAffichageCoeur * CAffichageCoeur_make(void) {
  MALLOC_BZERO(CAffichageCoeur,this);
  
  ASSIGN_METHOD(CAffichageCoeur,this,InformerNbPV); 
  ASSIGN_METHOD(CAffichageCoeur,this,Render); 
  ASSIGN_METHOD(CAffichageCoeur,this,Life); 
  
  message("Création du module d'affichage de coeur...\n");
  JeSuisEnTrainDEtreAnimeDsl = false; 
  texcoeur = CTexture_make("./coeur.png");
  pv = 21;  
  temps = 0.0f;
  TypeAnimation = caONNEFAITRIEN;
  
  return this; 
}; 

void CAffichageCoeur_delete(CAffichageCoeur * this) {
  CTexture_delete(texcoeur);
  free(this); 
}; 

void CAffichageCoeur__InformerNbPV(CAffichageCoeur * this, int inpv) {
  if (pv == inpv) return; 
  if (JeSuisEnTrainDEtreAnimeDsl) return; 
  
  message("Coeur : InformerNbPV(%i) (alors que l'ancien pv vaut %i)\n", inpv, pv); 
  
  if (pv < inpv) { 
    pv = inpv; 
    return; 
  }; 
  
  if (pv > inpv) {
    message("Coeur : %i, %i\n", inpv / 7, pv / 7 - 1);
    
    if ((inpv / 7) < (pv / 7 - 1)) {
      //on perd des gros coeurs (plus que 1) : le num pv / 7
      pv = (inpv / 7) * 7;
      TypeAnimation = caPERDREGROSCOEUR;
    } 
    
    else if ((inpv / 7) == (pv / 7 - 1)) {
      //on perd un gros coeur : le num pv / 7
      nbpetitscoeursperdus = pv % 7;
      pv = (inpv / 7) * 7 + 6;
      message("Coeur : On perd un gros coeur : le n° %i. On a %i pvs temporairement.\n", inpv/7, pv);
      TypeAnimation = caECLATERGROSCOEUR;
    }
    
    else {
      //on perd que des petits coeurs
      nbpetitscoeursperdus = pv - inpv;
      pv = inpv;
      message("Coeur : On perd %i petit(s) coeur(s)\n", nbpetitscoeursperdus);
      TypeAnimation = caPERDREPETITSCOEURS;
    };
         
         
  }; 
   
  iAnimation = 0;
  JeSuisEnTrainDEtreAnimeDsl = true;
   
};





void CAffichageCoeur__Life(CAffichageCoeur * this) {
        iAnimation++;                          
        if (iAnimation > nb_Etape_Animation)                         
          JeSuisEnTrainDEtreAnimeDsl = false;



  temps += 0.1f;
    

};


void CAffichageCoeur__Render(const CAffichageCoeur * this) {
  int jj = 0;
  jj = 0;
  
  glEnable2D(); {
    
    CTexture__GLTextureCourante(texcoeur);
    
    glDisable(GL_LIGHTING);
    
    glBegin(GL_QUADS); {

  
#define CadreX 32
#define CadreY 450
#define TailleGrosCoeur (28+2.0f*cosf(temps+(jj++)/10.0f))
#define TailleCoeur (16-2.0f*cosf(temps+(jj++)/10.0f))
#define EspGrosCoeur (TailleGrosCoeur+4)
#define EspCoeur (TailleCoeur+4)
#define EcartGrosPetit 16
  
      for (int i = 0; i < (pv / 7); i++) {
        // toutes ces lignes de code sont très bizarres, 
        // car elles dépendent de l'ordre de l'évaluation. 
        // De plus, avec le jj++ dedans, TailleGrosCoeur et consort ne sont pas les mêmes
        // dans la même fonction!!!!
        BLITCX(CadreX + i * EspGrosCoeur, CadreY, TailleGrosCoeur, TailleGrosCoeur); 
      };
      
    
   
      int numdebpetitcoeur = 0;
    
      if (JeSuisEnTrainDEtreAnimeDsl) {
        float t = ((float) iAnimation) / nb_Etape_Animation;  
        int numgroscoeur = (pv / 7);                       
        switch(TypeAnimation) {
	case caONNEFAITRIEN: break;
        case caECLATERGROSCOEUR:
          
          numdebpetitcoeur = 1000;                 

          if (t < 0.5f) {
            t = min(t * 4.0f, 1.0f);
            /*le gros coeur va en avant*/
            BLITCX(CadreX + EspGrosCoeur * numgroscoeur + t*6*EspCoeur, CadreY, TailleGrosCoeur, TailleGrosCoeur);
                     
            /*on dessine les coeurs qui sont frappés par le gros coeur*/
            for (int i = 0; i < (nbpetitscoeursperdus); i++)
              BLIT(CadreX - EcartGrosPetit + (numgroscoeur) * EspGrosCoeur + i * EspCoeur + t * 400, CadreY + t * 64, TailleCoeur, TailleCoeur, 0, 0, 1, 1);         
                         

          }

          else {
            t = (t - 0.5f) * 2.0f;
            /*puis revient en arrière...*/
            float taillegroscoeurquidevientpetit = TailleGrosCoeur * (1-t) + t * TailleCoeur;
            BLITCX(CadreX + EspGrosCoeur * numgroscoeur + (1.0f-t) * 6 * EspCoeur, CadreY, taillegroscoeurquidevientpetit, taillegroscoeurquidevientpetit); 
            
            /*en déballant les petits coeurs...*/
            numdebpetitcoeur = (int) (6.0f*(1.0f-t));

          }
          break;
        
          
        case caPERDREPETITSCOEURS:
          /*les coeurs volent*/
          for (int i = (pv % 7); i < (pv % 7 + nbpetitscoeursperdus); i++)
            BLITCX(CadreX - EcartGrosPetit + (pv / 7) * EspGrosCoeur + i * EspCoeur + 16.0f * cos(temps), CadreY + (int) (t*64.0f), TailleCoeur, TailleCoeur);   
                
          break;



        case caPERDREGROSCOEUR:
          /* Un jour peut etre ... */
          break;
          
          
        default:
          messerr("coeurs__render: on ne devrait pas être ici.");
        }  
        

      }
    
  
           
      for (int i = numdebpetitcoeur; i< (pv % 7); i++)
        BLIT(CadreX - EcartGrosPetit + (pv / 7) * EspGrosCoeur + i * EspCoeur, CadreY, TailleCoeur, TailleCoeur, 0, 0, 1, 1);    
              
    
    } glEnd();

  } glDisable2D();
  
};







