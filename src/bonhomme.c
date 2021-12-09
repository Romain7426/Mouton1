#include "global.h"
#include "bonhomme.h"
#include "002_kernel.h"
#include "map.h"
#include "anime.h"
#include "camera.h"
#include <assert.h>


enum { MAX_IND_ANGLE = 10 }; 


// ***************************** PANTIN ***************************** 

#define OPENGL_PIXEL_FACTOR 0.38f 

void DirectionToVecteur(const TDirection d, TPoint3D * vec) {
  switch(d) {
  case DOS          : TPoint3D_assign__macro(*vec,  0.0f,  1.0f,  0.0f); break; 
  case FACE         : TPoint3D_assign__macro(*vec,  0.0f, -1.0f,  0.0f); break; 
  case PROFIL_VERS_G: TPoint3D_assign__macro(*vec, -1.0f,  0.0f,  0.0f); break; 
  case PROFIL_VERS_D: TPoint3D_assign__macro(*vec,  1.0f,  0.0f,  0.0f); break; 
  default: assert(false); 
  }; 
}; 
 
 
CPantin * CPantin__GetPantinFils(CPantin * this, int i) {
  if (this -> Membre[i].Pantin == NULL) { 
    //printf("On va créer un pantin intermédiaire au membre n° %i \n", i); 
    this -> Membre[i].Pantin = CPantin__make(); 
  }; 
  return this -> Membre[i].Pantin; 
}; 



CPantin * CPantin__make_aux(CPantin * this) { 
  //printf("Création du pantin...(pointeur = %p) \n", this); 
  BZERO_THIS(this); 
  this -> NbMembres = 0; 
  for (int i = 0; i < MAX_MEMBRE; i++)
    this -> Membre[i].Pantin = NULL;  
 
  this -> AjouterMembre                = CPantin__AjouterMembre; 
  this -> GetPantinFils                = CPantin__GetPantinFils; 
  this -> SetPantinFils                = CPantin__SetPantinFils; 
  this -> DetruirePantinFils           = CPantin__DetruirePantinFils; 
  this -> SetPantinFilsAuDernierMembre = CPantin__SetPantinFilsAuDernierMembre; 
  this -> SetAngleMembre               = CPantin__SetAngleMembre; 
  this -> GetNbMembres                 = CPantin__GetNbMembres; 
  
  return this; 
};  
 
CPantin * CPantin__make(void) { 
  CPantin * this = (CPantin *) malloc(sizeof(CPantin)); 
  return CPantin__make_aux(this); 
}; 

void CPantin__delete_aux(CPantin * this) { 
  if (this == NULL) return; 
  //printf("Destruction du pantin %p\n", this); 
  for (int i = 0; i < this -> NbMembres; i++) { 
    CTexture_delete(this -> Membre[i].Texture); 
    CPantin__delete(this -> Membre[i].Pantin); 
  }; 
  //printf("    Fin de la destruction du pantin %p\n", this); 
}; 
 
void CPantin__delete(CPantin * this) { 
  CPantin__delete_aux(this); 
  free(this); 
}; 





int CPantin__GetNbMembres(const CPantin * this) {
  return this -> NbMembres;
};

void CPantin__SetPantinFils(CPantin * this, int i, CPantin * pantin) {
  //printf("  On accroche le pantin n° %p au membre n° %i du pantin %p \n", pantin, i, this);  
  if (this -> Membre[i].Pantin != NULL) {
    //printf("    Destruction du pantin du membre n° %i \n", i);   
    CPantin__delete(this -> Membre[i].Pantin); //on supprime au préalable l'éventuel pantin fils       
  };
  this -> Membre[i].Pantin = pantin;     
};      

void CPantin__DetruirePantinFils(CPantin * this, int i) {
  //printf("  On retire le pantin n° %p au membre n° %i du pantin %p \n", this -> Membre[i].Pantin, i, this);
  CPantin__delete(this -> Membre[i].Pantin);
  this -> Membre[i].Pantin = NULL;
}; 

void CPantin__SetPantinFilsAuDernierMembre(CPantin * this, CPantin * pantin) {
  this -> SetPantinFils(this, this -> NbMembres - 1, pantin);
};    



void CPantin__SetAngleMembre(CPantin * this, int i, float angle) {
  this -> Membre[i].angle = angle;  
}    


