#include "global.h"
#include "script_api.h"
#include "002_kernel.h"
#include "script.h"
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

extern api_contexte_t api_contexte; // RL: Declared in kernel.c // RL: On the long run, should become a local variable. 
 
api_contexte_t * api_contexte__make_r(api_contexte_t * this) { 
  bzero(this, sizeof(*this)); 
  return this; 
}; 

api_contexte_t * api_contexte__make(void) { 
  api_contexte_t * this = (api_contexte_t *) malloc(sizeof(api_contexte_t)); 
  api_contexte__make_r(this); 
  this -> malloced_huh = true; 
  return this; 
}; 

void api_contexte__delete_r(api_contexte_t * this) { 
  bzero(this, sizeof(*this)); 
}; 

void api_contexte__delete(api_contexte_t * this) { 
  const int malloced_huh = this -> malloced_huh; 
  api_contexte__delete_r(this); 
  if (malloced_huh) { free(this); }; 
}; 




// ------------------------------------- 

void SCRIPT_AjouterObjetAnime(const char* qui, const char * filename) { 
  printf("SCRIPT_AjouterObjetAnime(%s, %s)\n", qui, filename); 
  CBonhomme * o = CBonhomme__make(filename); 
  CMap__AjouterObjet_nom((*(api_contexte.Map)), qui, &o -> parent1); 
  Kernel_Script_YieldToKernel(); 
}; 

void SCRIPT_AjouterObjetNonAnime(const char* qui, const char* filename) {
  printf("SCRIPT_AjouterObjetNonAnime(%s, %s)\n", qui, filename);
  CObjNonAnime * o = CObjNonAnime__make(filename);
  CMap__AjouterObjet_nom((*(api_contexte.Map)), qui, &o -> parent);     
};

#if 1 
bool SCRIPT_EstEnTrainDExecuterUnScript(void) {
  //return (*(api_contexte.ModeJeu)) == mjSCRIPT;     
  //return false; 
  //return (*(api_contexte.TypeInstructionCourante)) != Script_Automaton_Idle; 
  //return (*(api_contexte.TypeInstructionCourante)) != Script_Automaton_Idle || (((*(api_contexte.TypeInstructionCourante)) == ticChangerDeCarte) && ((api_contexte.TypeInstructionPrecedente == Script_Automaton_Idle))); 
  if ((*(api_contexte.TypeInstructionCourante)) == Script_Automaton_Idle) { return false; }; 
  if ((*(api_contexte.TypeInstructionCourante)) != ticChangerDeCarte) { return true; }; 
  return api_contexte.TypeInstructionPrecedente != Script_Automaton_Idle; 
}; 
#endif 

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
#if 1 
  assert(false); 
#elif 0 
  //api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  //api_contexte.TypeInstructionPrecedente = ticInstruction; 
  *(api_contexte.TypeInstructionCourante) = ticInstructionScript; 
  *(api_contexte.Kernel_Script_Modal_ref) = Kernel_Script_Modal__ScriptIsMaster; 
#else 
  (*(api_contexte.ModeJeu)) = mjSCRIPT; 
  (*(api_contexte.TypeInstructionCourante)) = ticInstructionScript; 
#endif 
};

void SCRIPT_Quit(void) { 
/*à appeler quand on quitte le script (lors du dernier execute)
 cette procédure rend la main au jeu
 
 appuyer sur "haut" fera de nouveau bouger le héros etc...*/
  //fprintf(stderr, "SCRIPT_Quit\n");
#if 0 
  (*(api_contexte.ModeJeu)) = mjJEU; 
#endif 
}; 


const char * SCRIPT_GetNomCarte(void) {
  if ((*(api_contexte.Map)) == NULL)
    return "";
  else
    return CMap__GetNomCarte((*(api_contexte.Map))); 
};



