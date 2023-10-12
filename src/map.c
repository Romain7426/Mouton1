#include "global.h"
#include "map.h"
#include "015_game_events.h" 
#include "010_game.h" 
#include "physicalobj.h"
#include "objnonanime.h"
#include "bonhomme.h"
#include "evenement.h"
#include <carte.h>

// RL: A 'CMap' is a big array containing all the items on the ground (and in the sky?) - it's a local world: 
//      * Fixed objects 
//      * NPCs 
//      * teleportation areas 
//      * anything 
// 
//     There's really nothing related to OpenGL here. In the spirit, it's a big array. 
// 
// RL: Inside we have two main structures: 
//      * 'Voisinages', which contains all the objects. 
//      * 'ZonesTeleportation', which contains the gates. 
//      * And that's it! 
// 

//#define VOISINAGE_IS_TAB
enum { VOISINAGE_X_SIZE =   63 }; 
enum { VOISINAGE_Y_SIZE =   63 }; 
enum { VOISINAGE_SIZE   =   63 }; 
enum { DicoObjets_SIZE  = 2048 }; 
enum { ZonesTeleportation_SIZE = 32 }; 
struct CMap { 
  char * NomCarte; 
  
  // RL: lattice-coordinates are the game-level designers coordinates. 
  //     3DS, villages, objects, animes, everything, is in lattice-coordinate. 
  // RL: For computation purposes, there are two other coordinate systems: (i) map, (ii) manifold. 
  //      (ii) Manifold-coordinates should never be seen by any user whatsoever, they should never be used ever in the game. 
  //           They are only used when rendering, when all the objects are actually mapped onto the riemannian manifold. 
  //           They should be absolutely transparent, never directly manipulated, and invisible to any user or developer (manifold-developers excepted, obviously). 
  //       (i) Map-coordinates should never be used by any gameplay developer. 
  //           However, when mapping to the ground and to the manifold, the ground and the manifold are agnostic about the lattice coordinates. 
  //           Before giving them any coordinates, the lattice coordinates should be normalized. 
  //           So map-coordinates are used as a uniform communication between different coordinate systems. 
  //           They are normalized coordinates. 
  //           The idea is that the lattice coordinates (0,lattice_height) are the map coordinates (0, over_spanning_h). 
  //     In any case, if one does not know which one to use, it means that he wants the lattice-coordinate system. 
  // RL: NB: The physical engine & newton engine is also in lattice coordinates. 
  
  uint8_t lattice_width ; // RL: In vertices, not in cells. 
  uint8_t lattice_height; // RL: In vertices, not in cells. 
  
  uint8_t over_spanning_w; // RL: If this local map is bigger than a simple map. In this case, it spans over 'over_spanning_w' in width. 
  uint8_t over_spanning_h; // RL: If this local map is bigger than a simple map. In this case, it spans over 'over_spanning_h' in height. 
  
  uint8_t global_map_i; // RL: In the global map of the world, this map is #'global_map_i' on the  width-axis. 
  uint8_t global_map_j; // RL: In the global map of the world, this map is #'global_map_j' on the height-axis. 
  // RL: 'global_map_i' & 'global_map_j' are only used when rendering, when mapping data onto the manifold (by definition, the position on the manifold is not agnostic). 
  //     They should be ignored anywhere else. 
  
  // RL: Scale factors to change lattice coordinates to map coordinates (map coordinates are the normalized ones). 
  float lattice_to_map_scale_factor__x; // RL: Computed 
  float lattice_to_map_scale_factor__y; // RL: Computed 
  float lattice_to_map_scale_factor__z; // RL: Computed 
  // RL: NB: z-coordinate needs to be rescaled as well:  
  //           All objects z-dimensions are proportional to their x-dimensions & y-dimensions. 
  //           So, when mapping to map-coordinates, the z-dimensions need to be rescaled as well. 
  //           For instance, if 'lattice_width' & 'lattice_height' are both doubled, then the x-dimensions and the 
  //           y-dimensions would be divided by two; but, if not rescaled, z-dimensions would not be so, meaning 
  //           that objects would look twice as high. 
  //           Therefore, z-dimensions need to be rescaled as well. 
  
  

  // RL: Ground 
  CSol * Sol; 
  
  
  // RL: Objects (scenery & animated) in the maps 
  // RL: TODO XXX FIXME: Management is bad. 
  // RL: Supposedly, there is a neighborhood management. 
  CPhysicalObj * Voisinages_array[VOISINAGE_X_SIZE][VOISINAGE_Y_SIZE][VOISINAGE_SIZE]; 
  // RL: This is for looking up map-objects by names. 
  CPhysicalObj * objets_array     [DicoObjets_SIZE]; 
  char *         objets_noms_array[DicoObjets_SIZE]; 
  int16_t        objets_nb; 
  
  
  
  // RL: Gateways between maps. 
  CZoneTeleportation * ZonesTeleportation_array[ZonesTeleportation_SIZE]; 
  int ZonesTeleportation_nb; 
  
  
  // Ça c pour la gestion des eveneents. 
  //evenements_t evt_carte; 
  //struct tab_evt_bool (* tab_evt_carte)(struct CMap * this);
  
  
  
  
  
  
  
  
  
  // *** METHODS *** 
  
  void (* delete)(CMap * this);
  const char * (* GetNomCarte)(const struct CMap * this);

  //void (* Life)(struct CMap * this, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau); 
  //void (* Life)(const CMap * this, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y); 
  void (* Life)(CMap * this, const bool EnVaisseau); 
  //void (* Render)(const struct CMap * this, const riemann_t * our_manifold, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau); 
  //void (* Render)(const CMap * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y, const bool EnVaisseau); 
  void (* Render)(const CMap * this, const CCamera * Camera, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau); 
  //void (* Render)(const CMap * this, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y); 
  
  
  float (* GETZ0_vXY )(const CMap * this, const float lattice_x, const float lattice_y); 
  float (* GETZ0_vP3D)(const CMap * this, const TPoint3D lattice_pos); 
  
  float (* GET_ZEau)(const CMap * this); 
  
  void           (* AjouterObjet           )(struct CMap * this, CPhysicalObj * o); 
  void           (* AjouterObjet_nom       )(struct CMap * this, const char * nom, CPhysicalObj * o); 
  CPhysicalObj * (* RetrouverObjetViaSonNom)(struct CMap * this, const char * nom); 
  
  const CZoneTeleportation * (* VaTonBouger             )(const CMap * this, const CPhysicalObj * aHero);
  void                       (* AjouterZoneTeleportation)(      CMap * this, const TPoint3D position, const TPoint3D dimension, const TDirection depart_direction, const char * destination_carte, const TPoint3D destination_position, const TDirection destination_direction);   
  
  void (* AjouterParticules)(struct CMap * this, TPoint3D p, const char * nom, const bool MoteurPhysiqueActif);
  
  void (* TraiterOrdresDeplacement)(struct CMap * this, struct CBonhomme * aHero, const bool MoteurPhysiqueActif);
  
  
  
