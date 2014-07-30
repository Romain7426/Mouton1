#ifndef PHYSICALOBJ_HPP
#define PHYSICALOBJ_HPP

struct TPoint2D;
struct TPoint3D;
struct CSol;
struct CPhysicalObj;
struct CBonhomme;
struct CEvenement;
struct CObjActionnable;
struct CMap;

#include "action.h"
#include "sol.h"




enum TMethodePlacement {mpABSOLU, mpRELATIF};
TYPEDEF_TYPENAME_WITHOUT_ENUM(TMethodePlacement);


/* 
   Ceci est une structe abstraite pour définir des choses matérielles.
   But : modéliser un point matériel (position, vitesse, forces...)
*/
//struct CPhysicalObj : public CObjActionnable {
struct CPhysicalObj {
  CObjActionnable parent1;
  //protected:
    
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
    
  //public:
  //virtual const char * const filename;
  const char * const filename;


  //public:

    
  bool Immerge; /* vaut vrai si la chose est entièrement immergé dans l'eau */
  bool DansEau; /* vaut vrai si la chose est dans l'eau (^m si c'est qu'un doigt de pied */
  bool Compressible; /* vaut vrai ssi ça se compresse avec le tore
			Typiquement, être vivant, bonhomme --> faux
			pierre, maison ---> vrai */
                   
  bool Fixe; /* calcule-t-on les forces appliqués à l'objet ?? */
    
  bool AuSol;
  bool Hostile;

  float CoeffFrottementFluide, CoeffFrottementFluideZ; 


#if   
  CPhysicalObj(CPhysicalObj * this);
  CPhysicalObj(CPhysicalObj * this, const char * filename);
  virtual ~CPhysicalObj(CPhysicalObj * this) {}
#endif

  bool IsVolumeNul(CPhysicalObj * this) const;
    
  TPoint3D GetDimension(CPhysicalObj * this, const CSol * Map) const;
  float NormeVitesse(CPhysicalObj * this) const;

  TPoint3D GetPosition(CPhysicalObj * this) const;
    
  void SetPosition(CPhysicalObj * this, TPoint3D pos);
  
  void SetPosition(CPhysicalObj * this, float x, float y, TMethodePlacement mp, const CMap * CMap);
  void SetZ(CPhysicalObj * this, float z, TMethodePlacement mp);
  
  void SetDimension(CPhysicalObj * this, float dx, float dy, float dz);
    
  /* pour gérer les forces dans le moteur physique (CPhysicalObj * this, appelé à chaque boucle) */
  void InitForce(CPhysicalObj * this);
  void AddForce(CPhysicalObj * this, TPoint3D f);
  void AddForce(CPhysicalObj * this, float fx, float fy, float fz);
  TPoint3D GetVitesse(CPhysicalObj * this) const;
  TPoint3D GetForce(CPhysicalObj * this) const;
  void CalcNewPosition(CPhysicalObj * this);
  void ValiderPosition(CPhysicalObj * this, const bool MoteurPhysiqueActif);
    
  void TesterSol(CPhysicalObj * this, const CSol * Map);
  // friend void TesterPosition(CPhysicalObj * this, CPhysicalObj * po);
    
  /* retourne vrai ssi il n'y a pas de colision */
  bool TesterPosition(CPhysicalObj * this, const CSol * Map, const CPhysicalObj * po);
    
  
  bool IsBloque(CPhysicalObj * this) const;



  /* 
     un objet physique pur ne s'affiche pas...
     mais ses descendants (CPhysicalObj * this, bonhomme et objnonanime oui)
     d'où le mot clé "virtual" 
  */
  virtual void Render(CPhysicalObj * this, const CSol * Map) const;

 
  // gestion des points de vies
  void PerdrePV(CPhysicalObj * this, int nbpv);
  bool Is0PV(CPhysicalObj * this) const;
  void SetPVMax(CPhysicalObj * this, int nbpv);
  void GagnerPV(CPhysicalObj * this, int nbpv);
  int GetPV(CPhysicalObj * this) const;

  void SetObjetEphemere(CPhysicalObj * this, int nbPV); 




};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CPhysicalObj * this, CPhysicalObj);
DECLARE_NEW_OPERATOR_FOR_STRUCT(CPhysicalObj * this, CPhysicalObj);






  virtual void Render(CPhysicalObj * this, const CSol * Map) const
  {
#if AFFICHER_CUBE_DEBUG == true
          
    TPoint3D d = GetDimension(CPhysicalObj * this, Map);      

    /* les cubes pour lesquels on a rejeté la position, sont rouges */
    if (CPhysicalObj * this, !nvalid_position) {
      glColor3f(CPhysicalObj * this, 1.0f, 0.0f, 0.0f);
    }
         
    if (CPhysicalObj * this, Immerge) {
      glColor3f(CPhysicalObj * this, 0.0f, 0.0f, 1.0f); 
    }
         
#if 0
    if (CPhysicalObj * this, IsVolumeNul(CPhysicalObj * this, )) {
      glColor3f(CPhysicalObj * this, 0.0f, 0.0f, 0.0f);   
      d.x = 0.2f;
      d.y = 0.2f;
      d.z = 10.0f;
    }
#endif
    
#if 1
    Map -> AfficherCube(CPhysicalObj * this, p.x - d.x, p.y - d.y, p.z, 2*d.x, 2*d.y, d.z);
         
    glColor3f(CPhysicalObj * this, 1.0f, 1.0f, 1.0f);
#endif
#endif /* AFFICHER_CUBE_DEBUG */       
  };
   






#endif /* PHYSICALOBJ_HPP */

