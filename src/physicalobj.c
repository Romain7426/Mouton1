#include "global.h"
#include "physicalobj.h"
#include "text.h"
#include "map.h"

//extern CMap * Map;

//extern CPhysicalObj * CPhysicalObj_make(void);

#if 0
bool IsVolumeNul(CPhysicalObj * this) const;
TPoint3D GetDimension(CPhysicalObj * this, const CSol * Map) const;
float NormeVitesse(CPhysicalObj * this) const;
TPoint3D GetPosition(CPhysicalObj * this) const;
void SetPosition(CPhysicalObj * this, TPoint3D pos);
void SetPosition(CPhysicalObj * this, float x, float y, TMethodePlacement mp, const CMap * CMap);
void SetZ(CPhysicalObj * this, float z, TMethodePlacement mp);
void SetDimension(CPhysicalObj * this, float dx, float dy, float dz);
void InitForce(CPhysicalObj * this);
void AddForce(CPhysicalObj * this, TPoint3D f);
void AddForce(CPhysicalObj * this, float fx, float fy, float fz);
TPoint3D GetVitesse(CPhysicalObj * this) const;
TPoint3D GetForce(CPhysicalObj * this) const;
void CalcNewPosition(CPhysicalObj * this);
void ValiderPosition(CPhysicalObj * this, const bool MoteurPhysiqueActif);
void TesterSol(CPhysicalObj * this, const CSol * Map);
bool TesterPosition(CPhysicalObj * this, const CSol * Map, const CPhysicalObj * po);
bool IsBloque(CPhysicalObj * this) const;
void Render(CPhysicalObj * this, const CSol * Map) const;
void PerdrePV(CPhysicalObj * this, int nbpv);
bool Is0PV(CPhysicalObj * this) const;
void SetPVMax(CPhysicalObj * this, int nbpv);
void GagnerPV(CPhysicalObj * this, int nbpv);
int GetPV(CPhysicalObj * this) const;
void SetObjetEphemere(CPhysicalObj * this, int nbPV); 
#endif 









#if   0
  struct CPhysicalObj(struct CPhysicalObj * this);
  struct CPhysicalObj(struct CPhysicalObj * this, const char * filename);
  virtual ~struct CPhysicalObj(struct CPhysicalObj * this) {}


   

#endif










#define D_T 0.1f

TPoint3D CPhysicalObj__GetPosition(const CPhysicalObj * this) {
  return this -> p;
};


void CPhysicalObj__SetPosition_vP3D(CPhysicalObj * this, const TPoint3D pos) {
  printf("SetPosition sur %p : %f, %f, %f\n", this, pos.x, pos.y, pos.z);      
  this -> p = this -> np = pos;
};


void CPhysicalObj__SetPosition_vXY(CPhysicalObj * this, const float x, const float y, const TMethodePlacement mp, const CMap * Map) {
  /*on place corectement en (x, y)*/
  if (mp == mpRELATIF) {
    TPoint3D_add_self2(this -> p, x, y, 0); 
  }
  else { 
    TPoint3D_assign(this -> p, x, y, 0); 
  }; 
  
  /*puis on ajuste l'altitude de l'objet*/
  this -> p.z = Map -> parent.GETZ(&Map -> parent, x, y); 
};


void CPhysicalObj__SetZ(CPhysicalObj * this, const float nz, const TMethodePlacement mp) {
  this -> np.z = this -> p.z = nz + ((mp == mpRELATIF) ? this -> p.z : 0.0f);  
};

bool CPhysicalObj__IsBloque(const CPhysicalObj * this) {
  return !this -> nvalid_position;   
};



void CPhysicalObj__SetDimension(CPhysicalObj * this, const float dx, const float dy, const float dz) {
  printf("SetDimension sur %p : %f, %f, %f\n", this, dx, dy, dz);   
  this -> dimension.x = dx / 2.0f;
  this -> dimension.y = dy / 2.0f;
  this -> dimension.z = dz / 2.0f;   
};   

bool CPhysicalObj__IsVolumeNul(const CPhysicalObj * this) {
  return (this -> dimension.x * this -> dimension.y * this -> dimension.z) < 1.0f;
};

void CPhysicalObj__InitForce(CPhysicalObj * this) {
  this -> f.x   = 0.0f; 
  this -> f.y   = 0.0f; 
  this -> f.z   = 0.0f; 
  this -> f.arf = 1.0f;  
};


void CPhysicalObj__AddForce_vP3D(CPhysicalObj * this, const TPoint3D ff) {
  TPoint3D_add_self(this -> f, ff);
};


TPoint3D CPhysicalObj__GetForce(const CPhysicalObj * this) {
  return this -> f;   
};   


TPoint3D CPhysicalObj__GetVitesse(const CPhysicalObj * this) {
  return this -> v; 
};

