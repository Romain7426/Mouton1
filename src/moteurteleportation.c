#include "global.h"
#include "moteurteleportation.h"
#include "map.h"
#include "bonhomme.h"
#include "text.h" //pour enable2D
//#include "camera.h" //pour initcamera
#include "script_api.h"
#include "015_game_events.h" 
#include "010_game.h" 



// ***************************** CZoneTeleportation ***************************** 

struct CZoneTeleportation { 
  TPoint3D   position; 
  TPoint3D   dimension; 
  TDirection depart_direction; // RL: That terrible thing should be removed. 
  char *     destination_carte; 
  TPoint3D   destination_position; 
  TDirection destination_direction; 
}; 

const int8_t CZoneTeleportation_bytesize_actual = sizeof(struct CZoneTeleportation); 
//ASSERT_COMPILE__TOPLEVEL(CZoneTeleportation_bytesize >= CZoneTeleportation_bytesize_actual); 

CZoneTeleportation * CZoneTeleportation_make(TPoint3D in_position, TPoint3D in_dimension, TDirection in_depart_direction, const char * in_destination_carte, TPoint3D in_destination_position, TDirection in_destination_direction) { 
  MALLOC_BZERO(CZoneTeleportation,this);
  
  this -> position = in_position;
  this -> dimension = in_dimension;
  this -> depart_direction = in_depart_direction;

  this -> destination_carte = strcopy(in_destination_carte);
  this -> destination_position = in_destination_position;
  this -> destination_direction = in_destination_direction;

  return this; 
}; 

void CZoneTeleportation_delete(CZoneTeleportation * this) {
  free(this); 
}; 

CZoneTeleportation * CZoneTeleportation_copy(const CZoneTeleportation * zt_src) {
  MALLOC_BZERO(CZoneTeleportation,this);
  *this = *zt_src; 
  this -> destination_carte = strcopy(zt_src -> destination_carte); 
  return this; 
}; 

bool CZoneTeleportation__dedans_huh(const CZoneTeleportation * this, const TPoint3D p) { 
  return ((this -> position.x <= p.x) &&
          (this -> position.y <= p.y) &&
          (this -> position.z <= p.z) &&
          (p.x <= this -> position.x + this -> dimension.x) &&
          (p.y <= this -> position.y + this -> dimension.y) &&
          (p.z <= this -> position.z + this -> dimension.z) ); 
}; 

const char *         CZoneTeleportation__destination_carte(const CZoneTeleportation * this) { 
  return this -> destination_carte; 
}; 
TDirection     CZoneTeleportation__depart_direction (const CZoneTeleportation * this) { 
  return this -> depart_direction; 
}; 
TPoint3D       CZoneTeleportation__position         (const CZoneTeleportation * this) { 
  return this -> position; 
}; 
TPoint3D       CZoneTeleportation__dimension        (const CZoneTeleportation * this) {
  return this -> dimension; 
}; 






/**********************
  moteur de téléportation
***************************************************/

enum { NB_ANIM2_TELEPORTATION = 32 }; 



struct CMoteurTeleportation {
  CZoneTeleportation * zt;
  int anim;
  float r, v, b;
            
  void (* DebuterTeleportation)(struct CMoteurTeleportation * this, const CZoneTeleportation * in_zt);
  // on commence une téléportation
  
  bool (* IsTeleportationEnCours)(const struct CMoteurTeleportation * this);
  // précise si le jeu est en train de réaliser une téléportation
  
  void (* SetCouleurFondu)(struct CMoteurTeleportation * this, int in_couleur);
  
  //void (* Life)(struct CMoteurTeleportation * this, struct CMap * &Map, bool &EnVaisseau, struct CBonhomme * &Hero, bool &SCRIPT_SystemeRendMainAuScript);
  void (* Life)(struct CMoteurTeleportation * this, struct CMap * * Map_ptr, bool * EnVaisseau_ptr, struct CBonhomme * * Hero_ptr, bool * SCRIPT_SystemeRendMainAuScript_ptr);