// informe le jeu que l'on va afficher un message 
void SCRIPT_AfficherMessage(const char * msg) { 
  //fprintf(stderr, "<%s:" STRINGIFY(__LINE__) ">: " "@msg = %p" "\n", __func__, msg); fflush(NULL); 
  
    
  CMessageTexte * MessageTexte = *(api_contexte.MessageTexte_ref); 
  
  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticAfficherMessage;
  MessageTexte -> SetMsg(MessageTexte, msg);
  //(*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false; 
#if 0 
  while (not((*(api_contexte.SCRIPT_SystemeRendMainAuScript))))
    SCRIPT_unepassedeboucle();
#endif 
  (*(api_contexte.TypeInstructionCourante)) = ticAfficherMessage; 
  
  Kernel_Script_YieldToKernel(); 
};




void SCRIPT_Camera_SetPosition(const float x, const float y, const float z, const TMethodePlacement mp) {
  //Camera.pos = ((mp == mpRELATIF) ? Camera.pos : Point3D_make(0.0f, 0.0f, 0.0f))  +  Point3D_make(x, y, z); 

  if (mp == mpRELATIF) { 
    //TPoint3D_add_self_expanded__macro((*(api_contexte.Camera_ref)) -> lattice__target_position, x, y, z); 
    TPoint3D_add_self_expanded__macro(*CCamera__lattice__target_position((*(api_contexte.Camera_ref))), x, y, z); 
  } 
  else { 
    //TPoint3D_assign__macro((*(api_contexte.Camera_ref)) -> lattice__target_position, x, y, z); 
    TPoint3D_assign__macro(*CCamera__lattice__target_position((*(api_contexte.Camera_ref))), x, y, z); 
  }; 
}; 

void SCRIPT_Camera_Init(void) { 
  CCamera * Camera = *(api_contexte.Camera_ref); CCamera__InitCamera(Camera); 
  Kernel_Script_YieldToKernel(); 
}; 

void SCRIPT_Camera_SolidariserAuHeros(void) { 
  CCamera * Camera = *(api_contexte.Camera_ref); CCamera__SolidariserAuHeros(Camera); 
}; 

void SCRIPT_Camera_DeSolidariser(void) { 
  CCamera * Camera = *(api_contexte.Camera_ref); CCamera__DeSolidariser(Camera); 
}; 

void SCRIPT_Camera_Baisser(void) { 
  CCamera * Camera = *(api_contexte.Camera_ref); 
  //Camera -> angleZ += PI/32.0f; 
  *CCamera__angleZ(Camera) += PI/32.0f; 
  Kernel_Script_YieldToKernel(); 
}; 


void SCRIPT_Camera_Rotate(const float degree_angle_x, const float degree_angle_y, const float degree_angle_z, const TMethodePlacement mp) {
#if 0 
  (*(api_contexte.Camera_ref)) -> angleXY = ((mp == mpRELATIF) ? (*(api_contexte.Camera_ref)) -> angleXY : 0.0f) + PI * degree_angle_x / 180.0f;
  //Camera -> angleHB = ((mp == mpRELATIF) ? Camera -> angleHB : 0.0f) + PI * degree_angle_y / 180.0f;
  (*(api_contexte.Camera_ref)) -> angleZ = ((mp == mpRELATIF) ? (*(api_contexte.Camera_ref)) -> angleZ : 0.0f) + PI * degree_angle_y / 180.0f;
#else 
  { 
    CCamera * Camera = *(api_contexte.Camera_ref); 
    const float radian_angle_x = PI * degree_angle_x / 180.0f; 
    const float radian_angle_y = PI * degree_angle_y / 180.0f; 
    if (mp == mpRELATIF) { 
      *CCamera__angleXY(Camera) += radian_angle_x; 
      *CCamera__angleZ (Camera) += radian_angle_y; 
    }
    else { 
      *CCamera__angleXY(Camera) = radian_angle_x; 
      *CCamera__angleZ (Camera) = radian_angle_y; 
    }; 
  }; 
#endif 
};


