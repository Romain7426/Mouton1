#include "global.h"
#include "physicalobj.h"
#include "text.h"
#include "map.h"

#define D_T 0.1f
//#define GRAVITY 100.0f 
#define GRAVITY 20.0f 


void CPhysicalObj__PerdrePV(CPhysicalObj * this, const int nbpv) { 
  this -> pv -= nbpv; 
}; 

void CPhysicalObj__SetPVMax(CPhysicalObj * this, const int nbpv, const int set_pv_as_well_huh) { 
  this -> pvmax = nbpv; 
  if (set_pv_as_well_huh) { 
    this -> pv = nbpv; 
  } 
  else { 
    this -> pv = MIN(nbpv, this -> pv); 
  }; 
}; 
 
void CPhysicalObj__GagnerPV(CPhysicalObj * this, const int nbpv) { 
  this -> pv += nbpv; 
  if (this -> pv > this -> pvmax) this -> pv = this -> pvmax; 
}; 

int CPhysicalObj__GetPV(const CPhysicalObj * this) {
  return this -> pv;   
}; 

bool CPhysicalObj__Is0PV(const CPhysicalObj * this) {
  return (this -> pv <= 0); 
}; 

void CPhysicalObj__SetObjetEphemere(CPhysicalObj * this, const int nbPV) { 
  this -> is_objet_ephemere = true; 
  this -> SetPVMax(this, nbPV, /*set_pv_as_well_huh*/true); 
}; 

void CPhysicalObj__Life(CPhysicalObj * this) { 
  // FS: /*un objet éphémère perd un point de vie à chaque tour*/ 
  if (this -> is_objet_ephemere) { 
    this -> PerdrePV(this, 1); 
  }; 
}; 


TPoint3D CPhysicalObj__GetPosition(const CPhysicalObj * this) {
  return this -> p;
};

float CPhysicalObj__GetPosition_x(const CPhysicalObj * this) {
  return this -> p.x;
};

float CPhysicalObj__GetPosition_y(const CPhysicalObj * this) {
  return this -> p.y;
};

float CPhysicalObj__GetPosition_z(const CPhysicalObj * this) {
  return this -> p.z;
};

void CPhysicalObj__SetPosition_vP3D(CPhysicalObj * this, const TPoint3D lattice_pos, const CMap * Map) { 
  //printf("SetPosition sur %p : %f, %f, %f\n", this, pos.x, pos.y, pos.z);      
  //this -> p = this -> np = lattice_pos;
  this -> p  = lattice_pos; 
  this -> z0 = Map -> GETZ0_vXY(Map, this -> p.x, this -> p.y); 
}; 

void CPhysicalObj__SetPosition_vXY(CPhysicalObj * this, const float lattice_x, const float lattice_y, const TMethodePlacement mp, const CMap * Map) {
  if (mp == mpRELATIF) {
    this -> p.x += lattice_x; 
    this -> p.y += lattice_y; 
  } 
  else { 
    this -> p.x = lattice_x; 
    this -> p.y = lattice_y; 
  }; 
  
#if 1 
  this -> z0  = Map -> GETZ0_vXY(Map, this -> p.x, this -> p.y); 
  this -> p.z = this -> z0; 
#else 
  const float map_x = lattice_x / Map -> lattice_width ; 
  const float map_y = lattice_y / Map -> lattice_height; 
  this -> p.z = Map -> Sol -> GETZ(Map -> Sol, map_x, map_y); 
#endif 
}; 

void CPhysicalObj__SetPosition_vXYZ(CPhysicalObj * this, const float lattice_x, const float lattice_y, const float lattice_z, const CMap * Map) {
  this -> p.x = lattice_x; 
  this -> p.y = lattice_y; 
  this -> p.z = lattice_z; 
  this -> z0  = Map -> GETZ0_vXY(Map, this -> p.x, this -> p.y); 
}; 

void CPhysicalObj__SetZ(CPhysicalObj * this, const float nz, const TMethodePlacement mp) { 
  this -> np.z = this -> p.z = nz + ((mp == mpRELATIF) ? this -> p.z : 0.0f); 
}; 

void CPhysicalObj__SetDimension(CPhysicalObj * this, const float dx, const float dy, const float dz) {
  //printf("SetDimension sur %p : %f, %f, %f\n", this, dx, dy, dz);  
  this -> d.x = dx / 2.0f; 
  this -> d.y = dy / 2.0f; 
  //this -> dimension.z = dz / 2.0f; 
  this -> d.z = dz; 
  this -> volume = dx * dy * dz; 
}; 

