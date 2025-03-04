#include "global.h"
#include "camera.h"
//#include "kernel.h"
#include "map.h"
#include "bonhomme.h"

enum { NB_ETAPES_ANIM_CAMERA = 16 }; 

// RL: Used in apiscript.c 
#define lattice__dist_defaut 4.0f //90.0f //87.5f //75.0f //50.0f //100.0f //150.0f




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


const int16_t CCamera_bytesize_actual = sizeof(CCamera);  
//ASSERT_COMPILE__TOPLEVEL(CCamera_bytesize >= CCamera_bytesize_actual); 




static float bary(const float a, const float b, const float t, const float nb) { 
  return (a * t + b * (nb - t)) / nb; 
}; 

#if 1 
TDirection ConvertirDirectionAvecVue(const TDirection d, const CCamera * Camera) { 
  int dd = d; 
  //dd = dd + (int) ((Camera -> angleXY - PI/2.0f - PI/4.0f)*2.0f / PI); 
  //dd += (int) ((Camera -> angleXY  PI/2.0f - PI/4.0f)*2.0f / PI); 
  // RL: Conversion of 'angleXY' to an 'int'. 
  //        When 'angleXY' is in [-π/4 ; +π/4] , it should return 1 
  const float angleXY_f   = ((Camera -> angleXY + PI/2.0f + PI/4.0f) * 2.0f / PI); 
  const int   angleXY_int = floorf(angleXY_f); 
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    AngleXY     = %f x 2π"  "\n", __func__,     Camera -> angleXY / (2.0f * PI)); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    AngleXY_f   = %f "  "\n", __func__,     angleXY_f); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    AngleXY_int = %d"   "\n", __func__,     angleXY_int); 
#endif 
  dd += angleXY_int; 
  //if (dd < 0) dd+=4; 
  //dd = (dd % 4); 
  //dd %= 4; // RL: This is garbage as the returned result is between ]-4 ; 4[... 
  dd &= 3; 
  //if (dd < 0) dd = dd + 4; 
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    dd = %d"  "\n", __func__,     dd); 
  assert(0 <= dd && dd < 4); 
#endif 
  return (TDirection) dd; 
}; 
#else 
TDirection ConvertirDirectionAvecVue(const TDirection d, const CCamera * Camera) { 
  int dd = d; 
  dd = dd + (int) ((Camera -> angleXY - PI/2.0f - PI/4.0f)*2.0f / PI); 
  if (dd < 0) dd+=4; 
  dd = (dd % 4); 
  if (dd < 0) dd = dd + 4; 
  return (TDirection) dd; 
}; 
#endif 

#if 1 
TDirection ConvertirDirectionAvecVue2(const TDirection d, const CCamera * Camera) { 
  int dd = d; 
  //dd = dd + (int) ((Camera -> angleXY - PI/2.0f - PI/4.0f)*2.0f / PI); 
  //dd += (int) ((Camera -> angleXY  PI/2.0f - PI/4.0f)*2.0f / PI); 
  // RL: Conversion of 'angleXY' to an 'int'. 
  //        When 'angleXY' is in [-π/4 ; +π/4] , it should return 1 
  const float angleXY_f   = ((Camera -> angleXY + PI/2.0f + PI/4.0f) * 2.0f / PI); 
  const int   angleXY_int = floorf(angleXY_f); 
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    AngleXY     = %f x 2π"  "\n", __func__,     Camera -> angleXY / (2.0f * PI)); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    AngleXY_f   = %f "  "\n", __func__,     angleXY_f); 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    AngleXY_int = %d"   "\n", __func__,     angleXY_int); 
#endif 
  dd -= angleXY_int; 
  //if (dd < 0) dd+=4; 
  //dd = (dd % 4); 
  //dd %= 4; // RL: This is garbage as the returned result is between ]-4 ; 4[... 
  dd &= 3; 
  //if (dd < 0) dd = dd + 4; 
#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "    dd = %d"  "\n", __func__,     dd); 
  assert(0 <= dd && dd < 4); 
#endif 
  return (TDirection) dd; 
}; 
#else 
TDirection ConvertirDirectionAvecVue2(const TDirection d, const CCamera * Camera) { 
  int dd = d;
     
  dd = dd - (int) ((Camera -> angleXY - PI/2.0f - PI/4.0f)*2.0f / PI);
  if (dd < 0) dd+=4;           
  dd = (dd % 4);
     
  if (dd < 0) dd = dd + 4;
  return (TDirection) dd;
};
#endif 

