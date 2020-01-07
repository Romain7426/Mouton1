#ifndef MOTEURTELEPORTATION_H
#define MOTEURTELEPORTATION_H

/****************************************************
   MOTEUR DE TELEPORTATION
******************************************/

struct CMoteurTeleportation {
  CZoneTeleportation * zt;
  int anim;
  float r, v, b;
            
  void (* DebuterTeleportation)(struct CMoteurTeleportation * this, struct CZoneTeleportation in_zt);
  // on commence une t�l�portation
  
  bool (* IsTeleportationEnCours)(const struct CMoteurTeleportation * this);
  // pr�cise si le jeu est en train de r�aliser une t�l�portation
  
  void (* SetCouleurFondu)(struct CMoteurTeleportation * this, int in_couleur);
  
  //void (* Life)(struct CMoteurTeleportation * this, struct CMap * &Map, bool &EnVaisseau, struct CBonhomme * &Hero, bool &SCRIPT_SystemeRendMainAuScript);
  void (* Life)(struct CMoteurTeleportation * this, struct CMap * * Map_ptr, bool * EnVaisseau_ptr, struct CBonhomme * * Hero_ptr, bool * SCRIPT_SystemeRendMainAuScript_ptr);

  //void (* Render)(const struct CMoteurTeleportation * this, struct CMap * &Map, bool &EnVaisseau, struct CBonhomme * &Hero);
  void (* Render)(const struct CMoteurTeleportation * this, struct CMap * * Map_ptr, bool * EnVaisseau_ptr, struct CBonhomme * * Hero_ptr);
  /*si le jeu ne fait pas de t�l�portation, ==> ne fait rien
    sinon, avance dans la t�l�portation
    (dessine le fondu... � placer en fin de RaiseRender())
    charge la nouvelle carte
    puis fondu inverse
  */
};

extern CMoteurTeleportation * CMoteurTeleportation_make(void);
extern void CMoteurTeleportation_delete(CMoteurTeleportation * this);

extern void CMoteurTeleportation__DebuterTeleportation(CMoteurTeleportation * this, CZoneTeleportation in_zt);
extern bool CMoteurTeleportation__IsTeleportationEnCours(const CMoteurTeleportation * this);
extern void CMoteurTeleportation__SetCouleurFondu(CMoteurTeleportation * this, int in_couleur);
extern void CMoteurTeleportation__Life(CMoteurTeleportation * this, CMap * * Map_ptr, bool * EnVaisseau_ptr, CBonhomme * * Hero_ptr, bool * SCRIPT_SystemeRendMainAuScript_ptr);
extern void CMoteurTeleportation__Render(const CMoteurTeleportation * this, CMap * * Map_ptr, bool * EnVaisseau_ptr, CBonhomme * * Hero_ptr);


#endif