int CPantin__AjouterMembre(CPantin * this, const char * fichier_image,
                           const float px, const float py, const float pz,
                           const float tx, const float ty, const float angle)
{
  printf("  Ajout du membre (%s, %f, %f, %f, %f, %f, %f) au pantin %p\n", fichier_image, px, py, pz, tx, ty, angle, this); 
                         
  if (this -> NbMembres >= MAX_MEMBRE) { 
    messerr("ERREUR : Ajout du membre impossible!!!!\n"); 
    return -1; 
  }; 
  
  int i = this -> NbMembres;
  //printf("  (Membre numéro %i)\n", i);   
  // FS: /*ma façon à moi d'ajouter un nouveau membre*/
  this -> NbMembres++;    
    
  /*on remplit les champs...*/
  /* if (px == -1.0f)
     Membre[i].texture = NULL;
     
     else*/
  {
    //this -> Membre[i].resTexture = gestionTexture.prendre(fichier_image);
    this -> Membre[i].Texture  = CTexture_make(fichier_image); 
    this -> Membre[i].taille_x = tx / this -> Membre[i].Texture -> taillex; 
    this -> Membre[i].taille_y = ty / this -> Membre[i].Texture -> tailley; 
  }    
  //printf("arf\n"); 
  this -> Membre[i].px = px*OPENGL_PIXEL_FACTOR;
  this -> Membre[i].py = py*OPENGL_PIXEL_FACTOR;
  this -> Membre[i].pz = pz*OPENGL_PIXEL_FACTOR;
  this -> Membre[i].taille_pixelx = tx;
  this -> Membre[i].taille_pixely = ty;
  //printf("arf2\n"); 
    
  //printf("arf3\n"); 
  this -> Membre[i].angle_max = angle; 
  this -> Membre[i].Pantin    =  NULL; 
    
  //printf("  Fin de l'ajout du membre réussi !!\n"); 
#if 0 
  { 
    FILE * out_stream = stdout; 
    fprintf(out_stream, "AJOUT MEMBRE '%s' À %p { " "\n", fichier_image, this); 
    fprintf(out_stream, "\t" "texture                       = %p" "\n", this -> Membre[i].Texture); 
    fprintf(out_stream, "\t" "px, py, pz                    = %f, %f, %f" "\n", this -> Membre[i].px, this -> Membre[i].py, this -> Membre[i].pz); 
    fprintf(out_stream, "\t" "taille_x x taille_y           = %f x %f" "\n", this -> Membre[i].taille_x, this -> Membre[i].taille_y); 
    fprintf(out_stream, "\t" "taille_pixelx x taille_pixely = %f x %f" "\n", this -> Membre[i].taille_pixelx, this -> Membre[i].taille_pixely); 
    fprintf(out_stream, "\t" "angle, angle_max              = %f, %f " "\n", this -> Membre[i].angle, this -> Membre[i].angle_max); 
    fprintf(out_stream, "}; " "\n"); 
  }; 
#endif 

  return i;
};    






// ***************************** BONHOMME ***************************** 

bool CBonhomme__EstInvisible(const CBonhomme * this) {
  return (this -> invisible_etape > 0);    
};

void CBonhomme__DevenirInvisible(CBonhomme * this, const int nbetape) {
  this -> invisible_etape = nbetape;
};    


void CBonhomme__Frapper(CBonhomme * this) {
  if (this -> Etat == ebFrapper) return;
  this -> Etat = ebFrapper;
  this -> EtapeEtat = 0; 
};    

bool CBonhomme__EnTrainDeFrapper(const CBonhomme * this) {
  return this -> Etat == ebFrapper;
}; 


void CBonhomme__SetDirection(CBonhomme * this, const TDirection NouvelleDirection) {
  this -> Direction = NouvelleDirection; 
}; 

TDirection CBonhomme__GetDirection(const CBonhomme * this) {
  return this -> Direction;
};


#if 1 
void CBonhomme__Avancer(CBonhomme * this, const TDirection Direction, const bool slow_walk_huh) {
  if (this -> Etat != ebPretAMarcher) { return; }; 
  CPhysicalObj * o = &this -> parent1; 
  
//#define force_marche 16.0f 
  const float force_marche = slow_walk_huh ? this -> force_marche * 0.10f : this -> force_marche; 
  switch (Direction) { 
  case DOS          : o -> Acceleration_add_vXYZ(o,                   0.0f,   force_marche, 0.0f); break; 
  case FACE         : o -> Acceleration_add_vXYZ(o,                   0.0f, - force_marche, 0.0f); break; 
  case PROFIL_VERS_G: o -> Acceleration_add_vXYZ(o, - force_marche,                   0.0f, 0.0f); break; 
  case PROFIL_VERS_D: o -> Acceleration_add_vXYZ(o,   force_marche,                   0.0f, 0.0f); break; 
  default: assert(false); 
  }; 
    
  this -> SetDirection(this, Direction); 
}; 
#else 
//void CBonhomme__Avancer(TDirection Direction, float FacteurCompression)
//void CBonhomme__Avancer(CBonhomme * this, const TDirection Direction, const CMap * Map) {
//void CBonhomme__Avancer(CBonhomme * this, const TDirection Direction, const float FacteurCompression) {
void CBonhomme__Avancer(CBonhomme * this, const TDirection Direction, const riemann_t * our_manifold) {
  /*on n'avance pas si on frappe par exemple
    ATTENTION: cela n'empêche pas que le gars soit poussé s'il frappe car
    les poussages se font directement via Acceleration_add_vXYZ
    Avancer n'est appelé que par les commandes*/
  if (this -> Etat != ebPretAMarcher)
    return;
  
  CPhysicalObj * o = &this -> parent1; 

  // RL: 'FacteurCompression' should not be needed here, as his position on the local _*_does not_*_ change with the compression factor. 
#if 1 
  const float FacteurCompression = our_manifold -> FacteurCompression(our_manifold, /*map_j*/0, o -> GetPosition(o).y); 
#else 
  //float FacteurCompression; 
  const float FacteurCompression = Map -> parent.FacteurCompression(&Map -> parent, o -> GetPosition(o).y); 
#endif 

#define force_marche 0.8f 
  switch (Direction) { 
  case DOS          : o -> Acceleration_add_vXYZ(o,                                0.0f,  force_marche, 0.0f); break; 
  case FACE         : o -> Acceleration_add_vXYZ(o,                                0.0f, -force_marche, 0.0f); break; 
  case PROFIL_VERS_G: o -> Acceleration_add_vXYZ(o, - force_marche / FacteurCompression,          0.0f, 0.0f); break; 
  case PROFIL_VERS_D: o -> Acceleration_add_vXYZ(o,   force_marche / FacteurCompression,          0.0f, 0.0f); break; 
  default: assert(false); 
  }; 
    
  this -> SetDirection(this, Direction); 
}; 
#endif 