  //void (* TesterPosition)(struct CMap * this, CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
  //CPhysicalObj * (* TesterPositionHero)(struct CMap * this, struct CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
  
}; 

const int32_t CMap_bytesize_actual = sizeof(struct CMap); 
ASSERT_COMPILE_TOPLEVEL(CMap_bytesize >= CMap_bytesize_actual); 



float          CMap__lattice_to_map_scale_factor__x(const CMap * this) { return this -> lattice_to_map_scale_factor__x; };  
float          CMap__lattice_to_map_scale_factor__y(const CMap * this) { return this -> lattice_to_map_scale_factor__y; };  
float          CMap__lattice_to_map_scale_factor__z(const CMap * this) { return this -> lattice_to_map_scale_factor__z; };  
uint8_t        CMap__lattice_width(const CMap * this) { return this -> lattice_width; };  
uint8_t        CMap__lattice_height(const CMap * this) { return this -> lattice_height; };  
const CSol *   CMap__Sol(const CMap * this) { return this -> Sol; };  
      CSol *   CMap__Sol_mutable(CMap * this) { return this -> Sol; };  
uint8_t        CMap__global_map_i(const CMap * this) { return this -> global_map_i; };  
uint8_t        CMap__global_map_j(const CMap * this) { return this -> global_map_j; };  



TDirection DirectionAleatoire(void) {
  //return (TDirection) (rand() % 4);
  return (TDirection) (arc4random_uniform(4));
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


#define PARCOURS_OBJETS__TRIANGLE__DEBUT(__iii0__,__jjj0__,__kkk0__)		\
  {									\
  int iii = (__iii0__);							\
  int jjj = (__jjj0__);							\
  int kkk = (__kkk0__);							\
  for (; iii < VOISINAGE_X_SIZE; iii++, jjj = 0)			\
    for (; jjj < VOISINAGE_Y_SIZE; jjj++, kkk = 0)			\
      for (; kkk < VOISINAGE_SIZE; kkk++)				\
        {								\
  CPhysicalObj * o_parcours = this -> Voisinages_array[iii][jjj][kkk];	\
  if (o_parcours == NULL)						\
    continue;



#define PARCOURS_OBJETS_FIN }

#define PARCOURS_OBJETS__TRIANGLE__FIN }; }; 



#if 0 

#define PARCOURS_ZONESTELEPORTATIONS                                    \
  for (CAccesseur<CZoneTeleportation> a = ZonesTeleportation.ObtenirAcces(); not(a.IsFin()); a.AllerSuivant())
 
#elif 0  

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
  ASSIGN_METHOD(CMap,this,GET_ZEau); 

  // CSol(EnVaisseau)
  //CSol_make_aux(this -> Sol, EnVaisseau); 
  //CSol_module -> make_content(this -> Sol, EnVaisseau); 
  this -> Sol = CSol_module -> make(); 
  
  
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

  //printf("Constructeur CMap(%s)\n", filename);

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
    //printf("nom de fichier réel: %s\n", reelfile); 
    
    //int ret = CMap__parse(this, CARTESDIR, filename); 
    const int ret = CMap__ReadDescriptionFile(this, map_i, map_j, our_manifold, CARTESDIR, filename); 
    if (ret){ 
      messerr("échec de l'analyse du fichier \"%s\"." "\n", reelfile); 
      assert(false); 
    } 
    else { 
      message("<<< analyse ok du fichier \"%s\"." "\n", reelfile); 
    }; 
    free(reelfile); 
  }; 
  
  //printf("Fin de la construction CMap__CMap()\n"); 
  
  Game_Events_Raise(GAME_EVENTS__MAP__LOADED_STARTING_FADING); 

  return this; 
}; 


void CMap__delete(CMap * this) { 
  //printf("Destruction de la carte %p\n", this); 
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
  const float map_x = lattice_x * this -> lattice_to_map_scale_factor__x; // / this -> lattice_width;
  const float map_y = lattice_y * this -> lattice_to_map_scale_factor__y; // / this -> lattice_height; 
  const float map_z = CSol__GET_MAP_Z(this -> Sol, map_x, map_y); 
  const float lattice_z = map_z / this -> lattice_to_map_scale_factor__z; 
  return lattice_z; 
}; 

float CMap__GETZ0_vP3D(const CMap * this, const TPoint3D lattice_pos) { 
  return CMap__GETZ0_vXY(this, lattice_pos.x, lattice_pos.y); 
}; 

float CMap__GET_ZEau(const CMap * this) { 
  return CSol__map_ZEau(this -> Sol) / this -> lattice_to_map_scale_factor__z; 
}; 



static void CMap__NormalizePosition(CMap * this, CPhysicalObj * o) { 
  if (NULL == o) { return; }; 
  
  // RL: Normalizing its position. 
  { 
    o -> p.x = MAX(0, MIN(this -> lattice_width , o -> p.x)); 
    o -> p.y = MAX(0, MIN(this -> lattice_height, o -> p.y)); 
    o -> z0  = this -> GETZ0_vP3D(this, o -> p); 
    o -> p.z = MAX(o -> z0, o -> p.z); 

    o -> np   = o -> p; 
    o -> z0_n = o -> z0; 
  }; 

}; 


void CMap__AjouterObjet(CMap * this, CPhysicalObj * o) { 
  //printf("Ajout de l'objet physique (pointeur: %p; filename: %s) à la carte\n", o, o == NULL ? "<NULL object>" : o -> filename);
  if (NULL == o) { return; }; 

  const TPoint3D lattice_pos = o -> GetPosition(o);
  
  //printf("Taille de la carte en sommets (treilli): %d x %d" "\n", this -> lattice_width, this -> lattice_height); 
  //printf("Position de l'objet: %f x %f" "\n", lattice_pos.x, lattice_pos.y); 
  
  if (!(o -> Fixe_huh)) {
    //printf("RL: On ajoute un objet qui se déplace." "\n"); 
    //printf("    On l'ajoute donc dans le voisinage trivial." "\n"); 
    int added_huh = false; 
    for (int iv = 0; iv < VOISINAGE_SIZE; iv++) { 
      if (NULL != this -> Voisinages_array[0][0][iv]) continue; 
      this -> Voisinages_array[0][0][iv] = o; 
      added_huh = true; 
      break; 
    };
#if 1 
    if (!added_huh) { 
      messerr("Je n'ai pas trouvé d'emplacement libre dans le voisinage %d x %d pour l'object '%s'." "\n", 0, 0, o -> filename); 
      // RL: TODO XXX FIXME: Memory leak as 'o' won't be owned by anyone. 
    }; 
#else 
    assert(added_huh); 
#endif 
  } 
  else { 
    //printf("RL: On ajoute un objet qui ne bouge pas." "\n"); 
    const int ix = MIN(VOISINAGE_X_SIZE - 1,((int) (lattice_pos.x / taille_case))); 
    const int iy = MIN(VOISINAGE_Y_SIZE - 1,((int) (lattice_pos.y / taille_case))); 
    //printf("    On l'ajoute donc dans le voisinage: %d x %d " "\n", ix, iy); 
    int added_huh = false; 
    for (int iv = 0; iv < VOISINAGE_SIZE; iv++) { 
      if (NULL != this -> Voisinages_array[ix][iy][iv]) continue; 
      this -> Voisinages_array[ix][iy][iv] = o; 
      added_huh = true; 
      break; 
    }; 
#if 1 
    if (!added_huh) { 
      messerr("Je n'ai pas trouvé d'emplacement libre dans le voisinage %d x %d pour l'object '%s'." "\n", ix, iy, o -> filename); 
      // RL: TODO XXX FIXME: Memory leak as 'o' won't be owned by anyone. 
    }; 
#else 
    assert(added_huh); 
#endif 
  }; 
  
  //printf("Ajout de l'objet physique réussi!!\n"); 
}; 
 
 

void CMap__AjouterObjet_nom(CMap * this, const char * nom, CPhysicalObj * o) {
  //printf("Ajout de l'objet physique (pointeur %p) à la carte, de nom %s \n", o, nom); 
  this -> AjouterObjet(this, o); 
  
  assert(this -> objets_nb < DicoObjets_SIZE); 
  this -> objets_array[this -> objets_nb] = o; 
  this -> objets_noms_array[this -> objets_nb] = strcopy(nom); 
  this -> objets_nb++; 
  
  //printf("Ajout de l'objet physique réussi!!" "\n"); 
}; 
 
void CMap__Dico_EnleverObjet(CMap * this, CPhysicalObj * o) { 
  //printf("Enlèvement de l'objet physique (pointeur %p) à la carte " "\n", o); 
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

#if 0
  printf("Ajout d'une zone de téléportation \n");
  printf(" position: (%f, %f, %f)\n", position.x, position.y, position.z);
  printf(" dimension: (%f, %f, %f)\n", dimension.x, dimension.y, dimension.z);
#endif 

  assert(this -> ZonesTeleportation_nb < ZonesTeleportation_SIZE); 
  this -> ZonesTeleportation_array[this -> ZonesTeleportation_nb] = zt;
  this -> ZonesTeleportation_nb++; 
}; 

const CZoneTeleportation * CMap__VaTonBouger(const CMap * this, const CPhysicalObj * aHero) { 
  const TPoint3D p = aHero -> GetPosition(aHero);
  for (int izt = 0; izt < this -> ZonesTeleportation_nb; izt++) { 
    const CZoneTeleportation * zt_parcours = this -> ZonesTeleportation_array[izt]; 
    const bool dedans_huh = CZoneTeleportation__dedans_huh(zt_parcours, p); 
    if (dedans_huh) return zt_parcours; 
  }; 
  return NULL;
}; 


void CMap__TraiterOrdresDeplacement(CMap * this, CBonhomme * aHero, const bool MoteurPhysiqueActif) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " >>> this = %p - aHero = %p - MoteurPhysiqueActif = %s "   "\n", __func__, this, aHero, MoteurPhysiqueActif ? "TRUE":"FALSE"); 

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