//TPoint3D CPhysicalObj__GetDimension(const CPhysicalObj * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold) { 
TPoint3D CPhysicalObj__GetDimension(const CPhysicalObj * this) { 
#if 1 
  return this -> d; 
#else 
  TPoint3D d = this -> dimension; 
  // FS: /*si ce n'est pas compressible, dans le repère adapté, les objets paraissent plus grands...*/ 
  // RL: Perhaps, but should not be there. This has nothing to do with the physical-engine, but the rendering-engine. 
  //     From an in-game point-of-view, a character does not see anything changing. 
  //     And we had an issue with that: some positions become invalid afterward, blocking the hero!! And that is definitely weird and not intuitive. 
  //     To the point that we had to implement a "disable physical engine" feature. 
  if (!this -> Compressible_huh) { 
    const float FacteurCompression = our_manifold -> FacteurCompression(our_manifold, /*map_j*/0, this -> p.y / (float) lattice_height); 
    d.x = d.x / FacteurCompression; 
  }; 
  return d; 
#endif 
}; 

bool CPhysicalObj__IsVolumeNul(const CPhysicalObj * this) { 
  //return (this -> dimension.x * this -> dimension.y * this -> dimension.z) < 1.0f; 
  //return this -> volume < 1.0f; 
  return this -> volume < 0.01f; 
}; 

TPoint3D CPhysicalObj__GetVitesse(const CPhysicalObj * this) {
  return this -> v; 
};

float CPhysicalObj__NormeVitesse(const CPhysicalObj * this) {
  return fabs(this -> v.x) + fabs(this -> v.y);
};


#if 1 
void CPhysicalObj__Acceleration_reset(CPhysicalObj * this) {
  this -> a.x   =      0.0f; 
  this -> a.y   =      0.0f; 
  this -> a.z   = - GRAVITY; 
}; 

void CPhysicalObj__Acceleration_add_vP3D(struct CPhysicalObj * this, const TPoint3D delta_a) { 
  this -> a.x += delta_a.x; 
  this -> a.y += delta_a.y; 
  this -> a.z += delta_a.z; 
}; 

void CPhysicalObj__Acceleration_add_vXYZ(struct CPhysicalObj * this, const float delta_a_x, const float delta_a_y, const float delta_a_z) { 
  this -> a.x += delta_a_x; 
  this -> a.y += delta_a_y; 
  this -> a.z += delta_a_z; 
};

void CPhysicalObj__Force_add_by_mass_unit_vP3D(struct CPhysicalObj * this, const TPoint3D foverm) { 
  this -> a.x += foverm.x; 
  this -> a.y += foverm.y; 
  this -> a.z += foverm.z; 
}; 
 
void CPhysicalObj__Force_add_by_mass_unit_vXYZ(struct CPhysicalObj * this, const float foverm_x, const float foverm_y, const float foverm_z) { 
  this -> a.x += foverm_x; 
  this -> a.y += foverm_y; 
  this -> a.z += foverm_z; 
}; 

void CPhysicalObj__Force_add_over_whole_mass_vP3D(struct CPhysicalObj * this, const TPoint3D f) { 
  this -> a.x += f.x / this -> masse; 
  this -> a.y += f.y / this -> masse; 
  this -> a.z += f.z / this -> masse; 
}; 
 
void CPhysicalObj__Force_add_over_whole_mass_vXYZ(struct CPhysicalObj * this, const float f_x, const float f_y, const float f_z) { 
  this -> a.x += f_x / this -> masse; 
  this -> a.y += f_y / this -> masse; 
  this -> a.z += f_z / this -> masse; 
}; 
 
void CPhysicalObj__Energy_add_by_mass_unit_vXYZ(struct CPhysicalObj * this, const float Eoverm_x, const float Eoverm_y, const float Eoverm_z) { 
  //                   =>  F/m = √[2 (E/m)] / ΔT 
  const float foverm_x = copysignf(1, Eoverm_x) * sqrtf(2.0f * fabs(Eoverm_x) / this -> masse) / D_T; 
  const float foverm_y = copysignf(1, Eoverm_y) * sqrtf(2.0f * fabs(Eoverm_y) / this -> masse) / D_T; 
  const float foverm_z = copysignf(1, Eoverm_z) * sqrtf(2.0f * fabs(Eoverm_z) / this -> masse) / D_T; 
  CPhysicalObj__Force_add_by_mass_unit_vXYZ(this, foverm_x, foverm_y, foverm_z); 
}; 

