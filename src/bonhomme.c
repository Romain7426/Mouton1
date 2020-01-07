#include "global.h"
#include "bonhomme.h"
#include "main.h"
#include "map.h"
#include "anime.h"
#include "camera.h"
#include <assert.h>



#define FACT_PIXEL_OPENGL 0.38

void DirectionToVecteur(TDirection d, TPoint3D * vec) {
  switch(d) {
  case DOS:   TPoint3D_assign(*vec, 0.0f,  1.0f, 0.0f); break; 
  case FACE:  TPoint3D_assign(*vec, 0.0f, -1.0f, 0.0f); break; 
  case PROFIL_VERS_G:  TPoint3D_assign(*vec, -1.0f, 0.0f, 0.0f); break; 
  case PROFIL_VERS_D:  TPoint3D_assign(*vec,  1.0f, 0.0f, 0.0f); break; 
  default: assert(false);
  }; 
}; 
 
 
CPantin * CPantin__GetPantinFils(CPantin * this, int i) {
  if (this -> Membre[i].Pantin == NULL) {
    printf("On va créer un pantin intermédiaire au membre n° %i \n", i);
    this -> Membre[i].Pantin = CPantin_make();
  }; 
  return this -> Membre[i].Pantin;   
}; 



CPantin * CPantin_make_aux(CPantin * this) {
  printf("Création du pantin...(pointeur = %p) \n", this); 
  this -> NbMembres = 0; 
  for (int i = 0; i < MAX_MEMBRE; i++)
    this -> Membre[i].Pantin = NULL;  
 
  this -> AjouterMembre = CPantin__AjouterMembre; 
  this -> GetPantinFils = CPantin__GetPantinFils; 
  this -> SetPantinFils = CPantin__SetPantinFils; 
  this -> DetruirePantinFils = CPantin__DetruirePantinFils; 
  this -> SetPantinFilsAuDernierMembre = CPantin__SetPantinFilsAuDernierMembre; 
  this -> SetAngleMembre = CPantin__SetAngleMembre; 
  this -> GetNbMembres = CPantin__GetNbMembres; 

  return this; 
};  
 
CPantin * CPantin_make(void) { 
  CPantin * this = (CPantin *) malloc(sizeof(CPantin)); 
  return CPantin_make_aux(this); 
}; 

void CPantin_delete_aux(CPantin * this) {
  printf("Destruction du pantin %p\n", this);                  
  for (int i = 0; i < this -> NbMembres; i++) {
    CTexture_delete(this -> Membre[i].Texture); 
    CPantin_delete(this -> Membre[i].Pantin); 
  }; 
  printf("    Fin de la destruction du pantin %p\n", this);
}; 
 
void CPantin_delete(CPantin * this) {
  CPantin_delete_aux(this); 
  free(this); 
}; 





int CPantin__GetNbMembres(const CPantin * this) {
  return this -> NbMembres;
};

void CPantin__SetPantinFils(CPantin * this, int i, CPantin * pantin) {
  printf("  On accroche le pantin n° %p au membre n° %i du pantin %p \n", pantin, i, this);  
  if (this -> Membre[i].Pantin != NULL) {
    printf("    Destruction du pantin du membre n° %i \n", i);   
    CPantin_delete(this -> Membre[i].Pantin); //on supprime au préalable l'éventuel pantin fils       
  };
  this -> Membre[i].Pantin = pantin;     
};      

void CPantin__DetruirePantinFils(CPantin * this, int i) {
  printf("  On retire le pantin n° %p au membre n° %i du pantin %p \n", this -> Membre[i].Pantin, i, this);
  CPantin_delete(this -> Membre[i].Pantin);
  this -> Membre[i].Pantin = NULL;
}; 

void CPantin__SetPantinFilsAuDernierMembre(CPantin * this, CPantin * pantin) {
  this -> SetPantinFils(this, this -> NbMembres - 1, pantin);
};    



void CPantin__SetAngleMembre(CPantin * this, int i, float angle) {
  this -> Membre[i].angle = angle;  
}    