void SCRIPT_Camera_Zoom(const float zoom_factor) { 
/*zoom = 1.0f : normal
  zoom = 2.0f : on agrandit par 2, la caméra est deux fois plus près
  du point quel regarde */
  //(*(api_contexte.Camera_ref)) -> SetDist((*(api_contexte.Camera_ref)), lattice__dist_defaut / zoom); 
  //(*(api_contexte.Camera_ref)) -> Zoom((*(api_contexte.Camera_ref)), TZoomMethod_Absolu, zoom_factor); 
  CCamera__Zoom((*(api_contexte.Camera_ref)), TZoomMethod_Absolu, zoom_factor); 
  Kernel_Script_YieldToKernel(); 
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
// RL: Beware! The 'add' function is part of 'CMenuAbstrait' but not of 'CMiniMenu'. 
//void SCRIPT_BeginAfficherMenu(void) { 
CMenuAbstrait * SCRIPT_BeginAfficherMenu(void) { 
//CMiniMenu * SCRIPT_BeginAfficherMenu(void) { 
  if (NULL != (*(api_contexte.MiniMenu))) { 
    CMiniMenu_delete((*(api_contexte.MiniMenu))); 
    (*(api_contexte.MiniMenu)) = NULL; 
  }; 
  //(*(api_contexte.MiniMenu)) = CMiniMenu_make(100, 200, 10000); 
  (*(api_contexte.MiniMenu)) = CMiniMenu_make(/*x*/100, /*y*/270, /*w*/10000); 
  (*(api_contexte.MiniMenu)) -> parent.NomSousMenu[0] = strcopy("<DEFAULT>"); 
  (*(api_contexte.MiniMenu)) -> parent.iphi = 0; 
  //(*(api_contexte.TypeInstructionCourante)) = ticMiniMenu;  
  return &(*(api_contexte.MiniMenu)) -> parent; 
  //return (*(api_contexte.MiniMenu)); 
}; 

int SCRIPT_AfficherMenu(const char * msg) { 
  CMessageTexte * MessageTexte = *(api_contexte.MessageTexte_ref); 
#if 0 
  //fprintf(stderr, "%s: " "msg = %s" "\n", __func__, msg); 
  //dprintf(2, "%s: " "msg = %s" "\n", __func__, msg); 
  messerr("%s: " "msg = %s" "\n", __func__, msg); 
#endif 
  // à appeler pour réellement afficher le menu 
  // une fois l'exécution du menu terminé, le jeu "rend la main" au script
  //   ===> on récupère le choix effectué par l'utilisation dans un menu via 
  //        cette fonction 
  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticMiniMenu;
  MessageTexte -> SetMsg(MessageTexte, msg);
  //(*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false;
#if 0
  while (not((*(api_contexte.SCRIPT_SystemeRendMainAuScript))))
    SCRIPT_unepassedeboucle();
#endif
  
  
  Kernel_Script_YieldToKernel(); 
  
  
  return (*(api_contexte.MiniMenu)) -> parent.itheta; // RL: Should be ignored. 
}; 


void SCRIPT_RecevoirUneArme(const char * nom_arme) {
  printf("SCRIPT_RecevoirUneArme(%s)\n", nom_arme);
  //char * filename_icone;
  //filename_icone = (char *) malloc(sizeof(char) * (strlen(nom_arme) + 4 + 1));
  // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
  //char filename_icone[strlen(nom_arme) + 4 + 1];
  enum { filename_icone__bytesize = 1<<10 }; 
  const size_t filename_icone__cstrlen = strlen(nom_arme) + 4; 
  assert(filename_icone__bytesize > filename_icone__cstrlen); 
  char filename_icone[filename_icone__bytesize];
  strcpy(filename_icone, nom_arme);
  strcat(filename_icone, ".png");
  
  //(*(api_contexte.Menu)) -> Add1((*(api_contexte.Menu)), ANNEAU_MENU_ARME, nom_arme, filename_icone);
  //(*(api_contexte.Menu)) -> parent.Add(&(*(api_contexte.Menu)) -> parent, ANNEAU_MENU_ARME, nom_arme, filename_icone);
  (*(api_contexte.Menu_InventaireArmes)) -> parent.Add(&(*(api_contexte.Menu_InventaireArmes)) -> parent, ANNEAU_MENU_ARME, nom_arme, filename_icone);
  
  //free(filename_icone);
}; 

#if 1
void SCRIPT_ChangerDeCarte_vZT(const CZoneTeleportation * pzt) { 
  //CMoteurTeleportation * MoteurTeleportation = *(api_contexte.MoteurTeleportation_ref); 
  CMoteurTeleportation * MoteurTeleportation = api_contexte.MoteurTeleportation; 
  message("SCRIPT_ChangerDeCarte(%s, ...)" "\n", CZoneTeleportation__destination_carte(pzt)); 
  //(*(api_contexte.TypeInstructionCourante)) = ticChangerDeCarte; 
  CMoteurTeleportation__SetCouleurFondu     (MoteurTeleportation, 0); 
  CMoteurTeleportation__DebuterTeleportation(MoteurTeleportation, pzt); 
  
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " *(api_contexte.TypeInstructionPrecedente) = %d "   "\n", __func__, (api_contexte.TypeInstructionPrecedente)); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " *(api_contexte.TypeInstructionCourante) = %d "   "\n", __func__, *(api_contexte.TypeInstructionCourante)); 
#endif 
  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticChangerDeCarte; 
  Kernel_Script_YieldToKernel(); 
};