void CPhysicalObj__Energy_add_by_mass_unit_vP3D(struct CPhysicalObj * this, const TPoint3D Eoverm) { 
  CPhysicalObj__Energy_add_by_mass_unit_vXYZ(this, Eoverm.x, Eoverm.y, Eoverm.z); 
}; 

void CPhysicalObj__Energy_add_over_whole_mass_vXYZ(struct CPhysicalObj * this, const float E_x, const float E_y, const float E_z) { 
  CPhysicalObj__Energy_add_by_mass_unit_vXYZ(this, E_x / this -> masse, E_y / this -> masse, E_z / this -> masse); 
}; 

void CPhysicalObj__Energy_add_over_whole_mass_vP3D(struct CPhysicalObj * this, const TPoint3D E) { 
  CPhysicalObj__Energy_add_by_mass_unit_vXYZ(this, E.x / this -> masse, E.y / this -> masse, E.z / this -> masse); 
}; 

#else 
void CPhysicalObj__InitForce(CPhysicalObj * this) {
  this -> f.x   =  0.0f; 
  this -> f.y   =  0.0f; 
  this -> f.z   = -1.0f; // RL: Gravity 
  this -> f.arf =  1.0f;  
};

void CPhysicalObj__AddForce_vP3D(CPhysicalObj * this, const TPoint3D ff) {
  this -> f.x += ff.x; 
  this -> f.y += ff.y; 
  this -> f.y += ff.z; 
}; 

void CPhysicalObj__AddForce_vXYZ(CPhysicalObj * this, const float fx, const float fy, const float fz) {
  this -> f.x += fx; 
  this -> f.y += fy; 
  this -> f.y += fz; 
};

TPoint3D CPhysicalObj__GetForce(const CPhysicalObj * this) {
  return this -> f;   
}; 
#endif 


void CPhysicalObj__NewtonEngine__Frottements_apply(CPhysicalObj * this) { 
  if (!this -> is_objet_ephemere) { 
    if (this -> DansEau_huh) { 
      this -> Acceleration_add_vXYZ(this, 0.0f, 0.0f, 0.9f * GRAVITY); // RL: Archimède: Gravitation is less strong in water. 
      // FS: dans l'eau les frottements fluides sont plus importants 
      this -> CoeffFrottementFluideXY = 3.0f; 
      this -> CoeffFrottementFluideZ  = 1.0f; 
    } 
    else { 
      // FS: dans l'air, les frottements fluides sont assez petits 
      this -> CoeffFrottementFluideXY = 2.0f; 
      this -> CoeffFrottementFluideZ  = 0.0f; 
    }; 
  } 
  else { 
    // RL: Pour un objet éphémère, les frottements sont différents. 
    this -> CoeffFrottementFluideXY = 1.0f; 
    this -> CoeffFrottementFluideZ  = 15.0f; 
  }; 

#if 1 
  this -> a.x -= this -> CoeffFrottementFluideXY * (this -> v.x); 
  this -> a.y -= this -> CoeffFrottementFluideXY * (this -> v.y); 
  this -> a.z -= this -> CoeffFrottementFluideZ  * (this -> v.z); 
#else 
  // RL: The energy of a constant force F over ΔT is E = ½ F² / m * (ΔT)² 
  //     And all that energy will be transferred to V until F becomes null. 
  //     And then V will become constant. 
  // RL: The kinetic energy for a speed V is E = ½ m V² 
  //     Therefore m² V² = F² * (ΔT)² 
  //     Therefore m V = F * (ΔT) 
  //     Therefore   V = F/m * (ΔT) 
  // RL: So if V increased by ΔV, then the kinetic energy increased by 
  this -> a.x -= this -> CoeffFrottementFluide  * (this -> v.x); 
  this -> a.y -= this -> CoeffFrottementFluide  * (this -> v.y); 
  this -> a.z -= this -> CoeffFrottementFluideZ * (this -> v.z); 
#endif 
}; 

