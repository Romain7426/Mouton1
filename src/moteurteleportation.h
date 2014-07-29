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
  // on commence une t�l�portation
  
  bool IsTeleportationEnCours(void) const;
  // pr�cise si le jeu est en train de r�aliser une t�l�portation
  
  void SetCouleurFondu(int in_couleur);
  
  void Life(CMap * &Map, bool &EnVaisseau, CBonhomme * &Hero, bool &SCRIPT_SystemeRendMainAuScript);
  void Render(CMap * &Map, bool &EnVaisseau, CBonhomme * &Hero) const;
  /*si le jeu ne fait pas de t�l�portation, ==> ne fait rien
    sinon, avance dans la t�l�portation
    (dessine le fondu... � placer en fin de RaiseRender())
    charge la nouvelle carte
    puis fondu inverse
  */

  
};






#endif