void CBonhomme__Life(CBonhomme * this) { 
  CPhysicalObj * o = &this -> parent1; 
  CPantin      * p = &this -> pantin; 
  
  o -> Life(o); 
  
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this = '%s' "   "\n", __func__, this -> filename); 

  // FS: on anime le pantin en donnant les angles des membres
  for (int i = 0; i < p -> GetNbMembres(p); i++) {
    p -> SetAngleMembre(p, i, p -> Membre[i].angle_max * this -> iangle / MAX_IND_ANGLE); 
  };

  CPantin * p_arme = p -> GetPantinFils(p, MEMBRE_AVEC_ARME); 
  p_arme -> SetAngleMembre(p_arme, 0, -150); 
    
  if (this -> Etat == ebFrapper) {
#define NB_ETAPE_ETAT 8
    this -> iangle = 0; 
    p -> SetAngleMembre(p, MEMBRE_AVEC_ARME, -220*(2*NB_ETAPE_ETAT - this -> EtapeEtat) / (3*NB_ETAPE_ETAT));
    p_arme -> SetAngleMembre(p_arme, 0, -90*(NB_ETAPE_ETAT - this -> EtapeEtat) / (NB_ETAPE_ETAT)) ;
    this -> EtapeEtat++;
    
    if (this -> EtapeEtat > NB_ETAPE_ETAT) {
      this -> Etat = ebPretAMarcher;
      this -> EtapeEtat = 0;
    }; 
  }; 
    
    
  // FS: clignotement quand on est invisible 
  if (this -> invisible_etape > 0) this -> invisible_etape--; 
  if (this -> invisible_etape % 2 == 1) return; 
  
  this -> iangle += o -> NormeVitesse(o) * this -> sens_iangle*2.0f; 
  if (o -> Immerge_huh) 
    this -> iangle += 1.0f * this -> sens_iangle; //dans l'eau on bouge (on nage) 
  else if (o -> NormeVitesse(o) < 0.1f) 
    this -> iangle = 0; 
  
  if (this -> iangle >= MAX_IND_ANGLE) 
    this -> sens_iangle = -1; 
  
  if (this -> iangle <= -MAX_IND_ANGLE) 
    this -> sens_iangle = 1; 
  
}; 

