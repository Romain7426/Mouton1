#include "global.hpp"
#include "camera.hpp"
#include "kernel.hpp"
#include "map.hpp"
#include "bonhomme.hpp"



#define NB_ETAPES_ANIM_CAMERA 16







float bary(float a, float b, float t, float nb) {
  return (a * t + b * (nb - t)) / nb; 
}

TDirection ConvertirDirectionAvecVue(TDirection d, CCamera Camera) {
  int dd = d;
     
  dd = dd + (int) ((Camera.angleXY - PI/2.0f - PI/4.0f)*2.0f / PI);           
  if (dd < 0) dd+=4;   
  dd = (dd % 4);
     
  if (dd < 0) dd = dd + 4;
  return (TDirection) dd;
}

TDirection ConvertirDirectionAvecVue2(TDirection d, CCamera Camera) {
  int dd = d;
     
  dd = dd - (int) ((Camera.angleXY - PI/2.0f - PI/4.0f)*2.0f / PI);
  if (dd < 0) dd+=4;           
  dd = (dd % 4);
     
  if (dd < 0) dd = dd + 4;
  return (TDirection) dd;
}

void CCamera::SolidariserAuHeros(void) {
  solidaire_au_heros = true; 
}

void CCamera::DeSolidariser(void) {
  solidaire_au_heros = false; 
}



CCamera::CCamera()  : a_dist(0.0f), dist(0.0f), anim(0) {
     
}

bool CCamera::IsSolidaireAuHeros() const
{
  return solidaire_au_heros; 
}


void CCamera::SetDist(float in_new_dist) {
  a_dist = dist; 
  dist = in_new_dist;  
  anim = NB_ETAPES_ANIM_CAMERA;   
     
}


void CCamera::InitCamera(void) {
  SetDist(dist_defaut);
  angleXY = PI/2.0f;
  angleHB = -PI/4.0f;  

}
  
  
void CCamera::CalcCamera(const CBonhomme * Hero, const CMap * Map) {
  if (angleXY > 0)
    angleXY -= 2*PI;
     
  /*si c'est fixé au héros*/ 
  if (solidaire_au_heros) 
    pos = Hero->GetPosition();
    
  // Map->LookAt(Camera.pos.x, Camera.pos.y, Camera.pos.z);
  Map->LookAt(pos.x, pos.y, pos.z, bary(a_dist, dist, anim, NB_ETAPES_ANIM_CAMERA), angleXY, angleHB);
                
  if (anim > 0) anim --;
     
}




void CCamera::EffetPsychadelique(void) {
#define NB_PAS 50 
  for (int i = 0; i<=NB_PAS; i++)
    {
      float f =  (float) (NB_PAS-i)  / ((float) NB_PAS);
            
      dist = 150.0f - f * 100.0f;
      angleXY = PI/2.0f + f * 2.0f*PI;
            
      SCRIPT_unepassedeboucle();        
    }     
     
     
}