void CPhysicalObj__NewtonEngine__OneStepFoward__NoValidationYet(CPhysicalObj * this) { 
#if 0
  // FS: /*par défaut, l'objet physique n'est pas bloqué et se trouve dans une position valide*/ 
  this -> nvalid_position   = true; 
  this -> nvalid_position_x = true; 
  this -> nvalid_position_y = true; 
  this -> nvalid_position_z = true; 
#endif 

  this -> np    = this -> p; 
  
  this -> np.x += D_T * this -> v.x; 
  this -> np.y += D_T * this -> v.y; 
  this -> np.z += D_T * this -> v.z; 
  
  this -> v.x += D_T * this -> a.x; 
  this -> v.y += D_T * this -> a.y; 
  this -> v.z += D_T * this -> a.z; 
  
  CPhysicalObj__Acceleration_reset(this); // RL: The acceleration is a dirac. Has to be reset every single pass, as soon as it's used (all its energy got discontinuously transferred to 'v'). 
}; 





#if 1 
void CPhysicalObj__ValiderPosition(CPhysicalObj * this, const float lattice_ZEau) { 
  this -> AuSol_huh   = (this -> np.z <= this -> z0_n); 
  
  if (this -> np.z <= this -> z0_n) this -> np.z = this -> z0_n; 
  
  this -> DansEau_huh = (this -> np.z <= lattice_ZEau);
  
  this -> Immerge_huh = (this -> np.z + this -> d.z < lattice_ZEau); 
  
  this -> p  = this -> np; 
  this -> z0 = this -> z0_n; 
  if (this -> AuSol_huh) if (this -> v.z <= 0) { this -> v.z = 0; }; 
}; 
#else 
void CPhysicalObj__ValiderPosition(CPhysicalObj * this, const bool MoteurPhysiqueActif) {
  //char s[1000]; 
   
  if (this -> IsVolumeNul(this)) { 
    this -> nvalid_position = true; 
  }; 

  this -> AuSol_huh = this -> np.z <= this -> z0_n; 
  
  //glColor3f(1.0f, 0.0f, 0.0f );
  /*  if (volumemax < 0.99f*ancvolumemax)
      {
      sprintf(s, "ouf ! %f", volumemax);
      Text->print(0,0,1000,10,s);
      nvalid_position = true; 
      printf("gestionnaire de chocs : on accepte le nouvel état car il est meilleur que l'état pourri d'avant\n");
      printf("volume courant : %f, volume d'avant : %f", volumemax, ancvolumemax);
      }
      else
      {
      sprintf(s, "%f", volumemax);
      Text->print(0,0,1000,10,s);
      }
  */
  //this -> ancvolumemax = this -> volumemax; 
  //this -> volumemax    = 0.0f; 
  
   
   
  if (this -> nvalid_position || (!MoteurPhysiqueActif)
      /*&& nvalid_position_y && nvalid_position_z*/) { 
    //si la position est valide, on accepte la nouvelle position (np)
    this -> p = this -> np; 
  } 
  else { 
       
    /*   if (nvalid_position_x)
	 p.x = np.x;
	 else
	 v.x = 0.0f;
           
	 if (nvalid_position_y)
	 p.y = np.y;
	 else
	 v.y = 0.0f;
           
	 if (valid_position_z)
	 p.z = np.z;
	 else
	 v.z = 0.0f;
        
	 //pour qu'il y ait des rebondissements       
	 f = 0.2f*f;
	 v = f;   
        
	 valid_position_x = nvalid_position_x;
	 valid_position_y = nvalid_position_y;
	 valid_position_z = nvalid_position_z;*/
  }; 
}; 
#endif 




void CPhysicalObj__BordersAndGroundAndSlope__AdjustAndCorrectNP(CPhysicalObj * this, const CMap * Map) { 
  // RL: Borders 
  if (this -> np.x <= 0) this -> np.x = 0; 
  if (this -> np.y <= 0) this -> np.y = 0; 
  if (this -> np.x >= Map -> lattice_width ) this -> np.x = Map -> lattice_width ; 
  if (this -> np.y >= Map -> lattice_height) this -> np.y = Map -> lattice_height; 

  // RL: Ground and Slope 
#if 1 
  const float lattice_z0__n = Map -> GETZ0_vXY(Map, this -> np.x, this -> np.y); 
#else 
  const float map_x__n  = this -> np.x / Map -> lattice_width ; 
  const float map_y__n  = this -> np.y / Map -> lattice_height; 
  const float map_z0__n = Map -> GETZ0_vXY(Map, map_x__n, map_y__n); 
#endif 

  //this -> z0_n = map_z0__n; 
  this -> z0_n = lattice_z0__n; 

#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " GROUND - this -> z0_n = %f - this -> np.z = %f -  this -> p.z = %f "  "\n", __func__, this -> z0_n, this -> np.z, this -> p.z); 
#endif   
  
  if (this -> np.z > this -> z0_n) { 
    // RL: If the new position is above the ground, then no slope is to be looked at.  
    //this -> AuSol_huh = false; 
    return; 
  }; 

  //this -> AuSol_huh = this -> np.z <= this -> z0_n; 

  // RL: We can't go underground. 
  if (this -> np.z < lattice_z0__n) { 
    this -> np.z      = lattice_z0__n; 
    this -> v.z       = 0.0f; // RL: We hit the ground. 
    //this -> AuSol_huh = true; 
  }; 
  
  if (this -> p.z > this -> z0) { 
    // RL: If the old position is above the ground, then no slope is to be looked at.  
    return; 
  }; 
  
  // RL: From now onward, both 'p' & 'np' are on the ground. 

#if 0 
  fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " SLOPE  - this -> z0_n = %f - this -> np.z = %f -  this -> p.z = %f "  "\n", __func__, this -> z0_n, this -> np.z, this -> p.z); 