#if 1 
int CBonhomme__ReadDescriptionFile(CBonhomme * this, const char * anime_datadir, const char * anime_filename) { 
  anime_t anime_data[1]; 
  int     anime_stdlog_d = -1; 
  int     anime_file_d   = -1; 
  goto label__start; 

  assert(false); 

 label__error__exit_fail: { 
    if (0 <= anime_stdlog_d) close(anime_stdlog_d); 
    if (0 <= anime_file_d) close(anime_file_d); 
    return -1; 
  }; 
  
  assert(false); 

label__start: {}; 
  { 
    char anime_fullpath[strlen(anime_datadir) + strlen(anime_filename) + 1];
    strcat(strcpy(anime_fullpath, anime_datadir), anime_filename); 
    dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: INFO: " "Chargement d'un anime décrit par le fichier: %s" "\n", __func__, anime_fullpath); 
    
#define LOG_SUFF ".log"
    char anime_log[strlen(LOGDIR) + strlen(anime_filename) + strlen(LOG_SUFF) + 1];
    strcat(strcat(strcpy(anime_log, LOGDIR), anime_filename), LOG_SUFF);
    dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: INFO: " "Fichier log de l'analyse de ce fichier anime: %s" "\n", __func__, anime_log); 

  label__anime_both_file_and_log__open: 
    
  label__anime_log__open: { 
      anime_stdlog_d = -1; 
      for (;;) { 
	anime_stdlog_d = open(anime_log, O_WRONLY | O_CREAT | O_TRUNC, (mode_t)0666); 
	if (0 <= anime_stdlog_d) break; 
	messerr("ERREUR: Le fichier pour écrire le log de l'analyse de la description de l'objet animé n'a pas pu être ouvert: '%s'" "\n", anime_log); 
	messerr("        Voulez-vous réessayer?" "\n"); 
	{
	  char c; 
	  const int nb_read = read(stdin_d, &c, 1); 
	  if (0 == nb_read) { continue; }; 
	  if (c == 'n') { goto label__error__exit_fail; }; 
	  continue; 
	}; 
	goto label__error__exit_fail; 
      }; 
    }; 
    
  label__anime_file__open: { 
      anime_file_d = -1; 
      for (;;) { 
	anime_file_d = open(anime_fullpath, O_RDONLY); 
	if (0 <= anime_file_d) break; 
	messerr("ERREUR: Le fichier de description de l'objet animé n'a pas pu être ouvert: '%s'" "\n", anime_fullpath); 
	messerr("        Voulez-vous réessayer?" "\n"); 
	{
	  char c; 
	  const int nb_read = read(stdin_d, &c, 1); 
	  if (0 == nb_read) { continue; }; 
	  if (c == 'n') { goto label__error__exit_fail; }; 
	  continue; 
	}; 
	goto label__error__exit_fail; 
      }; 
    }; 
      
    anime__make_r(anime_data, anime_stdlog_d); 

    for(;;) { 
      const int_anime_error_t anime_error_id = anime__fill_from_file(anime_data, anime_filename, anime_file_d, anime_stdlog_d); 
      if (ANIME__OK == anime_error_id) break; 
      if (0 < anime_error_id) { 
	dprintf(fileno(stdout), "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: WARNING: %s: %s" "\n", __func__, anime_filename, int_anime_error__get_cstr(anime_error_id)); 
	break; 
      }; 
      { 
	messerr("ERREUR: Le fichier de description de l'objet animé n'a pas pu être lu et/ou analysé: '%s'" "\n", anime_fullpath); 
	messerr("        ERROR_ID: %s" "\n", int_anime_error__get_cstr(anime_error_id)); 
	messerr("        ERROR_DESC: %s" "\n", anime_data -> error_str); 
	messerr("        Pour plus d'informations, veuillez vous reporter au compte-rendu rendant compte de cette tentative échouée: '%s'" "\n", anime_log); 
	messerr("        Voulez-vous réessayer? (o/n)" "\n"); 
	{
	  char c; 
	  for (;;) { 
	    const ssize_t nb_read = read(stdin_d, &c, 1); 
	    if (0 == nb_read) { continue; }; 
	    if (-1 == nb_read) goto label__error__exit_fail; 
	    break; 
	  }; 
	  if (c == 'n') { goto label__error__exit_fail; }; 
	  close(anime_file_d); anime_file_d = -1; 
	  close(anime_stdlog_d); anime_stdlog_d = -1; 
	  goto label__anime_both_file_and_log__open; 
	};
	assert(false); 
      }; 
      assert(false); 
    }; 
    
    // Success 
    anime__print_d(anime_data, anime_stdlog_d); 
 
    // Closing files. 
    close(anime_file_d); anime_file_d = -1; 
    close(anime_stdlog_d); anime_stdlog_d = -1; 
  }; 
  
  this -> parent1.SetDimension(&this -> parent1, anime_data -> choc_longueur, anime_data -> choc_largeur, anime_data -> choc_hauteur); 
  this -> parent1.masse = anime_data -> masse / 240.0f; 
  if (NULL == this -> parent1.filename) this -> parent1.filename = strcopy(anime_filename);
  this -> parent1.pvmax       = anime_data -> vie; 
  this -> parent1.Hostile_huh = anime_data -> hostile; 
  
  if (NULL == this -> filename) this -> filename = strcopy(anime_filename);
  
  { 
    CObjActionnable * this_action = this -> parent1.actions; 
    for (int i = 0; i < anime_data -> actions_nb; i++) {
      this_action -> AjouterAction(this_action, anime_data -> actions_array_affichage[i], anime_data -> actions_array_icone[i], anime_data -> actions_array_gestionnaire_fichier[i], anime_data -> actions_array_gestionnaire_proc[i]); 
    }; 
  }; 

  { 
    CPantin * this_pantin = &this -> pantin; 
    for (int racine_i = 0; racine_i < anime_data -> racines_nb; racine_i++) { 
      const char  * qui      = anime_data -> racines_qui[racine_i]; 
      const float   x        = anime_data -> racines_x[racine_i]; 
      const float   y        = anime_data -> racines_y[racine_i]; 
      const float   z        = anime_data -> racines_z[racine_i]; 
      const float   angle_y  = anime_data -> racines_angle_y[racine_i]; 
      const int     membre_i = anime__membres_lookup(anime_data, qui); 
      if (0 > membre_i) { 
	messerr(__FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__FUNCTION__) ":" "Impossible de trouver le membre nommé '%s'" "\n", qui); 
	continue; 
      }; 
      const char  * image       = anime_data -> membres_image[membre_i]; 
      const float   largeur     = anime_data -> membres_largeur[membre_i]; 
      const float   hauteur     = anime_data -> membres_hauteur[membre_i]; 
      const float   angle_y_max = anime_data -> membres_angle_max_y[membre_i]; 
      this_pantin -> AjouterMembre(this_pantin, image, x, y, z, largeur, hauteur, angle_y_max); 
    }; 
  };
  
  return 0; 
}; 
#else 
int CBonhomme__ReadDescriptionFile_old001(CBonhomme * this, const char * dir, const char * filename) { 
  anime_t         * anime_data  =  NULL; 
  CObjActionnable * this_action =  this -> parent1.actions; 
  CPantin         * this_pantin = &this -> pantin; 

  { 
    char anime_fullpath[strlen(dir) + strlen(filename) + 1];
    strcat(strcpy(anime_fullpath, dir), filename);
#define LOG_SUFF ".log"
    char anime_log[strlen(LOGDIR) + strlen(filename) + strlen(LOG_SUFF) + 1];
    strcat(strcat(strcpy(anime_log, LOGDIR), filename), LOG_SUFF);
    for(;;) { 
      anime_data = anime__make_from_file(anime_fullpath, anime_log); 
      if (NULL != anime_data) { break; }; 
//      if (NULL == anime_data) { 
      {
	messerr("ERREUR: Le fichier de description de l'objet animé n'a pas pu être lu et/ou analysé: '%s'" "\n", anime_fullpath); 
	messerr("        Pour plus d'information, veuillez vous reporter au compte-rendu rendant compte de cette tentative échouée: '%s'" "\n", anime_log); 
	messerr("        Voulez-vous réessayer?" "\n"); 
	{
	  char c; 
	  const int nb_read = read(stdin_d, &c, 1); 
	  if (0 == nb_read) { continue; }; 
	  if (c == 'n') { return -1; }; 
	  continue; 
	}; 
	return -1; 
      }; 
    }; 
  }; 
  
  this -> parent1.SetDimension(&this -> parent1, anime_data -> choc_longueur, anime_data -> choc_largeur, anime_data -> choc_hauteur); 
  this -> parent1.masse = anime_data -> masse / 240.0f; 
  if (NULL == this -> parent1.filename) this -> parent1.filename = strcopy(filename);
  this -> parent1.pvmax       = anime_data -> vie; 
  this -> parent1.Hostile_huh = anime_data -> hostile; 
  
  if (NULL == this -> filename) this -> filename = strcopy(filename);
  
  for (int i = 0; i < anime_data -> actions_nb; i++) {
    this_action -> AjouterAction(this_action, anime_data -> actions_array_affichage[i], anime_data -> actions_array_icone[i], anime_data -> actions_array_gestionnaire_fichier[i], anime_data -> actions_array_gestionnaire_proc[i]); 
  }; 

  for (int racine_i = 0; racine_i < anime_data -> racines_nb; racine_i++) { 
    const char  * qui      = anime_data -> racines_qui[racine_i]; 
    const float   x        = anime_data -> racines_x[racine_i]; 
    const float   y        = anime_data -> racines_y[racine_i]; 
    const float   z        = anime_data -> racines_z[racine_i]; 
    const float   angle_y  = anime_data -> racines_angle_y[racine_i]; 
    const int     membre_i = anime__membres_lookup(anime_data, qui); 
    if (0 > membre_i) { 
      messerr(__FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__FUNCTION__) ":" "Impossible de trouver le membre nommé '%s'" "\n", qui); 
      continue; 
    }; 
    const char  * image       = anime_data -> membres_image[membre_i]; 
    const float   largeur     = anime_data -> membres_largeur[membre_i]; 
    const float   hauteur     = anime_data -> membres_hauteur[membre_i]; 
    const float   angle_y_max = anime_data -> membres_angle_max_y[membre_i]; 
    this_pantin -> AjouterMembre(this_pantin, image, x, y, z, largeur, hauteur, angle_y_max); 
  }; 
  
  anime__delete(anime_data); 
  
  return 0; 
}; 
#endif 