//#define NB_PARTICULES 10 
enum { NB_PARTICULES = 10 }; //10 }; 
CBonhomme * particule = NULL; 
void CMap__AjouterParticules(CMap * this, const TPoint3D p, const char * nom, const bool MoteurPhysiqueActif) {
  //printf("Ajout d'une flopée de particules au point (%f, %f, %f,) \n...", p.x, p.y, p.z);

  for (int i = 0; i < NB_PARTICULES; i++) { 
    CBonhomme    * b = CBonhomme__make(nom); 
    //particule = b; 
    CPhysicalObj * o = &b -> parent1; 
    o -> SetDimension(o, 0.0f,0.0f,0.0f); 
    //o -> SetPosition_vP3D(o, p, this); 
    o -> SetPosition_vXYZ(o, p.x, p.y, p.z + 2.0f, this); 
    o -> SetObjetEphemere(o, 127); 
    o -> Hostile_huh = false; 
    const TPoint3D pp = o -> GetPosition(o); 
    //printf("Coordonnées de la particule : (%f, %f, %f,) \n", pp.x, pp.y, pp.z); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, o, pp.x, pp.y, pp.z); 
#if 1
#define GENFORCE ((float) (arc4random_uniform(2000)-1000)) / 100.0f 
    //o -> Force_massique__add_vXYZ(o, GENFORCE, GENFORCE, 10.0f); 
    //o -> Force_massique__add_vXYZ(o, 0.0f, 0.0f, 60.0f); 
    o -> Force_massique__add_vXYZ(o, GENFORCE, GENFORCE, 60.0f); 
#else  
    o -> InitForce(o); 
#define GENPOS ((float) (rand()%2000-1000)) / 200.0f 
    o -> AddForce_vXYZ(o, GENPOS, GENPOS, 100.0f); 
    //o -> CalcNewPosition(o); 
    //o -> ValiderPosition(o, MoteurPhysiqueActif); 
#endif 
    this -> AjouterObjet(this, o); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Coordonnées de la particule %p : (%f, %f, %f) "  "\n", __func__, o, o -> p.x, o -> p.y, o -> p.z); 
    o -> np = o -> p; 
  }; 
  
  //printf("Ajout des particules effectué!\n");
};



void CMap__Life(CMap * this, const bool EnVaisseau) { 
  CSol__Life(this -> Sol); 
  // RL: TODO XXX FIXME 

  // RL: Éclaboussures eau 
#if 0 
  if (this -> Sol -> yatilEau(this -> Sol, map_x, map_y, map_z)) { 
    if (!(o -> DansEau_huh)) { 
      //printf(" L'objet %p va rentrer dans l'eau. Sa position est la suivante : %f, %f, %f. Nous allons générer une floppée de particules d'eau.\n", o, i, j, z);
      
      if (not(o -> IsVolumeNul(o))) { 
        this -> AjouterParticules(this, o -> GetPosition(o), "eclaboussures.anime", MoteurPhysiqueActif); 
      }; 
    }; 
  }; 
#endif 

}; 


//void CMap__Life_GamePlay(CMap * this, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau) {
void CMap__Life_GamePlay(CMap * this, const int animate_but_do_not_aliven_huh, const bool EnVaisseau) { 
  if (EnVaisseau) return; 

  int hostile_nb = 0; 
  
  PARCOURS_OBJETS 
  //PARCOURS_OBJETS_VOISINAGES_PROCHE(pos) 
    { 
      if (o_parcours -> Hostile_huh) hostile_nb ++; 
      
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

  if (not(animate_but_do_not_aliven_huh)) { 
    if (0 == hostile_nb) { Game_Events_Raise(GAME_EVENTS__MAP__ALL_HOSTILES_DEAD); }; 
  }; 
};


void CMap__Life_Simulate_Objects(CMap * this, const bool EnVaisseau) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    EnVaisseau     = %s "  "\n", __func__,  EnVaisseau ? "TRUE" : "FALSE" ); 
  
  if (EnVaisseau) return; 

  PARCOURS_OBJETS
    {
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
      //if (o_parcours -> subtype != 2) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours -> subtype = %d "  "\n", __func__, o_parcours -> subtype); }; 
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
	CBonhomme * b = (CBonhomme *) o_parcours; 
        //if (rand() % 40 == 1) { 
	if (arc4random_uniform(100) == 0) { 
	  b -> SetDirection(b, DirectionAleatoire()); 
	}; 
        if (arc4random_uniform(40) < 35) { 
	  // RL: Do not move 
	} 
	else { 
	  b -> Avancer(b, b -> GetDirection(b), /*slow_walk_huh*/false); 
	}; 
      }; 
            
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN; 
}; 

