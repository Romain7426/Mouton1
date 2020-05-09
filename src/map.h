#ifndef MAP_H
#define MAP_H



// RL: What that thing is doing here? 
struct CZoneTeleportation { 
  TPoint3D   position; 
  TPoint3D   dimension; 
  TDirection depart_direction; // RL: That terrible thing should be removed. 
  char *     destination_carte; 
  TPoint3D   destination_position; 
  TDirection destination_direction; 
}; 
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CZoneTeleportation); 
  
//CZoneTeleportation(void) {}; 
extern CZoneTeleportation * CZoneTeleportation_make(TPoint3D in_position, TPoint3D in_dimension, TDirection in_depart_direction, const char * in_destination_carte, TPoint3D in_destination_position, TDirection in_destination_direction); 
extern CZoneTeleportation * CZoneTeleportation_copy(const CZoneTeleportation * this); 
extern void CZoneTeleportation_delete(CZoneTeleportation * this); 






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






extern CMap * CMap__make(const char * filename, const int map_i, const int map_j, const riemann_t * our_manifold, const bool EnVaisseau);
extern void   CMap__delete(CMap * this); 

//extern int CMap__parse(CMap * this, const char * dir, const char * filename);
//extern int CMap__yycarteparse(CMap * this);
extern int CMap__ReadDescriptionFile(CMap * this, const int map_i, const int map_j, const riemann_t * our_manifold, const char * dir, const char * filename);
extern const char * CMap__GetNomCarte(const struct CMap * this);
//extern void CMap__Life(struct CMap * this, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau);
extern void CMap__Life(struct CMap * this, const bool EnVaisseau); 
//extern void CMap__Render(const struct CMap * this, const riemann_t * our_manifold, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau); 
//extern void CMap__Render(const CMap * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y, const bool EnVaisseau); 
extern void CMap__Render(const CMap * this, const CCamera * Camera, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau); 
//extern void CMap__ChargerZ(struct CMap * this, const int map_i, const int map_j, const riemann_t * our_manifold, const char * filename);
extern void CMap__AjouterObjet(struct CMap * this, CPhysicalObj * o);  
extern void CMap__AjouterObjet_nom(struct CMap * this, const char * nom, CPhysicalObj * o);
extern CPhysicalObj * CMap__RetrouverObjetViaSonNom(CMap * this, const char * nom);
extern void CMap__AjouterZoneTeleportation(struct CMap * this, TPoint3D position, TPoint3D dimension, TDirection depart_direction, const char * destination_carte, TPoint3D destination_position, TDirection destination_direction);
extern void CMap__AjouterParticules(struct CMap * this, TPoint3D p, const char * nom, const bool MoteurPhysiqueActif);
//extern void CMap__TesterPosition(struct CMap * this, CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
//extern CPhysicalObj * CMap__TesterPositionHero(struct CMap * this, struct CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
extern void CMap__TraiterOrdresDeplacement(struct CMap * this, struct CBonhomme * aHero, const bool MoteurPhysiqueActif);
extern const CZoneTeleportation * CMap__VaTonBouger(const CMap * this, const CPhysicalObj * aHero);
//extern struct tab_evt_bool CMap__tab_evt_carte(struct CMap * this);




extern void           CMap__Life_GamePlay              (CMap * this, const bool EnVaisseau); 
extern void           CMap__Life_NewtonEngine_Objects  (CMap * this, const bool EnVaisseau); 
//extern void           CMap__Life_NewtonEngine_Sword    (CMap * this, const CPhysicalObj * Hero_o); 
extern void           CMap__Life_Choc_Sword(CMap * this, const CPhysicalObj * Hero_o); 
extern void           CMap__Life_RemoveDeads           (CMap * this, const bool EnVaisseau); 
extern CPhysicalObj * CMap__GetNearestInteractingObject(CMap * this, const CPhysicalObj * Hero_o); 
extern float          CMap__GETZ0_vXY(const CMap * this, const float lattice_x, const float lattice_y); 
extern float          CMap__GETZ0_vP3D(const CMap * this, const TPoint3D lattice_pos); 
extern float          CMap__GET_ZEau(const CMap * this); 
extern void           CMap__Life_Simulate_Objects(CMap * this, const bool EnVaisseau); 
extern void           CMap__Life_Objects_ValiderPosition(CMap * this, const bool EnVaisseau); 
extern void           CMap__ChocEngine(CMap * this, CPhysicalObj * Hero_o); 
extern bool           CMap__ChocEngine_HeroGotHostileEncounterHuh_one(CMap * this, const CPhysicalObj * hero_o); 




#endif /* MAP_H */