int CPantin__AjouterMembre(CPantin * this, const char * fichier_image,
                           float px, float py, float pz,
                           float tx, float ty, float angle)
{
  printf("  Ajout du membre (%s, %f, %f, %f, %f, %f, %f) au pantin %p\n", fichier_image,
         px,  py,  pz,
         tx,  ty,  angle, this); 
                         
  if (this -> NbMembres >= MAX_MEMBRE) {
    printf("ERREUR : Ajout du membre impossible!!!!\n");
    return -1;
  }    
    
  int i = this -> NbMembres;
  printf("  (Membre numéro %i)\n", i);   
  /*ma façon à moi d'ajouter un nouveau membre*/
  this -> NbMembres++;    
    
  /*on remplit les champs...*/
  /* if (px == -1.0f)
     Membre[i].texture = NULL;
     
     else*/
  {
    //this -> Membre[i].resTexture = gestionTexture.prendre(fichier_image);
    this -> Membre[i].Texture = CTexture_make(fichier_image);
    this -> Membre[i].taille_x = tx / this -> Membre[i].Texture -> taillex;
    this -> Membre[i].taille_y = ty / this -> Membre[i].Texture -> tailley;
  }    
  printf("arf\n");
  this -> Membre[i].px = px*FACT_PIXEL_OPENGL;
  this -> Membre[i].py = py*FACT_PIXEL_OPENGL;
  this -> Membre[i].pz = pz*FACT_PIXEL_OPENGL;
  this -> Membre[i].taille_pixelx = tx;
  this -> Membre[i].taille_pixely = ty;
  printf("arf2\n");
    
  printf("arf3\n");
  this -> Membre[i].angle_max = angle;
  this -> Membre[i].Pantin = NULL;
    
  printf("  Fin de l'ajout du membre réussi !!\n");

  return i;
};    









int CBonhomme__ReadDescriptionFile(CBonhomme * this, const char * dir, const char * filename) {
  anime_t * anime_data = NULL; 
  CObjActionnable * this_action = &this -> parent1.parent; 
  CPantin * this_pantin = &this -> parent2; 

  { 
    char anime_fullpath[strlen(dir) + strlen(filename) + 1];
    strcat(strcpy(anime_fullpath, dir), filename);
    anime_data = anime_make_from_file(anime_fullpath); 
  }; 
  
  this -> parent1.SetDimension(&this -> parent1, anime_data -> choc_longueur, anime_data -> choc_hauteur, anime_data -> choc_hauteur);
  if (NULL == this -> parent1.filename) this -> parent1.filename = strcopy(filename);
  this -> parent1.pvmax = anime_data -> vie; 
  this -> parent1.Hostile = anime_data -> hostile; 

  if (NULL == this -> filename) this -> filename = strcopy(filename);

  for (int i = 0; i < anime_data -> actions_nb; i++) {
    this_action -> AjouterAction(this_action, anime_data -> actions_array_affichage[i], anime_data -> actions_array_icone[i], anime_data -> actions_array_gestionnaire_fichier[i], anime_data -> actions_array_gestionnaire_proc[i]); 
  };  

  for (int i = 0; i < anime_data -> racines_nb; i++) {
    const char * qui    = anime_data -> racines_qui[i]; 
    const float x       = anime_data -> racines_x[i]; 
    const float y       = anime_data -> racines_y[i]; 
    const float z       = anime_data -> racines_z[i]; 
    const float angle_y = anime_data -> racines_angle_y[i]; 
    const int membre_i  = anime__membres_lookup(anime_data, qui); 
    if (0 > membre_i) { 
      messerr(__FILE__ ": " BIGLIB_STRING(__LINE__) ": " BIGLIB_STRING(__FUNCTION__) ":" "Impossible de trouver le membre nommé '%s'" "\n", qui); 
      continue; 
    }; 
    const char * image      = anime_data -> membres_image[i]; 
    const float largeur     = anime_data -> membres_largeur[i]; 
    const float hauteur     = anime_data -> membres_hauteur[i]; 
    const float angle_y_max = anime_data -> membres_angle_max_y[i]; 
    this_pantin -> AjouterMembre(this_pantin, image, x, y, z, largeur, hauteur, angle_y_max); 
  }; 
  
  anime_delete(anime_data); 
  
  return 0; 
}; 