void CPhysicalObj__AddForce_vXYZ(CPhysicalObj * this, const float fx, const float fy, const float fz) {
  TPoint3D_add_self2(this -> f, fx, fy, fz);
};


void CPhysicalObj__CalcNewPosition(CPhysicalObj * this) {
  /* force de frottement fluide*/
  this -> f.x -= this -> CoeffFrottementFluide  * this -> v.x;
  this -> f.y -= this -> CoeffFrottementFluide  * this -> v.y;
  this -> f.z -= this -> CoeffFrottementFluideZ * this -> v.z;
  
  //this -> v  +=  D_T * this -> f;
  TPoint3D_add_self(this -> v, TPoint3D_scalar_mul(D_T, this -> f)); 
  //this -> np +=  D_T * this -> v;
  TPoint3D_add_self(this -> np, TPoint3D_scalar_mul(D_T, this -> v)); 
  
  /*par défaut, l'objet physique n'est pas blogué et se trouve
    dans une bonne position*/
   
  this -> nvalid_position   = true;
  this -> nvalid_position_x = true;
  this -> nvalid_position_y = true;
  this -> nvalid_position_z = true;
};



void CPhysicalObj__ValiderPosition(CPhysicalObj * this, const bool MoteurPhysiqueActif) {
  //char s[1000]; 
   
  /*un objet éphémère perd un point de vie à chaque tour*/
  if (this -> is_objet_ephemere)
    this -> PerdrePV(this, 1);
   
  if (this -> IsVolumeNul(this))
    this -> nvalid_position = true;
       
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
  this -> ancvolumemax = this -> volumemax;
  this -> volumemax = 0.0f;
    
   
   
  if (this -> nvalid_position || (!MoteurPhysiqueActif)
      /*&& nvalid_position_y && nvalid_position_z*/)
    //si la position est valide, on accepte la nouvelle position (np)
    this -> p = this -> np;
  else
    { 
       
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
    }  
};    




float CPhysicalObj__NormeVitesse(const CPhysicalObj * this) {
  return fabs(this -> v.x) + fabs(this -> v.y);
};


void CPhysicalObj__TesterSol(CPhysicalObj * this, const CSol * Sol)  {
  const float zmap = Sol -> GETZ(Sol, this -> p.x, this -> p.y);
  
  // gestion de l'altitude
  if (this -> np.z < zmap) {
    this -> np.z = zmap;
    this -> v.z = 0.0f;
    this -> AuSol = true;
  }
  else {
    this -> AuSol = false;
  };
  
  if (TPoint2D_Norme1(Sol -> Differentiel(Sol, this -> np)) > 10.0f) {      
    this -> np.x = this -> p.x;
    this -> np.y = this -> p.y;
  };

  // l'objet ne sort pas de la carte
  if (this -> np.y < 0) this -> np.y = 0;
  if (this -> np.x < 0) this -> np.x = 0;
  if (this -> np.y > Sol -> GetTailleY(Sol) - 1.0f) this -> np.y = Sol->GetTailleY(Sol)-1.0f;
  if (this -> np.x > Sol -> GetTailleX(Sol) - 1.0f) this -> np.x = Sol->GetTailleX(Sol)-1.0f;
};
 
 
TPoint3D CPhysicalObj__GetDimension(const CPhysicalObj * this, const CSol * Sol) {
  TPoint3D d = this -> dimension;
  /*si ce n'est pas compressible, dans le repère adapté,
    les objets paraissent plus grands...*/
  if (!this -> Compressible) {
    d.x = d.x / Sol -> FacteurCompression(Sol, this -> p.y);
  };
  return d;   
};  