void CMap__Life_NewtonEngine_Objects(CMap * this, const bool EnVaisseau) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    EnVaisseau     = %s "  "\n", __func__,  EnVaisseau ? "TRUE" : "FALSE" ); 
  
  if (EnVaisseau) return; 

  PARCOURS_OBJETS
    {
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
      //if (o_parcours -> subtype != 2) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours -> subtype = %d "  "\n", __func__, o_parcours -> subtype); }; 
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
	CBonhomme * b = (CBonhomme *) o_parcours; 
	CPhysicalObj__NewtonEngine__Frottements_apply(o_parcours); 
	CPhysicalObj__NewtonEngine__OneStepFoward__NoValidationYet(o_parcours); 
	CPhysicalObj__BordersAndGroundAndSlope__AdjustAndCorrectNP(o_parcours, this); 
      }; 
      
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN; 
}; 

void CMap__Life_Objects_ValiderPosition(CMap * this, const bool EnVaisseau) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    EnVaisseau     = %s "  "\n", __func__,  EnVaisseau ? "TRUE" : "FALSE" ); 
  
  if (EnVaisseau) return; 

  PARCOURS_OBJETS
    {
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
      //if (o_parcours -> subtype != 2) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours -> subtype = %d "  "\n", __func__, o_parcours -> subtype); }; 
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
	CBonhomme * b = (CBonhomme *) o_parcours; 
	CPhysicalObj__ValiderPosition(o_parcours, CMap__GET_ZEau(this)); 
      }; 
      
    }
  //FIN_PARCOURS_OBJETS_VOISINAGES;
  PARCOURS_OBJETS_FIN; 
}; 


void CMap__Life_NewtonEngine_ObjectsXXX(CMap * this, const bool EnVaisseau) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    EnVaisseau     = %s "  "\n", __func__,  EnVaisseau ? "TRUE" : "FALSE" ); 
  
  if (EnVaisseau) return; 

  PARCOURS_OBJETS
    {
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
      //if (o_parcours -> subtype != 2) { fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours -> subtype = %d "  "\n", __func__, o_parcours -> subtype); }; 
      if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
	//fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
	CBonhomme * b = (CBonhomme *) o_parcours; 
        //if (rand() % 40 == 1) { 
        if (arc4random_uniform(40) < 10) { 
	  // RL: Do not move 
	} 
	else { 
	  if (arc4random_uniform(40) == 0) { 
	    b -> SetDirection(b, DirectionAleatoire()); 
	  }; 
	  b -> Avancer(b, b -> GetDirection(b), /*slow_walk_huh*/false); 
	}; 
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


#if 1 
void CMap__Life_Choc_Sword(CMap * this, const CPhysicalObj * Hero_o) { 
  //if (EnVaisseau) return; 
  
  const CBonhomme * Hero_b = (const CBonhomme *) Hero_o; 

  if (!(Hero_b -> EnTrainDeFrapper(Hero_b))) return; 
  
#if 1 
  { 
    CPhysicalObj zone_epee = *(Hero_o); 
#if 1 
    switch (Hero_b -> GetDirection(Hero_b)) { 
    case FACE         : zone_epee.np.y -= ldexpf(zone_epee.d.y, 1); break; 
    case DOS          : zone_epee.np.y += ldexpf(zone_epee.d.y, 1); break; 
    case PROFIL_VERS_D: zone_epee.np.x += ldexpf(zone_epee.d.x, 1); break; 
    case PROFIL_VERS_G: zone_epee.np.x -= ldexpf(zone_epee.d.x, 1); break; 
    default: assert(false); 
    }; 
#else 
    TPoint3D d = Hero_o -> GetDimension(Hero_o); 
    zone_epee.SetDimension(&zone_epee, d.x, d.y, d.z); 
    
    TPoint3D dir; 
    switch (Hero_b -> GetDirection(Hero_b)) { 
    case FACE         : dir = TPoint3D_make_struct( 0.0f, -2*d.y, 0.0f); break; 
    case DOS          : dir = TPoint3D_make_struct( 0.0f,  1.0f, 0.0f); break; 
    case PROFIL_VERS_D: dir = TPoint3D_make_struct( 1.0f,  0.0f, 0.0f); break; 
    case PROFIL_VERS_G: dir = TPoint3D_make_struct(-1.0f,  0.0f, 0.0f); break; 
    default: assert(false); 
    }; 
      
    //zoneepee.SetPosition(&zoneepee, Hero_o -> GetPosition(Hero_o) + dir); 
    const TPoint3D hero_pos = Hero_o -> GetPosition(Hero_o); 
    zone_epee.SetPosition_vP3D(&zone_epee, TPoint3D_add__macro(hero_pos, dir), this); 
#endif 
      
      //PARCOURS_OBJETS_VOISINAGES_PROCHE(Hero->GetPosition()) 
      PARCOURS_OBJETS 
        { 
#if 0 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours = %p "  "\n", __func__,  o_parcours); 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours -> subtype = %d (anime_subtype = %d) "  "\n", __func__, o_parcours -> subtype, CPhysicalObj_subtype_CBonhomme); 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " o_parcours[%d][%d][%d] = %s "  "\n", __func__,  iii, jjj, kkk, o_parcours -> filename); 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Volume(o_parcours[%d][%d][%d]) = %f "  "\n", __func__, iii, jjj, kkk, o_parcours -> volume); 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " VolumeNul?(o_parcours[%d][%d][%d]) = %s "  "\n", __func__, iii, jjj, kkk, o_parcours -> IsVolumeNul(o_parcours) ? "TRUE" : "FALSE" ); 
#endif 

  	  if (CPhysicalObj_subtype_CBonhomme != o_parcours -> subtype) { continue; }; 
          if (o_parcours -> IsVolumeNul(o_parcours)) { continue; }; 
	  CBonhomme * b = (CBonhomme *) o_parcours; 
	  if (b -> EstInvisible(b)) { continue; }; 
	  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " EstInvisible?(o_parcours[%d][%d][%d]) = %s "  "\n", __func__, iii, jjj, kkk, b -> EstInvisible(b) ? "TRUE" : "FALSE" ); 
#if 1 
	  const int where = CPhysicalObj__DoTheyIntersect_huh(&zone_epee, o_parcours); 
#if 0 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " WHERE = %d "  "\n", __func__, where ); 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " where = %d - %d - %d "  "\n", __func__,  where & 1, where & 2, where & 4 ); 
	  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " hero_o.x,y = %f,%f [%f,%f] - épée_o.x,y = %f,%f [%f,%f] - o_parcours.x,y = %f,%f [%f,%f]  "  "\n", __func__, Hero_o -> np.x, Hero_o -> np.y, Hero_o -> d.x, Hero_o -> d.y, zone_epee.np.x, zone_epee.np.y, zone_epee.d.x, zone_epee.d.y, o_parcours -> np.x, o_parcours -> np.y, o_parcours -> d.x, o_parcours -> d.y); 
#endif 
	  if (7 != where) { continue; }; 
	  // RL: We got an intersection! 
	  o_parcours -> PerdrePV(o_parcours, 1); 
	  this -> AjouterParticules(this, o_parcours -> GetPosition(o_parcours), "sang.anime", /*MoteurPhysiqueActif*/true); 
#if 1 
	  switch (Hero_b -> GetDirection(Hero_b)) { 
	  case FACE         : o_parcours -> Force_massique__add_vXYZ(o_parcours,   0.0f, -10.0f, 0.0f); break; 
	  case DOS          : o_parcours -> Force_massique__add_vXYZ(o_parcours,   0.0f,  10.0f, 0.0f); break; 
	  case PROFIL_VERS_D: o_parcours -> Force_massique__add_vXYZ(o_parcours,  10.0f,   0.0f, 0.0f); break; 
	  case PROFIL_VERS_G: o_parcours -> Force_massique__add_vXYZ(o_parcours, -10.0f,   0.0f, 0.0f); break; 
	  default: assert(false); 
	  }; 
#else 
	  o_parcours -> Force_massique__add_vP3D(o_parcours, TPoint3D_scale__macro(10.0f, dir)); 
#endif 
	  b -> DevenirInvisible(b, 50); 
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
	  
	  return; 
        }
      //FIN_PARCOURS_OBJETS_VOISINAGES;
      PARCOURS_OBJETS_FIN;
    };
    
