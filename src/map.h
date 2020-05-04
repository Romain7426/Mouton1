#ifndef MAP_H
#define MAP_H

#if 0
struct TVoisinage {
  //CListe<CPhysicalObj> Objets;     
  //struct CPhysicalObj * Objets;     
  CPhysicalObj * Objets;     
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TVoisinage);
DEFINE_NEW_OPERATOR_FOR_STRUCT(TVoisinage);
#endif 


struct CZoneTeleportation { 
  TPoint3D   position; 
  TPoint3D   dimension; 
  TDirection depart_direction; 
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
//     There's nothing really OpenGL here. In the spirit, it's a big array. 
// 
// RL: Inside we have two main structures: 
//      * 'Voisinages', which contains all the objects. 
//      * 'ZonesTeleportation', which contains the gates. 
//      * And that's it! 
// 

//#define VOISINAGE_IS_TAB
enum { VOISINAGE_X_SIZE = 63 }; 
enum { VOISINAGE_Y_SIZE = 63 }; 
enum { VOISINAGE_SIZE = 63 }; 
enum { DicoObjets_SIZE = 2048 }; 
enum { ZonesTeleportation_SIZE = 32 }; 
struct CMap {
  char * NomCarte; 
  
  uint8_t lattice_width ; // RL: In vertices, not in cells. 
  uint8_t lattice_height; // RL: In vertices, not in cells. 

  uint8_t over_spanning_w; // RL: If this local map is bigger than a simple map. In this case, it spans over 'over_spanning_w' in width. 
  uint8_t over_spanning_h; // RL: If this local map is bigger than a simple map. In this case, it spans over 'over_spanning_h' in height. 

  uint8_t global_map_i; // RL: In the global map of the world, this map is #'global_map_i' on the  width-axis. 
  uint8_t global_map_j; // RL: In the global map of the world, this map is #'global_map_j' on the height-axis. 
  
  CSol * Sol; 
  
  CPhysicalObj * Voisinages_array[VOISINAGE_X_SIZE][VOISINAGE_Y_SIZE][VOISINAGE_SIZE]; 
  
  CPhysicalObj * objets_array[DicoObjets_SIZE]; 
  char * objets_noms_array[DicoObjets_SIZE]; 
  int objets_nb; 
  
  
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
  void (* Render)(const CMap * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau); 
  //void (* Render)(const CMap * this, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y); 
  
  
  float (* GETZ0_vXY )(const CMap * this, const float lattice_x, const float lattice_y); 
  float (* GETZ0_vP3D)(const CMap * this, const TPoint3D lattice_pos); 
  
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
extern void CMap__Render(const CMap * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_lattice_x, const float target_lattice_y, const bool EnVaisseau); 
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
extern void           CMap__Life_NewtonEngine_Sword    (CMap * this, const CPhysicalObj * Hero_o, const bool EnVaisseau); 
extern void           CMap__Life_RemoveDeads           (CMap * this, const bool EnVaisseau); 
extern CPhysicalObj * CMap__GetNearestInteractingObject(CMap * this, const CPhysicalObj * Hero_o); 
extern float CMap__GETZ0_vXY(const CMap * this, const float lattice_x, const float lattice_y); 
extern float CMap__GETZ0_vP3D(const CMap * this, const TPoint3D lattice_pos); 




#endif /* MAP_H */