CBonhomme * CBonhomme__make(const char * filename) {
  //fprintf(stderr, "Bonhomme: Constructeur: %s - pv = %d\n", filename, pv);
  CBonhomme * this = (CBonhomme *) malloc(sizeof(CBonhomme)); 
  bzero(this, sizeof(*this)); 
  CPhysicalObj * o = &this -> parent1; 
  CPhysicalObj__make_aux(o, CPhysicalObj_subtype_CBonhomme, filename); 
 
  CPantin * p = &this -> pantin; 
  CPantin__make_aux(p); 

  this -> make = CBonhomme__make; 
  this -> delete = CBonhomme__delete; 
  this -> TexCoord = CBonhomme__TexCoord; 
  this -> AfficherPantin = CBonhomme__AfficherPantin; 
  this -> SetDirection = CBonhomme__SetDirection; 
  this -> GetDirection = CBonhomme__GetDirection; 
  this -> Life = CBonhomme__Life;
  this -> Render = CBonhomme__Render;
  this -> Frapper = CBonhomme__Frapper;
  this -> EnTrainDeFrapper = CBonhomme__EnTrainDeFrapper;
  this -> EstInvisible = CBonhomme__EstInvisible;
  this -> DevenirInvisible = CBonhomme__DevenirInvisible;
  this -> Avancer = CBonhomme__Avancer;
  this -> AjouterOrdresDeplacement_vP  = CBonhomme__AjouterOrdresDeplacement_vP;
  this -> AjouterOrdresDeplacement_vXY = CBonhomme__AjouterOrdresDeplacement_vXY;
  this -> TraiterOrdresDeplacement     = CBonhomme__TraiterOrdresDeplacement;
  this -> ViderOrdresDeplacement       = CBonhomme__ViderOrdresDeplacement;
  this -> IsSoumisADesOrdres           = CBonhomme__IsSoumisADesOrdres;

  this -> iangle = 0; 
  this -> sens_iangle = 1; 
  this -> Direction = PROFIL_VERS_D; 
  this -> Etat = ebPretAMarcher; 
  this -> EtapeEtat = 0; 
  this -> invisible_etape = 0; 
  this -> filename = strcopy(filename); 
    
  o -> Compressible_huh = false;
  o -> Fixe_huh = false;
  o -> Hostile_huh = true;

  this -> force_marche = 1.25f; 

  this -> od_nb = 0; 
  this -> od_head = 0;  
  this -> od_tail = 0; 
  
  this -> ViderOrdresDeplacement(this);


  
  //printf("Création d'un petit bonhomme...\n"); 
  
  
  
  
  if (filename == NULL) return this;
  
  this -> filename = strcopy(filename); 
  
  //int ret = LireAnime(ANIMESDIR, filename, this);
  const int ret = CBonhomme__ReadDescriptionFile(this, ANIMESDIR, filename); 
  
  if (0 == ret) {
    printf("ANIME: Lecture réussie du fichier " ANIMESDIR "%s !\n", filename);
  }
  else {
    messerr("ANIME: Lecture avec erreur du fichier " ANIMESDIR "%s .\n", filename);
    assert(false);
  };
  
  //fprintf(stderr, "Bonhomme: Constructeur: %s - pv = %d\n", filename, pv);
 
  return this; 
}; 





void CBonhomme__delete(CBonhomme * this) {
  //printf("Destruction du bonhomme (CBonhomme__~CBonhomme() ) %p\n", this); 
  if (this -> filename != NULL) { free(this -> filename); }; 
  CPantin__delete_aux(&this -> pantin); 
  CPhysicalObj__delete_aux(&this -> parent1); 
  free(this); 
};


