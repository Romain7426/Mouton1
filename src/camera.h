#ifndef CAMERA_H
#define CAMERA_H

extern TDirection ConvertirDirectionAvecVue(const TDirection d, const struct CCamera * Camera);
extern TDirection ConvertirDirectionAvecVue2(const TDirection d, const struct CCamera * Camera);


// RL: Used in apiscript.c 
#define dist_defaut 100.0f //150.0f

struct CCamera {
  //private://pas touche !! 
  bool  solidaire_au_heros; 
  float             a_dist;  
  float               dist; 
  int                 anim; 
  
  //public:
  /********* les paramètres cools **************/

  // FS: /*le point que regarde la caméra (prévoir une instruction pour affecter ce paramètre en abs et en relatif*/
  TPoint3D lattice_position; 
  TPoint3D     map_position; 
  
  float manifold__camera_position[3]; 
  float manifold__target_position[3]; 
  float manifold__upward_direction[3]; 
  
  /*les angles de vues en radian... angleXY pour touner autour de uz... angleHB
    pour regarder de plus haut ou plus bas*/
  // RL: These angles are in radians. 
  float angleXY; // RL: In the plane (x-y), around z-axis. 
  float angleZ; //float angleHB; // RL: Distance in angle from z-axis - we're in a cone around the z-axis: Be D any axis in in the plane (x-y), it's a D-rotation. 
  
  
  
  
  // *** METHODS *** 
  
  bool (* IsSolidaireAuHeros)(const struct CCamera * this);
 
  void (* InitCamera)(struct CCamera * this);
  //initialise les paramètres pour une vue de jeu normal
  
  //attache la caméra au héros
  void (* SolidariserAuHeros)(struct CCamera * this);
  
  /*désattache la caméra au héros.
    le point courant est alors la dernier position du héros lorsqu'il 
    était encore lié à la caméra*/
  void (* DeSolidariser)(struct CCamera * this);
  
  /**** ne pas prévoir d'instructions pascal pour ça... 
	CalcCamera est automatiquement appelé dans RaiseRender)(struct CCamera * this)*/
  void (* CalcCamera)(struct CCamera * this, const struct CBonhomme * Hero, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
  void (* Blit)(const CCamera * this, const riemann_t * our_manifold); 
  
  void (* EffetPsychadelique)(struct CCamera * this);
  //*c'est nul*/
  
  void (* SetDist)(struct CCamera * this, float d);
  //*distance de laquelle on regarde. plus c petit, plus on est près du point qu'on regarde*/

};

extern CCamera * CCamera__make(void);
extern CCamera * CCamera__make_aux(CCamera * this);
extern void CCamera__delete(CCamera * this);
extern bool CCamera__IsSolidaireAuHeros(const struct CCamera * this);
extern void CCamera__InitCamera(struct CCamera * this);
extern void CCamera__SolidariserAuHeros(struct CCamera * this);
extern void CCamera__DeSolidariser(struct CCamera * this);
//extern void CCamera__CalcCamera(struct CCamera * this, const struct CBonhomme * Hero, const struct CMap * Map);
extern void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const int lattice_width, const int lattice_height, const riemann_t * our_manifold); 
extern void CCamera__Blit(const CCamera * this, const riemann_t * our_manifold); 
extern void CCamera__EffetPsychadelique(struct CCamera * this);
extern void CCamera__SetDist(struct CCamera * this, float d); 


#endif /* CAMERA_H */
