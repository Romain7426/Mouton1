#include "global.h"
#include "map.h"
#include "physicalobj.h"
#include "objnonanime.h"
#include "bonhomme.h"
#include "evenement.h"
#include "carte.h"

TDirection DirectionAleatoire(void) {
  return (TDirection) (rand() % 4);
}; 



#ifdef VOISINAGE_IS_TAB
static int  voisinage_nbelt(const CMap * map, int iii);
static void voisinage_ajouter(CMap * map, int iii, CPhysicalObj * o);
static void voisinage_detruire(CMap * map, int iii, int jjj);
#endif


//#define taille_case 5
enum { taille_case = 5 }; // RL: That's for neighborhood management. 
#define nb_voisinage_traitee 3
#define nb_voisinage_traitee_toutproche 1

#if 0 

#define PARCOURS_OBJETS                                         \
  if (Voisinages != NULL)                                       \
    for (int iii = 0; iii < maxindvoisinages; iii++)            \
      for (int jjj = 0; jjj < VOISINAGE_TAILLE; jjj++)          \
        {                                                       \
          CPhysicalObj * o_parcours = Voisinages[iii][jjj];     \
          if (o_parcours == NULL)                               \
            continue;

#elif 0 

#define PARCOURS_OBJETS                                                 \
  if (Voisinages != NULL)                                               \
    for (int iii = 0; iii < maxindvoisinages; iii++)                    \
      for (CAccesseur<CPhysicalObj> a = Voisinages[iii].Objets.ObtenirAcces(); !a.IsFin(); a.AllerSuivant()) \
        {                                                               \
          CPhysicalObj * o_parcours = a.Element();                      \
          if (o_parcours == NULL)                                       \
            continue;

#elif 1
#define PARCOURS_OBJETS                                         \
  for (int iii = 0; iii < VOISINAGE_X_SIZE; iii++)		\
    for (int jjj = 0; jjj < VOISINAGE_Y_SIZE; jjj++)		\
      for (int kkk = 0; kkk < VOISINAGE_SIZE; kkk++)		\
        {                                                       \
  CPhysicalObj * o_parcours = this -> Voisinages_array[iii][jjj][kkk];	\
          if (o_parcours == NULL)                               \
            continue;


#endif


#define PARCOURS_OBJETS_FIN }



#if 0 

#define PARCOURS_ZONESTELEPORTATIONS                                    \
  for (CAccesseur<CZoneTeleportation> a = ZonesTeleportation.ObtenirAcces(); not(a.IsFin()); a.AllerSuivant())
 
#else 

#define PARCOURS_ZONESTELEPORTATIONS                                    \
  for (int izt = 0; izt < this -> ZonesTeleportation_nb; izt++) {	\
  CZoneTeleportation * zt_parcours = this -> ZonesTeleportation_array[izt];	

#define PARCOURS_ZONESTELEPORTATIONS_FIN } 

#endif 



//#define maxindvoisinages_fun(ttt) ((((int) (((ttt) -> TailleX) / taille_case)) + 1) * (((int) (((ttt) -> TailleY) / taille_case)) + 1))
#define maxindvoisinages_fun(ttt) ((((int) (((ttt) -> TailleX) / taille_case))) * (((int) (((ttt) -> TailleY) / taille_case))))
#define maxindvoisinages  maxindvoisinages_fun(this -> Sol)
#define maxindvoisinages2 maxindvoisinages_fun(map)


// On affiche la case sur laquelle nous sommes
// et les cases à rayon de nbnb
// ainsi que le voisinage trivial (indicé 0)
#define PARCOURS_OBJETS_VOISINAGES__OLD(pos_A, nbnb_A)			\
  {                                                                     \
  const TPoint3D pos_ = (pos_A);					\
  const int nbnb_ = (nbnb_A);						\
  const int current_case_ix = (int) (((real) pos_.x) / ((real) taille_case)); \
  const int current_case_iy = (int) (((real) pos_.y) / ((real) taille_case)); \
  for (int biz = 0; biz <= 1; biz++)					\
    for (int ix = biz*(current_case_ix - nbnb_); ix <= biz*(current_case_ix + nbnb_); ix++) \
      if (ix >= 0)							\
	for (int iy = biz*(current_case_iy - nbnb_); iy <= biz*(current_case_iy + nbnb_); iy++) \
	  if (iy >= 0)							\
	    {								\
  int iii = ix + iy * ((int) (((real) TailleX) / ((real) taille_case))); \
  if ((iii >= 0) && (iii < maxindvoisinages))				\
    {									\
  iii += biz;								\
  if (Voisinages != NULL)						\
    for (CAccesseur<CPhysicalObj> a = Voisinages[iii].Objets.ObtenirAcces(); not(a.IsFin()); a.AllerSuivant()) \
      {									\
  CPhysicalObj * o_parcours = a.Element();				\
  if (o_parcours == NULL)						\
    continue;

#define PARCOURS_OBJETS_VOISINAGES_FIN__OLD }}}}

#define PARCOURS_OBJETS_VOISINAGES(pos_A, nbnb_A)			\
  {                                                                     \
  const TPoint3D pos_ = (pos_A);					\
  const int nbnb_ = (nbnb_A);						\
  const int current_case_ix = (int) (((real) pos_.x) / ((real) taille_case)); \
  const int current_case_iy = (int) (((real) pos_.y) / ((real) taille_case)); \
  for (int biz = 0; biz <= 1; biz++)					\
    for (int ix = biz*(current_case_ix - nbnb_); ix <= biz*(current_case_ix + nbnb_); ix++) \
      if (ix < 0) continue; else					\
	if (ix >= VOISINAGE_X_SIZE) continue; else			\
	  for (int iy = biz*(current_case_iy - nbnb_); iy <= biz*(current_case_iy + nbnb_); iy++) \
	    if (iy < 0) continue; else					\
	      if (iy >= VOISINAGE_Y_SIZE) continue; else		\
		for (int iv = 0; iv < VOISINAGE_SIZE; iv++)		\
		  {							\
  CPhysicalObj * o_parcours = this -> Voisinages_array[ix][iy][iv];	\
  if (o_parcours == NULL)						\
    continue;

#define PARCOURS_OBJETS_VOISINAGES_FIN }} 


#define PARCOURS_OBJETS_VOISINAGES_PROCHE(pos)     PARCOURS_OBJETS_VOISINAGES(pos, nb_voisinage_traitee)
#define PARCOURS_OBJETS_VOISINAGES_TOUTPROCHE(pos) PARCOURS_OBJETS_VOISINAGES(pos, nb_voisinage_traitee_toutproche)

/*\
  int ppppx = (pos).x; int ppppy = (pos).y; \
  for (int biz = 1; biz<= 1; biz++)                                     \
  for (int ix = biz*(ppppx / taille_case - nb_voisinage_traitee); ix <= biz*(ppppx / taille_case + nb_voisinage_traitee); ix++) \
  for (int iy = biz*(ppppy / taille_case - nb_voisinage_traitee); iy <= biz*(ppppy / taille_case + nb_voisinage_traitee); iy++) \
  { \
  int iii = (iy *TailleX/ taille_case + ix + 1)*biz; \
  if ((iii >= biz*1) && (iii < maxindvoisinages))                       \
  for (CAccesseur<CPhysicalObj> a = Voisinages[iii].Objets.ObtenirAcces(); !a.IsFin(); a.AllerSuivant())
*/





// ***************************** CZoneTeleportation ***************************** 

CZoneTeleportation * CZoneTeleportation_make(TPoint3D in_position, TPoint3D in_dimension, TDirection in_depart_direction, const char * in_destination_carte, TPoint3D in_destination_position, TDirection in_destination_direction) { 
  MALLOC_BZERO(CZoneTeleportation,this);
  
  this -> position = in_position;
  this -> dimension = in_dimension;
  this -> depart_direction = in_depart_direction;

  this -> destination_carte = strcopy(in_destination_carte);
  this -> destination_position = in_destination_position;
  this -> destination_direction = in_destination_direction;

  return this; 
}; 

void CZoneTeleportation_delete(CZoneTeleportation * this) {
  free(this); 
}; 

CZoneTeleportation * CZoneTeleportation_copy(const CZoneTeleportation * zt_src) {
  MALLOC_BZERO(CZoneTeleportation,this);
  *this = *zt_src; 
  this -> destination_carte = strcopy(zt_src -> destination_carte); 
  return this; 
}; 







// ***************************** CMap ***************************** 

#define NomCarte (this -> NomCarte) 
#define ZonesTeleportation (this -> ZonesTeleportation) 
#define evt_carte (this -> evt_carte) 
//#define Voisinages_array[VOISINAGE_X_SIZE][VOISINAGE_Y_SIZE][VOISINAGE_SIZE]; 
//#define DicoObjets


CMap * CMap__make(const char * filename, const int map_i, const int map_j, const riemann_t * our_manifold, const bool EnVaisseau) {
  MALLOC_BZERO(CMap,this);
  
  //ASSIGN_METHOD(CMap,this,parse); 
  //ASSIGN_METHOD(CMap,this,yycarteparse); 
  ASSIGN_METHOD(CMap,this,GetNomCarte); 
  ASSIGN_METHOD(CMap,this,delete); 
  ASSIGN_METHOD(CMap,this,Life); 
  ASSIGN_METHOD(CMap,this,Render); 
  //ASSIGN_METHOD(CMap,this,ChargerZ); 
  ASSIGN_METHOD(CMap,this,AjouterObjet); 
  ASSIGN_METHOD(CMap,this,AjouterObjet_nom); 
  ASSIGN_METHOD(CMap,this,RetrouverObjetViaSonNom); 
  ASSIGN_METHOD(CMap,this,AjouterZoneTeleportation); 
  ASSIGN_METHOD(CMap,this,AjouterParticules); 
  //ASSIGN_METHOD(CMap,this,TesterPosition); 
  //ASSIGN_METHOD(CMap,this,TesterPositionHero); 
  ASSIGN_METHOD(CMap,this,TraiterOrdresDeplacement); 
  ASSIGN_METHOD(CMap,this,VaTonBouger); 
  //ASSIGN_METHOD(CMap,this,tab_evt_carte); 
  ASSIGN_METHOD(CMap,this,GETZ0_vP3D); 
  ASSIGN_METHOD(CMap,this,GETZ0_vXY); 

  // CSol(EnVaisseau)
  //CSol_make_aux(this -> Sol, EnVaisseau); 
  //CSol_module -> make_content(this -> Sol, EnVaisseau); 
  this -> Sol = CSol_module -> make(EnVaisseau); 
  
  
  if (filename == NULL) return this;

  NomCarte = strcopy(filename); 
  
#if 1
  EvenementsModule -> Vider(EVT_ChargementCarte);
  EvenementsModule -> Vider(EVT_EntreeSurCarte);
  EvenementsModule -> Vider(EVT_PlusEnnemi);
#else 
  ViderEvenement(EVT_ChargementCarte);
  ViderEvenement(EVT_EntreeSurCarte);
  ViderEvenement(EVT_PlusEnnemi);
#endif

  printf("Constructeur CMap(%s)\n", filename);

#if 0 
  // RL: It should be already done through the BZERO. But, later on, we have some weird dangling pointers to already freed objects. 
  for (int i = 0; i < VOISINAGE_X_SIZE; i++) { 
    for (int j = 0; j < VOISINAGE_Y_SIZE; j++) { 
      for (int k = 0; k < VOISINAGE_SIZE; k++) { 
	this -> Voisinages_array[i][j][k] = NULL; 
      }; 
    }; 
  }; 
#endif 
  
  this -> objets_nb = 0; 
  
  this -> ZonesTeleportation_nb = 0; 
  
  {
    char * reelfile; 
    //reelfile = STRCAT2_(CARTESDIR, filename); 
    reelfile = strconcat2(CARTESDIR, filename); 
    printf("nom de fichier réel: %s\n", reelfile); 
    
    //int ret = CMap__parse(this, CARTESDIR, filename); 
    const int ret = CMap__ReadDescriptionFile(this, map_i, map_j, our_manifold, CARTESDIR, filename); 
    if (ret){ 
      messerr("échec de l'analyse du fichier \"%s\"." "\n", reelfile); 
      assert(false); 
    } 
    else { 
      message("analyse ok du fichier \"%s\"." "\n", reelfile); 
    }; 
    free(reelfile); 
  }; 
  
  printf("Fin de la construction CMap__CMap()\n"); 
  
  return this; 
}; 


void CMap__delete(CMap * this) { 
  printf("Destruction de la carte %p\n", this); 
  if (NULL == this) return; 
  
  for (int i = 0; i < this -> ZonesTeleportation_nb; i++) { 
    CZoneTeleportation_delete(this -> ZonesTeleportation_array[i]); 
  }; 
  
  for (int i = 0; i < this -> objets_nb; i++) { 
    //CPhysicalObj_delete(this -> objets_array[i]); // RL: Ils sont dans Voisinage. 
    free(this -> objets_noms_array[i]); 
  }; 
  
  for (int i = 0; i < VOISINAGE_X_SIZE; i++) { 
    for (int j = 0; j < VOISINAGE_Y_SIZE; j++) { 
      for (int k = 0; k < VOISINAGE_SIZE; k++) { 
	if (NULL == this -> Voisinages_array[i][j][k]) { continue; }; 
	// TODO XXX FIXME - RL: It crashes as it seems that the object has already been freed. 
	CPhysicalObj * o_parcours = this -> Voisinages_array[i][j][k]; 
	if (o_parcours -> subtype == CPhysicalObj_subtype_CBonhomme) { 
	  CBonhomme * o_bonhomme = (CBonhomme *) o_parcours; 
	  CBonhomme__delete(o_bonhomme); 
	} 
	else if (o_parcours -> subtype == CPhysicalObj_subtype_CObjNonAnime) { 
	  CObjNonAnime * o_nonanime = (CObjNonAnime *) o_parcours; 
	  CObjNonAnime__delete(o_nonanime); 
	} 
	else if (o_parcours -> subtype == CPhysicalObj_subtype_None) { 
	  CPhysicalObj__delete(o_parcours); 
	} 
	else { 
	  assert(false); 
	}; 
#if 1 
	this -> Voisinages_array[i][j][k] = NULL; // RL: Should be useless, but there is a weird bug living around. 
#endif 
      }; 
    }; 
  }; 
  
  free(NomCarte); 
  // TextureSol, Objets, ZonesTeleportation sont détruits automatiquement car ce ne sont pas des pointeurs 
  
  //CSol_delete_aux(this -> Sol); 
  //CSol_module -> delete_content(this -> Sol); 
  CSol_module -> delete(this -> Sol); 
  
  free(this); 
};


const char * CMap__GetNomCarte(const CMap * this) {
  return NomCarte;
};






float CMap__GETZ0_vXY(const CMap * this, const float lattice_x, const float lattice_y) { 
  const float map_x = lattice_x / this -> lattice_width;
  const float map_y = lattice_y / this -> lattice_height; 
  const float map_z = this -> Sol -> GETZ(this -> Sol, map_x, map_y); 
  const float lattice_z = map_z; 
  return lattice_z; 
}; 

float CMap__GETZ0_vP3D(const CMap * this, const TPoint3D lattice_pos) { 
  return CMap__GETZ0_vXY(this, lattice_pos.x, lattice_pos.y); 
}; 


#if 1 
void CMap__AjouterObjet(CMap * this, CPhysicalObj * o) { 
  printf("Ajout de l'objet physique (pointeur: %p; filename: %s) à la carte\n", o, o == NULL ? "<NULL object>" : o -> filename);
  if (NULL == o) { return; }; 
  
  // RL: Normalizing its position. 
  TPoint3D lattice_pos = o -> GetPosition(o);
  lattice_pos.x = MAX(0, MIN(this -> lattice_width , lattice_pos.x)); 
  lattice_pos.y = MAX(0, MIN(this -> lattice_height, lattice_pos.y)); 
  lattice_pos.z = this -> GETZ0_vP3D(this, lattice_pos); 
  o -> SetPosition_vP3D(o, lattice_pos, this); 
  
  
  printf("Taille de la carte en sommets (treilli): %d x %d" "\n", this -> lattice_width, this -> lattice_height); 
  printf("Position de l'objet: %f x %f" "\n", lattice_pos.x, lattice_pos.y); 
  
  if (!(o -> Fixe_huh)) {
    printf("RL: On ajoute un objet qui se déplace." "\n"); 
    printf("    On l'ajoute donc dans le voisinage trivial." "\n"); 
    int added_huh = false; 
    for (int iv = 0; iv < VOISINAGE_SIZE; iv++) { 
      if (NULL != this -> Voisinages_array[0][0][iv]) continue; 
      this -> Voisinages_array[0][0][iv] = o; 
      added_huh = true; 
      break; 
    };
    assert(added_huh); 
  } 
  else { 
    printf("RL: On ajoute un objet qui ne bouge pas." "\n"); 
    const int ix = MIN(VOISINAGE_X_SIZE,((int) (lattice_pos.x / taille_case))); 
    const int iy = MIN(VOISINAGE_Y_SIZE,((int) (lattice_pos.y / taille_case))); 
    printf("    On l'ajoute donc dans le voisinage: %d x %d " "\n", ix, iy); 
    int added_huh = false; 
    for (int iv = 0; iv < VOISINAGE_SIZE; iv++) { 
      if (NULL != this -> Voisinages_array[ix][iy][iv]) continue; 
      this -> Voisinages_array[ix][iy][iv] = o; 
      added_huh = true; 
      break; 
    }; 
    assert(added_huh); 
  }; 
  
  printf("Ajout de l'objet physique réussi!!\n"); 
}; 
#else 
void CMap__AjouterObjet(CMap * this, CPhysicalObj * o) { 
  printf("Ajout de l'objet physique (pointeur: %p; filename: %s) à la carte\n", o, o == NULL ? "<NULL object>" : o -> filename);
  if (NULL == o) { return; }; 
  
  const TPoint3D lattice_pos = o -> GetPosition(o);
  
  // RL: Normalizing its position. 
  lattice_pos.x = MAX(0,MIN(this -> lattice_width ,lattice_pos.x)); 
  lattice_pos.y = MAX(0,MIN(this -> lattice_height,lattice_pos.y)); 
  lattice_pos.z = this -> GETZ0_vP3D(this -> Sol, lattice_pos); 
  o -> SetPosition_vP3D(o, lattice_pos); 
  
  
  printf("Taille de la carte en sommets (treilli): %d x %d" "\n", this -> lattice_width, this -> lattice_height); 
  printf("Position de l'objet: %f x %f" "\n", lattice_pos.x, lattice_pos.y); 
  
  if (o -> Fixe_huh) {
    printf("RL: On ajoute dans un objet fixe.\n"); 
    //int iii = ((int) (pos.y / taille_case)) * ((int) (TailleX / taille_case)) + ((int) pos.x / taille_case);
    //int iii = ((int) (pos.x / taille_case))  +  ((int) (pos.y / taille_case)) * ((int) (this -> Sol -> TailleX / taille_case));
    const int ix = MIN(VOISINAGE_X_SIZE,((int) (pos.x / taille_case))); 
    const int iy = MIN(VOISINAGE_Y_SIZE,((int) (pos.y / taille_case))); 
#if 0 
    int iii = ix + iy * ((int) (this -> Sol -> TailleX / taille_case)); 
    
    if ((iii < 0) || (iii >= maxindvoisinages))
      iii = -1; // un +1 est fait ensuite, donc tout va bien :-)

    printf("On ajoute dans le voisinage n° %i (coord. x = %f, y %f)\n", iii, pos.x, pos.y);
#if 1
    Voisinages[iii+1].Objets.Empiler_sans_copie(o);
#elif 0
    voisinage_ajouter(this, iii+1, o); 
#endif 
#elif 1 
    int added_huh = false; 
    for (int iv = 0; iv < VOISINAGE_SIZE; iv++) { 
      if (NULL != this -> Voisinages_array[ix][iy][iv]) continue; 
      this -> Voisinages_array[ix][iy][iv] = o; 
      added_huh = true; 
      break; 
    };
    assert(added_huh); 
#endif
  }
  else {
    printf("RL: On ajoute dans un objet pas fixe.\n"); 
    printf("On ajoute dans le voisinage trivial.\n"); 
#if 0 
    Voisinages[0].Objets.Empiler_sans_copie(o);
#elif 0
    voisinage_ajouter(this, 0, o);
#elif 1 
    int added_huh = false; 
    for (int iv = 0; iv < VOISINAGE_SIZE; iv++) {
      if (NULL != this -> Voisinages_array[0][0][iv]) continue; 
      this -> Voisinages_array[0][0][iv] = o; 
      added_huh = true; 
      break; 
    };
    assert(added_huh); 
#endif
  }; 
  
  
  printf("Ajout de l'objet physique réussi!!\n"); 
}; 
#endif 
 
 

void CMap__AjouterObjet_nom(CMap * this, const char * nom, CPhysicalObj * o) {
  printf("Ajout de l'objet physique (pointeur %p) à la carte, de nom %s \n", o, nom); 
  this -> AjouterObjet(this, o); 
  
  assert(this -> objets_nb < DicoObjets_SIZE); 
  this -> objets_array[this -> objets_nb] = o; 
  this -> objets_noms_array[this -> objets_nb] = strcopy(nom); 
  this -> objets_nb++; 
  
  printf("Ajout de l'objet physique réussi!!" "\n"); 
}; 
 
void CMap__Dico_EnleverObjet(CMap * this, CPhysicalObj * o) { 
  printf("Enlèvement de l'objet physique (pointeur %p) à la carte " "\n", o); 
  for (int i = 0; i < this -> objets_nb; i++) { 
    if (o != this -> objets_array[i]) continue; 
    free(this -> objets_noms_array[i]); 
    this -> objets_noms_array[i] = NULL; 
    this -> objets_array[i] = NULL; 
    return; 
  }; 
}; 
 
 
 
CPhysicalObj * CMap__RetrouverObjetViaSonNom(CMap * this, const char * nom) { 
  for (int i = 0; i < this -> objets_nb; i++) { 
    if (0 != strcmp(nom, this -> objets_noms_array[i])) continue; 
    return this -> objets_array[i]; 
  }; 
  return NULL; 
}; 
 


/* exemple d'utilisation

   TPoint3D pos, dim, posdest;

   pos = Point3D(0.0f, 0.0f,0.0f);
   dim = Point3D(2.0f, 2.0f, 128.0f);
   posdest = Point3D(0.0f, 4.0f, 0.0f);

   Map -> AjouterZoneTeleportation(pos, dim, DOS, "carte.carte", posdest, DOS);
*/
void CMap__AjouterZoneTeleportation(CMap * this, TPoint3D position, TPoint3D dimension, TDirection depart_direction, const char * destination_carte, TPoint3D destination_position, TDirection destination_direction) {
  CZoneTeleportation * zt = CZoneTeleportation_make(position, dimension, depart_direction, destination_carte, destination_position, destination_direction);

  printf("Ajout d'une zone de téléportation \n");
  printf(" position: (%f, %f, %f)\n", position.x, position.y, position.z);
  printf(" dimension: (%f, %f, %f)\n", dimension.x, dimension.y, dimension.z);

  assert(this -> ZonesTeleportation_nb < ZonesTeleportation_SIZE); 
  this -> ZonesTeleportation_array[this -> ZonesTeleportation_nb] = zt;
  this -> ZonesTeleportation_nb++; 
}; 

const CZoneTeleportation * CMap__VaTonBouger(const CMap * this, const CPhysicalObj * aHero) { 
  TPoint3D p = aHero -> GetPosition(aHero);

  PARCOURS_ZONESTELEPORTATIONS
    {
      if ((zt_parcours->position.x <= p.x) &&
          (zt_parcours->position.y <= p.y) &&
          (zt_parcours->position.z <= p.z) &&
          (p.x <= zt_parcours->position.x + zt_parcours->dimension.x) &&
          (p.y <= zt_parcours->position.y + zt_parcours->dimension.y) &&
          (p.z <= zt_parcours->position.z + zt_parcours->dimension.z) )
        return zt_parcours;

    }
  PARCOURS_ZONESTELEPORTATIONS_FIN;

  return NULL;
}; 


void CMap__TraiterOrdresDeplacement(CMap * this, CBonhomme * aHero, const bool MoteurPhysiqueActif) {
  aHero -> TraiterOrdresDeplacement(aHero, this, MoteurPhysiqueActif);

  PARCOURS_OBJETS
    {
#if 0
      CBonhomme * b = dynamic_cast<CBonhomme *>(a.Element());
#elif 0
      CBonhomme * b = dynamic_cast<CBonhomme *>(o_parcours);
#elif 1 
      if (!(CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype)) continue; 
      CBonhomme * b = (CBonhomme *) o_parcours; 
#endif 
      b -> TraiterOrdresDeplacement(b, this, MoteurPhysiqueActif); 
    } 
  PARCOURS_OBJETS_FIN;
}; 














void CMap__AjouterParticules(CMap * this, const TPoint3D p, const char * nom, const bool MoteurPhysiqueActif) {
#define NB_PARTICULES 10
  //printf("Ajout d'une flopée de particules au point (%f, %f, %f,) \n...", p.x, p.y, p.z);

#ifdef NB_PARTICULES
  for (int i = 0; i < NB_PARTICULES; i++) { 
    CBonhomme    * b = CBonhomme__make(nom); 
    CPhysicalObj * o = &b -> parent1; 
    o -> SetDimension(o, 0.0f,0.0f,0.0f); 
    o -> SetPosition_vP3D(o, p, this); 
    o -> SetObjetEphemere(o, 32); 
    o -> Hostile_huh = false; 
    const TPoint3D pp = o -> GetPosition(o); 
    //printf("Coordonnée des particules : (%f, %f, %f,) \n", pp.x, pp.y, pp.z); 
#if 0 
    o -> InitForce(o); 
#define GENPOS ((float) (rand()%2000-1000)) / 200.0f 
    o -> AddForce_vXYZ(o, GENPOS, GENPOS, 100.0f); 
    //o -> CalcNewPosition(o); 
    //o -> ValiderPosition(o, MoteurPhysiqueActif); 
#endif 
    this -> AjouterObjet(this, o); 
  }; 
#endif
  
  //printf("Ajout des particules effectué!\n");
};



void CMap__Life(CMap * this, const bool EnVaisseau) { 
  // RL: TODO XXX FIXME 
}; 


//void CMap__Life_GamePlay(CMap * this, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau) {
void CMap__Life_GamePlay(CMap * this, const bool EnVaisseau) { 
  if (EnVaisseau) return; 

  PARCOURS_OBJETS 
  //PARCOURS_OBJETS_VOISINAGES_PROCHE(pos) 
    { 
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	CBonhomme * b = (CBonhomme *) o_parcours; 
	b -> Life(b); 
      }
      //else if (CObjNonAnime * nonanime = dynamic_cast<CObjNonAnime *>(o_parcours)) {
      else if (CPhysicalObj_subtype_CObjNonAnime == o_parcours -> subtype) {
	CObjNonAnime * nonanime = (CObjNonAnime *) o_parcours; 
	//nonanime -> Life(nonanime, this -> Sol); 
      } 
      else { 
	//o_parcours -> Life(o_parcours, this -> Sol); 
      }; 
      
    }
  PARCOURS_OBJETS_FIN;
  //PARCOURS_OBJETS_VOISINAGES_FIN;
};

void CMap__Life_NewtonEngine_Objects(CMap * this, const bool EnVaisseau) {
  if (EnVaisseau) return; 

  PARCOURS_OBJETS
    {
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	CBonhomme * b = (CBonhomme *) o_parcours; 
        //if (rand() % 40 == 1) { 
        if (arc4random_uniform(40) == 0) { 
          b -> SetDirection(b, DirectionAleatoire()); 
	}; 
        b -> Avancer(b, b -> GetDirection(b)); 
      }; 
      
#if 0 
      if (not(o_parcours -> Fixe_huh)) { 
        this -> TesterPosition(this, o_parcours, MoteurPhysiqueActif); 
        if (!o_parcours -> TesterPosition(o_parcours, this -> lattice_width, this -> lattice_height, Hero_o)) { 
          if (o_parcours -> Hostile_huh) { 
            if (not(Hero -> EstInvisible(Hero))) { 
              //le héros se fait toucher par un ennemi 
              Hero_o -> PerdrePV(Hero_o, 5); 
              Hero -> DevenirInvisible(Hero, 200); 
            }; 
	  }; 
        }; 
        o_parcours -> ValiderPosition(o_parcours, MoteurPhysiqueActif); 
        o_parcours -> InitForce(o_parcours); 
      }; 
#endif 
      
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN; 
}; 


void CMap__Life_NewtonEngine_Sword(CMap * this, const CPhysicalObj * Hero_o, const bool EnVaisseau) {
  if (EnVaisseau) return; 

  const CBonhomme * Hero_b = (const CBonhomme *) Hero_o; 

  // la physique de l'épée
#if 1
  {
    if (Hero_b -> EnTrainDeFrapper(Hero_b)) { 
      CPhysicalObj zone_epee = *(Hero_o); 
      TPoint3D d = Hero_o -> GetDimension(Hero_o); 
      zone_epee.SetDimension(&zone_epee, d.x, d.y, d.z); 

      TPoint3D dir;
      switch (Hero_b -> GetDirection(Hero_b)) { 
      case FACE         : dir = TPoint3D_make_struct( 0.0f, -1.0f, 0.0f); break; 
      case DOS          : dir = TPoint3D_make_struct( 0.0f,  1.0f, 0.0f); break; 
      case PROFIL_VERS_D: dir = TPoint3D_make_struct( 1.0f,  0.0f, 0.0f); break; 
      case PROFIL_VERS_G: dir = TPoint3D_make_struct(-1.0f,  0.0f, 0.0f); break; 
      default: assert(false); 
      }; 
      
      //zoneepee.SetPosition(&zoneepee, Hero_o -> GetPosition(Hero_o) + dir); 
      const TPoint3D hero_pos = Hero_o -> GetPosition(Hero_o); 
      zone_epee.SetPosition_vP3D(&zone_epee, TPoint3D_add__macro(hero_pos, dir), this); 
      
      //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
      PARCOURS_OBJETS 
        {
	  if (CPhysicalObj_subtype_CBonhomme != o_parcours -> subtype) continue; 
	  
	  CBonhomme * b = (CBonhomme *) o_parcours; 
	  
          if (!o_parcours -> IsVolumeNul(o_parcours)) { 
#if 1 
	    // RL: TODO XXX FIXME 
#else 
	    if ((!(o_parcours->TesterPosition(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold, &zoneepee))) && (!(b->EstInvisible(b)))) {
              //on a frappé a.Element()
              printf("Le héros a frappé un bonhomme\n");
              o_parcours -> PerdrePV(o_parcours, 1);
              this -> AjouterParticules(this, o_parcours -> GetPosition(o_parcours), "sang.anime", MoteurPhysiqueActif);
              o_parcours -> AddForce_vP3D(o_parcours, TPoint3D_scale__macro(10.0f, dir));
              b -> DevenirInvisible(b, 50);
            }; 
#endif 
	  }; 

        }
      //FIN_PARCOURS_OBJETS_VOISINAGES;
      PARCOURS_OBJETS_FIN;
    };
    
  };
#endif
}; 



void CMap__Life_RemoveDeads(CMap * this, const bool EnVaisseau) { 
  if (EnVaisseau) return; 

  PARCOURS_OBJETS 
    {
      if (not(o_parcours -> Fixe_huh) && o_parcours -> Is0PV(o_parcours)) { 
	CMap__Dico_EnleverObjet(this, o_parcours); 
        if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	  CBonhomme * b = (CBonhomme *) o_parcours; 
          b -> delete(b); 
        } 
        else if (CPhysicalObj_subtype_CObjNonAnime == o_parcours -> subtype) { 
	  CObjNonAnime * nonanime = (CObjNonAnime *) o_parcours; 
          nonanime -> delete(nonanime); 
        } 
        else { 
          o_parcours -> delete(o_parcours); 
	}; 
	this -> Voisinages_array[iii][jjj][kkk] = NULL; 
      }; 
    }
  PARCOURS_OBJETS_FIN;
}; 






#if 1 
// RL: Returns the closest item with which the hero can interact. 
CPhysicalObj * CMap__GetNearestInteractingObject(CMap * this, const CPhysicalObj * Hero_o) { 
  const CBonhomme * Hero_b = (const CBonhomme *) Hero_o; 
  
#if 0 
  this   -> TesterPosition(this, Hero_o, our_manifold, MoteurPhysiqueActif);
  Hero_o -> ValiderPosition(Hero_o, MoteurPhysiqueActif);
  Hero_o -> InitForce(Hero_o);
#endif 
  
  // on trouve l'élément le plus proche
  CPhysicalObj * elementproche = NULL;
  {
#define norme_minimum_pour_etre_proche 50.0f 
    float norme1_du_proche = norme_minimum_pour_etre_proche; 
    
    PARCOURS_OBJETS 
      { 
	TPoint3D diff_vec; 
	TPoint3D_sub(o_parcours -> GetPosition(o_parcours), Hero_o -> GetPosition(Hero_o), &diff_vec); 
        const float norme1_courante = TPoint3D_Norme1(diff_vec); 
	
        if (norme1_courante < norme1_du_proche) { 
          norme1_du_proche = norme1_courante; 
          elementproche    = o_parcours; 
        }; 
      } 
    PARCOURS_OBJETS_FIN; 
  }; 
  
  return elementproche; 
}; 

#else 
/*on informe la carte de la position du héro

  en retour, elle nous offre un pointeur vers l'élément le plus proche
  OU NULL si trop loin
*/
// En fait cette fonction est le moteur physique………… 
// RL: Returns the closest item with which the hero can interact. 
CPhysicalObj * CMap__TesterPositionHero(CMap * this, CPhysicalObj * Hero_o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif) { 
  
  CBonhomme * Hero_b = (CBonhomme *) Hero_o;

  this   -> TesterPosition(this, Hero_o, our_manifold, MoteurPhysiqueActif);
  Hero_o -> ValiderPosition(Hero_o, MoteurPhysiqueActif);
  Hero_o -> InitForce(Hero_o);


  // on fait bouger les objets 
  // RL: Je suis sceptique que cela devrait être dans cette procédure. 
  PARCOURS_OBJETS
    {
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) {  
	CBonhomme * b = (CBonhomme *) o_parcours; 
        if (rand() % 20 == 1) 
          b -> SetDirection(b, DirectionAleatoire()); 

        b -> Avancer(b, b -> GetDirection(b), our_manifold); 
      }; 
      
      if (not(o_parcours -> Fixe_huh)) { 
        this -> TesterPosition(this, o_parcours, our_manifold, MoteurPhysiqueActif); 
        if (!o_parcours -> TesterPosition(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold, Hero_o)) { 
          if (o_parcours -> Hostile_huh) { 
            if (not(Hero -> EstInvisible(Hero))) { 
              //le héros se fait toucher par un ennemi 
              Hero_o -> PerdrePV(Hero_o, 5); 
              Hero -> DevenirInvisible(Hero, 200); 
            }; 
	  }; 
        }; 
        o_parcours -> ValiderPosition(o_parcours, MoteurPhysiqueActif); 
        o_parcours -> InitForce(o_parcours); 
      }; 
      
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN;
  
  
  // la phsyique de l'épée
#if 1
  {
    if (Hero -> EnTrainDeFrapper(Hero)) { 
      CPhysicalObj zoneepee = *(Hero_o); 
      TPoint3D d = Hero_o -> GetDimension(Hero_o, this -> lattice_width, this -> lattice_height, our_manifold); 
      zoneepee.SetDimension(&zoneepee, d.x, d.y, d.z); 

      TPoint3D dir;
      switch (Hero -> GetDirection(Hero)) {
      case FACE: dir = TPoint3D_make_struct(0.0f, -1.0f, 0.0f); break;
      case DOS: dir = TPoint3D_make_struct(0.0f, 1.0f, 0.0f); break;
      case PROFIL_VERS_D: dir = TPoint3D_make_struct(1.0f, 0.0f, 0.0f); break;
      case PROFIL_VERS_G: dir = TPoint3D_make_struct(-1.0f, 0.0f, 0.0f); break;
      default: assert(false);
      } 
      
      //zoneepee.SetPosition(&zoneepee, Hero_o -> GetPosition(Hero_o) + dir); 
      const TPoint3D hero_pos = Hero_o -> GetPosition(Hero_o); 
      zoneepee.SetPosition_vP3D(&zoneepee, TPoint3D_add__macro(hero_pos, dir)); 
      
      //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
      PARCOURS_OBJETS
        {
	  if (CPhysicalObj_subtype_CBonhomme != o_parcours -> subtype) continue; 
	  
	  CBonhomme * b = (CBonhomme *) o_parcours; 

          if (!o_parcours -> IsVolumeNul(o_parcours)) { 
	    if ((!(o_parcours->TesterPosition(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold, &zoneepee))) && (!(b->EstInvisible(b)))) {
              //on a frappé a.Element()
              printf("Le héros a frappé un bonhomme\n");
              o_parcours -> PerdrePV(o_parcours, 1);
              this -> AjouterParticules(this, o_parcours -> GetPosition(o_parcours), "sang.anime", MoteurPhysiqueActif);
              o_parcours -> AddForce_vP3D(o_parcours, TPoint3D_scale__macro(10.0f, dir));
              b -> DevenirInvisible(b, 50);
            }; 
	  }; 

        }
      //FIN_PARCOURS_OBJETS_VOISINAGES;
      PARCOURS_OBJETS_FIN;
    };
    
  };
#endif

  // on enlève les éléments qui n'ont plus de vie
  PARCOURS_OBJETS
    {
      if (not(o_parcours -> Fixe_huh) && o_parcours -> Is0PV(o_parcours)) {
#if 0 
        a.DetruireElementCourant();
#elif 0
        voisinage_detruire(this, iii, jjj);
#else 
	CPhysicalObj__delete(this -> Voisinages_array[iii][jjj][kkk]); 
	this -> Voisinages_array[iii][jjj][kkk] = NULL; 
	// RL: Et dans le dico? 
#endif
      };
    }
  PARCOURS_OBJETS_FIN;

  
  
  
  // on trouve l'élément le plus proche
  CPhysicalObj * elementproche = NULL;
  {
#define norme_minimum_pour_etre_proche 50.0f
    float norme1_du_proche = norme_minimum_pour_etre_proche;

    PARCOURS_OBJETS
      {
	TPoint3D diff_vec; 
	TPoint3D_sub(o_parcours -> GetPosition(o_parcours), Hero_o -> GetPosition(Hero_o), &diff_vec); 
        const float norme1_courante = TPoint3D_Norme1(diff_vec);
	
        if (norme1_courante < norme1_du_proche) {
          norme1_du_proche = norme1_courante;
          elementproche = o_parcours;
        };
      }
    PARCOURS_OBJETS_FIN;
  };


  return elementproche;
  return NULL;



  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  //CPhysicalObj * elementproche = NULL; /*ce qu'on rend à la fin de cette fonction*/


  // on nettoie la liste des objets... on vire ceux qui ont 0 PV
  bool unennemiestdecede = false;
  int nb_ennemis = 0;
  float norme1_du_proche = norme_minimum_pour_etre_proche;
  PARCOURS_OBJETS
    {

      //fprintf(stderr, "ACC: courant: %p - precedent: %p - liste: %p\n", a.pointeurcourant, a.pointeurprecedent, a.maliste);
      if (o_parcours -> Is0PV(o_parcours)) {
        if (o_parcours -> Hostile_huh)
          unennemiestdecede = true;
#if 0
        a.DetruireElementCourant();
#elif 0
        voisinage_detruire(this, iii, jjj);
#elif 1 
	CPhysicalObj__delete(this -> Voisinages_array[iii][jjj][kkk]); 
	this -> Voisinages_array[iii][jjj][kkk] = NULL; 
	// Et dans le dico? 
#endif
      }
      else {
        if (o_parcours -> Hostile_huh) nb_ennemis++;

	TPoint3D diff_vec; 
	TPoint3D_sub(o_parcours -> GetPosition(o_parcours), Hero_o -> GetPosition(Hero_o), &diff_vec); 
        const float norme1_courante = TPoint3D_Norme1(diff_vec);
	
        if (norme1_courante < norme1_du_proche) {
          norme1_du_proche = norme1_courante;
          elementproche = o_parcours;
        }; 
      }; 
    }
  PARCOURS_OBJETS_FIN;

  if (unennemiestdecede && (nb_ennemis == 0)) {
    //RaiseEvenement(EVT_PlusEnnemi); 
    EvenementsModule -> Raise(EVT_PlusEnnemi); 
  }; 



  if (Hero -> EnTrainDeFrapper(Hero)) {
    CPhysicalObj zoneepee = (*Hero_o);
    TPoint3D d = Hero_o -> GetDimension(Hero_o, this -> lattice_width, this -> lattice_height, our_manifold);
    zoneepee.SetDimension(&zoneepee, d.x, d.y, d.z);

    TPoint3D dir;
    switch (Hero -> GetDirection(Hero)) {
    case FACE: dir = TPoint3D_make_struct(0.0f, -1.0f, 0.0f); break;
    case DOS: dir = TPoint3D_make_struct(0.0f, 1.0f, 0.0f); break;
    case PROFIL_VERS_D: dir = TPoint3D_make_struct(1.0f, 0.0f, 0.0f); break;
    case PROFIL_VERS_G: dir = TPoint3D_make_struct(-1.0f, 0.0f, 0.0f); break;
    default: assert(false);
    }

    TPoint3D hero_pos = Hero_o -> GetPosition(Hero_o); 
    zoneepee.SetPosition_vP3D(&zoneepee, TPoint3D_add__macro(hero_pos, dir));
    
    //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
    PARCOURS_OBJETS
      {
	if (CPhysicalObj_subtype_CBonhomme != o_parcours -> subtype) continue; 
        if (o_parcours -> IsVolumeNul(o_parcours)) continue;
	
        CBonhomme* b = (CBonhomme *) o_parcours;

	if ((!(o_parcours -> TesterPosition(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold, &zoneepee))) && (!(b -> EstInvisible(b)))) {
	  //on a frappé a.Element()
	  printf("Le héros a frappé un bonhomme\n");
	  o_parcours -> PerdrePV(o_parcours, 1);
	  this -> AjouterParticules(this, o_parcours -> GetPosition(o_parcours), "sang.anime", MoteurPhysiqueActif);
	  o_parcours -> AddForce_vP3D(o_parcours, TPoint3D_scale__macro(10.0f,dir)); 
	  b -> DevenirInvisible(b, 50);
	}

      }
    //FIN_PARCOURS_OBJETS_VOISINAGES;
    PARCOURS_OBJETS_FIN;

  }


  // on ne fait bouger que les ennemis près du héros: le reste du monde n'évolue pas!!!!
  //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition())
  PARCOURS_OBJETS
    {
      /*si l'objet courant est un bonhomme*/
      //if (CBonhomme* b = dynamic_cast<CBonhomme *>(o_parcours)) {
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	CBonhomme* b = (CBonhomme *) o_parcours;
	if (rand() % 20 == 1)
	  b -> SetDirection(b, DirectionAleatoire());
	
	b -> Avancer(b, b -> GetDirection(b), our_manifold);
      }
      
      if (!(o_parcours->Fixe_huh)) {
	this -> TesterPosition(this, o_parcours, our_manifold, MoteurPhysiqueActif);
	if (!o_parcours -> TesterPosition(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold, Hero_o)) {
	  if (o_parcours -> Hostile_huh)
	    if (!Hero -> EstInvisible(Hero)) {
	      //le héros se fait toucher par un ennemi
	      Hero_o -> PerdrePV(Hero_o, 5);
	      Hero -> DevenirInvisible(Hero, 200);
	    }
        }
        o_parcours -> ValiderPosition(o_parcours, MoteurPhysiqueActif);
        o_parcours -> InitForce(o_parcours);
      }
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN;

  
  return elementproche;
}; 
#endif 






#if 0 
void CMap__NewtonEngine_InteractAdjustCorrect(CMap * this, CPhysicalObj * o, const bool MoteurPhysiqueActif) { 
  // FS: on teste si la position temporaire de o est correct
  const TPoint3D pp = o -> GetPosition(o);
  const float lattice_x = pp.x; 
  const float lattice_y = pp.y; 
  const float lattice_z = pp.z; 
  const float map_x = lattice_x / this -> lattice_width;
  const float map_y = lattice_y / this -> lattice_height; 
  const float map_z = lattice_z; 

  if (this -> Sol -> yatilEau(this -> Sol, map_x, map_y, map_z)) { 
    if (!(o -> DansEau_huh)) { 
      //printf(" L'objet %p va rentrer dans l'eau. Sa position est la suivante : %f, %f, %f. Nous allons générer une floppée de particules d'eau.\n", o, i, j, z);

      if (not(o -> IsVolumeNul(o))) { 
        this -> AjouterParticules(this, o -> GetPosition(o), "eclaboussures.anime", MoteurPhysiqueActif); 
      }; 
      
      o -> DansEau_huh = true;
    }; 
    
    //o -> AddForce_vXYZ(o, 0.0f, 0.0f, -1.0f); // RL: The object is drowning. 
    o -> Acceleration_add_vXYZ(o, 0.0f, 0.0f, 9.0f); // RL: Archimede: Gravitation is less strong in water. 
    
    // RL: Are we fully under water? 
    //o -> Immerge_huh = this -> Sol -> yatilEau(this -> Sol, map_x, map_y, map_z + 20.0f); 
    o -> Immerge_huh = this -> Sol -> yatilEau(this -> Sol, map_x, map_y, map_z + o -> d.z); 

    // FS: dans l'eau les frottements fluides sont plus importants
    o -> CoeffFrottementFluideXY = 3.0f; 
    o -> CoeffFrottementFluideZ  = 1.0f; 
  } 
  else { 
    o -> DansEau_huh = false; 
    //o -> AddForce_vXYZ(o, 0.0f, 0.0f, -10.0f); // RL: Gravitation 
    o -> Immerge_huh = false; 
    // FS: dans l'air, les frottements fluides sont assez petits 
    //o -> CoeffFrottementFluide  = 1.0f; 
    //o -> CoeffFrottementFluideZ = 0.0f; 
  }; 
}; 
#elif 0  
void CMap__TesterPosition(CMap * this, CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif) {
  // FS: on teste si la position temporaire de o est correct
  const TPoint3D pp = o -> GetPosition(o);
  const float lattice_x = pp.x; 
  const float lattice_y = pp.y; 
  const float lattice_z = pp.z; 
  const float map_x = lattice_x / this -> lattice_width;
  const float map_y = lattice_y / this -> lattice_height; 
  const float map_z = lattice_z; 

  if (this -> Sol -> yatilEau(this -> Sol, map_x, map_y, map_z)) { 
    if (!(o -> DansEau_huh)) { 
      //printf(" L'objet %p va rentrer dans l'eau. Sa position est la suivante : %f, %f, %f. Nous allons générer une floppée de particules d'eau.\n", o, i, j, z);

      if (not(o -> IsVolumeNul(o))) { 
        this -> AjouterParticules(this, o -> GetPosition(o), "eclaboussures.anime", MoteurPhysiqueActif); 
      }; 
      
      o -> DansEau_huh = true;
    }; 
    
    o -> AddForce_vXYZ(o, 0.0f, 0.0f, -1.0f); // RL: The object is drowning. 
    
    // RL: Are we fully under water? 
    o -> Immerge_huh = this -> Sol -> yatilEau(this -> Sol, map_x, map_y, map_z + 20.0f); 

    // FS: dans l'eau les frottements fluides sont plus importants
    o -> CoeffFrottementFluide  = 3.0f;
    o -> CoeffFrottementFluideZ = 1.0f;
  } 
  else { 
    o -> DansEau_huh = false; 
    o -> AddForce_vXYZ(o, 0.0f, 0.0f, -10.0f); // RL: Gravitation 
    o -> Immerge_huh = false; 
    // FS: dans l'air, les frottements fluides sont assez petits 
    o -> CoeffFrottementFluide  = 1.0f; 
    o -> CoeffFrottementFluideZ = 0.0f; 
  }; 
  
  o -> CalcNewPosition(o); 
  o -> TesterSol(o, this -> Sol); 
  
  //PARCOURS_OBJETS_VOISINAGES_TOUTPROCHE(o->GetPosition()) 
  PARCOURS_OBJETS { 
    if (o_parcours == o) continue; 
    o -> TesterPosition(o, this -> lattice_width, this -> lattice_height, our_manifold, o_parcours); 
  } PARCOURS_OBJETS_FIN; 
  //FIN_PARCOURS_OBJETS_VOISINAGES; 
  
}; 
#endif  



















#if 1
void CMap__Render(const CMap * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau) { 
  this -> Sol -> Render(this -> Sol, our_manifold, nb_cells_displayed_x, nb_cells_displayed_y, target_map_i, target_map_j, target_lattice_x / (float) this -> lattice_width, target_lattice_y / (float) this -> lattice_height); 
  
  const TPoint3D pos = TPoint3D_make_struct(target_lattice_x, target_lattice_y, 0.0f); 
  
  
  if (not(EnVaisseau)) {
    //PARCOURS_OBJETS
    PARCOURS_OBJETS_VOISINAGES_PROCHE(pos) 
      {
        if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
          //fprintf(stderr, "Bonhomme: Rendering: %s\n", b -> filename); 
	  const CBonhomme * b = (const CBonhomme *) o_parcours; 
          b -> Render(b, this -> lattice_width, this -> lattice_height, our_manifold); 
        } 
        else if (CPhysicalObj_subtype_CObjNonAnime == o_parcours -> subtype) { 
	  const CObjNonAnime * nonanime = (const CObjNonAnime *) o_parcours; 
	  //fprintf(stderr, "ObjPhys: Rendering: %s\n", o_parcours -> filename); 
          nonanime -> Render(nonanime, this -> lattice_width, this -> lattice_height, our_manifold); 
        } 
        else { 
          o_parcours -> Render(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold); 
	}; 
	
      }
    //PARCOURS_OBJETS_FIN;
    PARCOURS_OBJETS_VOISINAGES_FIN;
  }
  else { // _ en vaisseau _
    PARCOURS_OBJETS
      {
#if 0
        int i = (int) a.Element()->GetPosition().x;
        int j = (int) a.Element()->GetPosition().y;
#endif
        const int i = (int) o_parcours -> GetPosition(o_parcours).x; 
        const int j = (int) o_parcours -> GetPosition(o_parcours).y; 
	
	
        //const bool b = ((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        const bool b = true; //((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        if (b) { 
          o_parcours -> Render(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold); 
	}; 
      }
    PARCOURS_OBJETS_FIN; 
  }; // _ en vaisseau _ 
  
  
  
  { 
    //fprintf(stderr, "ZoneTeleportationBlit\n"); 
    //int i = 0; 
    PARCOURS_ZONESTELEPORTATIONS { 
      //fprintf(stderr, "ZoneTeleportationRender: i = %d\n", i++); 
      our_manifold -> AfficherCube(our_manifold, /*map_i*/0, /*map_j*/0, zt_parcours -> position.x / this -> lattice_width, zt_parcours -> position.y / this -> lattice_height, zt_parcours -> position.z, zt_parcours -> dimension.x / this -> lattice_width, zt_parcours -> dimension.y / this -> lattice_height, zt_parcours -> dimension.z); 
    } PARCOURS_ZONESTELEPORTATIONS_FIN; 
  }; 
  
}; 
#else 
//void CMap__Render(const CMap * this, const riemann_t * our_manifold, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau) { 
void CMap__Render(const CMap * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau) { 
  //this -> Sol -> Render(this -> Sol, i1, j1, i2, j2); 
  this -> Sol -> Render(this -> Sol, our_manifold, nb_cells_displayed_x, nb_cells_displayed_y, target_map_i, target_map_j, target_lattice_x / (float) this -> lattice_width, target_lattice_y / (float) this -> lattice_height); 
  
  //const TPoint3D pos = TPoint3D_make_struct((i1 + i2) / 2, (j1 + j2) / 2, 0.0f); 
  const TPoint3D pos = TPoint3D_make_struct(target_lattice_x, target_lattice_y, 0.0f); 
  
  
  if (not(EnVaisseau)) {
    //PARCOURS_OBJETS
    PARCOURS_OBJETS_VOISINAGES_PROCHE(pos) 
      {
#if 0 
        const int i = (int) o_parcours -> GetPosition(o_parcours).x; 
        const int j = (int) o_parcours -> GetPosition(o_parcours).y; 
#endif 	
#if 0
        const char * filename = o_parcours -> filename; 
        if (filename != NULL) { 
          if (0 != strcmp(filename, "./heros.anime")) {
            fprintf(stderr, "ObjPhys: Rendering: %s\n", filename);
            fflush(NULL);
          }; 
	}; 
        //fprintf(stderr, "iii = %d - jjj = %d - ", iii, jjj);
#endif
	
        //bool test = ((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        //if (test)
        //if (CBonhomme * b = dynamic_cast<CBonhomme *>(o_parcours)) { 
        if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
          //fprintf(stderr, "Bonhomme: Rendering: %s\n", b -> filename); 
	  const CBonhomme * b = (const CBonhomme *) o_parcours; 
          b -> Render(b, this -> lattice_width, this -> lattice_height, our_manifold); 
        } 
        //else if (CObjNonAnime * nonanime = dynamic_cast<CObjNonAnime *>(o_parcours)) { 
        else if (CPhysicalObj_subtype_CObjNonAnime == o_parcours -> subtype) { 
	  const CObjNonAnime * nonanime = (const CObjNonAnime *) o_parcours; 
	  //fprintf(stderr, "ObjPhys: Rendering: %s\n", o_parcours -> filename); 
          nonanime -> Render(nonanime, this -> lattice_width, this -> lattice_height, our_manifold); 
        } 
        else { 
          o_parcours -> Render(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold); 
	}; 
	
      }
    //PARCOURS_OBJETS_FIN;
    PARCOURS_OBJETS_VOISINAGES_FIN;

  }
  else { // _ en vaisseau _
    PARCOURS_OBJETS
      {
#if 0
        int i = (int) a.Element()->GetPosition().x;
        int j = (int) a.Element()->GetPosition().y;
#endif
        const int i = (int) o_parcours -> GetPosition(o_parcours).x; 
        const int j = (int) o_parcours -> GetPosition(o_parcours).y; 
	
	
        //const bool b = ((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        const bool b = true; //((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        if (b) { 
          o_parcours -> Render(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold); 
	}; 
      }
    PARCOURS_OBJETS_FIN; 
  }; // _ en vaisseau _ 
  
  
  
  { 
    //fprintf(stderr, "ZoneTeleportationBlit\n"); 
    //int i = 0; 
    PARCOURS_ZONESTELEPORTATIONS { 
      //fprintf(stderr, "ZoneTeleportationRender: i = %d\n", i++); 
      our_manifold -> AfficherCube(our_manifold, /*map_i*/0, /*map_j*/0, zt_parcours -> position.x, zt_parcours -> position.y, zt_parcours -> position.z, zt_parcours -> dimension.x, zt_parcours -> dimension.y, zt_parcours -> dimension.z); 
    } PARCOURS_ZONESTELEPORTATIONS_FIN; 
  }; 
  
}; 
#endif 




int CMap__ReadDescriptionFile(CMap * this, const int map_i, const int map_j, const riemann_t * our_manifold, const char * dir, const char * filename) {
  carte_t * carte_data  = NULL; 
  CSol    * this_parent = this -> Sol; 
  
  { 
    char carte_fullpath[strlen(dir) + strlen(filename) + 1];
    strcat(strcpy(carte_fullpath, dir), filename); 
#define LOG_SUFF ".log"
    char carte_log[strlen(LOGDIR) + strlen(filename) + strlen(LOG_SUFF) + 1];
    strcat(strcat(strcpy(carte_log, LOGDIR), filename), LOG_SUFF);
    carte_data = carte_make_from_file(carte_fullpath, carte_log); 
    if (carte_data == NULL) { 
      messerr("ERREUR: Le fichier de description de carte n'a pas pu être lu et/ou analysé: '%s'" "\n", carte_fullpath); 
      messerr("        Veuillez vous reporter au compte-rendu rendant compte de cette tentative échouée: '%s'" "\n", carte_log); 
      return -1; 
    }; 
  }; 
  
  if (!SCRIPT_EstEnTrainDExecuterUnScript()) {
    SCRIPT_JouerMusique(carte_data -> musique); 
  }; 
  
  
  // *** GROUND *** 
  this_parent -> ZEau = carte_data -> niveau_eau; 
  //this -> ChargerZ(this, map_i, map_j, our_manifold, carte_data -> fichier_de_zone_de_niveau); 
  this_parent -> ChargerZ(this_parent, map_i, map_j, our_manifold, carte_data -> fichier_de_zone_de_niveau); 
  message("Chargement en mémoire de %d textures pour le sol." "\n", carte_data -> texture_nb); 
  if (carte_data -> texture_nb >= NB_MAX_TEXTURESOL) { 
    messerr("ERREUR: Il n'y pas assez d'emplacements pour charger les textures du sol - [carte_data_textures = %d][NB_MAX_TEXTURES = %d]" "\n", carte_data -> texture_nb, NB_MAX_TEXTURESOL);
    return -1; 
  }; 
  for (int i = 0; i < carte_data -> texture_nb; i++) { 
    message("Chargement en mémoire de la texture %3d (couleur associée = %09d - fichier image = \"%s\")." "\n", i, carte_data -> texture_indice[i], carte_data -> texture_image[i]); 
    this_parent -> AjouterTextureSol(this_parent, carte_data -> texture_image[i], carte_data -> texture_indice[i]); 
  }; 
  this_parent -> ChargerIndiceTextureBitmap(this_parent, carte_data -> fichier_de_zone_de_texture); 
  
  
  this -> lattice_width  = this_parent -> TailleX; 
  this -> lattice_height = this_parent -> TailleY; 

  this -> over_spanning_w = this -> lattice_width  / 32; 
  this -> over_spanning_h = this -> lattice_height / 32; 
  
  this -> global_map_i = map_i; 
  this -> global_map_j = map_j; 
  

  const int TailleX = 1; //this_parent -> TailleX; 
  const int TailleY = 1; //this_parent -> TailleY; 
  
  
  // *** SCENERY OBJECTS & LIVING OBJECTS *** 
  for (int i = 0; i < carte_data -> objet_nb; i++) { 
    if (carte_data -> objet_anime_huh[i]) { 
      CBonhomme    * bonhomme = CBonhomme__make(carte_data -> objet_fichier[i]); 
      CPhysicalObj * o        = (CPhysicalObj *) bonhomme; 
      o    -> SetPosition_vP3D(o, TPoint3D_make_struct(carte_data -> objet_x[i] / (float)TailleX, carte_data -> objet_y[i] / (float)TailleY, carte_data -> objet_z[i]), this); 
      this -> AjouterObjet_nom(this, carte_data -> objet_nom[i], o);
      continue; 
    }
    else {
      CObjNonAnime * nonanime = CObjNonAnime__make(carte_data -> objet_fichier[i]);
      CPhysicalObj * o        = (CPhysicalObj *) nonanime; 
      o -> SetPosition_vP3D(o, TPoint3D_make_struct(carte_data -> objet_x[i] / (float)TailleX, carte_data -> objet_y[i] / (float)TailleY, carte_data -> objet_z[i]), this); 
      this -> AjouterObjet_nom(this, carte_data -> objet_nom[i], o);
      continue; 
    }; 
  }; 


  // *** TELEPORTATION AREAS *** 
  for (int i = 0; i < carte_data -> teleportation_nb; i++) { 
    this -> AjouterZoneTeleportation(this, 
        TPoint3D_make_struct(carte_data -> teleportation_x[i]        / (float)TailleX, carte_data -> teleportation_y[i]       / (float)TailleY, carte_data -> teleportation_z[i]), 
        TPoint3D_make_struct(carte_data -> teleportation_longueur[i] / (float)TailleX, carte_data -> teleportation_largeur[i] / (float)TailleY, carte_data -> teleportation_hauteur[i]), 
        carte_data -> teleportation_direction[i], 
        carte_data -> teleportation_destination[i], 
        TPoint3D_make_struct(carte_data -> teleportation_destination_x[i], carte_data -> teleportation_destination_y[i], carte_data -> teleportation_destination_z[i]), 
        carte_data -> teleportation_destination_direction[i]); 
  }; 
  
  // *** EVENTS *** 
  for (int i = 0; i < carte_data -> events_nb; i++) { 
    //AddTraitementEvenement((type_evt)carte_data -> events_genere[i], carte_data -> events_gestion_fichier[i], carte_data -> events_gestion_proc[i]); 
    EvenementsModule -> AddTraitement((type_evt)carte_data -> events_genere[i], carte_data -> events_gestion_fichier[i], carte_data -> events_gestion_proc[i]); 
  }; 
  
  
  
  carte_delete(carte_data); 
  
  return 0; 
}; 