#endif   


  // RL: If the slope is too high, then we can't move there. 
  //if (fabs(this -> np.z - this -> p.z) > 10.0f) { 
  if (fabs(this -> np.z - this -> p.z) > 0.25f) { 
    this -> np.x = this -> p.x; 
    this -> np.y = this -> p.y; 
    this -> np.z = this -> p.z; 
    this -> z0_n = this -> z0; 
  }; 
  
}; 
 




static bool Segment__DoTheyIntersect_huh(const float __a1__, const float __a2__, const float __b1__, const float __b2__) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " __a1__ = %f, __a2__ = %f, __b1__ = %f, __b2__ = %f "  "\n", __func__, __a1__, __a2__, __b1__, __b2__ ); 
  float a1; float a2; float b1; float b2; 
  if (__a1__ < __b1__) { 
    a1 = __a1__; 
    a2 = __a2__; 
    b1 = __b1__; 
    b2 = __b2__; 
  }
  else {
    a1 = __b1__; 
    a2 = __b2__; 
    b1 = __a1__; 
    b2 = __a2__; 
  }; 
#if 0
  if (b1 < a2) { 
    fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " __a1__ = %f, __a2__ = %f, __b1__ = %f, __b2__ = %f "  "\n", __func__, __a1__, __a2__, __b1__, __b2__ ); 
  }; 
#endif 
  return (b1 < a2); 
}; 

