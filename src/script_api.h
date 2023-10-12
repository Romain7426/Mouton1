#ifndef APISCRIPT_H
#define APISCRIPT_H


struct api_contexte_t { 
  int8_t malloced_huh; 
  
  enum TModeJeu * ModeJeu; 
  
  //bool * SCRIPT_SystemeRendMainAuScript; 
  
  struct CMap * * Map; 
  struct CMusique * * Musique; 
  
  //struct CMenuAbstrait * * Menu; 
  //struct CMenu * * Menu; 
  struct CMenu * * Menu_InventaireArmes; 
  struct CBonhomme * * Hero; 
  
  float * Temps; 
  float * marche_compression; 
  
  enum TTypeInstructionCourante * TypeInstructionCourante; 
  int8_t TypeInstructionPrecedente; 
  int8_t * Kernel_Script_Modal_ref; 

  
  //struct CMenuAbstrait * * MiniMenu; 
  struct CMiniMenu * * MiniMenu; 
  int nbpasses; 
  struct CBonhomme * b; 
  
  //riemann_t * our_manifold; 
  riemann_t * * our_manifold_ref; 
  
  CCamera * * Camera_ref; 
  
  //CMoteurTeleportation * * MoteurTeleportation_ref; 
  CMoteurTeleportation * MoteurTeleportation; 
  
  CMenuEntreeNom * * MenuEntreeNom_ref; 

  bool * EnVaisseau_ref; 

  CText * * Text_ref; 
  CMessageTexte * * MessageTexte_ref; 

}; 
extern api_contexte_t * api_contexte__make_r  (api_contexte_t * api_contexte); 
extern api_contexte_t * api_contexte__make    (void); 
extern void             api_contexte__delete_r(api_contexte_t * api_contexte); 
extern void             api_contexte__delete  (api_contexte_t * api_contexte); 

extern bool SCRIPT_EstEnTrainDExecuterUnScript(void);


extern void SCRIPT_Init(void);
extern void SCRIPT_Quit(void);


extern void SCRIPT_AfficherMessage(const char * msg);

//extern void SCRIPT_BeginAfficherMenu(void); 
//extern CMenuAbstrait* MiniMenu; 
//extern int SCRIPT_GetChoixMenu(void); 
extern CMenuAbstrait * SCRIPT_BeginAfficherMenu(void); 
//extern CMiniMenu * SCRIPT_BeginAfficherMenu(void); 
extern int  SCRIPT_AfficherMenu(const char * msg); 

extern void SCRIPT_Readln(void); 


extern const char * SCRIPT_GetNomCarte(void); 

extern void SCRIPT_BloquerTemps(void);
extern void SCRIPT_DebloquerTemps(void);
extern void SCRIPT_SetTemps(const float t);

extern void SCRIPT_JouerMusique(const char * fichier); 

extern void SCRIPT_AjouterObjetAnime(const char * qui, const char * filename); 
extern void SCRIPT_AjouterObjetNonAnime(const char * qui, const char * filename); 
extern void SCRIPT_SupprimerObjet(const char * qui); 




//extern void SCRIPT_ChangerDeCarte(CZoneTeleportation zt);
#if 1
extern void SCRIPT_ChangerDeCarte_vZT(const CZoneTeleportation * zt);
extern void SCRIPT_ChangerDeCarte_vXY(const char * nom_carte, const float x, const float y, const TDirection direction);
extern void SCRIPT_ChangerDeCarte_vXYZ(const char * nom_carte, const float x, const float y, const float z, const TDirection direction);
extern void SCRIPT_SetCouleurFondu(const int color);
extern void SCRIPT_fondu(void);
#else 
extern void SCRIPT_ChangerDeCarte_vZT(CMoteurTeleportation * MoteurTeleportation, const struct CZoneTeleportation ZoneTeleportation);
extern void SCRIPT_ChangerDeCarte_vXY(CMoteurTeleportation * MoteurTeleportation, const char * nom_carte, const float x, const float y, const TDirection direction);
extern void SCRIPT_ChangerDeCarte_vXYZ(CMoteurTeleportation * MoteurTeleportation, const char * nom_carte, const float x, const float y, const float z, const TDirection direction);
extern void SCRIPT_SetCouleurFondu(struct CMoteurTeleportation * MoteurTeleportation, const int color);
extern void SCRIPT_fondu(struct CMoteurTeleportation * MoteurTeleportation);
#endif 


extern void SCRIPT_SetPosition_vP3D(const char * qui, const TPoint3D position);
extern void SCRIPT_SetPosition_vXY(const char * qui, const float x, const float y, const enum TMethodePlacement mp); 
extern void SCRIPT_SetPosition_vXYZ(const char * qui, const float given_x, const float given_y, const float given_z, const TMethodePlacement mp); 
extern void SCRIPT_SetZ(const char * qui, const float z, const TMethodePlacement mp);
extern void SCRIPT_SetDirection(const char * qui, const TDirection d);

extern void SCRIPT_RecevoirUneArme(const char * nom_arme); 
extern void SCRIPT_Frapper(const char * qui); 

extern void SCRIPT_Deplacer(const char * qui, const float x, const float y, const TMethodePlacement mp); 

extern void SCRIPT_Wait(const int nbpasses);
extern void SCRIPT_WaitFor(const char * qui);

extern void SCRIPT_Camera_SetPosition(const float x, const float y, const float z, const TMethodePlacement mp);
extern void SCRIPT_Camera_Init(void);
extern void SCRIPT_Camera_SolidariserAuHeros(void);
extern void SCRIPT_Camera_DeSolidariser(void);
extern void SCRIPT_Camera_Rotate(const float angle_x, const float angle_y, const float angle_z, const TMethodePlacement mp);
extern void SCRIPT_Camera_Zoom(const float zoom);
extern void SCRIPT_Camera_Baisser(void); 



#endif /* APISCRIPT_H */ 
