#ifndef APISCRIPT_H
#define APISCRIPT_H

enum TTypeInstructionCourante {
  ticInstructionScript, /*instruction genre if, + etc... géré par le script*/
  ticAfficherMessage, /*instruction affichermessage (la boucle du jeu s'en occupe*/
  ticMiniMenu, /*itou*/
  ticChangerDeCarte,
  ticReadln,
  ticWait,
  ticWaitFor,
  ticNOMBRE
};
TYPEDEF_TYPENAME_WITHOUT_ENUM(TTypeInstructionCourante);

struct api_contexte_t {
  enum TModeJeu * ModeJeu;

  bool * SCRIPT_SystemeRendMainAuScript;
  
  struct CMap * * Map;
  struct CMusique * * Musique;
  
  //struct CMenuAbstrait * * Menu;
  struct CMenu * * Menu;
  struct CBonhomme * * Hero;

  float * Temps;
  float * marche_compression;
  
  enum TTypeInstructionCourante * TypeInstructionCourante;

  //struct CMenuAbstrait * * MiniMenu;
  struct CMiniMenu * * MiniMenu;
  int nbpasses;
  struct CBonhomme * b;
};
extern api_contexte_t * api_contexte_make(void); 




extern void SCRIPT_BloquerTemps(void);
extern void SCRIPT_DebloquerTemps(void);
extern void SCRIPT_Init(void);
extern void SCRIPT_Quit(void);
extern bool SCRIPT_EstEnTrainDExecuterUnScript(void);

extern const char * SCRIPT_GetNomCarte(void);
extern void SCRIPT_AfficherMessage(const char * msg);
extern void SCRIPT_BeginAfficherMenu(void);
//extern CMenuAbstrait* MiniMenu;
extern int SCRIPT_AfficherMenu(const char * msg);
//extern int SCRIPT_GetChoixMenu(void);
extern void SCRIPT_JouerMusique(const char* fichier);
extern void SCRIPT_RecevoirUneArme(const char* nom_arme);
//extern void SCRIPT_ChangerDeCarte(CZoneTeleportation zt);
extern void SCRIPT_ChangerDeCarte_vZT(CMoteurTeleportation * MoteurTeleportation, struct CZoneTeleportation ZoneTeleportation);
extern void SCRIPT_ChangerDeCarte_vXY(CMoteurTeleportation * MoteurTeleportation, const char * nom_carte, float x, float y, TDirection direction);
extern void SCRIPT_ChangerDeCarte_vXYZ(CMoteurTeleportation * MoteurTeleportation, const char * nom_carte, float x, float y, float z, TDirection direction);


extern void SCRIPT_AjouterObjetAnime(const char* qui, const char* filename);
extern void SCRIPT_AjouterObjetNonAnime(const char* qui, const char* filename);

extern void SCRIPT_SetPosition_vTPoint3d(const char* qui, TPoint3D position);
extern void SCRIPT_SetPosition_vExpanded(const char* qui, float x, float y, enum TMethodePlacement mp);
extern void SCRIPT_SetZ(const char* qui, float z, TMethodePlacement mp);
extern void SCRIPT_SetDirection(const char* qui, TDirection d);

extern void SCRIPT_Frapper(const char* qui);
extern void SCRIPT_Deplacer(const char* qui, float x, float y, TMethodePlacement mp);
extern void SCRIPT_SupprimerObjet(const char* qui);

extern void SCRIPT_Wait(int nbpasses);
extern void SCRIPT_WaitFor(const char* qui);
extern void SCRIPT_SetCouleurFondu(struct CMoteurTeleportation * MoteurTeleportation, int color);
extern void SCRIPT_fondu(struct CMoteurTeleportation * MoteurTeleportation);
//extern void SCRIPT_SetCouleurFondu(int color);
//extern void SCRIPT_fondu(void);




/*pour la caméra :*/
extern void SCRIPT_Camera_SetPosition(float x, float y, float z, TMethodePlacement mp);



extern void SCRIPT_Camera_Rotate(float angle_x, float angle_y, float angle_z, TMethodePlacement mp);

extern void SCRIPT_Camera_Zoom(float zoom);
extern void SCRIPT_SetTemps(float t);

//extern const char * SCRIPT_Readln(void);
//extern char * SCRIPT_Readln(CMenuEntreeNom * MenuEntreeNom);
extern void SCRIPT_Readln(struct CMenuEntreeNom * MenuEntreeNom);


extern void EVENEMENT_ChargementCarte(void);

extern void EVENEMENT_PlusDEnnemi(void);

#endif