void SCRIPT_ChangerDeCarte_vXYZ(const char * nom_carte, const float x, const float y, const float z, const TDirection direction) { 
  CZoneTeleportation * zt; 
  TPoint3D nul; TPoint3D_assign__macro(nul, 0, 0, 0); 
  TPoint3D destination_position; TPoint3D_assign__macro(destination_position, x, y, z); 
  zt = CZoneTeleportation_make(/*position*/nul, /*dimension*/nul, /*depart_direction*/0, /*in_destination_carte*/nom_carte, destination_position, direction); 
  SCRIPT_ChangerDeCarte_vZT(zt); 
}; 

void SCRIPT_ChangerDeCarte_vXY(const char * nom_carte, const float x, const float y, const TDirection direction) { 
  SCRIPT_ChangerDeCarte_vXYZ(nom_carte, x, y, 0.0f, direction); 
}; 






#elif 0 
void SCRIPT_ChangerDeCarte_vZT(const struct CZoneTeleportation ZoneTeleportation) { 
  //CMoteurTeleportation * MoteurTeleportation = *(api_contexte.MoteurTeleportation_ref); 
  CMoteurTeleportation * MoteurTeleportation = api_contexte.MoteurTeleportation; 
  message("SCRIPT_ChangerDeCarte(%s, ...)" "\n", ZoneTeleportation.destination_carte); 
  //(*(api_contexte.TypeInstructionCourante)) = ticChangerDeCarte; 
  CMoteurTeleportation__SetCouleurFondu     (MoteurTeleportation, 0); 
  CMoteurTeleportation__DebuterTeleportation(MoteurTeleportation, ZoneTeleportation); 
  
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " *(api_contexte.TypeInstructionPrecedente) = %d "   "\n", __func__, (api_contexte.TypeInstructionPrecedente)); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " *(api_contexte.TypeInstructionCourante) = %d "   "\n", __func__, *(api_contexte.TypeInstructionCourante)); 
#endif 
  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticChangerDeCarte; 
  Kernel_Script_YieldToKernel(); 
};

void SCRIPT_ChangerDeCarte_vXYZ(const char * nom_carte, const float x, const float y, const float z, const TDirection direction) { 
  CZoneTeleportation zt; 
  
  zt.destination_carte = (char *) strcopy(nom_carte);  
  zt.destination_position.x = x;
  zt.destination_position.y = y;
  zt.destination_position.z = z;   
  zt.destination_direction = direction;
  
  SCRIPT_ChangerDeCarte_vZT(zt); 
}; 

void SCRIPT_ChangerDeCarte_vXY(const char * nom_carte, const float x, const float y, const TDirection direction) { 
  SCRIPT_ChangerDeCarte_vXYZ(nom_carte, x, y, 0.0f, direction); 
}; 

