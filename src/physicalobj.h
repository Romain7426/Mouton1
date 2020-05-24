#ifndef PHYSICALOBJ_H 
#define PHYSICALOBJ_H 

enum TMethodePlacement { mpABSOLU, mpRELATIF }; 
TYPEDEF_TYPENAME_WITHOUT_ENUM(TMethodePlacement);


enum { CPhysicalObj_subtype_None, CPhysicalObj_subtype_CBonhomme, CPhysicalObj_subtype_CObjNonAnime }; 

/* 
   Ceci est une structe abstraite pour définir des choses matérielles. 
   But: modéliser un point matériel (position, vitesse, forces...) 
*/
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CPhysicalObj);
DECLARE_NEW_OPERATOR_FOR_STRUCT(CPhysicalObj);
//struct CPhysicalObj : public CObjActionnable {
struct CPhysicalObj { 
  //CObjActionnable parent;
  CObjActionnable * actions;
  
  int8_t subtype; 

  char * filename;
  
  
  // *** Gameplay *** 
  
  int8_t pv; 
  int8_t pvmax; 
  int8_t is_objet_ephemere; 
  
  int8_t DansEau_huh; // FS: /* vaut vrai si la chose rentre dans l'eau, mais sans être complètement immergé */ 
  int8_t Immerge_huh; // FS: /* vaut vrai si la chose est entièrement immergé dans l'eau */ 
  int8_t Compressible_huh; // FS: /* vaut vrai ssi ça se compresse avec le tore. Typiquement, être vivant, bonhomme --> faux ; pierre, maison ---> vrai */ 
  
  int8_t Fixe_huh; // FS: /* calcule-t-on les forces appliquées à l'objet ?? */ 
  
  int8_t AuSol_huh; 
  int8_t Hostile_huh; 
  
  
  // *** Newton Engine *** 
  
  // RL: All of these data are in lattice coordinates. 
  // RL: NB: All of these data applies on the whole object, especially on the point standing for the whole object. 
  //         Especially the acceleration: it does not depends on its mass. 
  // RL: Modelly speaking, each pass, the accélération is reset to 0. 
  //     Therefore, 
  //      - 'accélération' is a series of diracs 
  //      - 'vitesse' is piecewise continuous (it has jumps) 
  //      - 'point' is continuous, and its derivative is piecewise continuous (has jumps). 
  TPoint3D p; // position,    // RL: 'p' stands for the whole object - it's on the bottom, and centered. 
  TPoint3D d; // dimension,   // RL: The rest of the object is modelized as a cube: 
                              //       from (p.x - d.x, p.y - d.y, p.z) to (p.x + d.x, p.y + d.y, p.z + d.z) 
                              //     As one can see, 'd' stores the radius on x & y, while it stores the diameter on z. 
  float volume;               // RL: To check whether an object has a null volume. 
                              //      - An object having a null volume cannot be hit by the sword. 
                              //      - Does not generate any splash when going into water. 
  TPoint3D v; // vitesse,     // RL: Of 'p' 
  TPoint3D a; // accélération // RL: Of 'p' 
  float masse; // RL: The mass has two impacts: (i) on space; (ii) on time. 
               //      - On time, it's called 'inertia': a force uniformely applied to the whole object will imply a lesser dirac (acceleration) on the object. 
               //      - On space: one quantity of energy applied to an object (somehow a "force") is uniformly divided within the object according to its mass. 
               //        (By mass unit, E/m = ½ V² = ½ (Δa)² = ½ (F/m)² (ΔT)²  
               //                   =>  F/m = √[2 (E/m)] / ΔT 
               //                   =>  a   = √[2 (E/m)] / ΔT                  ) 
  
  // RL: NB: We do not modelize any self-rotation of objects - they're supposed not to do so. 
  
  // RL: Newton's law: after dirac is applied to the object, its speed gonna stay constant. 
  //     Speed decreases because of the resistance of the air. 
  //     So, in order to decrease speed, we need to modelize that counter-force. 
  float CoeffFrottementFluideXY; 
  float CoeffFrottementFluideZ; 
  
