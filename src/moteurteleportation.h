#ifndef MOTEURTELEPORTATION_H
#define MOTEURTELEPORTATION_H


struct CZoneTeleportation;
struct CMap;
struct CBonhomme;


/****************************************************
   MOTEUR DE TELEPORTATION
******************************************/
struct CMoteurTeleportation;



struct CMoteurTeleportation {
  //private:
  CZoneTeleportation * zt;
  int anim;
  float r, v, b;
            
  //public:
#if 0
  CMoteurTeleportation(void);
#endif
  
  void DebuterTeleportation(struct CMoteurTeleportation * this, struct CZoneTeleportation in_zt);
  // on commence une téléportation
  
  bool IsTeleportationEnCours(const struct CMoteurTeleportation * this);
  // précise si le jeu est en train de réaliser une téléportation
  
  void SetCouleurFondu(struct CMoteurTeleportation * this, int in_couleur);
  
  void Life(struct CMoteurTeleportation * this, struct CMap * &Map, bool &EnVaisseau, struct CBonhomme * &Hero, bool &SCRIPT_SystemeRendMainAuScript);
  void Render(const struct CMoteurTeleportation * this, struct CMap * &Map, bool &EnVaisseau, struct CBonhomme * &Hero);
  /*si le jeu ne fait pas de téléportation, ==> ne fait rien
    sinon, avance dans la téléportation
    (dessine le fondu... à placer en fin de RaiseRender())
    charge la nouvelle carte
    puis fondu inverse
  */
};






#endif
