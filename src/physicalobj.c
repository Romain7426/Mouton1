#include "global.h"
#include "physicalobj.h"
#include "text.h"
#include "map.h"

//extern CMap * Map;

CPhysicalObj(CPhysicalObj * this);
CPhysicalObj(CPhysicalObj * this, const char * filename);
virtual ~CPhysicalObj(CPhysicalObj * this) {}

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
virtual void Render(CPhysicalObj * this, const CSol * Map) const;
void PerdrePV(CPhysicalObj * this, int nbpv);
bool Is0PV(CPhysicalObj * this) const;
void SetPVMax(CPhysicalObj * this, int nbpv);
void GagnerPV(CPhysicalObj * this, int nbpv);
int GetPV(CPhysicalObj * this) const;
void SetObjetEphemere(CPhysicalObj * this, int nbPV); 










#if   0
  struct CPhysicalObj(struct CPhysicalObj * this);
  struct CPhysicalObj(struct CPhysicalObj * this, const char * filename);
  virtual ~struct CPhysicalObj(struct CPhysicalObj * this) {}


  virtual void Render(struct CPhysicalObj * this, const CSol * Map) const
  {
#if AFFICHER_CUBE_DEBUG == true
          
    TPoint3D d = GetDimension(struct CPhysicalObj * this, Map);      

    /* les cubes pour lesquels on a rejeté la position, sont rouges */
    if (struct CPhysicalObj * this, !nvalid_position) {
      glColor3f(struct CPhysicalObj * this, 1.0f, 0.0f, 0.0f);
    }
         
    if (struct CPhysicalObj * this, Immerge) {
      glColor3f(struct CPhysicalObj * this, 0.0f, 0.0f, 1.0f); 
    }
         
#if 0
    if (struct CPhysicalObj * this, IsVolumeNul(struct CPhysicalObj * this, )) {
      glColor3f(struct CPhysicalObj * this, 0.0f, 0.0f, 0.0f);   
      d.x = 0.2f;
      d.y = 0.2f;
      d.z = 10.0f;
    }
#endif
    
#if 1
    Map -> AfficherCube(struct CPhysicalObj * this, p.x - d.x, p.y - d.y, p.z, 2*d.x, 2*d.y, d.z);
         
    glColor3f(struct CPhysicalObj * this, 1.0f, 1.0f, 1.0f);
#endif
#endif /* AFFICHER_CUBE_DEBUG */       
  };
   

#endif










#define D_T 0.1f

//bool MoteurPhysiqueActif = true;


CPhysicalObj::CPhysicalObj(void) : filename(NULL) {
  CPhysicalObj("--NULL--");
}

CPhysicalObj::CPhysicalObj(const char * filename) :
  nvalid_position(true),
  valid_position_x(true),
  valid_position_y(true), 
  valid_position_z(true),
  ancvolumemax(0.0f),
  volumemax(0.0f),
  pv(1),
  pvmax(1),
  is_objet_ephemere(false),
  Immerge(false),
  DansEau(false),
  AuSol(false),
  Hostile(false),
  filename(strcopy(filename))
{
  printf("CPhysicalObj::CPhysicalObj()\n");                             

  p.x = 0.0f;
  p.y = 0.0f;
  p.z = 0.0f;
  p.arf = 1.0f;
    
  np.x = 0.0f;
  np.y = 0.0f;
  np.z = 0.0f;
  np.arf = 1.0f;
    
  v.x = 0.0f;
  v.y = 0.0f;
  v.z = 0.0f;
  v.arf = 1.0f;  
    
  dimension.x = 0.0f;
  dimension.y = 0.0f;
  dimension.z = 0.0f;
  dimension.arf = 1.0f; 
    
  InitForce();   
}



TPoint3D CPhysicalObj::GetPosition() const {
  return p;
}


void CPhysicalObj::SetPosition(TPoint3D pos) {
  printf("SetPosition sur %p : %f, %f, %f\n", this, pos.x, pos.y, pos.z);      
  p = np = pos;
}


void CPhysicalObj::SetPosition(float x, float y, TMethodePlacement mp, const CMap * Map) {
  p = ((mp == mpRELATIF) ? p : Point3D(0.0f, 0.0f, 0.0f))
    + Point3D(x, y, 0.0f);
  /*on place corectement en (x, y)*/
  
  p.z = Map->GETZ(x, y);    
  /*puis on ajuste l'altitude de l'objet*/

}


void CPhysicalObj::SetZ(float nz, TMethodePlacement mp) {
  np.z = p.z = ((mp == mpRELATIF) ? p.z : 0.0f) + nz;  
}

bool CPhysicalObj::IsBloque() const {
  return !nvalid_position;   
}    



void CPhysicalObj::SetDimension(float dx, float dy, float dz) {
  printf("SetDimension sur %p : %f, %f, %f\n", this, dx, dy, dz);   
  dimension.x = dx / 2.0f;
  dimension.y = dy / 2.0f;
  dimension.z = dz / 2.0f;   
    
}    

bool CPhysicalObj::IsVolumeNul() const {
  return (dimension.x * dimension.y * dimension.z) < 1.0f;
}    

void CPhysicalObj::InitForce() {
  f.x = 0.0f;
  f.y = 0.0f;
  f.z = 0.0f;
  f.arf = 1.0f; 
    
}


void CPhysicalObj::AddForce(TPoint3D ff) {
  f = f + ff;
}


TPoint3D CPhysicalObj::GetForce() const {
  return f;   
}    


TPoint3D CPhysicalObj::GetVitesse() const {
  return v;   
} 

void CPhysicalObj::AddForce(float fx, float fy, float fz) {
  f.x = f.x + fx;
  f.y = f.y + fy;
  f.z = f.z + fz;
}


