#ifndef CAMERA_H
#define CAMERA_H

extern TDirection ConvertirDirectionAvecVue(const TDirection d, const struct CCamera * Camera);
extern TDirection ConvertirDirectionAvecVue2(const TDirection d, const struct CCamera * Camera);

enum TZoomMethod { TZoomMethod_Absolu, TZoomMethod_Relatif }; 
typedef enum TZoomMethod TZoomMethod; 


struct CCamera {
  //private://pas touche !! 
  bool  solidaire_au_heros; 
  int                 anim; 
  float             a_dist;  
  
  // RL: The camera has four liberty degrees (all in lattice units): 
  //     'target'  is the point that the camera is looking at. 
  //     'dist'    is the distance from which the camera looks at the target point (the camera is on the 'dist'-sphere). 
  //     'angleZ'  is the angle with the z-axis: 0 means that the camera is on the z-axis; π/2 means that the camera is in the xy-plane. 
  //     'angleXY' is the angle in the xy-plane: 0 means that the camera is aligned with the x-axis; π/2 means that the camera is aligned with the y-axis. 
  //               NB: 'angleXY' is still needed even when 'angleZ' is zero: it gives the 'upward_direction' (when 'angleZ' is zero, there's still on liberty degree left: it can spin around the z-axis) 
  // RL: 'camera_position'  is computed (by 'CalcCamera'). 
  // RL: 'upward_direction' is computed (by 'CalcCamera'). 
  // 
  // RL: 'upward_direction' answers the question of where is 'up' or 'down' 
  //                (if the camera is on the z-axis, then it can still spin around; 
  //                 if the camera is on the x-axis, then it can still spin around; 
  //                 if the camera is on any   axis, then it can still spin around). 
  TPoint3D lattice__target_position; // RL: Liberty degree. 
  float               lattice__dist; // RL: Liberty degree. 
  float                      angleZ; // RL: Liberty degree. // RL: Radians, not degrees. // RL: Angle with the z-axis (0 → z-axis ; π/2 → xy-plane) 
  float                     angleXY; // RL: Liberty degree. // RL: Radians, not degrees. // RL: Angle in the xy-plane (0 → x-axis ; π/2 → y-axis) 
  TPoint3D     map__target_position;    // RL: Computed (by 'CalcCamera'). 
  float   manifold__camera_position[3]; // RL: Computed (by 'CalcCamera').  
  float   manifold__target_position[3]; // RL: Computed (by 'CalcCamera'). 
  float  manifold__upward_direction[3]; // RL: Computed (by 'CalcCamera'). 
  float                   map__dist; // RL: Computed (by 'CalcCamera'). 
  float              manifold__dist; // RL: Computed (by 'CalcCamera'). 
  
  
  
  
  
  // *** METHODS *** 
  
  bool (* IsSolidaireAuHeros)(const struct CCamera * this);
 
  void (* InitCamera)(struct CCamera * this);
  //initialise les paramètres pour une vue de jeu normal
  
  // FS: attache la caméra au héros
  void (* SolidariserAuHeros)(struct CCamera * this);
  
  // FS: /*désattache la caméra au héros. le point courant est alors la dernier position du héros lorsqu'il était encore lié à la caméra*/
  void (* DeSolidariser)(struct CCamera * this);
  
  //void (* CalcCamera)(struct CCamera * this, const struct CBonhomme * Hero, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
  void (* CalcCamera)(struct CCamera * this, const struct CBonhomme * Hero, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold); 
  void (* Blit)(const CCamera * this, const riemann_t * our_manifold); 
  
  void (* EffetPsychadelique)(struct CCamera * this);
  // FS: /*c'est nul*/
  
  void (* SetDist)(struct CCamera * this, const float lattice_dist); 
  // FS: /*distance de laquelle on regarde. plus c petit, plus on est près du point qu'on regarde*/

  void (* Zoom)(CCamera * this, const TZoomMethod zoom_method, const float zoom_factor); 

};

extern CCamera * CCamera__make(void);
extern CCamera * CCamera__make_aux(CCamera * this);
extern void CCamera__delete(CCamera * this);
extern bool CCamera__IsSolidaireAuHeros(const struct CCamera * this);
extern void CCamera__InitCamera(struct CCamera * this);
extern void CCamera__SolidariserAuHeros(struct CCamera * this);
extern void CCamera__DeSolidariser(struct CCamera * this);
//extern void CCamera__CalcCamera(struct CCamera * this, const struct CBonhomme * Hero, const struct CMap * Map);
//extern void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
extern void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold); 
extern void CCamera__Blit(const CCamera * this, const riemann_t * our_manifold); 
extern void CCamera__EffetPsychadelique(struct CCamera * this);
extern void CCamera__SetDist(struct CCamera * this, float d); 
extern void CCamera__Zoom(CCamera * this, const TZoomMethod zoom_method, const float zoom_factor); 


#endif /* CAMERA_H */
