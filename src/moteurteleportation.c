#include "global.h"
#include "moteurteleportation.h"
#include "map.h"
#include "bonhomme.h"
#include "text.h" //pour enable2D
//#include "camera.h" //pour initcamera
#include "script_api.h"





/**********************
  moteur de téléportation
***************************************************/

#define NB_ANIM2_TELEPORTATION 32


CMoteurTeleportation * CMoteurTeleportation__make_content(CMoteurTeleportation * this) { 
  bzero(this, sizeof(*this)); 
  
  ASSIGN_METHOD(CMoteurTeleportation,this,DebuterTeleportation); 
  ASSIGN_METHOD(CMoteurTeleportation,this,IsTeleportationEnCours); 
  ASSIGN_METHOD(CMoteurTeleportation,this,SetCouleurFondu); 
  ASSIGN_METHOD(CMoteurTeleportation,this,Life); 
  ASSIGN_METHOD(CMoteurTeleportation,this,Render); 
  ASSIGN_METHOD(CMoteurTeleportation,this,make); 
  ASSIGN_METHOD(CMoteurTeleportation,this,make_content); 
  ASSIGN_METHOD(CMoteurTeleportation,this,delete); 
  ASSIGN_METHOD(CMoteurTeleportation,this,delete_content); 
  
  this -> anim = 0; 
  this -> r = 0.0f;
  this -> v = 0.0f;
  this -> b = 0.0f;
  
  return this; 
};

CMoteurTeleportation * CMoteurTeleportation__make(void) {
  //MALLOC_BZERO(CMoteurTeleportation,this); 
  CMoteurTeleportation * this = NULL; 
  this = (CMoteurTeleportation *) malloc(sizeof(*this)); 
  return CMoteurTeleportation__make_content(this); 
};

void CMoteurTeleportation__delete_content(CMoteurTeleportation * this) {
  if (this -> zt != NULL) { 
    CZoneTeleportation_delete(this -> zt); 
    this -> zt = NULL; 
  }; 
}; 

void CMoteurTeleportation__delete(CMoteurTeleportation * this) {
  CMoteurTeleportation__delete_content(this); 
  free(this);
}; 

void CMoteurTeleportation__DebuterTeleportation(CMoteurTeleportation * this, CZoneTeleportation in_zt) {
  this -> zt   = CZoneTeleportation_copy(&in_zt); 
  this -> anim = 2 * NB_ANIM2_TELEPORTATION; 
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
    if (this -> zt -> destination_carte != NULL) {
      //RaiseEvenement(EVT_EntreeSurCarte);
      EvenementsModule -> Raise(EVT_EntreeSurCarte);
    }; 
    
    *SCRIPT_SystemeRendMainAuScript_ref = true;
  }; 

};


void CMoteurTeleportation__Render(const CMoteurTeleportation * this, CMap * * Map_ref, bool * EnVaisseau_ref, CBonhomme * * Hero_ref, const riemann_t * our_manifold) {
  if (this -> anim == 0) return;
  
  if (this -> anim >= NB_ANIM2_TELEPORTATION) {
    // RL: Why that thing is in render??? Good Lord. 
    if ((this -> anim == NB_ANIM2_TELEPORTATION) && (this -> zt -> destination_carte != NULL)  && (this -> zt -> destination_carte[0] != '\0')) { 
      CMap__delete(*Map_ref); 
      *Map_ref = NULL; 

      printf("Le moteur de téléportation charge la carte...\n");
      



      // RL: Why that thing is in render??? Good Lord. 
      if (0 == strcmp(this -> zt -> destination_carte, "tore.carte")) {
        printf("On est en vaisseau car on est sur tore.carte !!!\n");                         
        *EnVaisseau_ref = true;
      }
      else {
        *EnVaisseau_ref = false;
        //  Camera.InitCamera();
      }; 



        
      // RL: Why that thing is in render??? Good Lord. 
      *Map_ref = CMap__make(this -> zt -> destination_carte, /*map_i*/0, /*map_j*/0, our_manifold, *EnVaisseau_ref);
      CBonhomme * Hero = *Hero_ref; 
      CPhysicalObj * aHero = &Hero -> parent1; 
      //aHero -> SetPosition_vXY(aHero, this -> zt -> destination_position.x, this -> zt -> destination_position.y, mpABSOLU, *Map_ref); 
      aHero -> SetPosition_vP3D(aHero, this -> zt -> destination_position, *Map_ref); 
      if (aHero -> p.z < aHero -> z0) aHero -> p.z = aHero -> z0; 
      Hero  -> SetDirection(Hero, this -> zt -> destination_direction); 
      //aHero -> Acceleration_add_vXYZ(aHero, 0.0f, 0.0f, 200.0f); // RL: WHY??? // RL: The z-coordinate was not normalized... 
      Hero  -> ViderOrdresDeplacement(Hero); 
      
      // FS: ne marche que si le changement de carte s'est effectué en dehors d'un script :) 
      //RaiseEvenement(EVT_ChargementCarte); 
      EvenementsModule -> Raise(EVT_ChargementCarte); 
      
      
      
      
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