#endif
}; 
#else 
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
#endif 


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

#if 0 
  if (unennemiestdecede && (nb_ennemis == 0)) {
    //RaiseEvenement(EVT_PlusEnnemi); 
    EvenementsModule -> Raise(EVT_PlusEnnemi); 
  }; 
#endif 
}; 






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
#define norme_minimum_pour_etre_proche 3.0f 
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




bool CMap__ChocEngine_HeroGotHostileEncounterHuh_one(CMap * this, const CPhysicalObj * hero_o) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Hero_o = %p "  "\n", __func__,  Hero_o ); 

  PARCOURS_OBJETS { 
    if ( o_parcours -> is_objet_ephemere) { continue; }; 
    if (!o_parcours -> Hostile_huh) { continue; }; 
    if ( o_parcours -> IsVolumeNul(o_parcours)) { continue; }; 
    if ( o_parcours -> subtype != CPhysicalObj_subtype_CBonhomme) { continue; }; 
    // RL: If the objects do not intersect on one coordinate, then they do not intersect. 
    const int where = CPhysicalObj__DoTheyIntersect_huh(hero_o, o_parcours); 
    if (where == 7) return true; 
  } PARCOURS_OBJETS_FIN; 
  
  return false; 
}; 



void CMap__ChocEngine_OneObject(CMap * this, const CPhysicalObj * hero_o, CPhysicalObj * this_o, const int iii0, const int jjj0, const int kkk0) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Hero_o = %p "  "\n", __func__,  Hero_o ); 

  if (this_o != hero_o) { 
    const int where = CPhysicalObj__DoTheyIntersect_huh(this_o, hero_o); 
    if (7 == where) { 
      this_o -> np = this_o -> p; 
      return ; 
    }; 
  }; 
  
  // RL: That's dumb, as it does not take into account the immovable objects... 
  //PARCOURS_OBJETS__TRIANGLE__DEBUT(iii0,jjj0,kkk0) { 
  PARCOURS_OBJETS__TRIANGLE__DEBUT(0,0,0) { 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this_o = %s - o_parcours[%d][%d][%d] = %s "  "\n", __func__,  this_o -> filename, iii, jjj, kkk, o_parcours -> filename); 
#if 1 
    if (this_o == o_parcours) { continue; }; 
#else 
    assert(this_o != o_parcours); 
#endif 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Volume(o_parcours[%d][%d][%d]) = %f "  "\n", __func__, iii, jjj, kkk, o_parcours -> volume); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " VolumeNul?(o_parcours[%d][%d][%d]) = %s "  "\n", __func__, iii, jjj, kkk, o_parcours -> IsVolumeNul(o_parcours) ? "TRUE" : "FALSE" ); 
    if (o_parcours -> IsVolumeNul(o_parcours)) { continue; }; 
    // RL: If the objects do not intersect on one coordinate, then they do not intersect. 
    const int where = CPhysicalObj__DoTheyIntersect_huh(this_o, o_parcours); 
#if 0 
    if (0 == strcmp(o_parcours -> filename, "maison03.nonanime")) { 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " VolumeNul?(o_parcours[%d][%d][%d]) = %s "  "\n", __func__, iii, jjj, kkk, o_parcours -> IsVolumeNul(o_parcours) ? "TRUE" : "FALSE" ); 
      fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this_o.x,y = %f,%f,%f [%f,%f,%f] - o_parcours.x,y = %f,%f,%f [%f,%f,%f]  "  "\n", __func__,  this_o -> np.x, this_o -> np.y, this_o -> np.z, this_o -> d.x, this_o -> d.y, this_o -> d.z, o_parcours -> np.x, o_parcours -> np.y, o_parcours -> np.z, o_parcours -> d.x, o_parcours -> d.y, o_parcours -> d.z); 
      fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " where = %d - %d - %d "  "\n", __func__,  where & 1, where & 2, where & 4 ); 
    }; 
#endif 
#if 1 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " where = %d - %d - %d "  "\n", __func__,  where & 1, where & 2, where & 4 ); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this_o.x,y = %f,%f [%f,%f] - o_parcours.x,y = %f,%f [%f,%f]  "  "\n", __func__,  this_o -> np.x, this_o -> np.y, this_o -> d.x, this_o -> d.y, o_parcours -> np.x, o_parcours -> np.y, o_parcours -> d.x, o_parcours -> d.y); 
    if (7 != where) { continue; }; 

    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this_o = %s - o_parcours[%d][%d][%d] = %s "  "\n", __func__,  this_o -> filename, iii, jjj, kkk, o_parcours -> filename); 
    
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this_o.x,y = %f,%f [%f,%f] - o_parcours.x,y = %f,%f [%f,%f]  "  "\n", __func__,  this_o -> np.x, this_o -> np.y, this_o -> d.x, this_o -> d.y, o_parcours -> np.x, o_parcours -> np.y, o_parcours -> d.x, o_parcours -> d.y); 
    
#if 0 
    int * a; a = NULL; 
    *a = 1; 
    //(*((int *) ((int)floorf(0.5f)))) = 1; 
#endif 
    
    this_o     -> np = this_o     -> p; 
    //o_parcours -> np = o_parcours -> p; 
    return; 

