#ifndef MOTEURTELEPORTATION_HPP
#define MOTEURTELEPORTATION_HPP


class CZoneTeleportation;
class CMap;
class CBonhomme;


/****************************************************
   MOTEUR DE TELEPORTATION
******************************************/
class CMoteurTeleportation;



class CMoteurTeleportation {
private:
  CZoneTeleportation * zt;
  int anim;
  float r, v, b;
            
public:
  CMoteurTeleportation(void);
           
  void DebuterTeleportation(CZoneTeleportation in_zt);
  // on commence une téléportation
  
  bool IsTeleportationEnCours(void) const;
  // précise si le jeu est en train de réaliser une téléportation
  
  void SetCouleurFondu(int in_couleur);
  
  void Life(CMap * &Map, bool &EnVaisseau, CBonhomme * &Hero, bool &SCRIPT_SystemeRendMainAuScript);
  void Render(CMap * &Map, bool &EnVaisseau, CBonhomme * &Hero) const;
  /*si le jeu ne fait pas de téléportation, ==> ne fait rien
    sinon, avance dans la téléportation
    (dessine le fondu... à placer en fin de RaiseRender())
    charge la nouvelle carte
    puis fondu inverse
  */

  
};






#endif
