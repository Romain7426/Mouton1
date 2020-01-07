#include "global.h"
#include "moteurteleportation.h"
#include "map.h"
#include "bonhomme.h"
#include "apiscript.h"
#include "text.h" //pour enable2D
#include "camera.h" //pour initcamera





/**********************
  moteur de téléportation
***************************************************/

#define NB_ANIM2_TELEPORTATION 32


CMoteurTeleportation * CMoteurTeleportation_make(void) {
  MALLOC_BZERO(CMoteurTeleportation,this);
  
  ASSIGN_METHOD(CMoteurTeleportation,this,DebuterTeleportation); 
  ASSIGN_METHOD(CMoteurTeleportation,this,IsTeleportationEnCours); 
  ASSIGN_METHOD(CMoteurTeleportation,this,SetCouleurFondu); 
  ASSIGN_METHOD(CMoteurTeleportation,this,Life); 
  ASSIGN_METHOD(CMoteurTeleportation,this,Render); 
  
  this -> anim = 0; 
  this -> r = 0.0f;
  this -> v = 0.0f;
  this -> b = 0.0f;
  
  return this; 
};

void CMoteurTeleportation_delete(CMoteurTeleportation * this) {
  if (this -> zt != NULL) CZoneTeleportation_delete(this -> zt); 
  free(this);
}; 

void CMoteurTeleportation__DebuterTeleportation(CMoteurTeleportation * this, CZoneTeleportation in_zt) {
  this -> zt = CZoneTeleportation_copy(&in_zt);
  this -> anim = 2*NB_ANIM2_TELEPORTATION;
};

void CMoteurTeleportation__SetCouleurFondu(CMoteurTeleportation * this, int in_couleur) {
  this -> r = ((float) ( in_couleur & 255)) / 255.0f;  
  this -> v = ((float) ((in_couleur & 256*255) >> 8 ) ) / 255.0f;  
  this -> b = ((float) ((in_couleur & (256*256*255)) >> 16)) / 255.0f;
  
  printf("CMoteurTeleportation__SetCouleurFondu(%i) effectuée!\n", in_couleur);
  printf("    r = %f\n", this -> r);
  printf("    v = %f\n", this -> v);
  printf("    b = %f\n", this -> b);
};

bool CMoteurTeleportation__IsTeleportationEnCours(const CMoteurTeleportation * this) {
  return (this -> anim > 1);   
};




void CMoteurTeleportation__Life(CMoteurTeleportation * this, CMap * * Map_ref, bool * EnVaisseau_ref, CBonhomme * * Hero_ref, bool * SCRIPT_SystemeRendMainAuScript_ref) {
  if (this -> anim == 0) return;
  
  this -> anim--;
  
  
  /*anim == 1, ça veut dire que la téléportation est presque terminé
    il faut donc informer le niveau supérieur qu'on va rendre la main
    
    (la boucle dans SCRIPT_ChangerDeCarte())
  */
  if (this -> anim == 1) {
    if (this -> zt -> destination_carte != NULL)
      RaiseEvenement(EVT_EntreeSurCarte);
    
    *SCRIPT_SystemeRendMainAuScript_ref = true;
  }; 

};


void CMoteurTeleportation__Render(const CMoteurTeleportation * this, CMap * * Map_ref, bool * EnVaisseau_ref, CBonhomme * * Hero_ref) {
  if (this -> anim == 0) return;
  
  if (this -> anim >= NB_ANIM2_TELEPORTATION) {
    if ((this -> anim == NB_ANIM2_TELEPORTATION) && (this -> zt -> destination_carte != NULL)  && (this -> zt -> destination_carte[0] != '\0')) {
      CMap_delete(*Map_ref);
      *Map_ref = NULL;

      printf("Le moteur de téléportation charge la carte...\n");
      
      if (0 == strcmp(this -> zt -> destination_carte, "tore.carte")) {
        printf("On est en vaisseau car on est sur tore.carte !!!\n");                         
        *EnVaisseau_ref = true;
      }
      else {
        *EnVaisseau_ref = false;
        //  Camera.InitCamera();
      }
        
      *Map_ref = CMap_make(this -> zt -> destination_carte, *EnVaisseau_ref);
      CBonhomme * Hero = *Hero_ref; 
      CPhysicalObj * aHero = &Hero -> parent1; 
      aHero -> SetPosition_vTPoint3D(aHero, this -> zt -> destination_position);
      Hero -> SetDirection(Hero, this -> zt -> destination_direction);
      aHero -> AddForce_vXYZ(aHero, 0.0f, 0.0f, 200.0f);
      Hero -> ViderOrdresDeplacement(Hero);
      
      // ne marche que si le changement de carte s'est effectué en dehors d'un script :)
      RaiseEvenement(EVT_ChargementCarte);
    }

#if 1
    glEnable2D(); {
      glDisable(GL_TEXTURE_2D);
      glColor4f(this -> r, this -> v, this -> b, 1.0f - ((float) (this -> anim - NB_ANIM2_TELEPORTATION)) / (float) NB_ANIM2_TELEPORTATION);
      BEGIN_RECTANGLE_END(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    } glDisable2D();
#endif
  }
  
  else if (this -> anim < NB_ANIM2_TELEPORTATION) {
#if 1
    glEnable2D(); {
      glDisable(GL_TEXTURE_2D);
      glColor4f(this -> r, this -> v, this -> b, ((float) (this -> anim)) / (float) NB_ANIM2_TELEPORTATION);
      BEGIN_RECTANGLE_END(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    } glDisable2D();
#endif
  }

  
  printf("ANIM du moteur de téléportation = %i\n", this -> anim);
}; 