void CBonhomme__TexCoord(const CBonhomme * this, const int i, const float tx, const float ty, const CCamera * Camera) { 
  const TDirection direction_affichee = ConvertirDirectionAvecVue2(this -> Direction, Camera); 

  const CPantin * p = &this -> pantin; 

  if (PROFIL_VERS_G == direction_affichee) 
    glTexCoord2f(PROFIL_VERS_D      * p -> Membre[i].taille_x + (1-tx) * p -> Membre[i].taille_x, ty * p -> Membre[i].taille_y); 
  else 
    glTexCoord2f(direction_affichee * p -> Membre[i].taille_x +    tx  * p -> Membre[i].taille_x, ty * p -> Membre[i].taille_y); 
}; 



void CBonhomme__AfficherPantin(const CBonhomme * this, const CPantin * pantin, const int lattice_width, const int lattice_height, const CCamera * Camera) {
  if (pantin == NULL) return; 
  
  // RL: TODO XXX FIXME: lattice_width & lattice_height issues here. // RL: Actually, seems like we do not. 
  
  //printf("Affichage du pantin n° %i \n", pantin); 

#if 0 
  //fprintf(stderr, "HERE\n");
  if (0 == strcmp(this -> filename, "sang.anime")) { 
    static int count = 0; 
    const CPhysicalObj * o = &this -> parent1; 
    fprintf(stderr, "Bonhomme: AfficherPantin: %s - count = %d""\n", this -> filename, count);
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sang_o[%p].x,y,z = %f,%f,%f [%f,%f,%f] "  "\n", __func__, o, o -> np.x, o -> np.y, o -> np.z, o -> d.x, o -> d.y, o -> d.z); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sang_o[%p].x,y,z = %f,%f,%f [%f,%f,%f] "  "\n", __func__, o, o -> p.x, o -> p.y, o -> p.z, o -> d.x, o -> d.y, o -> d.z); 
    fflush(NULL);
    count++; 
  }; 
#endif

  
  // FS: /*le gars regarde dans la direction x*/ 
  for (int i = 0; i < pantin -> GetNbMembres(pantin); i++) { 
    //printf("Affichage du membre n° %i\n", i); 
    const float a = pantin -> Membre[i].angle; 
    pantin -> Membre[i].Texture -> GLTextureCourante(pantin -> Membre[i].Texture);  
    glPushMatrix(); { 
#if 1 
      const TDirection direction_affichee = ConvertirDirectionAvecVue2(this -> Direction, Camera); 
      
      if ((direction_affichee == PROFIL_VERS_G) || (direction_affichee == PROFIL_VERS_D)) 
	glTranslatef(pantin -> Membre[i].px, pantin -> Membre[i].py * 0.05f, pantin -> Membre[i].pz); 
      else 
	glTranslatef(pantin -> Membre[i].px, pantin -> Membre[i].py, pantin -> Membre[i].pz); 
#else 
      const TDirection direction_affichee = FACE;//ConvertirDirectionAvecVue2(this -> Direction, Camera); 
      glTranslatef(pantin -> Membre[i].px, pantin -> Membre[i].py, pantin -> Membre[i].pz); 
#endif 
      
      glRotatef(a, 0.0f, 1.0f, 0.0f); 
      
#define TX pantin -> Membre[i].taille_pixelx * OPENGL_PIXEL_FACTOR
#define TY pantin -> Membre[i].taille_pixely * OPENGL_PIXEL_FACTOR
      
      glBegin(GL_QUADS); do { 
	if (direction_affichee == PROFIL_VERS_D) { 
	  this -> TexCoord(this, i, 0.0f, 0.0f, Camera);    glVertex3f(-TX, 0.0f, 0.0f); 
	  this -> TexCoord(this, i, 1.0f, 0.0f, Camera);    glVertex3f( TX, 0.0f, 0.0f); 
	  this -> TexCoord(this, i, 1.0f, 1.0f, Camera);    glVertex3f( TX, 0.0f, -TY); 
	  this -> TexCoord(this, i, 0.0f, 1.0f, Camera);    glVertex3f(-TX, 0.0f, -TY); 
	  break; 
	};
	if (direction_affichee == PROFIL_VERS_G) { 
	  this -> TexCoord(this, i, 0.0f, 0.0f, Camera);    glVertex3f( TX, 0.0f, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 0.0f, Camera);    glVertex3f(-TX, 0.0f, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 1.0f, Camera);    glVertex3f(-TX, 0.0f, -TY);
	  this -> TexCoord(this, i, 0.0f, 1.0f, Camera);    glVertex3f( TX, 0.0f, -TY);
	  break; 
	};
	if (direction_affichee == FACE) { 
	  this -> TexCoord(this, i, 0.0f, 0.0f, Camera);    glVertex3f(0.0f, -TX, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 0.0f, Camera);    glVertex3f(0.0f,  TX, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 1.0f, Camera);    glVertex3f(0.0f,  TX, -TY);
	  this -> TexCoord(this, i, 0.0f, 1.0f, Camera);    glVertex3f(0.0f, -TX, -TY);
	  break; 
	};
	if (direction_affichee == DOS) { 
	  this -> TexCoord(this, i, 0.0f, 0.0f, Camera);    glVertex3f(0.0f,  TX, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 0.0f, Camera);    glVertex3f(0.0f, -TX, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 1.0f, Camera);    glVertex3f(0.0f, -TX, -TY);
	  this -> TexCoord(this, i, 0.0f, 1.0f, Camera);    glVertex3f(0.0f,  TX, -TY);
	  break; 
	}; 
      } while (false); glEnd(); 
      
      // RL: Without that line, the sword is not displayed. 
      this -> AfficherPantin(this, pantin -> Membre[i].Pantin, lattice_width, lattice_height, Camera); 
      
    } glPopMatrix(); 
  }; 
}; 




