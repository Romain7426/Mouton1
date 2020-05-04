#include "global.h"
#include "apiscript.h"
#include "002_kernel.h"
//#include "main.h"
#include "physicalobj.h"
#include "bonhomme.h"
#include "map.h"
#include "menu.h"
#include "text.h"
#include "menu.h"
#include "moteurteleportation.h"
#include "map.h"
#include "son.h"
#include "camera.h"
#include "menuentreenom.h"
#include "objnonanime.h"

/****************************
   API pour le script
   ******************************************************/

api_contexte_t * api_contexte_make(void) {
  api_contexte_t * this = (api_contexte_t *) malloc(sizeof(api_contexte_t)); 
  bzero(this, sizeof(api_contexte_t)); 
  return this; 
}; 

void SCRIPT_AjouterObjetAnime(const char* qui, const char * filename) { 
  printf("SCRIPT_AjouterObjetAnime(%s, %s)\n", qui, filename); 
  CBonhomme * o = CBonhomme__make(filename); 
  (*(api_contexte.Map)) -> AjouterObjet_nom((*(api_contexte.Map)), qui, &o -> parent1); 
}; 

void SCRIPT_AjouterObjetNonAnime(const char* qui, const char* filename) {
  printf("SCRIPT_AjouterObjetNonAnime(%s, %s)\n", qui, filename);
  CObjNonAnime * o = CObjNonAnime__make(filename);
  (*(api_contexte.Map)) -> AjouterObjet_nom((*(api_contexte.Map)), qui, &o -> parent);     
};

bool SCRIPT_EstEnTrainDExecuterUnScript(void) {
  //return (*(api_contexte.ModeJeu)) == mjSCRIPT;     
  return false; 
};

void SCRIPT_SetTemps(const float t) { 
/* 0.0f : il fait jour 
   0.5f : il fait nuit*/
#if 1 
  (*(api_contexte.our_manifold_ref)) -> temps__set(*(api_contexte.our_manifold_ref), t);   
#else 
  (*(api_contexte.Temps)) = 2*PI*t; 
#endif 
}; 

void SCRIPT_BloquerTemps(void) { 
#if 1 
  (*(api_contexte.our_manifold_ref)) -> temps__bloque(*(api_contexte.our_manifold_ref));   
#else 
  (*(api_contexte.marche_compression)) = 0.0f; 
#endif 
}; 

void SCRIPT_DebloquerTemps(void) { 
#if 1 
  (*(api_contexte.our_manifold_ref)) -> temps__debloque(*(api_contexte.our_manifold_ref));   
#else 
  (*(api_contexte.marche_compression)) = marche_compression_defaut; 
#endif 
}; 

void SCRIPT_Init(void) {
/*à appeler quand on commencer à exécuter un script
(lors du premier execute)

 une fois cette procédure appelée le jeu sait qu'il exécute un
 script, les entrées clavier sont redirigé automatiquement vers 
 un défilement de texte, un choix de menu, ou rien...
 défini dans le script*/
#if 0 
  (*(api_contexte.ModeJeu)) = mjSCRIPT; 
  (*(api_contexte.TypeInstructionCourante)) = ticInstructionScript; 
#endif 
};

void SCRIPT_Quit(void) { 
/*à appeler quand on quitte le script (lors du dernier execute)
 cette procédure rend la main au jeu
 
 appuyer sur "haut" fera de nouveau bouger le héros etc...*/
  fprintf(stderr, "SCRIPT_Quit\n");
#if 0 
  (*(api_contexte.ModeJeu)) = mjJEU; 
#endif 
}; 


const char * SCRIPT_GetNomCarte(void) {
  if ((*(api_contexte.Map)) == NULL)
    return "";
  else
    return (*(api_contexte.Map)) -> GetNomCarte((*(api_contexte.Map))); 
};