CCamera * CCamera__make_aux(CCamera * this) {
  this -> IsSolidaireAuHeros = CCamera__IsSolidaireAuHeros; 
  this -> InitCamera         = CCamera__InitCamera; 
  this -> SolidariserAuHeros = CCamera__SolidariserAuHeros; 
  this -> DeSolidariser      = CCamera__DeSolidariser; 
  this -> CalcCamera         = CCamera__CalcCamera; 
  this -> EffetPsychadelique = CCamera__EffetPsychadelique; 
  this -> SetDist            = CCamera__SetDist; 
  this -> Blit               = CCamera__Blit; 
  this -> Zoom               = CCamera__Zoom; 
  
  this -> a_dist             = 0.0f; 
  this -> lattice__dist      = 0.0f; 
  this -> anim               = 0; 
  this -> solidaire_au_heros = true; 
  
  return this; 
}; 

CCamera * CCamera__make(void) {
  CCamera * this = (CCamera *) malloc(sizeof(*this)); 
  bzero(this, sizeof(*this)); 
  
  return CCamera__make_aux(this); 
}; 

void CCamera__delete(CCamera * this) { 
  free(this); 
}; 


void CCamera__SolidariserAuHeros(CCamera * this) {
  this -> solidaire_au_heros = true; 
};

void CCamera__DeSolidariser(CCamera * this) {
  this -> solidaire_au_heros = false; 
};

bool CCamera__IsSolidaireAuHeros(const CCamera * this) {
  return this -> solidaire_au_heros; 
};


void CCamera__SetDist(CCamera * this, const float in_new_dist) {
  this -> a_dist = this -> lattice__dist; 
  this -> lattice__dist = in_new_dist;  
  this -> anim = NB_ETAPES_ANIM_CAMERA;   
};

void CCamera__Zoom(CCamera * this, const TZoomMethod zoom_method, const float zoom_factor) { 
  switch (zoom_method) { 
    case TZoomMethod_Relatif: CCamera__SetDist(this, this -> lattice__dist / zoom_factor); break; 
    case TZoomMethod_Absolu : CCamera__SetDist(this, lattice__dist_defaut  / zoom_factor); break; 
  }; 
}; 



void CCamera__InitCamera(CCamera * this) { 
  //this -> SetDist(this, dist_defaut); 
  this -> lattice__dist = lattice__dist_defaut; 
  //this -> angleXY =   PI / 2.0f; 
  //this -> angleHB = - PI / 4.0f; 
  //this -> angleXY = - PI / 2.0f; 
  //this -> angleXY = 0; 
  this -> angleXY = - PI / 2.0f; 
  //this -> angleZ  =   PI / 4.0f; 
  //this -> angleZ  =   3.0f * PI / 8.0f; 
  //this -> angleZ  =   5.0f * PI / 16.0f; 
  this -> angleZ  =   11.0f * PI / 32.0f; 
  //this -> angleZ  =   10.0f * PI / 32.0f; 
}; 