CBonhomme * CBonhomme_make(const char * filename) {
  //fprintf(stderr, "Bonhomme: Constructeur: %s - pv = %d\n", filename, pv);
  CBonhomme * this = (CBonhomme *) malloc(sizeof(CBonhomme)); 
  bzero(this, sizeof(*this)); 
  CPhysicalObj * o = &this -> parent1; 
  CPhysicalObj_make_aux(o, CPhysicalObj_subtype_CBonhomme, filename); 

  this -> TexCoord = CBonhomme__TexCoord;
  this -> AfficherPantin = CBonhomme__AfficherPantin;
  this -> SetDirection = CBonhomme__SetDirection;
  this -> GetDirection = CBonhomme__GetDirection;
  this -> Render = CBonhomme__Render;
  this -> Frapper = CBonhomme__Frapper;
  this -> EnTrainDeFrapper = CBonhomme__EnTrainDeFrapper;
  this -> EstInvisible = CBonhomme__EstInvisible;
  this -> DevenirInvisible = CBonhomme__DevenirInvisible;
  this -> Avancer = CBonhomme__Avancer;
  this -> AjouterOrdresDeplacement_vP = CBonhomme__AjouterOrdresDeplacement_vP;
  this -> AjouterOrdresDeplacement_vXY = CBonhomme__AjouterOrdresDeplacement_vXY;
  this -> TraiterOrdresDeplacement = CBonhomme__TraiterOrdresDeplacement;
  this -> ViderOrdresDeplacement = CBonhomme__ViderOrdresDeplacement;
  this -> IsSoumisADesOrdres = CBonhomme__IsSoumisADesOrdres;

  this -> iangle = 0; 
  this -> sens_iangle = 1; 
  this -> Direction = PROFIL_VERS_D; 
  this -> Etat = ebPretAMarcher; 
  this -> EtapeEtat = 0; 
  this -> invisible_etape = 0; 
  this -> filename = strcopy(filename); 
    
  o -> Compressible = false;
  o -> Fixe = false;
  o -> Hostile = true;

  this -> od_nb = 0; 
  this -> od_head = 0;  
  this -> od_tail = 0; 

  
  printf("Création d'un petit bonhomme...\n"); 
   
  // si jamais on ne donne pas de nom de fichier, alors on ne charge pas de script
  if (filename == NULL) return this;

  this -> filename = strcopy(filename); 
  
  this -> ViderOrdresDeplacement(this);
  
  //int ret = LireAnime(ANIMESDIR, filename, this);
  int ret = CBonhomme__ReadDescriptionFile(this, ANIMESDIR, filename); 
  
  if (0 == ret) {
    printf("ANIME: Lecture réussie du fichier " ANIMESDIR "%s !\n", filename);
  }
  else {
    printf("ANIME: Lecture avec erreur du fichier " ANIMESDIR "%s .\n", filename);
    assert(false);
  };
  
  //fprintf(stderr, "Bonhomme: Constructeur: %s - pv = %d\n", filename, pv);
 
  return this; 
};





void CBonhomme_delete(CBonhomme * this) {
  printf("Destruction du bonhomme (CBonhomme__~CBonhomme() ) %p\n", this); 
  if (this -> filename != NULL) free(this -> filename); 
  CPhysicalObj_delete_aux(&this -> parent1); 
  free(this); 
};


void CBonhomme__TexCoord(const CBonhomme * this, int i, float tx, float ty) {
  TDirection direction_affichee = ConvertirDirectionAvecVue2(this -> Direction, Camera);

  const CPantin * p = &this -> parent2; 

  if (PROFIL_VERS_G == direction_affichee)
    glTexCoord2f(PROFIL_VERS_D * p -> Membre[i].taille_x + (1-tx) * p -> Membre[i].taille_x, ty * p -> Membre[i].taille_y);

  else
    glTexCoord2f(direction_affichee * p -> Membre[i].taille_x + tx * p -> Membre[i].taille_x, ty * p -> Membre[i].taille_y);
    
}    



