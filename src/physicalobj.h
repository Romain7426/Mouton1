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


  bool (* IsVolumeNul)(const struct CPhysicalObj * this);
  TPoint3D (* GetDimension)(const struct CPhysicalObj * this, const CSol * Map);
  float (* NormeVitesse)(const struct CPhysicalObj * this);
  TPoint3D (* GetPosition)(const struct CPhysicalObj * this);
  void (* SetPosition_vTPoint3D)(struct CPhysicalObj * this, TPoint3D pos);
  void (* SetPosition_vExpanded)(struct CPhysicalObj * this, float x, float y, TMethodePlacement mp, const CMap * CMap);
  void (* SetZ)(struct CPhysicalObj * this, float z, TMethodePlacement mp);
  void (* SetDimension)(struct CPhysicalObj * this, float dx, float dy, float dz);
    
  /* pour gérer les forces dans le moteur physique )(struct CPhysicalObj * this, appelé à chaque boucle) */
  void (* InitForce)(struct CPhysicalObj * this);
  void (* AddForce)(struct CPhysicalObj * this, TPoint3D f);
  //void (* AddForce_vTPoint3D)(struct CPhysicalObj * this, TPoint3D f);
  //void (* AddForce_vExpanded)(struct CPhysicalObj * this, float fx, float fy, float fz);
  TPoint3D (* GetVitesse)(const struct CPhysicalObj * this);
  TPoint3D (* GetForce)(const struct CPhysicalObj * this);
  void (* CalcNewPosition)(struct CPhysicalObj * this);
  void (* ValiderPosition)(const struct CPhysicalObj * this, const bool MoteurPhysiqueActif);
  void (* TesterSol)(struct CPhysicalObj * this, const CSol * Map);
  // friend void (* TesterPosition)(struct CPhysicalObj * this, struct CPhysicalObj * po);

  /* retourne vrai ssi il n'y a pas de colision */
  bool (* TesterPosition)(struct CPhysicalObj * this, const CSol * Map, const struct CPhysicalObj * po);
  bool (* IsBloque)(const struct CPhysicalObj * this);
  void (* Render)(const struct CPhysicalObj * this, const CSol * Map);

  // gestion des points de vies
  void (* PerdrePV)(struct CPhysicalObj * this, int nbpv);
  bool (* Is0PV)(const struct CPhysicalObj * this);
  void (* SetPVMax)(struct CPhysicalObj * this, int nbpv);
  void (* GagnerPV)(struct CPhysicalObj * this, int nbpv);
  int (* GetPV)(const struct CPhysicalObj * this);

  void (* SetObjetEphemere)(struct CPhysicalObj * this, int nbPV); 

};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CPhysicalObj);
DECLARE_NEW_OPERATOR_FOR_STRUCT(CPhysicalObj);









#endif /* PHYSICALOBJ_HPP */