//void CBonhomme__Render(const CBonhomme * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold, const CCamera * Camera) { 
void CBonhomme__Render(const CBonhomme * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold, const CCamera * Camera) { 
  
  if (this -> invisible_etape % 2 == 1) return; 
  
#if 0
  //fprintf(stderr, "HERE\n"); 
  if (0 != strcmp(filename, "./heros.anime")) {
    fprintf(stderr, "Bonhomme: Rendering: %s\n", filename);
    fflush(NULL);
  }
#endif
  const CPhysicalObj * o = &this -> parent1; 
  const CPantin      * p = &this -> pantin; 
#if 0 
  //fprintf(stderr, "HERE\n");
  if (0 == strcmp(this -> filename, "sang.anime")) { 
    static int count = 0; 
    fprintf(stderr, "Bonhomme: Rendering: %s - count = %d""\n", this -> filename, count);
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sang_o[%p].x,y,z = %f,%f,%f [%f,%f,%f] "  "\n", __func__, o, o -> np.x, o -> np.y, o -> np.z, o -> d.x, o -> d.y, o -> d.z); 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " sang_o[%p].x,y,z = %f,%f,%f [%f,%f,%f] V[%f,%f,%f] A[%f,%f,%f]"  "\n", __func__, o, o -> p.x, o -> p.y, o -> p.z, o -> d.x, o -> d.y, o -> d.z, o -> v.x, o -> v.y, o -> v.z, o -> a.x, o -> a.y, o -> a.z); 
    fflush(NULL);
    count++; 
  }; 
#endif 
  //o -> Render(o, lattice_width, lattice_height, our_manifold); 
  o -> Render(o, lattice_to_map_scale_factor__x, lattice_to_map_scale_factor__y, lattice_to_map_scale_factor__z, our_manifold); 
  
  
  glEnable(GL_TEXTURE_2D); 
  glDisable(GL_CULL_FACE); { 
    
    glPushMatrix(); { 
#if 1 
      // RL: This is a change of origin and a change of the tangent vector basis: local coordinates. 
      our_manifold -> MatricePour2D(our_manifold, /*map_i*/0, /*map_j*/0, o -> p.x * lattice_to_map_scale_factor__x, o -> p.y * lattice_to_map_scale_factor__y, o -> p.z  * lattice_to_map_scale_factor__z); 


      glScalef(lattice_to_map_scale_factor__x, lattice_to_map_scale_factor__y, lattice_to_map_scale_factor__z); 
      glScalef(0.05f, 0.05f, 0.05f); // RL: Constant factor. Figured out of the blue. 
#if 0 
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f); 
  glBegin(GL_LINES); { 
    for (int xx = 0; xx <= 1; xx++) { 
      for (int yy = 0; yy <= 1; yy++) { 
        for (int zz = 0; zz <= 1; zz++) { 
          glVertex3f(-0.5f          , -0.5f + yy*1.0f, 0.0f + zz*1.0f); 
          glVertex3f(-0.5f +    1.0f, -0.5f + yy*1.0f, 0.0f + zz*1.0f); 
	  
          glVertex3f(-0.5f + xx*1.0f, -0.5f          , 0.0f + zz*1.0f); 
          glVertex3f(-0.5f + xx*1.0f, -0.5f +    1.0f, 0.0f + zz*1.0f); 
	  
          glVertex3f(-0.5f + xx*1.0f, -0.5f + yy*1.0f, 0.0f          ); 
          glVertex3f(-0.5f + xx*1.0f, -0.5f + yy*1.0f, 0.0f +    1.0f); 
        }; 
      }; 
    }; 
  } glEnd(); 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
#endif 



#else 
      //Map -> MatricePour2D(Map, o -> p.x, o-> p.y, o -> p.z); 
      our_manifold -> MatricePour2D(our_manifold, /*map_i*/0, /*map_j*/0, o -> p.x / (float) lattice_width, o -> p.y / (float) lattice_height, o -> p.z); 
      //glRotatef(90.0f*Direction + 90.0f*((int) (2.0f * (Camera.angleXY - PI/4.0f) / PI)), 0.0f, 0.0f, 1.0f); 
      const float lattice_depth = (lattice_width + lattice_height) / 2.0f; 
      glScalef(1.0f / lattice_width, 1.0f / lattice_height, 1.0f / lattice_depth); 
      glScalef(0.05f, 0.05f, 40.0f); // RL: Constant factor. Figured out of the blue. 
#endif 


      
      
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    this -> Direction = %d"  "\n", __func__, this -> Direction); 
      glRotatef(90.0f * ((float)this -> Direction - 1.0f), 0.0f, 0.0f, 1.0f); 
      //glRotatef(90.0f * (this -> Direction - 0), 0.0f, 0.0f, 1.0f); 
      
      //this -> AfficherPantin(this, p, lattice_width, lattice_height, Camera); 
      this -> AfficherPantin(this, p, /*lattice_width*/0, /*lattice_height*/0, Camera); 
      
    } glPopMatrix(); 
    
  } glEnable(GL_CULL_FACE); 
  
}; 









COrdreDeplacement * CBonhomme__OrdreDeplacement_make(CBonhomme * this) {
  assert(this -> od_nb < CBonhomme_COrdreDeplacement_Liste_Size); 
  if (this -> od_tail == CBonhomme_COrdreDeplacement_Liste_Size) { 
    this -> od_tail = 0; 
  }; 
  COrdreDeplacement * od = this -> od_array + this -> od_tail; 
  this -> od_tail++; 
  this -> od_nb++; 
  return od; 
}; 

void CBonhomme__OrdreDeplacement_clear(CBonhomme * this) { 
  this -> od_nb   = 0; 
  this -> od_head = 0; 
  this -> od_tail = 0; 
}; 

