#ifndef PHYSICALOBJ_HPP
#define PHYSICALOBJ_HPP

struct TPoint2D;
struct TPoint3D;
class CSol;
class CPhysicalObj;
class CBonhomme;
class CEvenement;
class CObjActionnable;
class CMap;

#include "action.hpp"
#include "sol.hpp"




enum TMethodePlacement {mpABSOLU, mpRELATIF};

/* 
   Ceci est une classe abstraite pour définir des choses matérielles.
   But : modéliser un point matériel (position, vitesse, forces...)
*/
class CPhysicalObj : public CObjActionnable {
protected:
    
  bool nvalid_position;
  bool valid_position_x, valid_position_y, valid_position_z;
  bool nvalid_position_x, nvalid_position_y, nvalid_position_z;
  TPoint3D f, v, p, np, dimension;
  float ancvolumemax, volumemax;
  
  int pv, pvmax;
  bool is_objet_ephemere;
    
  /* pour la plupart des objets (sauf les 3DS),
     la zone de choc est un parallpipède
     de taille dimension (contenant longueur, largeur, hauteur)

     le centre de la face de base (en bas) est le point p*/
       
  /*force (accélération),
    vitesse,
    position,
    nouvelle position (calculée),
    dimension*/
    

public:

    
  bool Immerge; /* vaut vrai si la chose est entièrement immergé dans l'eau */
  bool DansEau; /* vaut vrai si la chose est dans l'eau (^m si c'est qu'un doigt de pied */
  bool Compressible; /* vaut vrai ssi ça se compresse avec le tore
			Typiquement, être vivant, bonhomme --> faux
			pierre, maison ---> vrai */
                   
  bool Fixe; /* calcule-t-on les forces appliqués à l'objet ?? */
    
  bool AuSol;
  bool Hostile;
  
  bool IsVolumeNul(void) const;
    
  TPoint3D GetDimension(const CSol * Map) const;
  float NormeVitesse(void) const;
  float CoeffFrottementFluide, CoeffFrottementFluideZ; 


  CPhysicalObj(void);
  CPhysicalObj(const char * filename);
  virtual ~CPhysicalObj(void) {}


  TPoint3D GetPosition(void) const;
    
  void SetPosition(TPoint3D pos);
  
  void SetPosition(float x, float y, TMethodePlacement mp, const CMap * CMap);
  void SetZ(float z, TMethodePlacement mp);
  
  void SetDimension(float dx, float dy, float dz);
    
  /* pour gérer les forces dans le moteur physique (appelé à chaque boucle) */
  void InitForce(void);
  void AddForce(TPoint3D f);
  void AddForce(float fx, float fy, float fz);
  TPoint3D GetVitesse(void) const;
  TPoint3D GetForce(void) const;
  void CalcNewPosition(void);
  void ValiderPosition(const bool MoteurPhysiqueActif);
    
  void TesterSol(const CSol * Map);
  // friend void TesterPosition(CPhysicalObj * po);
    
  /* retourne vrai ssi il n'y a pas de colision */
  bool TesterPosition(const CSol * Map, const CPhysicalObj * po);
    
  
  bool IsBloque(void) const;



  /* 
     un objet physique pur ne s'affiche pas...
     mais ses descendants (bonhomme et objnonanime oui)
     d'où le mot clé "virtual" 
  */
  virtual void Render(const CSol * Map) const
  {
#if AFFICHER_CUBE_DEBUG == true
          
    TPoint3D d = GetDimension(Map);      

    /* les cubes pour lesquels on a rejeté la position, sont rouges */
    if (!nvalid_position) {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
         
    if (Immerge) {
      glColor3f(0.0f, 0.0f, 1.0f); 
    }
         
#if 0
    if (IsVolumeNul()) {
      glColor3f(0.0f, 0.0f, 0.0f);   
      d.x = 0.2f;
      d.y = 0.2f;
      d.z = 10.0f;
    }
#endif
    
#if 1
    Map -> AfficherCube(p.x - d.x, p.y - d.y, p.z, 2*d.x, 2*d.y, d.z);
         
    glColor3f(1.0f, 1.0f, 1.0f);
#endif
#endif /* AFFICHER_CUBE_DEBUG */       
  };
   


 
  // gestion des points de vies
  void PerdrePV(int nbpv);
  bool Is0PV(void) const;
  void SetPVMax(int nbpv);
  void GagnerPV(int nbpv);
  int GetPV(void) const;

  void SetObjetEphemere(int nbPV); 




public:
  //virtual const char * const filename;
  const char * const filename;

};


#endif /* PHYSICALOBJ_HPP */