bool CPhysicalObj__TesterPosition(CPhysicalObj * this, const CSol * Sol, const CPhysicalObj * po) {
  if (!DEBUG_MOTEUR_PHYSIQUE) return false;   
  
  TPoint3D d1 = this -> GetDimension(this, Sol);
  TPoint3D d2 = po   -> GetDimension(po,   Sol);
      
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



void CPhysicalObj__PerdrePV(CPhysicalObj * this, const int nbpv) {
  this -> pv -= nbpv;
}    

void CPhysicalObj__SetPVMax(CPhysicalObj * this, const int nbpv) {
  this -> pv = this -> pvmax = nbpv;
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
  this -> SetPVMax(this, nbPV);
}; 


void CPhysicalObj__Render(const CPhysicalObj * this, const CSol * Sol) {
#if AFFICHER_CUBE_DEBUG == true
          
  TPoint3D d = this -> GetDimension(this, Sol); 
  
  /* les cubes pour lesquels on a rejeté la position, sont rouges */
  if (! this -> nvalid_position) {
    glColor3f(1.0f, 0.0f, 0.0f);
  }
  
  if (this -> Immerge) {
    glColor3f(0.0f, 0.0f, 1.0f); 
  }
  
#if 0
  if (this -> IsVolumeNul(this)) {
    glColor3f(0.0f, 0.0f, 0.0f);   
    d.x = 0.2f;
    d.y = 0.2f;
    d.z = 10.0f;
  }
#endif
  
#if 1
  Sol -> AfficherCube(Sol, this -> p.x - d.x, this -> p.y - d.y, this -> p.z, 2*d.x, 2*d.y, d.z);
  
  glColor3f(1.0f, 1.0f, 1.0f);
#endif
#endif /* AFFICHER_CUBE_DEBUG */       
};





CPhysicalObj * CPhysicalObj_make_assign_methods(CPhysicalObj * this) { 
  ASSIGN_METHOD(CPhysicalObj,this,Render); 
  ASSIGN_METHOD(CPhysicalObj,this,IsVolumeNul); 
  ASSIGN_METHOD(CPhysicalObj,this,GetDimension); 
  ASSIGN_METHOD(CPhysicalObj,this,NormeVitesse); 
  ASSIGN_METHOD(CPhysicalObj,this,GetPosition); 
  ASSIGN_METHOD(CPhysicalObj,this,SetPosition_vP3D); 
  ASSIGN_METHOD(CPhysicalObj,this,SetPosition_vXY); 
  ASSIGN_METHOD(CPhysicalObj,this,SetZ); 
  ASSIGN_METHOD(CPhysicalObj,this,SetDimension); 
  ASSIGN_METHOD(CPhysicalObj,this,InitForce); 
  ASSIGN_METHOD(CPhysicalObj,this,AddForce_vP3D); 
  ASSIGN_METHOD(CPhysicalObj,this,AddForce_vXYZ); 
  ASSIGN_METHOD(CPhysicalObj,this,GetVitesse); 
  ASSIGN_METHOD(CPhysicalObj,this,GetForce); 
  ASSIGN_METHOD(CPhysicalObj,this,CalcNewPosition); 
  ASSIGN_METHOD(CPhysicalObj,this,ValiderPosition); 
  ASSIGN_METHOD(CPhysicalObj,this,TesterSol); 
  ASSIGN_METHOD(CPhysicalObj,this,TesterPosition); 
  ASSIGN_METHOD(CPhysicalObj,this,IsBloque); 
  ASSIGN_METHOD(CPhysicalObj,this,Render); 
  ASSIGN_METHOD(CPhysicalObj,this,PerdrePV); 
  ASSIGN_METHOD(CPhysicalObj,this,Is0PV); 
  ASSIGN_METHOD(CPhysicalObj,this,SetPVMax); 
  ASSIGN_METHOD(CPhysicalObj,this,GagnerPV); 
  ASSIGN_METHOD(CPhysicalObj,this,GetPV); 
  ASSIGN_METHOD(CPhysicalObj,this,SetObjetEphemere);
  return this; 
}; 

CPhysicalObj * CPhysicalObj_make(const char * filename) { 
  MALLOC_BZERO(CPhysicalObj,this);
  CPhysicalObj_make_aux(this, CPhysicalObj_subtype_None, filename); 
  return this; 
}; 

CPhysicalObj * CPhysicalObj_make_aux(CPhysicalObj * this, const int subtype, const char * filename) { 
  printf("%s\n", __FUNCTION__);                             

  CObjActionnable_make_aux(&this -> parent);

  CPhysicalObj_make_assign_methods(this);
  
  this -> subtype = subtype; 

  this -> nvalid_position = true; 
  this -> valid_position_x = true; 
  this -> valid_position_y = true;  
  this -> valid_position_z = true; 
  this -> ancvolumemax = 0.0f; 
  this -> volumemax = 0.0f; 
  this -> pv = 1; 
  this -> pvmax = 1; 
  this -> is_objet_ephemere = false; 
  this -> Immerge = false; 
  this -> DansEau = false; 
  this -> AuSol = false; 
  this -> Hostile = false; 
  this -> filename = strcopy(filename);

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
    
  this -> dimension.x = 0.0f;
  this -> dimension.y = 0.0f;
  this -> dimension.z = 0.0f;
  this -> dimension.arf = 1.0f; 
    
  this -> InitForce(this);   

  return this; 
};



void CPhysicalObj_delete_aux(CPhysicalObj * this) {
  CObjActionnable_delete_aux(&this -> parent);
}; 

void CPhysicalObj_delete(CPhysicalObj * this) {
  CPhysicalObj_delete_aux(this); 
  free(this); 
};

CPhysicalObj * CPhysicalObj_copy_aux(CPhysicalObj * this, const CPhysicalObj * src) {
  *this = *src;
  CObjActionnable_copy_aux(&this -> parent, &src -> parent);
  return this; 
}; 

CPhysicalObj * CPhysicalObj_copy(const CPhysicalObj * src) {
  MALLOC_BZERO(CPhysicalObj,this);
  CPhysicalObj_copy_aux(this, src); 
  return this; 
}; 