COrdreDeplacement * CBonhomme__OrdreDeplacement_head(CBonhomme * this) {
  if (0 == this -> od_nb) return NULL; 
  //COrdreDeplacement * od = this -> od_array + this -> od_tail; 
  COrdreDeplacement * od = this -> od_array + this -> od_head; 
  return od; 
}; 

void CBonhomme__OrdreDeplacement_drop(CBonhomme * this) { 
  assert(this -> od_nb > 0); 
  this -> od_nb--; 
  this -> od_head++; 
  if (this -> od_head == CBonhomme_COrdreDeplacement_Liste_Size) { 
    this -> od_head = 0; 
  }; 
}; 


void CBonhomme__ViderOrdresDeplacement(CBonhomme * this) {
  CBonhomme__OrdreDeplacement_clear(this); 
};


void CBonhomme__AjouterOrdresDeplacement_vP(CBonhomme * this, const TPoint3D pos) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> this = %p - pos.x = %f - pos.y = %f "   "\n", __func__, this, pos.x, pos.y); 
  //printf("CBonhomme__AjouterOrdresDeplacement(TPoint3D pos)\n"); 
  //printf("On ajoute un ordre de déplacement au bonhomme %p vers le point (%f, %f, %f).\n", this, pos.x, pos.y, pos.z); 
  
#define epsilon 0.2f 
  const CPhysicalObj * o = &this -> parent1; 
  
  
  if (fabsf(o -> p.x - pos.x) > epsilon) { 
    COrdreDeplacement * od = CBonhomme__OrdreDeplacement_make(this);
    od -> destination = pos; 
    if (o -> p.x  < pos.x) 
      od -> direction =  PROFIL_VERS_D; 
    else 
      od -> direction =  PROFIL_VERS_G; 
    
    //printf("    minidéplacement de direction %i\n", od -> direction); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " ---- this = %p - destination.x = %f - destination.y = %f  "   "\n", __func__, this, od -> destination.x, od -> destination.y); 
  }; 
   
  if (fabs(o -> p.y - pos.y) > epsilon) {
    COrdreDeplacement * od = CBonhomme__OrdreDeplacement_make(this);
    od -> destination = pos;
    if (o -> p.y < pos.y)
      od -> direction =  DOS;
    else
      od -> direction =  FACE;     
    
    //printf("    puis minidéplacement de direction %i\n", od -> direction);
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " ---- this = %p - destination.x = %f - destination.y = %f  "   "\n", __func__, this, od -> destination.x, od -> destination.y); 
  }; 
  
  
  // rem: on s'en fout de pos.z…
};


void CBonhomme__AjouterOrdresDeplacement_vXY(CBonhomme * this, const float x, const float y, const TMethodePlacement mp) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> this = %p - x = %f - y = %f - mp = %d "   "\n", __func__, this, x, y, (int) mp); 
  TPoint3D pos; 
   
  if (mp == mpABSOLU) {
    pos.x = x; pos.y = y;
  }
  else {
    pos = this -> parent1.GetPosition(&this -> parent1); 
    pos.x += x; pos.y += y;
  }; 
       
  this -> AjouterOrdresDeplacement_vP(this, pos);
};


void CBonhomme__TraiterOrdresDeplacement(CBonhomme * this, const CMap * Map, const bool MoteurPhysiqueActif) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> this = %p - Map = %p - MoteurPhysiqueActif = %s "   "\n", __func__, this, Map, MoteurPhysiqueActif ? "TRUE":"FALSE"); 
  COrdreDeplacement * od = CBonhomme__OrdreDeplacement_head(this); 
  if (od == NULL) { return; }; 
  //printf("ordre de déplacement qu'on traite : %p (%i) \n", od, od -> direction); 
  
  
  CPhysicalObj * o = &this -> parent1; 
  
#define epsilon 0.2f 
  bool arrived_huh;
  
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> this = '%s' - Map = %p - MoteurPhysiqueActif = %s - od -> destination.x = %f - o -> p.x = %f - od -> destination.y = %f - o -> p.y = %f -  "   "\n", __func__, this -> filename, Map, MoteurPhysiqueActif ? "TRUE":"FALSE", od -> destination.x, o -> p.x, od -> destination.y, o -> p.y) ; 
  
  switch (od -> direction) {
  case DOS          : case FACE         : arrived_huh = fabsf(od -> destination.y - o -> p.y) < epsilon; break; 
  case PROFIL_VERS_G: case PROFIL_VERS_D: arrived_huh = fabsf(od -> destination.x - o -> p.x) < epsilon; break; 
  default: arrived_huh = true; assert(false); break; 
  }; 

  if (arrived_huh) { 
    //printf("C'est bon le bonhomme %p arrête le mini-déplacement vers %i.\n", this, od -> direction); 
    CBonhomme__OrdreDeplacement_drop(this); 
    return; 
  }; 
  
#if 0 
  o -> InitForce(o); 
  o -> CoeffFrottementFluide  = 1.0f; 
  o -> CoeffFrottementFluideZ = 0.0f; 
#endif 
  
  this -> Avancer(this, od -> direction, /*slow_walk_huh*/true); 
  
#if 0 
  o -> CalcNewPosition(o); 
  o -> TesterSol(o, &Map -> parent); 
  o -> ValiderPosition(o, MoteurPhysiqueActif); 
  o -> InitForce(o); 
#endif 
};




bool CBonhomme__IsSoumisADesOrdres(const CBonhomme * this) { 
  return (0 != this -> od_nb); 
}; 




