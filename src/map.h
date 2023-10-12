#ifndef MAP_H
#define MAP_H

enum {               CMap_bytesize = 1 << 21 }; 
extern const int32_t CMap_bytesize_actual; 
static void CMap__check_and_assert(const int8_t debug_print_huh, const int stderr_d) { 
  if (debug_print_huh) { 
    //fprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "I failed to clean up the log subdir.' " "\n", __func__); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CMap_bytesize: "); write_long_long_int(stderr_d, CMap_bytesize); write_eol(stderr_d); 
    write_string4(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<", __func__, "()>}: ", "CMap_bytesize_actual: "); write_long_long_int(stderr_d, CMap_bytesize_actual); write_eol(stderr_d); 
  }; 
  assert(CMap_bytesize >= CMap_bytesize_actual);   
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




extern void           CMap__Life_GamePlay              (CMap * this, const int animate_but_do_not_aliven_huh, const bool EnVaisseau); 
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
extern float          CMap__lattice_to_map_scale_factor__x(const CMap * this); 
extern float          CMap__lattice_to_map_scale_factor__y(const CMap * this); 
extern float          CMap__lattice_to_map_scale_factor__z(const CMap * this); 
extern uint8_t        CMap__lattice_width(const CMap * this); 
extern uint8_t        CMap__lattice_height(const CMap * this); 
extern const CSol *   CMap__Sol(const CMap * this); 
extern       CSol *   CMap__Sol_mutable(CMap * this); 
extern uint8_t        CMap__global_map_i(const CMap * this); 
extern uint8_t        CMap__global_map_j(const CMap * this); 




#endif /* MAP_H */