#else 
    if (0 == where) { continue; }; 

    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " where = %d - %d - %d "  "\n", __func__,  where & 1, where & 2, where & 4 ); 
      
    if (0 != (where & 1)) { 
      this_o     -> np.x = this_o     -> p.x; 
      o_parcours -> np.x = o_parcours -> p.x; 
    }; 
    
    if (0 != (where & 2)) { 
      this_o     -> np.y = this_o     -> p.y; 
      o_parcours -> np.y = o_parcours -> p.y; 
    }; 
    
    if (0 != (where & 4)) { 
      this_o     -> np.z = this_o     -> p.z; 
      o_parcours -> np.z = o_parcours -> p.z; 
    };
#endif  
    
  } PARCOURS_OBJETS__TRIANGLE__FIN; 
  
}; 


// RL: It's a quadratic function... Any idea? 
// RL:  - Yep: they could be pre-sorted by size: very big objects are tested at every loop, while small ones aren't. 
// RL:  - On the ground, we could that they are some forbidden locations. 
// RL:  - Organize the map by neighborhood. However that does change anything at the size issue. Because a big object could in a far neighborhood, so not tested, while should be so. 
//        Or an object could show up in multiple neighborhoods: all the ones in which he is. That's better. 
// RL: TODO XXX FIXME: Scenery objects should be considered like the ground - especially on the z-coordinate, so that the hero could walk 
//     on roofs (for instance); because, as of now, he cannot the gravity invalidates its position at every passes. 
void CMap__ChocEngine_MapObjects(CMap * this, const CPhysicalObj * hero_o) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Hero_o = %p "  "\n", __func__,  Hero_o ); 
  
  PARCOURS_OBJETS 
    { 
      // RL: Only 'anime' objects were moved. 
      if (CPhysicalObj_subtype_CBonhomme != o_parcours -> subtype) { continue; }; 
      CMap__ChocEngine_OneObject(this, hero_o, o_parcours, iii, jjj, kkk+1); 
    } 
  PARCOURS_OBJETS_FIN; 
  
}; 


void CMap__ChocEngine(CMap * this, CPhysicalObj * Hero_o) { 
  CMap__ChocEngine_OneObject(this, Hero_o, Hero_o, /*iii0*/0, /*jjj0*/0, /*kkk0*/0); 
  CMap__ChocEngine_MapObjects(this, Hero_o); 
}; 






















#if 1 

#else 
/*on informe la carte de la position du héro

  en retour, elle nous offre un pointeur vers l'élément le plus proche
  OU NULL si trop loin
*/
CPhysicalObj * CMap__TesterPositionHero(CMap * this, CPhysicalObj * Hero_o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif) {   
  CBonhomme * Hero_b = (CBonhomme *) Hero_o;
  this   -> TesterPosition(this, Hero_o, our_manifold, MoteurPhysiqueActif);
  Hero_o -> ValiderPosition(Hero_o, MoteurPhysiqueActif);
  Hero_o -> InitForce(Hero_o);
  return NULL;
}; 
#endif 






#if 0 
#elif 0 
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
}; 
#endif  


















extern bool show_choc_cube_huh; 

void CMap__Render(const CMap * this, const CCamera * Camera, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau) { 
  //this -> Sol -> Render(this -> Sol, our_manifold, nb_cells_displayed_x, nb_cells_displayed_y, target_map_i, target_map_j, target_lattice_x / (float) this -> lattice_width, target_lattice_y / (float) this -> lattice_height); 
  //this -> Sol -> Render(this -> Sol, our_manifold, target_map_i, target_map_j, target_lattice_x / ((float) this -> lattice_width), target_lattice_y / ((float) this -> lattice_height), ((float) nb_cells_displayed_x) / ((float) this -> lattice_width), ((float) nb_cells_displayed_y) / ((float) this -> lattice_height)); 
  //this -> Sol -> Render(this -> Sol, our_manifold, target_map_i, target_map_j, target_lattice_x * this -> lattice_to_map_scale_factor__x, target_lattice_y * this -> lattice_to_map_scale_factor__y, ((float) nb_cells_displayed_x) * this -> lattice_to_map_scale_factor__x, ((float) nb_cells_displayed_y) * this -> lattice_to_map_scale_factor__y); 
  CSol__Render(this -> Sol, our_manifold, target_map_i, target_map_j, target_lattice_x * this -> lattice_to_map_scale_factor__x, target_lattice_y * this -> lattice_to_map_scale_factor__y, ((float) nb_cells_displayed_x) * this -> lattice_to_map_scale_factor__x, ((float) nb_cells_displayed_y) * this -> lattice_to_map_scale_factor__y); 
  
 

  const TPoint3D pos = TPoint3D_make_struct(target_lattice_x, target_lattice_y, 0.0f); 
  
  
  if (not(EnVaisseau)) {
    //PARCOURS_OBJETS
    PARCOURS_OBJETS_VOISINAGES_PROCHE(pos) 
      {
        if (CPhysicalObj_subtype_CBonhomme == o_parcours -> subtype) { 
          //fprintf(stderr, "Bonhomme: Rendering: %s\n", o_parcours -> filename); 
	  const CBonhomme * b = (const CBonhomme *) o_parcours; 
          //b -> Render(b, this -> lattice_width, this -> lattice_height, our_manifold, Camera); 
	  b -> Render(b, this -> lattice_to_map_scale_factor__x, this -> lattice_to_map_scale_factor__y, this -> lattice_to_map_scale_factor__z, our_manifold, Camera); 
        } 
        else if (CPhysicalObj_subtype_CObjNonAnime == o_parcours -> subtype) { 
	  const CObjNonAnime * nonanime = (const CObjNonAnime *) o_parcours; 
	  //fprintf(stderr, "ObjPhys: Rendering: %s\n", o_parcours -> filename); 
          //nonanime -> Render(nonanime, this -> lattice_width, this -> lattice_height, our_manifold); 
          nonanime -> Render(nonanime, this -> lattice_to_map_scale_factor__x, this -> lattice_to_map_scale_factor__y, this -> lattice_to_map_scale_factor__z, our_manifold); 
        } 
        else { 
          //o_parcours -> Render(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold); 
	  o_parcours -> Render(o_parcours, this -> lattice_to_map_scale_factor__x, this -> lattice_to_map_scale_factor__y, this -> lattice_to_map_scale_factor__z, our_manifold); 
	}; 
	
      }
    //PARCOURS_OBJETS_FIN;
    PARCOURS_OBJETS_VOISINAGES_FIN;
  }
  else { // _ en vaisseau _
    PARCOURS_OBJETS
      {
        const int i = (int) o_parcours -> GetPosition(o_parcours).x; 
        const int j = (int) o_parcours -> GetPosition(o_parcours).y; 
	
	
        //const bool b = ((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        const bool b = true; //((i1 <= i) && (i <= i2) && (j1 <= j) && (j <= j2));
        if (b) { 
          //o_parcours -> Render(o_parcours, this -> lattice_width, this -> lattice_height, our_manifold); 
	  o_parcours -> Render(o_parcours, this -> lattice_to_map_scale_factor__x, this -> lattice_to_map_scale_factor__y, this -> lattice_to_map_scale_factor__z, our_manifold); 
	}; 
      }
    PARCOURS_OBJETS_FIN; 
  }; // _ en vaisseau _ 
  
  
  
  if (show_choc_cube_huh) { 
#if 1 
  for (int izt = 0; izt < this -> ZonesTeleportation_nb; izt++) { 
    const CZoneTeleportation * zt_parcours = this -> ZonesTeleportation_array[izt]; 
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
    TPoint3D zt_position  = CZoneTeleportation__position(zt_parcours); 
    TPoint3D zt_dimension = CZoneTeleportation__dimension(zt_parcours); 
    our_manifold -> AfficherCube(our_manifold, /*map_i*/0, /*map_j*/0, 
      zt_position.x  * this -> lattice_to_map_scale_factor__x, zt_position.y  * this -> lattice_to_map_scale_factor__y, zt_position.z  * this -> lattice_to_map_scale_factor__z, 
      zt_dimension.x * this -> lattice_to_map_scale_factor__x, zt_dimension.y * this -> lattice_to_map_scale_factor__y, zt_dimension.z * this -> lattice_to_map_scale_factor__z); 
  }; 
#elif 0 
    //fprintf(stderr, "ZoneTeleportationBlit\n"); 
    //int i = 0; 
    PARCOURS_ZONESTELEPORTATIONS { 
      //fprintf(stderr, "ZoneTeleportationRender: i = %d\n", i++); 
      if (show_choc_cube_huh) { 
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
	our_manifold -> AfficherCube(our_manifold, /*map_i*/0, /*map_j*/0, zt_parcours -> position.x * this -> lattice_to_map_scale_factor__x, zt_parcours -> position.y * this -> lattice_to_map_scale_factor__y, zt_parcours -> position.z * this -> lattice_to_map_scale_factor__z, zt_parcours -> dimension.x * this -> lattice_to_map_scale_factor__x, zt_parcours -> dimension.y * this -> lattice_to_map_scale_factor__y, zt_parcours -> dimension.z * this -> lattice_to_map_scale_factor__z); 
      }; 
    } PARCOURS_ZONESTELEPORTATIONS_FIN; 
#endif 
  }; 
  
}; 