#if 1 
int CPhysicalObj__DoTheyIntersect_huh(const CPhysicalObj * this, const CPhysicalObj * po) { 
  //fprintf(stderr, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " " Hero_o = %p "  "\n", __func__,  Hero_o ); 
  const TPoint3D d1 = this -> GetDimension(this); 
  const TPoint3D d2 = po   -> GetDimension(po  ); 
  
#if 1 
  int where = 0; 
  if (Segment__DoTheyIntersect_huh(this -> np.x - d1.x, this -> np.x + d1.x, po -> np.x - d2.x, po -> np.x + d2.x)) where |= 1; 
  if (Segment__DoTheyIntersect_huh(this -> np.y - d1.y, this -> np.y + d1.y, po -> np.y - d2.y, po -> np.y + d2.y)) where |= 2; 
  if (Segment__DoTheyIntersect_huh(this -> np.z       , this -> np.z + d1.z, po -> np.z       , po -> np.z + d2.z)) where |= 4; 
  return where; 
#else 
  if (Segment__DoTheyIntersect_huh(this -> np.x - d1.x, this -> np.x + d1.x, po -> np.x - d2.x, po -> np.x + d2.x)) return true; 
  if (Segment__DoTheyIntersect_huh(this -> np.y - d1.y, this -> np.y + d1.y, po -> np.y - d2.y, po -> np.x + d2.y)) return true; 
  if (Segment__DoTheyIntersect_huh(this -> np.z       , this -> np.z + d1.z, po -> np.z       , po -> np.z + d2.z)) return true; 
  return false; 
#endif 
  
};  
#else 
bool CPhysicalObj__TesterPosition(CPhysicalObj * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold, const CPhysicalObj * po) { 
  if (!DEBUG_MOTEUR_PHYSIQUE) return false; 
  
  TPoint3D d1 = this -> GetDimension(this, lattice_width, lattice_height, our_manifold); 
  TPoint3D d2 = po   -> GetDimension(po  , lattice_width, lattice_height, our_manifold); 
  
  /*np.x - d1.x = nouvelle abscisse la plus à gauche de notre objet 
    po->p.x - d2.x = abscisse la plus à gauche de po 
  */
  const float mnx1 = max(this -> np.x - d1.x, po -> p.x - d2.x); 
  const float mny1 = max(this -> np.y - d1.y, po -> p.y - d2.y); 
  const float mnz1 = max(this -> np.z,        po->p.z); 
  
  const float mnx2 = min(this -> np.x + d1.x, po->p.x + d2.x); 
  const float mny2 = min(this -> np.y + d1.y, po->p.y + d2.y); 
  const float mnz2 = min(this -> np.z + d1.z, po->p.z + d2.z);  
  
  /*itou avec l'ancienne position*/
  const float mx1 = max(this -> p.x - d1.x, po->p.x - d2.x); 
  const float my1 = max(this -> p.y - d1.y, po->p.y - d2.y); 
  const float mz1 = max(this -> p.z, po->p.z); 
    
  const float mx2 = min(this -> p.x + d1.x, po->p.x + d2.x); 
  const float my2 = min(this -> p.y + d1.y, po->p.y + d2.y); 
  const float mz2 = min(this -> p.z + d1.z, po->p.z + d2.z); 
    
  const float dmnx = mnx2 - mnx1;
  const float dmny = mny2 - mny1;
  const float dmnz = mnz2 - mnz1;
  float nvolume;
  
    
  if ((dmnx < 0.0f) || (dmny < 0.0f) || (dmnz < 0.0f))
    nvolume = -0.0f;
  else 
    nvolume = max(dmnx, 0.0f) * max(dmny, 0.0f) * max(dmnz, 0.0f);

  this -> volumemax += nvolume; // Here, 'this' cannot be 'const'. 
    
  if (nvolume > 0.0f) {
    /* si les parallèpipèdes ont une intersection,
       la position np n'est pas valide*/
    this -> nvalid_position = false;
    /*  po->AddForce(f);
	AddForce(po->f.x, po->f.y, po->f.z);*/
  };
  
  
  bool test_return;
  test_return = ((mnx1 <= mnx2) && (my1 <= my2) && (mz1 <= mz2));

  if (test_return)
    this -> nvalid_position_x = false;
  
  if ((mx1 <= mx2) && (mny1 <= mny2) && (mz1 <= mz2))
    this -> nvalid_position_y = false;
       
  if ((mx1 <= mx2) && (my1 <= my2) && (mnz1 <= mnz2))
    this -> nvalid_position_z = false;
         
  return !test_return;
};  
#endif 


bool CPhysicalObj__IsBloque(const CPhysicalObj * this) { 
#if 1 
  return false; 
#else 
  return !this -> nvalid_position; 
#endif 
}; 







extern bool show_choc_cube_huh; 

//void CPhysicalObj__Render(const CPhysicalObj * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold) { 
void CPhysicalObj__Render(const CPhysicalObj * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold) { 
  if (!(show_choc_cube_huh)) { return; }; 
#if AFFICHER_CUBE_DEBUG == true 
  
  //const TPoint3D d = this -> GetDimension(this, lattice_width, lattice_height, our_manifold); 
  const TPoint3D d = this -> GetDimension(this); 

#if 1 
  glColor3f(1.0f, 1.0f, 1.0f); 
#else 
  
  // FS: /* les cubes pour lesquels on a rejeté la position, sont rouges */ 
  if (!this -> nvalid_position) { 
    glColor3f(1.0f, 0.0f, 0.0f); 
  }; 
  
  if (this -> Immerge_huh) { 
    glColor3f(0.0f, 0.0f, 1.0f); 
  }; 
  
#if 0
  if (this -> IsVolumeNul(this)) { 
    glColor3f(0.0f, 0.0f, 0.0f);   
    d.x = 0.2f;
    d.y = 0.2f;
    d.z = 10.0f;
  }; 
#endif
#endif 
  
#if 1 
  our_manifold -> AfficherCube(our_manifold, 
			       /*map_i*/0, /*map_j*/0, 
			       /*map_x*/(this -> p.x - d.x) * lattice_to_map_scale_factor__x, /*map_y*/(this -> p.y - d.y) * lattice_to_map_scale_factor__y, /*map_z*/this -> p.z * lattice_to_map_scale_factor__z, 
			       /*map_dx*/2.0f*d.x * lattice_to_map_scale_factor__x, /*map_dy*/2.0f*d.y * lattice_to_map_scale_factor__y, /*map_dz*/d.z * lattice_to_map_scale_factor__z); 
#else 
  our_manifold -> AfficherCube(our_manifold, 
			       /*map_i*/0, /*map_j*/0, 
			       /*map_x*/(this -> p.x - d.x) / (float) lattice_width, /*map_y*/(this -> p.y - d.y) / (float) lattice_height, /*map_z*/this -> p.z, 
			       /*map_dx*/2.0f*d.x / (float) lattice_width, /*map_dy*/2.0f*d.y / (float) lattice_height, /*map_dz*/d.z); 
#endif 
  
  
  glColor3f(1.0f, 1.0f, 1.0f); 
  
  
#endif //* AFFICHER_CUBE_DEBUG */ 
};