void CBonhomme__AfficherPantin(const CBonhomme * this, const CPantin * pantin) {
  if (pantin == NULL) return;
  
  //printf("Affichage du pantin n° %i \n", pantin);
  
  /*le gars regarde dans la direction x*/
  for (int i = 0; i < pantin -> GetNbMembres(pantin); i++) { 
    //printf("Affichage du membre n° %i\n", i);
    float a = pantin -> Membre[i].angle;
    pantin -> Membre[i].Texture -> GLTextureCourante(pantin -> Membre[i].Texture );  
    glPushMatrix(); {
      TDirection direction_affichee = ConvertirDirectionAvecVue2(this -> Direction, Camera); 
      
      if ((direction_affichee == PROFIL_VERS_G) || (direction_affichee == PROFIL_VERS_D))
	glTranslatef(pantin -> Membre[i].px, pantin -> Membre[i].py*0.05f, pantin -> Membre[i].pz);
      else
	glTranslatef(pantin -> Membre[i].px, pantin -> Membre[i].py, pantin -> Membre[i].pz);
      
      glRotatef(a, 0.0f, 1.0f, 0.0f);
      
#define TX pantin -> Membre[i].taille_pixelx*FACT_PIXEL_OPENGL
#define TY pantin -> Membre[i].taille_pixely*FACT_PIXEL_OPENGL
      
      glBegin(GL_QUADS); { 
	if (direction_affichee == PROFIL_VERS_D) {
	  this -> TexCoord(this, i, 0.0f, 0.0f);    glVertex3f(-TX, 0.0f, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 0.0f);    glVertex3f( TX, 0.0f, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 1.0f);    glVertex3f( TX, 0.0f, -TY);
	  this -> TexCoord(this, i, 0.0f, 1.0f);    glVertex3f(-TX, 0.0f, -TY);
	};
	if (direction_affichee == PROFIL_VERS_G) {
	  this -> TexCoord(this, i, 0.0f, 0.0f);    glVertex3f( TX, 0.0f, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 0.0f);    glVertex3f(-TX, 0.0f, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 1.0f);    glVertex3f(-TX, 0.0f, -TY);
	  this -> TexCoord(this, i, 0.0f, 1.0f);    glVertex3f( TX, 0.0f, -TY);
	};
	if (direction_affichee == FACE) {
	  this -> TexCoord(this, i, 0.0f, 0.0f);    glVertex3f(0.0f, -TX, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 0.0f);    glVertex3f(0.0f,  TX, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 1.0f);    glVertex3f(0.0f,  TX, -TY);
	  this -> TexCoord(this, i, 0.0f, 1.0f);    glVertex3f(0.0f, -TX, -TY);
	};
	if (direction_affichee == DOS) {
	  this -> TexCoord(this, i, 0.0f, 0.0f);    glVertex3f(0.0f,  TX, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 0.0f);    glVertex3f(0.0f, -TX, 0.0f);
	  this -> TexCoord(this, i, 1.0f, 1.0f);    glVertex3f(0.0f, -TX, -TY);
	  this -> TexCoord(this, i, 0.0f, 1.0f);    glVertex3f(0.0f,  TX, -TY);
	}; 
      } glEnd(); 
      
      this -> AfficherPantin(this, pantin -> Membre[i].Pantin);
      
    } glPopMatrix(); 
  }; 
}; 



void CBonhomme__Frapper(CBonhomme * this) {
  if (this -> Etat == ebFrapper) return;
  this -> Etat = ebFrapper;
  this -> EtapeEtat = 0; 
};    


bool CBonhomme__EnTrainDeFrapper(const CBonhomme * this) {
  return this -> Etat == ebFrapper;
}    

void CBonhomme__Render(CBonhomme * this, const CSol * Map) {
#if 0
  //fprintf(stderr, "HERE\n");
  if (0 != strcmp(filename, "./heros.anime")) {
    fprintf(stderr, "Bonhomme: Rendering: %s\n", filename);
    fflush(NULL);
  }
#endif
  CPhysicalObj * o = &this -> parent1; 
  CPantin * p = &this -> parent2; 
  
  o -> Render(o, Map);

  glEnable(GL_TEXTURE_2D);
  glDisable(GL_CULL_FACE); {
    // on anime le pantin en donnant les angles des membres
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
    
    // clignotement quand on est invisible
    if (this -> invisible_etape > 0) this -> invisible_etape--;
    if (this -> invisible_etape % 2 == 1) return;
    
    glPushMatrix(); {
      Map -> MatricePour2D(Map, o -> p.x, o-> p.y, o -> p.z);
      glRotatef(90.0f * this -> Direction, 0.0f, 0.0f, 1.0f);
      //glRotatef(90.0f*Direction + 90.0f*((int) (2.0f * (Camera.angleXY - PI/4.0f) / PI)), 0.0f, 0.0f, 1.0f);
      
      this -> AfficherPantin(this, p);
      
    } glPopMatrix();
    
    
    this -> iangle += o -> NormeVitesse(o) * this -> sens_iangle*2.0f;
    if (o -> Immerge)
      this -> iangle += 1.0f * this -> sens_iangle; //dans l'eau on bouge (on nage)
    else if (o -> NormeVitesse(o) < 0.1f)
      this -> iangle = 0;
    
    if (this -> iangle >= MAX_IND_ANGLE)
      this -> sens_iangle = -1;
    
    if (this -> iangle <= -MAX_IND_ANGLE)
      this -> sens_iangle = 1;      
  
  } glEnable(GL_CULL_FACE);  
};    



void CBonhomme__SetDirection(CBonhomme * this, TDirection NouvelleDirection) {
  if ((NouvelleDirection < 0) || (NouvelleDirection > 3))
    printf("ERREUR : Direction spécifiée incorrecte\n");
  else
    this -> Direction = NouvelleDirection;
}; 


TDirection CBonhomme__GetDirection(const CBonhomme * this) {
  return this -> Direction;
};


