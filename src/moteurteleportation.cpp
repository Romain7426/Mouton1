#include "global.hpp"
#include "moteurteleportation.hpp"
#include "map.hpp"
#include "bonhomme.hpp"
#include "apiscript.hpp"
#include "text.hpp" //pour enable2D
#include "camera.hpp" //pour initcamera





/**********************
  moteur de téléportation
***************************************************/

#define NB_ANIM2_TELEPORTATION 32


CMoteurTeleportation::CMoteurTeleportation(void) : anim(0), r(0.0f), v(0.0f), b(0.0f) {}


void CMoteurTeleportation::DebuterTeleportation(CZoneTeleportation in_zt) {
  zt = new CZoneTeleportation(in_zt);
  anim = 2*NB_ANIM2_TELEPORTATION;
}


void CMoteurTeleportation::SetCouleurFondu(int in_couleur) {
  r = ((float) ( in_couleur & 255)) / 255.0f;  
  v = ((float) ((in_couleur & 256*255) >> 8 ) ) / 255.0f;  
  b = ((float) ((in_couleur & (256*256*255)) >> 16)) / 255.0f;
  
  printf("CMoteurTeleportation::SetCouleurFondu(%i) effectuée!\n", in_couleur);
  printf("    r = %f\n", r);
  printf("    v = %f\n", v);
  printf("    b = %f\n", b);
}


bool CMoteurTeleportation::IsTeleportationEnCours(void) const {
  return (anim > 1);   
}




void CMoteurTeleportation::Life(CMap * &Map, bool &EnVaisseau, CBonhomme * &Hero, bool &SCRIPT_SystemeRendMainAuScript) {
  if (anim == 0) return;

  anim--;


  /*anim == 1, ça veut dire que la téléportation est presque terminé
    il faut donc informer le niveau supérieur qu'on va rendre la main
    
    (la boucle dans SCRIPT_ChangerDeCarte())
  */
  if (anim == 1) {
    if (zt -> destination_carte != NULL)
      RaiseEvenement(EVT_EntreeSurCarte);
    
    SCRIPT_SystemeRendMainAuScript = true;
  }

}


void CMoteurTeleportation::Render(CMap * &Map, bool &EnVaisseau, CBonhomme * &Hero) const {
  if (anim == 0) return;
  
  if (anim >= NB_ANIM2_TELEPORTATION) {
    if ((anim == NB_ANIM2_TELEPORTATION) && (zt -> destination_carte != NULL)  && (zt -> destination_carte[0] != '\0')) {
      delete Map;
      Map = NULL;

      printf("Le moteur de téléportation charge la carte...\n");
      
      if (0 == strcmp(zt -> destination_carte, "tore.carte")) {
        printf("On est en vaisseau car on est sur tore.carte !!!\n");                         
        EnVaisseau = true;
      }
      else {
        EnVaisseau = false;
        //  Camera.InitCamera();
      }
        
      Map = new CMap(zt -> destination_carte, EnVaisseau);
      Hero -> SetPosition(zt -> destination_position);
      Hero -> SetDirection(zt -> destination_direction);
      Hero -> AddForce(0.0f, 0.0f, 200.0f);
      Hero -> ViderOrdresDeplacement();
      
      // ne marche que si le changement de carte s'est effectué en dehors d'un script :)
      RaiseEvenement(EVT_ChargementCarte);
    }

#if 1
    glEnable2D(); {
      glDisable(GL_TEXTURE_2D);
      glColor4f(r,v,b, 1.0f-((float) (anim - NB_ANIM2_TELEPORTATION)) / (float) NB_ANIM2_TELEPORTATION);
      BEGIN_RECTANGLE_END(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    } glDisable2D();
#endif
  }
  
  else if (anim < NB_ANIM2_TELEPORTATION) {
#if 1
    glEnable2D(); {
      glDisable(GL_TEXTURE_2D);
      glColor4f(r,v,b, ((float) (anim)) / (float) NB_ANIM2_TELEPORTATION);
      BEGIN_RECTANGLE_END(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    } glDisable2D();
#endif
  }

  
  printf("ANIM du moteur de téléportation = %i\n", anim);
}