//void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const CMap * Map) { 
//void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const int lattice_width, const int lattice_height, const riemann_t * our_manifold) { 
void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold) { 
#if 0 
  if (this -> angleXY > 0) { 
    this -> angleXY -= 2.0f * PI; 
  }; 
#endif 
  
  // FS: /*si c'est fixé au héros*/ 
  if (this -> solidaire_au_heros) {
    this -> lattice__target_position = Hero -> parent1.GetPosition(&Hero -> parent1); 
  }; 
  
  // Map->LookAt(Camera.pos.x, Camera.pos.y, Camera.pos.z); 
  const float lattice_b = bary(this -> a_dist, this -> lattice__dist, this -> anim, NB_ETAPES_ANIM_CAMERA); 
  //Map -> parent.LookAt_angle(&Map -> parent, this -> pos.x, this -> pos.y, this -> pos.z, b, this -> angleXY, this -> angleHB); 
  //our_manifold -> camera__LookAt_angle(our_manifold, /*map_i*/0, /*map_j*/0, this -> pos.x, this -> pos.y, this -> pos.z, b, this -> angleXY, this -> angleHB); 
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> pos.x, this -> pos.y, this -> pos.z, b, this -> angleXY, this -> angleHB, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
#if 1 
  this -> map__target_position.x = this -> lattice__target_position.x * lattice_to_map_scale_factor__x; 
  this -> map__target_position.y = this -> lattice__target_position.y * lattice_to_map_scale_factor__y; 
  this -> map__target_position.z = this -> lattice__target_position.z * lattice_to_map_scale_factor__z; 
#else 
  this -> map__target_position.x = this -> lattice__target_position.x / (float) lattice_width; 
  this -> map__target_position.y = this -> lattice__target_position.y / (float) lattice_height; 
  this -> map__target_position.z = this -> lattice__target_position.z; 
#endif 
  
  //const float dist_factor = (fabsf(cosf(this -> angleXY)) * lattice_to_map_scale_factor__x + fabsf(sinf(this -> angleXY)) * lattice_to_map_scale_factor__y) * fabsf(sinf(this -> angleZ)) + fabsf(cosf(this -> angleZ)) * lattice_to_map_scale_factor__z; 
  //const float dist_factor = (powf(cosf(this -> angleXY), 2.0f) * lattice_to_map_scale_factor__x + powf(sinf(this -> angleXY), 2.0f) * lattice_to_map_scale_factor__y); 
  const float dist_factor = (powf(cosf(this -> angleXY), 2.0f) * lattice_to_map_scale_factor__x + powf(sinf(this -> angleXY), 2.0f) * lattice_to_map_scale_factor__y) * powf(sinf(this -> angleZ), 2.0f) + powf(cosf(this -> angleZ), 2.0f) * lattice_to_map_scale_factor__z; 
  //const float dist_factor = (ldexpf(cosf(this -> angleXY), 2.0f) * lattice_to_map_scale_factor__x + ldexpf(sinf(this -> angleXY), 2.0f) * lattice_to_map_scale_factor__y) * ldexpf(sinf(	this -> angleZ), 1) + ldexpf(cosf(this -> angleZ), 1) * lattice_to_map_scale_factor__z; 
  this -> map__dist = dist_factor * this -> lattice__dist; 
  const float map_b = dist_factor * lattice_b; 
  
  
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map_position.x, this -> map_position.y, this -> map_position.z, b, this -> angleXY, this -> angleHB, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map_position.x, this -> map_position.y, this -> map_position.z, /*dist*/b, /*angleXY*/0, /*angleZ*/0, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map_position.x, this -> map_position.y, this -> map_position.z, /*dist*/b, /*angleXY*/0, /*angleZ*/this -> angleZ, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map__target_position.x, this -> map__target_position.y, this -> map__target_position.z, /*dist*/b, /*angleXY*/this -> angleXY, /*angleZ*/this -> angleZ, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map__target_position.x, this -> map__target_position.y, this -> map__target_position.z, /*map_dist*/map_b, /*angleXY*/this -> angleXY, /*angleZ*/this -> angleZ, &this -> manifold__dist, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  
  //this -> manifold__dist *= this -> lattice__dist / lattice_b; 
  
  if (this -> anim > 0) this -> anim --; 
}; 

void CCamera__Blit(const CCamera * this, const riemann_t * our_manifold) { 
  our_manifold -> camera__LookAt__Blit(our_manifold, (const float (*)[3])&this -> manifold__camera_position, (const float (*)[3])&this -> manifold__target_position, (const float (*)[3])&this -> manifold__upward_direction); 
}; 


void CCamera__EffetPsychadelique(CCamera * this) {
#define NB_PAS 50 
  for (int i = 0; i <= NB_PAS; i++) {
    const float f   = ((float) (NB_PAS - i)) / ((float) NB_PAS); 
    this -> lattice__dist = 150.0f - f * 100.0f; 
    this -> angleXY       = PI / 2.0f + f * 2.0f * PI; 
    //SCRIPT_unepassedeboucle();        
  }; 
}; 


float    * CCamera__angleXY(CCamera * this) { 
  return &(this -> angleXY); 
}; 

float    * CCamera__angleZ(CCamera * this) { 
  return &(this -> angleZ); 
}; 

float    * CCamera__lattice__dist           (CCamera * this) { 
  return &(this -> lattice__dist); 
}; 

TPoint3D * CCamera__lattice__target_position(CCamera * this) { 
  return &(this -> lattice__target_position); 
}; 

TPoint3D * CCamera__map__target_position    (CCamera * this) { 
  return &(this -> map__target_position); 
}; 