CPhysicalObj * CPhysicalObj__make_assign_methods(CPhysicalObj * this) { 
  ASSIGN_METHOD(CPhysicalObj,this,make); 
  ASSIGN_METHOD(CPhysicalObj,this,make_aux); 
  ASSIGN_METHOD(CPhysicalObj,this,delete); 
  ASSIGN_METHOD(CPhysicalObj,this,delete_aux); 
  ASSIGN_METHOD(CPhysicalObj,this,copy); 
  ASSIGN_METHOD(CPhysicalObj,this,copy_aux); 
  ASSIGN_METHOD(CPhysicalObj,this,Life); 
  ASSIGN_METHOD(CPhysicalObj,this,Render); 
  ASSIGN_METHOD(CPhysicalObj,this,IsVolumeNul); 
  ASSIGN_METHOD(CPhysicalObj,this,GetDimension); 
  ASSIGN_METHOD(CPhysicalObj,this,NormeVitesse); 
  ASSIGN_METHOD(CPhysicalObj,this,GetVitesse); 
  ASSIGN_METHOD(CPhysicalObj,this,GetPosition); 
  ASSIGN_METHOD(CPhysicalObj,this,GetPosition_x); 
  ASSIGN_METHOD(CPhysicalObj,this,GetPosition_y); 
  ASSIGN_METHOD(CPhysicalObj,this,GetPosition_z); 
  ASSIGN_METHOD(CPhysicalObj,this,SetPosition_vP3D); 
  ASSIGN_METHOD(CPhysicalObj,this,SetPosition_vXY); 
  ASSIGN_METHOD(CPhysicalObj,this,SetPosition_vXYZ); 
  ASSIGN_METHOD(CPhysicalObj,this,SetZ); 
  ASSIGN_METHOD(CPhysicalObj,this,SetDimension); 
  //ASSIGN_METHOD(CPhysicalObj,this,InitForce); 
  //ASSIGN_METHOD(CPhysicalObj,this,AddForce_vP3D); 
  //ASSIGN_METHOD(CPhysicalObj,this,AddForce_vXYZ); 
  //ASSIGN_METHOD(CPhysicalObj,this,GetForce); 
  //ASSIGN_METHOD(CPhysicalObj,this,CalcNewPosition); 
  //ASSIGN_METHOD(CPhysicalObj,this,ValiderPosition); 
  //ASSIGN_METHOD(CPhysicalObj,this,TesterSol); 
  //ASSIGN_METHOD(CPhysicalObj,this,TesterPosition); 
  ASSIGN_METHOD(CPhysicalObj,this,IsBloque); 
  ASSIGN_METHOD(CPhysicalObj,this,Render); 
  ASSIGN_METHOD(CPhysicalObj,this,PerdrePV); 
  ASSIGN_METHOD(CPhysicalObj,this,Is0PV); 
  ASSIGN_METHOD(CPhysicalObj,this,SetPVMax); 
  ASSIGN_METHOD(CPhysicalObj,this,GagnerPV); 
  ASSIGN_METHOD(CPhysicalObj,this,GetPV); 
  ASSIGN_METHOD(CPhysicalObj,this,SetObjetEphemere);
  
  ASSIGN_METHOD(CPhysicalObj,this,Acceleration_add_vP3D); 
  ASSIGN_METHOD(CPhysicalObj,this,Acceleration_add_vXYZ); 
  ASSIGN_METHOD(CPhysicalObj,this,Force_add_by_mass_unit_vP3D); 
  ASSIGN_METHOD(CPhysicalObj,this,Force_add_by_mass_unit_vXYZ); 
  ASSIGN_METHOD(CPhysicalObj,this,Force_add_over_whole_mass_vP3D); 
  ASSIGN_METHOD(CPhysicalObj,this,Force_add_over_whole_mass_vXYZ); 
  ASSIGN_METHOD(CPhysicalObj,this,Energy_add_by_mass_unit_vP3D); 
  ASSIGN_METHOD(CPhysicalObj,this,Energy_add_by_mass_unit_vXYZ); 
  ASSIGN_METHOD(CPhysicalObj,this,Energy_add_over_whole_mass_vP3D); 
  ASSIGN_METHOD(CPhysicalObj,this,Energy_add_over_whole_mass_vXYZ); 
  ASSIGN_METHOD(CPhysicalObj,this,NewtonEngine__Frottements_apply             ); 
  ASSIGN_METHOD(CPhysicalObj,this,NewtonEngine__OneStepFoward__NoValidationYet); 
  ASSIGN_METHOD(CPhysicalObj,this,BordersAndGroundAndSlope__AdjustAndCorrectNP); 
  ASSIGN_METHOD(CPhysicalObj,this,DoTheyIntersect_huh); 

  this -> Force_massique__add_vXYZ = this -> Force_add_by_mass_unit_vXYZ; 
  this -> Force_massique__add_vP3D = this -> Force_add_by_mass_unit_vP3D; 
  
  return this; 
}; 