void SCRIPT_SetCouleurFondu(const int color) { 
  //CMoteurTeleportation * MoteurTeleportation = *(api_contexte.MoteurTeleportation_ref); 
  CMoteurTeleportation * MoteurTeleportation = api_contexte.MoteurTeleportation; 
  CMoteurTeleportation__SetCouleurFondu(MoteurTeleportation, color);
}; 

void SCRIPT_fondu(void) { 
  //CMoteurTeleportation * MoteurTeleportation = *(api_contexte.MoteurTeleportation_ref); 
  CMoteurTeleportation * MoteurTeleportation = api_contexte.MoteurTeleportation; 
  printf("SCRIPT_fondu\n"); 
  // FS: /*pour faire un fondu, on fait comme si on faisait un changement de carte... mais... on reste au ^m endroit...cela se traduit par destination_carte == NULL*/ 
  CZoneTeleportation zt; 
  zt.destination_carte = NULL; 
  CMoteurTeleportation__DebuterTeleportation(MoteurTeleportation, zt); 
}; 

#else 
void SCRIPT_ChangerDeCarte_vZT(CMoteurTeleportation * MoteurTeleportation, CZoneTeleportation ZoneTeleportation) {
  fprintf(stderr, "SCRIPT_ChangerDeCarte(%s, ...)\n", ZoneTeleportation.destination_carte); 
  
  MoteurTeleportation -> SetCouleurFondu(MoteurTeleportation, 0);  
  MoteurTeleportation -> DebuterTeleportation(MoteurTeleportation, ZoneTeleportation); 

  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticChangerDeCarte; 
  Kernel_Script_YieldToKernel(); 
  
  
  //(*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false;
  
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
  
  //(*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false;
  
#if 0
  while (not(*(api_contexte.SCRIPT_SystemeRendMainAuScript)))
    SCRIPT_unepassedeboucle();
#endif
}; 

#endif 


CPhysicalObj * SCRIPT_RetrouverObjetViaSonNom(const char * qui) { 
  if (0 == strcmp(qui, "heros")) 
    return &(*(api_contexte.Hero)) -> parent1;
  else           
    return CMap__RetrouverObjetViaSonNom((*(api_contexte.Map)), qui);
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
  Kernel_Script_YieldToKernel(); 
}; 

void SCRIPT_SetPosition_vXYZ(const char * qui, const float given_x, const float given_y, const float given_z, const TMethodePlacement mp) { 
  printf("SCRIPT_SetPosition_vXYZ(%s, %f, %f, %f ...)\n", qui, given_x, given_y, given_z); 
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 
  if (mp == mpABSOLU) { 
    o -> SetPosition_vXYZ(o, given_x, given_y, given_z, (*(api_contexte.Map))); 
  } 
  else { 
    const float x = o -> GetPosition_x(o) + given_x; 
    const float y = o -> GetPosition_y(o) + given_y; 
    const float z = o -> GetPosition_z(o) + given_z; 
    o -> SetPosition_vXYZ(o, x, y, z, (*(api_contexte.Map))); 
  }; 
  Kernel_Script_YieldToKernel(); 
}; 

void SCRIPT_SetDirection(const char * qui, TDirection d) { 
  printf("SCRIPT_SetDirection(%s, ...)\n", qui); 
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 
  if (CPhysicalObj_subtype_CBonhomme != o -> subtype) { 
    messerr("ERREUR : L'objet %s n'est pas un bonhomme. Il ne peut s'orienter.\n", qui); 
    return; 
  }; 

  CBonhomme * b = (CBonhomme *) o; 
  b -> SetDirection(b, d);
  Kernel_Script_YieldToKernel(); 
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
  if (CPhysicalObj_subtype_CBonhomme != o -> subtype) { 
    messerr("ERREUR : L'objet %s n'est pas un bonhomme. Il ne peut frapper.\n", qui); 
    return; 
  }; 
  CBonhomme * b = (CBonhomme *) o; 
  b -> Frapper(b);
  
  Kernel_Script_YieldToKernel(); 
}; 
 