int CMap__ReadDescriptionFile(CMap * this, const int global_map_i, const int global_map_j, const riemann_t * our_manifold, const char * dir, const char * filename) { 
  carte_t * carte_data  = NULL; 
  CSol    * this_parent = this -> Sol; 
  
  { 
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char carte_fullpath[strlen(dir) + strlen(filename) + 1]; 
    enum { carte_fullpath__bytesize = 1 << 10 }; 
    const size_t carte_fullpath__cstrlen = strlen(dir) + strlen(filename); 
    assert(carte_fullpath__bytesize > carte_fullpath__cstrlen); 
    char carte_fullpath[carte_fullpath__bytesize]; 
    strcat(strcpy(carte_fullpath, dir), filename); 
#define LOG_SUFF ".log" 
    // For some unknown reasons, VLAs & ALLOCAs make «-fstack-protector» fail. 
    //char carte_log[strlen(LOGDIR) + strlen(filename) + strlen(LOG_SUFF) + 1]; 
    enum { carte_log__bytesize = 1 << 10 }; 
    const size_t carte_log__cstrlen = strlen(LOGDIR) + strlen(filename) + strlen(LOG_SUFF); 
    assert(carte_log__bytesize > carte_log__cstrlen); 
    char carte_log[carte_log__bytesize]; 
    strcat(strcat(strcpy(carte_log, LOGDIR), filename), LOG_SUFF); 
    for(;;) { 
      carte_data = carte_make_from_file(carte_fullpath, carte_log); 
      if (NULL != carte_data) { break; }; 
      //if (carte_data == NULL) { 
      { 
	messerr("ERREUR: Le fichier de description de carte n'a pas pu être lu et/ou analysé: '%s'" "\n", carte_fullpath); 
	messerr("        Veuillez vous reporter au compte-rendu rendant compte de cette tentative échouée: '%s'" "\n", carte_log); 
	messerr("        Voulez-vous réessayer?" "\n"); 
	{
	  char c; 
	  const int nb_read = read(stdin_d, &c, 1); 
	  if (0 == nb_read) { continue; }; 
	  if (c == 'n') { return -1; }; 
	  continue; 
	}; 
#if 0 
	{ 
	  SCRIPT_BeginAfficherMenu(); 
	  MiniMenu -> Add(MiniMenu, 0, "Je veux réessayer.", NULL); 
	  MiniMenu -> Add(MiniMenu, 0, "Je veux arrêter.", NULL); 
	  SCRIPT_AfficherMenu("Problème lors de la lecture du ficher de description de carte."); 
	  // RL: Can't do that, as we need to loop in the game engine, while it's blocked here... 
	  //     We should definitely improve that. 
	}; 
#endif 
	return -1; 
      }; 
    }; 
  }; 

#if 0 
  // RL: TODO XXX FIXME 
  SCRIPT_JouerMusique(carte_data -> musique); 
#else 
  if (!SCRIPT_EstEnTrainDExecuterUnScript()) { 
    SCRIPT_JouerMusique(carte_data -> musique); 
  }; 
#endif 
  

  // *** GENERAL DATA *** 
#if 1 
  this -> lattice_width  = carte_data -> lattice_width; 
  this -> lattice_height = carte_data -> lattice_height;

  this -> over_spanning_w = carte_data -> over_spanning_w; 
  this -> over_spanning_h = carte_data -> over_spanning_h; 
#else 
  this -> lattice_width  = this_parent -> TailleX; 
  this -> lattice_height = this_parent -> TailleY; 

  this -> over_spanning_w = this -> lattice_width  / 32; 
  this -> over_spanning_h = this -> lattice_height / 32; 
#endif 
  
  this -> global_map_i = global_map_i; 
  this -> global_map_j = global_map_j; 

  this -> lattice_to_map_scale_factor__x = ((float) this -> over_spanning_w) / ((float) this -> lattice_width ); 
  this -> lattice_to_map_scale_factor__y = ((float) this -> over_spanning_h) / ((float) this -> lattice_height); 
  //this -> lattice_to_map_scale_factor__z = 2.0f / (((float) this -> lattice_width) + ((float) this -> lattice_height)); 
  this -> lattice_to_map_scale_factor__z = (this -> lattice_to_map_scale_factor__x + this -> lattice_to_map_scale_factor__y) / 2.0f; 
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this -> lattice_to_map_scale_factor__x = %f "  "\n", __func__, this -> lattice_to_map_scale_factor__x); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this -> lattice_to_map_scale_factor__y = %f "  "\n", __func__, this -> lattice_to_map_scale_factor__y); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " this -> lattice_to_map_scale_factor__z = %f "  "\n", __func__, this -> lattice_to_map_scale_factor__z); 
#endif 
  
  
  // *** GROUND *** 
  //this_parent -> ZEau = carte_data -> niveau_eau; 
  //this_parent -> map_ZEau = carte_data -> niveau_eau * this -> lattice_to_map_scale_factor__z; 
  *CSol__map_ZEau_ref(this_parent) = carte_data -> niveau_eau * this -> lattice_to_map_scale_factor__z; 
  
  //message("Chargement en mémoire de %d textures pour le sol." "\n", carte_data -> texture_nb); 
  if (carte_data -> texture_nb >= NB_MAX_TEXTURESOL) { 
    messerr("ERREUR: Il n'y pas assez d'emplacements pour charger les textures du sol - [carte_data_textures = %d][NB_MAX_TEXTURES = %d]" "\n", carte_data -> texture_nb, NB_MAX_TEXTURESOL);
    return -1; 
  }; 
  for (int i = 0; i < carte_data -> texture_nb; i++) { 
    //message("Chargement en mémoire de la texture %3d (couleur associée = %09d - fichier image = \"%s\")." "\n", i, carte_data -> texture_indice[i], carte_data -> texture_image[i]); 
    //this_parent -> AjouterTextureSol(this_parent, carte_data -> texture_image[i], carte_data -> texture_indice[i]); 
    CSol__AjouterTextureSol(this_parent, carte_data -> texture_image[i], carte_data -> texture_indice[i]); 
  }; 
  //this_parent -> init(this_parent, global_map_i, global_map_j, /*over_spanning_w*/1, /*over_spanning_h*/1, our_manifold, /*z_filename*/carte_data -> fichier_de_zone_de_niveau, /*texture_filename*/carte_data -> fichier_de_zone_de_texture); 
  //this_parent -> init(this_parent, global_map_i, global_map_j, /*over_spanning_w*/this -> over_spanning_w, /*over_spanning_h*/this -> over_spanning_h, this -> lattice_to_map_scale_factor__z, our_manifold, /*z_filename*/carte_data -> fichier_de_zone_de_niveau, /*texture_filename*/carte_data -> fichier_de_zone_de_texture); 
  CSol__init(this_parent, global_map_i, global_map_j, /*over_spanning_w*/this -> over_spanning_w, /*over_spanning_h*/this -> over_spanning_h, this -> lattice_to_map_scale_factor__z, our_manifold, /*z_filename*/carte_data -> fichier_de_zone_de_niveau, /*texture_filename*/carte_data -> fichier_de_zone_de_texture); 
  
  