CPhysicalObj * CPhysicalObj__make(const char * filename) { 
  MALLOC_BZERO(CPhysicalObj,this);
  CPhysicalObj__make_aux(this, CPhysicalObj_subtype_None, filename); 
  return this; 
}; 

CPhysicalObj * CPhysicalObj__make_aux(CPhysicalObj * this, const int subtype, const char * filename) { 
  //printf("%s\n", __FUNCTION__);                             
  
  //CObjActionnable_make_aux(&this -> parent);
  this -> actions = CObjActionnable_make();
  
  CPhysicalObj__make_assign_methods(this);
  
  this -> subtype = subtype; 

#if 0   
  this -> nvalid_position  = true; 
  this -> valid_position_x = true; 
  this -> valid_position_y = true;  
  this -> valid_position_z = true; 
  //this -> ancvolumemax = 0.0f; 
  //this -> volumemax = 0.0f; 
#endif 
  this -> pv    = 1; 
  this -> pvmax = 1; 
  this -> is_objet_ephemere = false; 
  this -> Immerge_huh = false; 
  this -> DansEau_huh = false; 
  this -> AuSol_huh   = false; 
  this -> Hostile_huh = false; 
  this -> filename    = strcopy(filename);
  
  this -> p.x = 0.0f;
  this -> p.y = 0.0f;
  this -> p.z = 0.0f;
  this -> p.arf = 1.0f;
    
  this -> np.x = 0.0f;
  this -> np.y = 0.0f;
  this -> np.z = 0.0f;
  this -> np.arf = 1.0f;
    
  this -> v.x = 0.0f;
  this -> v.y = 0.0f;
  this -> v.z = 0.0f;
  this -> v.arf = 1.0f;  
    
  this -> d.x = 0.0f;
  this -> d.y = 0.0f;
  this -> d.z = 0.0f;
  this -> d.arf = 1.0f; 
  this -> volume = 0.0f;
    
  this -> CoeffFrottementFluideXY = 1.0f; 
  this -> CoeffFrottementFluideZ  = 0.0f; 
  
  this -> masse = 1.0f; 
  
  CPhysicalObj__Acceleration_reset(this); 
  
  return this; 
};



void CPhysicalObj__delete_aux(CPhysicalObj * this) {
  //CObjActionnable_delete_aux(&this -> parent); 
  CObjActionnable_delete(this -> actions); 
}; 

void CPhysicalObj__delete(CPhysicalObj * this) {
  CPhysicalObj__delete_aux(this); 
  free(this); 
};

CPhysicalObj * CPhysicalObj__copy_aux(CPhysicalObj * this, const CPhysicalObj * src) {
  *this = *src;
  //CObjActionnable_copy_aux(&this -> parent, &src -> parent);
  CObjActionnable_copy_aux(this -> actions, src -> actions);
  return this; 
}; 

CPhysicalObj * CPhysicalObj__copy(const CPhysicalObj * src) {
  MALLOC_BZERO(CPhysicalObj,this);
  CPhysicalObj__copy_aux(this, src); 
  return this; 
}; 