// informe le jeu que l'on va afficher un message 
void SCRIPT_AfficherMessage(const char * msg) { 
  //fprintf(stderr, "<%s:" STRINGIFY(__LINE__) ">: " "@msg = %p" "\n", __func__, msg); fflush(NULL); 
  
  (*(api_contexte.TypeInstructionCourante)) = ticAfficherMessage;
  MessageTexte -> SetMsg(MessageTexte, msg);
  (*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false; 
#if 0 
  while (not((*(api_contexte.SCRIPT_SystemeRendMainAuScript))))
    SCRIPT_unepassedeboucle();
#endif 
  (*(api_contexte.TypeInstructionCourante)) = ticAfficherMessage;  
};




void SCRIPT_Camera_SetPosition(const float x, const float y, const float z, const TMethodePlacement mp) {
  //Camera.pos = ((mp == mpRELATIF) ? Camera.pos : Point3D_make(0.0f, 0.0f, 0.0f))  +  Point3D_make(x, y, z); 

  if (mp == mpRELATIF) { 
    TPoint3D_add_self_expanded__macro(Camera -> lattice_position, x, y, z); 
  } 
  else { 
    TPoint3D_assign__macro(Camera -> lattice_position, x, y, z); 
  }; 
}; 



void SCRIPT_Camera_Rotate(const float degree_angle_x, const float degree_angle_y, const float degree_angle_z, const TMethodePlacement mp) {
  Camera -> angleXY = ((mp == mpRELATIF) ? Camera -> angleXY : 0.0f) + PI * degree_angle_x / 180.0f;
  //Camera -> angleHB = ((mp == mpRELATIF) ? Camera -> angleHB : 0.0f) + PI * degree_angle_y / 180.0f;
  Camera -> angleZ = ((mp == mpRELATIF) ? Camera -> angleZ : 0.0f) + PI * degree_angle_y / 180.0f;
};


void SCRIPT_Camera_Zoom(const float zoom) { 
/*zoom = 1.0f : normal
  zoom = 2.0f : on agrandit par 2, la caméra est deux fois plus près
  du point quel regarde */
  Camera -> SetDist(Camera, dist_defaut / zoom);   
}; 




/*exemple d'utilisation :
     SCRIPT_BeginAfficherMenu();
     MiniMenu->Add(0, "Bisounours", "bisou.png");
     MiniMenu->Add(0, "Fifi Brindacier", "fifi.png"); 
     :
     :
     SCRIPT_AfficherMenu("Choisis ton héros :");                           
*/
// RL: Why the 'add' function is not part of the apiscript? 
//     It might be the reason that the script is behaving weirdly. 
//     And it's definitely better than global var. 
/*à appelr lors d'un début de menu*/
//void SCRIPT_BeginAfficherMenu(void) { 
CMenuAbstrait * SCRIPT_BeginAfficherMenu(void) { 
  if (NULL != (*(api_contexte.MiniMenu))) { 
    CMiniMenu_delete((*(api_contexte.MiniMenu))); 
    (*(api_contexte.MiniMenu)) = NULL; 
  }; 
  //(*(api_contexte.MiniMenu)) = CMiniMenu_make(100, 200, 10000); 
  (*(api_contexte.MiniMenu)) = CMiniMenu_make(/*x*/100, /*y*/270, /*w*/10000); 
  (*(api_contexte.MiniMenu)) -> parent.NomSousMenu[0] = strcopy("<DEFAULT>"); 
  (*(api_contexte.MiniMenu)) -> parent.iphi = 0; 
  (*(api_contexte.TypeInstructionCourante)) = ticMiniMenu;  
  return &(*(api_contexte.MiniMenu)) -> parent; 
}; 

int SCRIPT_AfficherMenu(const char * msg) { 
#if 0 
  //fprintf(stderr, "%s: " "msg = %s" "\n", __func__, msg); 
  //dprintf(2, "%s: " "msg = %s" "\n", __func__, msg); 
  messerr("%s: " "msg = %s" "\n", __func__, msg); 
#endif 
  // à appeler pour réellement afficher le menu 
  // une fois l'exécution du menu terminé, le jeu "rend la main" au script
  //   ===> on récupère le choix effectué par l'utilisation dans un menu via 
  //        cette fonction 
  (*(api_contexte.TypeInstructionCourante)) = ticMiniMenu;
  MessageTexte -> SetMsg(MessageTexte, msg);
  (*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false;
#if 0
  while (not((*(api_contexte.SCRIPT_SystemeRendMainAuScript))))
    SCRIPT_unepassedeboucle();
#endif
     
  return (*(api_contexte.MiniMenu)) -> parent.itheta; // RL: Should be ignored. 
}; 


void SCRIPT_RecevoirUneArme(const char * nom_arme) {
  printf("SCRIPT_RecevoirUneArme(%s)\n", nom_arme);
  //char * filename_icone;
  //filename_icone = (char *) malloc(sizeof(char) * (strlen(nom_arme) + 4 + 1));
  char filename_icone[strlen(nom_arme) + 4 + 1];
  strcpy(filename_icone, nom_arme);
  strcat(filename_icone, ".png");
  
  //(*(api_contexte.Menu)) -> Add1((*(api_contexte.Menu)), ANNEAU_MENU_ARME, nom_arme, filename_icone);
  (*(api_contexte.Menu)) -> parent.Add(&(*(api_contexte.Menu)) -> parent, ANNEAU_MENU_ARME, nom_arme, filename_icone);
  
  //free(filename_icone);
}; 


void SCRIPT_ChangerDeCarte_vZT(CMoteurTeleportation * MoteurTeleportation, CZoneTeleportation ZoneTeleportation) {
  fprintf(stderr, "SCRIPT_ChangerDeCarte(%s, ...)\n", ZoneTeleportation.destination_carte);
  (*(api_contexte.TypeInstructionCourante)) = ticChangerDeCarte;
  MoteurTeleportation -> SetCouleurFondu(MoteurTeleportation, 0);  
  MoteurTeleportation -> DebuterTeleportation(MoteurTeleportation, ZoneTeleportation);
  
  (*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false;
  
#if 0
  while (not(*(api_contexte.SCRIPT_SystemeRendMainAuScript)))
    SCRIPT_unepassedeboucle();
#endif
}; 

void SCRIPT_ChangerDeCarte_vXYZ(CMoteurTeleportation * MoteurTeleportation, const char * nom_carte, float x, float y, float z, TDirection direction) {
  CZoneTeleportation zt;
  
  zt.destination_carte = (char *) strcopy(nom_carte);  
  zt.destination_position.x = x;
  zt.destination_position.y = y;
  zt.destination_position.z = z;   
  zt.destination_direction = direction;
  
  SCRIPT_ChangerDeCarte_vZT(MoteurTeleportation, zt);
}; 

void SCRIPT_ChangerDeCarte_vXY(CMoteurTeleportation * MoteurTeleportation, const char * nom_carte, float x, float y, TDirection direction) {                        
  SCRIPT_ChangerDeCarte_vXYZ(MoteurTeleportation, nom_carte, x, y, 0.0f, direction);
}; 


CPhysicalObj * SCRIPT_RetrouverObjetViaSonNom(const char * qui) { 
  if (0 == strcmp(qui, "heros")) 
    return &(*(api_contexte.Hero)) -> parent1;
  else           
    return (*(api_contexte.Map)) -> RetrouverObjetViaSonNom((*(api_contexte.Map)), qui);
}; 


void SCRIPT_SetPosition_vP3D(const char * qui, const TPoint3D position) { 
  printf("SCRIPT_SetPosition(%s, une position)\n", qui); 
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 
  o -> SetPosition_vP3D(o, position, (*(api_contexte.Map)));
}; 

void SCRIPT_SetPosition_vXY(const char * qui, const float x, const float y, const TMethodePlacement mp) { 
  printf("SCRIPT_SetPosition(%s, %f, %f, ...)\n", qui, x, y); 
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  };
  o -> SetPosition_vXY(o, x, y, mp, (*(api_contexte.Map)));
}; 

void SCRIPT_SetDirection(const char * qui, TDirection d) { 
  printf("SCRIPT_SetDirection(%s, ...)\n", qui); 
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 
  CBonhomme * b = (CBonhomme *) o; 
  if (CPhysicalObj_subtype_CBonhomme != o -> subtype) { 
    printf("ERREUR : L'objet %s n'est pas un bonhomme. Il ne peut s'orienter.\n", qui); 
  } 
  else
    b -> SetDirection(b, d);
}; 

void SCRIPT_SetZ(const char * qui, float z, TMethodePlacement mp) { 
  printf("SCRIPT_SetZ(%s, ...)\n", qui);
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 
  o -> SetZ(o, z, mp);
}; 
 
void SCRIPT_Frapper(const char* qui) { 
  printf("SCRIPT_Frapper(%s)\n", qui);   
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 
  CBonhomme * b = (CBonhomme *) o; 
  if (CPhysicalObj_subtype_CBonhomme != o -> subtype) { 
    printf("ERREUR : L'objet %s n'est pas un bonhomme. Il ne peut frapper.\n", qui); 
  } 
  else
    b -> Frapper(b);
}; 
 
void SCRIPT_Deplacer(const char * qui, float x, float y, TMethodePlacement mp) { 
  printf("SCRIPT_Deplacer(%s, %f, %f, ...)\n", qui, x, y); 
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 

  CBonhomme * b = (CBonhomme *) o; 
  
  if (CPhysicalObj_subtype_CBonhomme != o -> subtype) { 
    printf("ERREUR : L'objet %s n'est pas un bonhomme. Il ne peut se déplacer.\n", qui); 
  } 
  else
    b -> AjouterOrdresDeplacement_vXY(b, x, y, mp);
}; 

void SCRIPT_SupprimerObjet(const char * qui) { 
  printf("SCRIPT_SupprimerObjet(%s)\n", qui); 
  /* détruire (*(api_contexte.Map))->RetrouverObjetViaSonNom(qui)*/ 
  TPoint3D pos;
  pos.x = 5000.0f;
  pos.y = 5000.0f;
  pos.z = 5000.0f;
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 
  o -> SetPosition_vP3D(o, pos, (*(api_contexte.Map)));
  /*pour l'instant au lieu de le détruire, on l'envoie au paradis :):)*/
}; 


// permet d'attendre nbpasses*5 centisecondes environ
void SCRIPT_Wait(int nbpasses) {
  api_contexte.nbpasses = nbpasses;
  (*(api_contexte.TypeInstructionCourante)) = ticWait;
  return;
  
  
  SDL_Delay(100*nbpasses);
  
  return;
#if 0 
  for (int i = 0; i < nbpasses; i++)
    SCRIPT_unepassedeboucle();     
#endif 
}; 


// attend qu'un objet n'a plus de mouvement
void SCRIPT_WaitFor(const char * qui) {
  printf("SCRIPT_WaitFor(%s)\n", qui);

  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 
  CBonhomme * b = (CBonhomme *) o; 
  
  if (CPhysicalObj_subtype_CBonhomme != o -> subtype) { 
    printf("ERREUR: L'objet %s n'est pas un bonhomme. On ne peut pas l'attendre.\n", qui); 
    return; 
  }; 

  api_contexte.b = b;
  (*(api_contexte.TypeInstructionCourante)) = ticWaitFor;

#if 0
    while (b -> IsSoumisADesOrdres())
      //SCRIPT_unepassedeboucle();
      break;
#endif
}; 


void SCRIPT_SetCouleurFondu(CMoteurTeleportation * MoteurTeleportation, int color) {
  MoteurTeleportation -> SetCouleurFondu(MoteurTeleportation, color);
}; 


void SCRIPT_fondu(CMoteurTeleportation * MoteurTeleportation) {
  printf("SCRIPT_fondu\n");
  
  /*pour faire un fondu, on fait comme si on faisait un changement de carte...
    mais... on reste au ^m endroit...cela se traduit par destination_carte == NULL*/
  CZoneTeleportation zt;
  zt.destination_carte = NULL;
  MoteurTeleportation -> DebuterTeleportation(MoteurTeleportation, zt);
  
  (*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false;
  
#if 0
  while (not(*(api_contexte.SCRIPT_SystemeRendMainAuScript)))
    SCRIPT_unepassedeboucle();
#endif
}; 



void SCRIPT_JouerMusique(const char* fichier) {
  printf("SCRIPT_JouerMusique(%s)\n", fichier);
  bool musiqueachanger = false;
  
  if ((*(api_contexte.Musique)) == NULL) musiqueachanger = true;
  else if ((*(api_contexte.Musique))->NomMusique == NULL)
         musiqueachanger = true;
  else if (strcmp((*(api_contexte.Musique))->NomMusique, fichier))
    //si différent il faut charger la musique
    musiqueachanger = true;
  
  if (musiqueachanger) {
    CMusique_delete((*(api_contexte.Musique))); 
    (*(api_contexte.Musique)) = CMusique_make(fichier);
    (*(api_contexte.Musique)) -> Jouer((*(api_contexte.Musique)));
  };
  
}; 



void SCRIPT_Readln(CMenuEntreeNom * MenuEntreeNom) {
  printf("SCRIPT_Readln\n");
    
  MenuEntreeNom -> Init(MenuEntreeNom);
  (*(api_contexte.TypeInstructionCourante)) = ticReadln;
  (*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false;
  
#if 0
  while (not(*(api_contexte.SCRIPT_SystemeRendMainAuScript)))
    SCRIPT_unepassedeboucle();  
#endif
         
  //return strcopy(MenuEntreeNom->buffer);
}; 










