#include "global.h"
#include "camera.h"
//#include "kernel.h"
#include "map.h"
#include "bonhomme.h"



enum { NB_ETAPES_ANIM_CAMERA = 16 }; 







static float bary(const float a, const float b, const float t, const float nb) { 
  return (a * t + b * (nb - t)) / nb; 
}; 

TDirection ConvertirDirectionAvecVue(const TDirection d, const CCamera * Camera) { 
  int dd = d;
     
  dd = dd + (int) ((Camera -> angleXY - PI/2.0f - PI/4.0f)*2.0f / PI);           
  if (dd < 0) dd+=4;   
  dd = (dd % 4);
     
  if (dd < 0) dd = dd + 4;
  return (TDirection) dd;
};

TDirection ConvertirDirectionAvecVue2(const TDirection d, const CCamera * Camera) { 
  int dd = d;
     
  dd = dd - (int) ((Camera -> angleXY - PI/2.0f - PI/4.0f)*2.0f / PI);
  if (dd < 0) dd+=4;           
  dd = (dd % 4);
     
  if (dd < 0) dd = dd + 4;
  return (TDirection) dd;
};

CCamera * CCamera_make_aux(CCamera * this) {
  this -> IsSolidaireAuHeros = CCamera__IsSolidaireAuHeros; 
  this -> InitCamera = CCamera__InitCamera; 
  this -> SolidariserAuHeros = CCamera__SolidariserAuHeros; 
  this -> DeSolidariser = CCamera__DeSolidariser; 
  this -> CalcCamera = CCamera__CalcCamera; 
  this -> EffetPsychadelique = CCamera__EffetPsychadelique; 
  this -> SetDist = CCamera__SetDist; 
  
  this -> a_dist = 0.0f; 
  this -> dist = 0.0f; 
  this -> anim = 0; 
  this -> solidaire_au_heros = true; 
  
  return this; 
}; 

CCamera * CCamera_make(void) {
  CCamera * this = (CCamera *) malloc(sizeof(*this)); 
  bzero(this, sizeof(*this)); 
  
  return CCamera_make_aux(this); 
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
  this -> a_dist = this -> dist; 
  this -> dist = in_new_dist;  
  this -> anim = NB_ETAPES_ANIM_CAMERA;   
};

void CCamera__InitCamera(CCamera * this) { 
  this -> SetDist(this, dist_defaut); 
  this -> angleXY =   PI / 2.0f; 
  this -> angleHB = - PI / 4.0f; 
}; 

//void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const CMap * Map) { 
void CCamera__CalcCamera(CCamera * this, const CBonhomme * Hero, const riemann_t * our_manifold) { 
  if (this -> angleXY > 0) 
    this -> angleXY -= 2*PI; 
  
  //*si c'est fixé au héros*/ 
  if (this -> solidaire_au_heros) 
    this -> pos = Hero -> parent1.GetPosition(&Hero -> parent1); 
  
  // Map->LookAt(Camera.pos.x, Camera.pos.y, Camera.pos.z); 
  const float b = bary(this -> a_dist, this -> dist, this -> anim, NB_ETAPES_ANIM_CAMERA); 
  //Map -> parent.LookAt_angle(&Map -> parent, this -> pos.x, this -> pos.y, this -> pos.z, b, this -> angleXY, this -> angleHB); 
  our_manifold -> camera__LookAt_angle(our_manifold, /*map_i*/0, /*map_j*/0, this -> pos.x, this -> pos.y, this -> pos.z, b, this -> angleXY, this -> angleHB); 
  
  if (this -> anim > 0) this -> anim --; 
}; 


void CCamera__EffetPsychadelique(CCamera * this) {
#define NB_PAS 50 
  for (int i = 0; i <= NB_PAS; i++) {
    const float f =  (float) (NB_PAS-i)  / ((float) NB_PAS);
    this -> dist = 150.0f - f * 100.0f;
    this -> angleXY = PI/2.0f + f * 2.0f*PI;
    //SCRIPT_unepassedeboucle();        
  };  
};