  // RL: 'np' is the newly computed position: 
  //       'np' := 'p' + 'v' . ΔT 
  // RL: After having applied 'v', the new position may not be valid: 
  //      - out of the map 
  //      - must be above the ground 
  //      - the slope is too high 
  //      - there's already an object at that position 
  TPoint3D np;    // RL: That's the new computed position, but not yet tested & validated. 
  float    z0;    // RL: Ground level. Used to determine 'AuSol'. 
  float    z0_n;  // RL: Ground level at 'np'. 
  
#if 0 
  // RL: No idea what these are for. 
  bool nvalid_position; 
  bool  valid_position_x,  valid_position_y,  valid_position_z; 
  bool nvalid_position_x, nvalid_position_y, nvalid_position_z; 
  
  // RL: No idea what these are for. 
  //float ancvolumemax; 
  //float volumemax; 
#endif 
  
  
  
  
  
  // *** METHODS *** 
  
  CPhysicalObj * (* make      )(const char * filename); 
  CPhysicalObj * (* make_aux  )(      CPhysicalObj * this, const int subtype, const char * filename); 
  void           (* delete    )(      CPhysicalObj * this); 
  void           (* delete_aux)(      CPhysicalObj * this); 
  CPhysicalObj * (* copy      )(const CPhysicalObj * src); 
  CPhysicalObj * (* copy_aux  )(      CPhysicalObj * this, const CPhysicalObj * src); 
  
  // Gameplay 
  void (* PerdrePV        )(      struct CPhysicalObj * this, const int nbpv);
  bool (* Is0PV           )(const struct CPhysicalObj * this);
  void (* SetPVMax        )(      struct CPhysicalObj * this, const int nbpv, const int set_pv_as_well_huh);
  void (* GagnerPV        )(      struct CPhysicalObj * this, const int nbpv);
  int  (* GetPV           )(const struct CPhysicalObj * this);
  void (* SetPV           )(      struct CPhysicalObj * this, const int nbpv);
  void (* SetObjetEphemere)(      struct CPhysicalObj * this, const int nbPV); 
  
  TPoint3D (* GetDimension)(const struct CPhysicalObj * this); 
  void     (* SetDimension)(      struct CPhysicalObj * this, const float dx, const float dy, const float dz); 
  bool     (* IsVolumeNul )(const struct CPhysicalObj * this); 
  
  TPoint3D (* GetPosition     )(const struct CPhysicalObj * this); 
  float    (* GetPosition_x   )(const struct CPhysicalObj * this); 
  float    (* GetPosition_y   )(const struct CPhysicalObj * this); 
  float    (* GetPosition_z   )(const struct CPhysicalObj * this); 
  void     (* SetPosition_vP3D)(      struct CPhysicalObj * this, const TPoint3D lattice_pos, const CMap * Map); 
  void     (* SetPosition_vXY )(      struct CPhysicalObj * this, const float lattice_x, const float lattice_y, const TMethodePlacement mp, const CMap * CMap); 
  void     (* SetPosition_vXYZ)(      struct CPhysicalObj * this, const float lattice_x, const float lattice_y, const float lattice_z, const CMap * CMap); 
  void     (* SetZ            )(      struct CPhysicalObj * this, const float lattice_z, const TMethodePlacement mp); 
  
  TPoint3D (* GetVitesse      )(const struct CPhysicalObj * this); 
  float    (* NormeVitesse    )(const struct CPhysicalObj * this); 
  
#if 1 
  //void (* Acceleration_reset   )(struct CPhysicalObj * this); 
  
  // RL: These two functions are the ones one wants to call for key-hitting & user-controlling. 
  void (* Acceleration_add_vP3D)(struct CPhysicalObj * this, const TPoint3D delta_a); 
  void (* Acceleration_add_vXYZ)(struct CPhysicalObj * this, const float delta_a_x, const float delta_a_y, const float delta_a_z); 
  
  void (* Force_add_by_mass_unit_vP3D)(struct CPhysicalObj * this, const TPoint3D foverm); 
  void (* Force_add_by_mass_unit_vXYZ)(struct CPhysicalObj * this, const float foverm_x, const float foverm_y, const float foverm_z); 
  void (* Force_massique__add_vXYZ   )(struct CPhysicalObj * this, const float foverm_x, const float foverm_y, const float foverm_z); 
  void (* Force_massique__add_vP3D   )(struct CPhysicalObj * this, const TPoint3D foverm); 
  
  void (* Force_add_over_whole_mass_vP3D)(struct CPhysicalObj * this, const TPoint3D f); 
  void (* Force_add_over_whole_mass_vXYZ)(struct CPhysicalObj * this, const float f_x, const float f_y, const float f_z); 
  