void SCRIPT_Deplacer(const char * qui, const float x, const float y, const TMethodePlacement mp) { 
  printf("SCRIPT_Deplacer(%s, %f, %f, ...)\n", qui, x, y); 
  CPhysicalObj * o = SCRIPT_RetrouverObjetViaSonNom(qui); 
  if (NULL == o) { 
    messerr("%s: " "I could not find the object named '%s'." "\n", __func__, qui); 
    return; 
  }; 

  if (CPhysicalObj_subtype_CBonhomme != o -> subtype) { 
    messerr("ERREUR: L'objet %s n'est pas un bonhomme. Il ne peut se déplacer.\n", qui); 
    return; 
  }; 

  CBonhomme * b = (CBonhomme *) o; 
  b -> AjouterOrdresDeplacement_vXY(b, x, y, mp); 
  
  Kernel_Script_YieldToKernel(); 
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
void SCRIPT_Wait(const int nbpasses) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " nbpasses = %d "   "\n", __func__, nbpasses); 
  api_contexte.nbpasses = nbpasses; 
  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticWait; 
  Kernel_Script_YieldToKernel(); 
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
  
  if (CPhysicalObj_subtype_CBonhomme != o -> subtype) { 
    messerr("ERREUR: L'objet %s n'est pas un bonhomme. On ne peut pas l'attendre.\n", qui); 
    return; 
  }; 

  CBonhomme * b = (CBonhomme *) o; 
  api_contexte.b = b;
  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticWaitFor; 

#if 0
    while (b -> IsSoumisADesOrdres())
      //SCRIPT_unepassedeboucle();
      break;
#endif

  Kernel_Script_YieldToKernel(); 
}; 





void SCRIPT_JouerMusique(const char* fichier) {
  printf("SCRIPT_JouerMusique(%s)\n", fichier);
  bool musiqueachanger = false;

  if (fichier == NULL || *fichier == '\0') { 
    if (*(api_contexte.Musique) != NULL) { 
      CMusique_delete((*(api_contexte.Musique)));  
    (*(api_contexte.Musique)) = NULL; 
    }; 
    CMusique__Jouer(NULL); 
    Kernel_Script_YieldToKernel(); 
    return; 
  }; 
  
  if ((*(api_contexte.Musique)) == NULL) musiqueachanger = true;
  else if ((*(api_contexte.Musique))->NomMusique == NULL)
         musiqueachanger = true;
  else if (strcmp((*(api_contexte.Musique))->NomMusique, fichier))
    //si différent il faut charger la musique
    musiqueachanger = true;
  
  if (musiqueachanger) { 
    if (*(api_contexte.Musique) != NULL) { CMusique_delete((*(api_contexte.Musique))); }; 
    (*(api_contexte.Musique)) = CMusique_make(fichier);
    (*(api_contexte.Musique)) -> Jouer((*(api_contexte.Musique)));
  };
  
  Kernel_Script_YieldToKernel(); 
}; 


#if 1 
//void SCRIPT_Readln(CMenuEntreeNom * MenuEntreeNom) {
void SCRIPT_Readln(void) { 
  CMenuEntreeNom * MenuEntreeNom = *(api_contexte.MenuEntreeNom_ref); 
  printf("SCRIPT_Readln\n"); 
    
  MenuEntreeNom -> Init(MenuEntreeNom); 
  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticReadln; 
}; 
#else 
//void SCRIPT_Readln(CMenuEntreeNom * MenuEntreeNom) {
void SCRIPT_Readln(void) { 
  CMenuEntreeNom * MenuEntreeNom = *(api_contexte.MenuEntreeNom_ref); 
  printf("SCRIPT_Readln\n"); 
    
  MenuEntreeNom -> Init(MenuEntreeNom); 
  api_contexte.TypeInstructionPrecedente = *(api_contexte.TypeInstructionCourante); 
  (*(api_contexte.TypeInstructionCourante)) = ticReadln; 
  //(*(api_contexte.SCRIPT_SystemeRendMainAuScript)) = false;
  
#if 0
  while (not(*(api_contexte.SCRIPT_SystemeRendMainAuScript)))
    SCRIPT_unepassedeboucle();  
#endif
         
  //return strcopy(MenuEntreeNom->buffer);
}; 
#endif 