#if 1 
  const int TailleX = 1; //this_parent -> TailleX; 
  const int TailleY = 1; //this_parent -> TailleY; 
#endif 
  
  
  // *** SCENERY OBJECTS & LIVING OBJECTS *** 
  for (int i = 0; i < carte_data -> objet_nb; i++) { 
    if (carte_data -> objet_anime_huh[i]) { 
      //continue; 
      //break; 
      //{ static int count = 0; if (count == 0) { count++; continue; }; if (count > 1) break; count++; }; 
      CBonhomme    * bonhomme = CBonhomme__make(carte_data -> objet_fichier[i]); 
      CPhysicalObj * o        = (CPhysicalObj *) bonhomme; 
      o    -> SetPosition_vP3D(o, TPoint3D_make_struct(carte_data -> objet_x[i] / (float)TailleX, carte_data -> objet_y[i] / (float)TailleY, carte_data -> objet_z[i]), this); 
      CMap__NormalizePosition(this, o); 
      this -> AjouterObjet_nom(this, carte_data -> objet_nom[i], o); 
      o    -> np = o -> p; 
      //break; 
      continue; 
    } 
    else { 
      //break; 
      //continue; 
      CObjNonAnime * nonanime = CObjNonAnime__make(carte_data -> objet_fichier[i]); 
      CPhysicalObj * o        = (CPhysicalObj *) nonanime; 
      o    -> SetPosition_vP3D(o, TPoint3D_make_struct(carte_data -> objet_x[i] / (float)TailleX, carte_data -> objet_y[i] / (float)TailleY, carte_data -> objet_z[i]), this); 
      CMap__NormalizePosition(this, o); 
      this -> AjouterObjet_nom(this, carte_data -> objet_nom[i], o); 
      o    -> np = o -> p; 
      nonanime -> angleZ = carte_data -> objet_angle_z[i] / 180.0f * PI; 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " carte_data -> objet_angle_z[i] = %f "  "\n", __func__, carte_data -> objet_angle_z[i]); 
      { 
	const float rotated_dx =   cosf(nonanime -> angleZ) * o -> d.x + sinf(nonanime -> angleZ) * o -> d.y; 
	const float rotated_dy = - sinf(nonanime -> angleZ) * o -> d.x + cosf(nonanime -> angleZ) * o -> d.y; 
	o -> d.x = fabsf(rotated_dx); 
	o -> d.y = fabsf(rotated_dy); 
      }; 
      //break; 
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
  
  Game_EventsHandlers__reset(); 
  for (int i = 0; i < carte_data -> events_nb; i++) { 
    //AddTraitementEvenement((type_evt)carte_data -> events_genere[i], carte_data -> events_gestion_fichier[i], carte_data -> events_gestion_proc[i]); 
    //EvenementsModule -> AddTraitement((type_evt)carte_data -> events_genere[i], carte_data -> events_gestion_fichier[i], carte_data -> events_gestion_proc[i]); 
    //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " carte_data -> events_genere[i] = %d - carte_data -> events_gestion_fichier[i] = %s - carte_data -> events_gestion_proc[i] = %s " "\n", __func__, carte_data -> events_genere[i], carte_data -> events_gestion_fichier[i], carte_data -> events_gestion_proc[i]); 
    if (3 == carte_data -> events_genere[i]) { 
      const int evt_type = GAME_EVENTS__MAP__ALL_HOSTILES_DEAD; 
      Game_EventsHandlers__push_script(evt_type, /*script_file*/carte_data -> events_gestion_fichier[i], /*script_name*/carte_data -> events_gestion_proc[i]); 
      continue; 
    }; 
    if (1 == carte_data -> events_genere[i]) { 
      const int evt_type = GAME_EVENTS__MAP__LOADED_STARTING_FADING; 
      Game_EventsHandlers__push_script(evt_type, /*script_file*/carte_data -> events_gestion_fichier[i], /*script_name*/carte_data -> events_gestion_proc[i]); 
      continue; 
    }; 
    if (2 == carte_data -> events_genere[i]) { 
      //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " carte_data -> events_genere[i] = %d - carte_data -> events_gestion_fichier[i] = %s - carte_data -> events_gestion_proc[i] = %s " "\n", __func__, carte_data -> events_genere[i], carte_data -> events_gestion_fichier[i], carte_data -> events_gestion_proc[i]); 
      const int evt_type = GAME_EVENTS__MAP__LOADED_READY; 
      Game_EventsHandlers__push_script(evt_type, /*script_file*/carte_data -> events_gestion_fichier[i], /*script_name*/carte_data -> events_gestion_proc[i]); 
      continue; 
    }; 
    messerr(" carte_data -> events_genere[i] = %d - carte_data -> events_gestion_fichier[i] = %s - carte_data -> events_gestion_proc[i] = %s " "\n", carte_data -> events_genere[i], carte_data -> events_gestion_fichier[i], carte_data -> events_gestion_proc[i]); 
  }; 
  
  
  
  carte_delete(carte_data); 
  
  return 0; 
}; 