  void (* Energy_add_by_mass_unit_vP3D)(struct CPhysicalObj * this, const TPoint3D Eoverm); 
  void (* Energy_add_by_mass_unit_vXYZ)(struct CPhysicalObj * this, const float Eoverm_x, const float Eoverm_y, const float Eoverm_z); 
  
  // RL: These are the functions to be used when energy is input into the system. 
  //     Because, unless the above ones, input energy is independent of the receiving system, 
  //     especially independent of the receiving system mass. 
  void (* Energy_add_over_whole_mass_vP3D)(struct CPhysicalObj * this, const TPoint3D E); 
  void (* Energy_add_over_whole_mass_vXYZ)(struct CPhysicalObj * this, const float E_x, const float E_y, const float E_z); 
#else 
  void (* InitForce)(struct CPhysicalObj * this); 
  //void (* AddForce)(struct CPhysicalObj * this, TPoint3D f); 
  void (* AddForce_vP3D)(struct CPhysicalObj * this, const TPoint3D f); 
  void (* AddForce_vXYZ)(struct CPhysicalObj * this, const float fx, const float fy, const float fz); 
  //TPoint3D (* GetForce)(const struct CPhysicalObj * this); 
#endif 
  
  // RL: Apply the Newton Engine. 
  void (* NewtonEngine__Frottements_apply             )(CPhysicalObj * this); 
  void (* NewtonEngine__OneStepFoward__NoValidationYet)(CPhysicalObj * this); 
  
  // RL: Correct 'np' for borders & ground & slope. 
  void (* BordersAndGroundAndSlope__AdjustAndCorrectNP)(CPhysicalObj * this, const CMap * Map); 

  // RL: Does the new position of the object intersect with the new position of any other object? 
  int (* DoTheyIntersect_huh)(const CPhysicalObj * this, const CPhysicalObj * po); 
  
  // RL: 'p' <- 'np' 
  //void (* ValiderPosition)(struct CPhysicalObj * this, const bool MoteurPhysiqueActif); 
  void (* ValiderPosition)(struct CPhysicalObj * this, const float lattice_ZEau); 

  // RL: ??? 
  bool (* IsBloque)(const struct CPhysicalObj * this); 

  //void (* Render)(const struct CPhysicalObj * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
  void (* Render)(const struct CPhysicalObj * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold); 
  void (* Life)(struct CPhysicalObj * this); 
  
  
#if 0 
  //* retourne vrai ssi il n'y a pas de colision */
  bool (* TesterPosition)(struct CPhysicalObj * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold, const struct CPhysicalObj * po);
  void (* CalcNewPosition)(struct CPhysicalObj * this); // RL: Prend en compte la vitesse actuelle, la force appliquée, et les frottements. 
  void (* TesterSol)(struct CPhysicalObj * this, const CSol * Map);
  // friend void (* TesterPosition)(struct CPhysicalObj * this, struct CPhysicalObj * po);
#endif 

};
extern CPhysicalObj * CPhysicalObj__make      (const char * filename); 
extern CPhysicalObj * CPhysicalObj__make_aux  (      CPhysicalObj * this, const int subtype, const char * filename); 
extern void           CPhysicalObj__delete    (      CPhysicalObj * this); 
extern void           CPhysicalObj__delete_aux(      CPhysicalObj * this); 
extern CPhysicalObj * CPhysicalObj__copy      (const CPhysicalObj * src); 
extern CPhysicalObj * CPhysicalObj__copy_aux  (      CPhysicalObj * this, const CPhysicalObj * src); 

//extern void CPhysicalObj__Render(const CPhysicalObj * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
extern void CPhysicalObj__Render(const CPhysicalObj * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold); 
extern void CPhysicalObj__Life(CPhysicalObj * this); 
extern int  CPhysicalObj__DoTheyIntersect_huh(const CPhysicalObj * this, const CPhysicalObj * po); 
extern void CPhysicalObj__BordersAndGroundAndSlope__AdjustAndCorrectNP(CPhysicalObj * this, const CMap * Map); 
extern void CPhysicalObj__NewtonEngine__OneStepFoward__NoValidationYet(CPhysicalObj * this); 
extern void CPhysicalObj__NewtonEngine__Frottements_apply(CPhysicalObj * this); 
extern void CPhysicalObj__ValiderPosition(CPhysicalObj * this, const float lattice_ZEau); 






#endif /* PHYSICALOBJ_H */