//void CBonhomme__Avancer(TDirection Direction, float FacteurCompression)
void CBonhomme__Avancer(CBonhomme * this, TDirection Direction, const CMap * Map) {
  /*on n'avance pas si on frappe par exemple
    ATTENTION: cela n'empêche pas que le gars soit poussé s'il frappe car
    les poussages se font directement via AddForce
    Avancer n'est appelé que par les commandes*/
  if (this -> Etat != ebPretAMarcher)
    return;
  
  CPhysicalObj * o = &this -> parent1; 
  float FacteurCompression;
  FacteurCompression = Map -> parent.FacteurCompression(&Map -> parent, o -> GetPosition(o).y);

#define force_marche 0.8f
  switch (Direction) {
  case DOS:  o -> AddForce_vXYZ(o, 0.0f,  force_marche, 0.0f); break;
  case FACE: o -> AddForce_vXYZ(o, 0.0f, -force_marche, 0.0f); break;
  case PROFIL_VERS_G: o -> AddForce_vXYZ(o, - force_marche / FacteurCompression, 0.0f, 0.0f); break;
  case PROFIL_VERS_D: o -> AddForce_vXYZ(o,   force_marche / FacteurCompression, 0.0f, 0.0f); break;
  default: assert(false);
  }
    
  this -> SetDirection(this, Direction);
}




bool CBonhomme__EstInvisible(const CBonhomme * this) {
  return (this -> invisible_etape > 0);    
};

void CBonhomme__DevenirInvisible(CBonhomme * this, int nbetape) {
  this -> invisible_etape = nbetape;
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
  this -> od_nb = 0; 
  this -> od_head = 0;  
  this -> od_tail = 0; 
}; 

COrdreDeplacement * CBonhomme__OrdreDeplacement_head(CBonhomme * this) {
  if (0 == this -> od_nb) return NULL; 
  COrdreDeplacement * od = this -> od_array + this -> od_tail; 
  return od; 
}; 

void CBonhomme__OrdreDeplacement_pop(CBonhomme * this) {
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
  printf("CBonhomme__AjouterOrdresDeplacement(TPoint3D pos)\n");   
  printf("On ajoute un ordre de déplacement au bonhomme %p vers le point (%f, %f, %f).\n", this, pos.x, pos.y, pos.z);

#define epsilon 0.2f
  const CPhysicalObj * o = &this -> parent1; 
  
  if (fabs(o -> p.x - pos.x) > epsilon) {
    COrdreDeplacement * od = CBonhomme__OrdreDeplacement_make(this);
    od -> destination = pos;
    if (o -> p.x  < pos.x)
      od -> direction =  PROFIL_VERS_D;
    else
      od -> direction =  PROFIL_VERS_G;
    
    printf("    minidéplacement de direction %i\n", od -> direction);
  }; 
   
  if (fabs(o -> p.y - pos.y) > epsilon) {
    COrdreDeplacement * od = CBonhomme__OrdreDeplacement_make(this);
    od -> destination = pos;
    if (o -> p.y  < pos.y)
      od -> direction =  DOS;
    else
      od -> direction =  FACE;     
    
    printf("    puis minidéplacement de direction %i\n", od -> direction);
  }; 
  
  // rem: on s'en fout de pos.z…
};


void CBonhomme__AjouterOrdresDeplacement_vXY(CBonhomme * this, const float x, const float y, const TMethodePlacement mp) {
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
  COrdreDeplacement * od = CBonhomme__OrdreDeplacement_head(this); 
    
  if (od) {
    printf("ordre de déplacement qu'on traite : %p (%i) \n", od, od -> direction); 
    
#define epsilon 0.2f
    bool b;
    CPhysicalObj * o = &this -> parent1; 
    
    switch (od -> direction) {
    case DOS: case FACE: b = fabs(od -> destination.y - o -> p.y) < epsilon; break;
    case PROFIL_VERS_G: case PROFIL_VERS_D: b = fabs(od -> destination.x - o -> p.x) < epsilon; break;
    default: b = true; assert(false); // C koi le bon `b' dans ce cas ?
    }
    
    o -> InitForce(o);
    o -> CoeffFrottementFluide = 1.0f; 
    o -> CoeffFrottementFluideZ = 0.0f; 
    
    if (b) {
      printf("C'est bon le bonhomme %p arrête le mini-déplacement vers %i.\n", this, od -> direction); 
      CBonhomme__OrdreDeplacement_pop(this); 
    }
    else {
      this -> Avancer(this, od -> direction, Map); 
    };
    
    
    o -> CalcNewPosition(o); 
    o -> TesterSol(o, &Map -> parent);  
    o -> ValiderPosition(o, MoteurPhysiqueActif);
    o -> InitForce(o);     
  }; 
};




bool CBonhomme__IsSoumisADesOrdres(const CBonhomme * this) {
  return (0 == this -> od_nb); 
};




