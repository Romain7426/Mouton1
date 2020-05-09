#include "global.h"
#include "camera.h"
//#include "kernel.h"
#include "map.h"
#include "bonhomme.h"



enum { NB_ETAPES_ANIM_CAMERA = 16 }; 



// RL: Used in apiscript.c 
#define lattice__dist_defaut 4.0f //90.0f //87.5f //75.0f //50.0f //100.0f //150.0f




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
  this -> map__dist = dist_factor * this -> lattice__dist; 
  const float map_b = dist_factor * lattice_b; 
  
  
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map_position.x, this -> map_position.y, this -> map_position.z, b, this -> angleXY, this -> angleHB, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map_position.x, this -> map_position.y, this -> map_position.z, /*dist*/b, /*angleXY*/0, /*angleZ*/0, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map_position.x, this -> map_position.y, this -> map_position.z, /*dist*/b, /*angleXY*/0, /*angleZ*/this -> angleZ, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  //our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map__target_position.x, this -> map__target_position.y, this -> map__target_position.z, /*dist*/b, /*angleXY*/this -> angleXY, /*angleZ*/this -> angleZ, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  our_manifold -> camera__LookAt__Compute(our_manifold, /*map_i*/0, /*map_j*/0, this -> map__target_position.x, this -> map__target_position.y, this -> map__target_position.z, /*map_dist*/map_b, /*angleXY*/this -> angleXY, /*angleZ*/this -> angleZ, &this -> manifold__dist, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
  
  this -> manifold__dist *= this -> lattice__dist / lattice_b; 
  
  if (this -> anim > 0) this -> anim --; 
}; 

void CCamera__Blit(const CCamera * this, const riemann_t * our_manifold) { 
  our_manifold -> camera__LookAt__Blit(our_manifold, &this -> manifold__camera_position, &this -> manifold__target_position, &this -> manifold__upward_direction); 
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