  //void (* Render)(const struct CMoteurTeleportation * this, struct CMap * &Map, bool &EnVaisseau, struct CBonhomme * &Hero);
  void (* Render)(const struct CMoteurTeleportation * this, struct CMap * * Map_ptr, bool * EnVaisseau_ptr, struct CBonhomme * * Hero_ptr, const riemann_t * our_manifold);
  /*si le jeu ne fait pas de téléportation, ==> ne fait rien
    sinon, avance dans la téléportation
    (dessine le fondu... à placer en fin de RaiseRender())
    charge la nouvelle carte
    puis fondu inverse
  */
  
  CMoteurTeleportation * (* make)(void);
  CMoteurTeleportation * (* make_content)(CMoteurTeleportation * this);
  void (* delete)(CMoteurTeleportation * this);
  void (* delete_content)(CMoteurTeleportation * this);
};

const int8_t CMoteurTeleportation_bytesize_actual = sizeof(struct CMoteurTeleportation); 
//ASSERT_COMPILE__TOPLEVEL(CMoteurTeleportation_bytesize >= CMoteurTeleportation_bytesize_actual); 







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

void CMoteurTeleportation__DebuterTeleportation(CMoteurTeleportation * this, const CZoneTeleportation * in_zt) {
  this -> zt   = CZoneTeleportation_copy(in_zt); 
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
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Map_ref = %p - EnVaisseau_ref = %p - Hero_ref = %p - SCRIPT_SystemeRendMainAuScript_ref = %p "   "\n", __func__, this, Map_ref, EnVaisseau_ref, Hero_ref, SCRIPT_SystemeRendMainAuScript_ref); 
  
  if (this -> anim <= 0) { 
    *SCRIPT_SystemeRendMainAuScript_ref = true; 
    return; 
  }; 
  
#if 0 
  if ((this -> anim == NB_ANIM2_TELEPORTATION) && (this -> zt -> destination_carte != NULL)  && (this -> zt -> destination_carte[0] != '\0')) { 
    CMap__delete(*Map_ref); 
    *Map_ref = NULL; 
    
    printf("Le moteur de téléportation charge la carte...\n");
      
    if (0 == strcmp(this -> zt -> destination_carte, "tore.carte")) {
      printf("On est en vaisseau car on est sur tore.carte !!!\n");                         
      *EnVaisseau_ref = true;
    }
    else {
      *EnVaisseau_ref = false;
      //  Camera.InitCamera();
    }; 
    
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
    
  }; 
#endif 
  
  this -> anim--;
  
  
  /*anim == 1, ça veut dire que la téléportation est presque terminé
    il faut donc informer le niveau supérieur qu'on va rendre la main
    
    (la boucle dans SCRIPT_ChangerDeCarte())
  */
  if (this -> anim == 1) { 
    if (this -> zt -> destination_carte != NULL) { 
      //RaiseEvenement(EVT_EntreeSurCarte); 
      //EvenementsModule -> Raise(EVT_EntreeSurCarte); 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Map_ref = %p - EnVaisseau_ref = %p - Hero_ref = %p - SCRIPT_SystemeRendMainAuScript_ref = %p "   "\n", __func__, this, Map_ref, EnVaisseau_ref, Hero_ref, SCRIPT_SystemeRendMainAuScript_ref); 
      //Game_Events_Raise(GAME_EVENTS__MAP__LOADED_READY); 
    }; 
    *SCRIPT_SystemeRendMainAuScript_ref = true; 
  }; 
  
}; 


void CMoteurTeleportation__Render(const CMoteurTeleportation * this, CMap * * Map_ref, bool * EnVaisseau_ref, CBonhomme * * Hero_ref, const riemann_t * our_manifold) {
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = %p - Map_ref = %p - EnVaisseau_ref = %p - Hero_ref = %p - our_manifold = %p "   "\n", __func__, this, Map_ref, EnVaisseau_ref, Hero_ref, our_manifold); 
  
  if (this -> anim == 0) return;


#if 1  
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
#endif 

  if (this -> anim >= NB_ANIM2_TELEPORTATION) {
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