void CPhysicalObj::CalcNewPosition() {
  /* force de frottement fluide*/
  f.x = f.x + -CoeffFrottementFluide * v.x;
  f.y = f.y + -CoeffFrottementFluide * v.y;
  f.z = f.z + -CoeffFrottementFluideZ * v.z;
   
   
  v = v + D_T * f;
  np = p + D_T * v;
  
  /*par défaut, l'objet physique n'est pas blogué et se trouve
    dans une bonne position*/
   
  nvalid_position = true;
  nvalid_position_x = true;
  nvalid_position_y = true;
  nvalid_position_z = true;
  
  
   
   
}



void CPhysicalObj::ValiderPosition(const bool MoteurPhysiqueActif) {
  //char s[1000]; 
   
  /*un objet éphémère perd un point de vie à chaque tour*/
  if (is_objet_ephemere)
    PerdrePV(1);
   
  if (IsVolumeNul())
    nvalid_position = true;
       
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
  ancvolumemax = volumemax;
  volumemax = 0.0f;
    
   
   
  if (nvalid_position || (!MoteurPhysiqueActif)
      /*&& nvalid_position_y && nvalid_position_z*/)
    //si la position est valide, on accepte la nouvelle position (np)
    p = np;
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
}    




float CPhysicalObj::NormeVitesse(void) const {
  return fabs(v.x) + fabs(v.y);
}


void CPhysicalObj::TesterSol(const CSol * Map)  {
  float zmap = Map->GETZ(p.x, p.y);
  
  // gestion de l'altitude
  if (np.z < zmap) {
    np.z = zmap;
    v.z = 0.0f;
    AuSol = true;
  }
  else
    AuSol = false;
  
  if (Norme1(Map->Differentiel(np)) > 10.0f) {      
    np.x = p.x;
    np.y = p.y;
  }

  // l'objet ne sort pas de la carte
  if (np.y < 0) np.y = 0;
  if (np.x < 0) np.x = 0;
  if (np.y > Map->GetTailleY()-1.0f) np.y = Map->GetTailleY()-1.0f;
  if (np.x > Map->GetTailleX()-1.0f) np.x = Map->GetTailleX()-1.0f;

}   
 
 
TPoint3D CPhysicalObj::GetDimension(const CSol * Map) const {
  TPoint3D d = dimension;
  /*si ce n'est pas compressible, dans le repère adapté,
    les objets paraissent plus grands...*/
  if (!Compressible)
    d.x = d.x / Map->FacteurCompression(p.y);
  return d;   
}    


bool CPhysicalObj::TesterPosition(const CSol * Map, const CPhysicalObj * po) {
  if (!DEBUG_MOTEUR_PHYSIQUE) return false;   
  
  TPoint3D d1 = GetDimension(Map);
  TPoint3D d2 = po->GetDimension(Map);
      
  /*np.x - d1.x = nouvelle abscisse la plus à gauche de notre objet
    po->p.x - d2.x = abscisse la plus à gauche de po
  */
  float mnx1 = max(np.x - d1.x, po->p.x - d2.x); 
  float mny1 = max(np.y - d1.y, po->p.y - d2.y); 
  float mnz1 = max(np.z, po->p.z); 
  
  float mnx2 = min(np.x + d1.x, po->p.x + d2.x); 
  float mny2 = min(np.y + d1.y, po->p.y + d2.y); 
  float mnz2 = min(np.z + d1.z, po->p.z + d2.z);  
  
  /*itou avec l'ancienne position*/
  float mx1 = max(p.x - d1.x, po->p.x - d2.x); 
  float my1 = max(p.y - d1.y, po->p.y - d2.y); 
  float mz1 = max(p.z, po->p.z); 
    
  float mx2 = min(p.x + d1.x, po->p.x + d2.x); 
  float my2 = min(p.y + d1.y, po->p.y + d2.y); 
  float mz2 = min(p.z + d1.z, po->p.z + d2.z); 
    
  float dmnx = mnx2 - mnx1;
  float dmny = mny2 - mny1;
  float dmnz = mnz2 - mnz1;
  float nvolume;
  
    
  if ((dmnx < 0.0f) || (dmny < 0.0f) || (dmnz < 0.0f))
    nvolume = -0.0f;
  else 
    nvolume = max(dmnx, 0.0f) * max(dmny, 0.0f) * max(dmnz, 0.0f);

  volumemax += nvolume;
    
  if (nvolume > 0.0f)
    {
      /* si les parallèpipèdes ont une intersection,
         la position np n'est pas valide*/
      nvalid_position = false;
      /*  po->AddForce(f);
          AddForce(po->f.x, po->f.y, po->f.z);*/
    }
  
  
  bool test_return;
  test_return = ((mnx1 <= mnx2) && (my1 <= my2) && (mz1 <= mz2));

  if (test_return)
    nvalid_position_x = false;
  
  if ((mx1 <= mx2) && (mny1 <= mny2) && (mz1 <= mz2))
    nvalid_position_y = false;
       
  if ((mx1 <= mx2) && (my1 <= my2) && (mnz1 <= mnz2))
    nvalid_position_z = false;
         
  return !test_return;
}    



void CPhysicalObj::PerdrePV(int nbpv) {
  pv-=nbpv;
}    

void CPhysicalObj::SetPVMax(int nbpv) {
  pv = pvmax = nbpv;
}


void CPhysicalObj::GagnerPV(int nbpv) {
  pv+=nbpv;
  if (pv > pvmax) pv = pvmax;
}

int CPhysicalObj::GetPV() const
{
  return pv;   
}  


bool CPhysicalObj::Is0PV() const
{
  return (pv<=0);  
}


void CPhysicalObj::SetObjetEphemere(int nbPV) {
  is_objet_ephemere = true;
  SetPVMax(nbPV);
     
}


