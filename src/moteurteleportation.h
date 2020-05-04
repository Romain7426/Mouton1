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

extern CMoteurTeleportation * CMoteurTeleportation__make(void);
extern CMoteurTeleportation * CMoteurTeleportation__make_content(CMoteurTeleportation * this);
extern void CMoteurTeleportation__delete(CMoteurTeleportation * this);
extern void CMoteurTeleportation__delete_content(CMoteurTeleportation * this);

extern void CMoteurTeleportation__DebuterTeleportation(CMoteurTeleportation * this, CZoneTeleportation in_zt);
extern bool CMoteurTeleportation__IsTeleportationEnCours(const CMoteurTeleportation * this);
extern void CMoteurTeleportation__SetCouleurFondu(CMoteurTeleportation * this, int in_couleur);
extern void CMoteurTeleportation__Life(CMoteurTeleportation * this, CMap * * Map_ptr, bool * EnVaisseau_ptr, CBonhomme * * Hero_ptr, bool * SCRIPT_SystemeRendMainAuScript_ptr);
extern void CMoteurTeleportation__Render(const CMoteurTeleportation * this, CMap * * Map_ptr, bool * EnVaisseau_ptr, CBonhomme * * Hero_ptr, const riemann_t * our_manifold);


#endif
