#ifndef BONHOMME_HPP
#define BONHOMME_HPP


#include "ressource.hpp"
#include "liste.hpp"

class CMap;
class CPhysicalObj;

#include "physicalobj.hpp"



#define MAX_MEMBRE 10
#define MEMBRE_AVEC_ARME 0

#define MAX_IND_ANGLE 10


TPoint3D DirectionToVecteur(TDirection d);


struct TMembre;
class COrdreDeplacement;
class CPantin;


class COrdreDeplacement {
public:
/*ordre de déplacement vers le point destination (on ne l'atteint pas forcément)
(en fait on ne l'atteint que sur une coordonnée*/
    TDirection direction;
    TPoint3D destination;
};


struct TMembre { 
  float px, py, pz;
  
  float angle_max, angle;
  float taille_x;
  float taille_y;
  float taille_pixelx, taille_pixely;
  
  ressource<CTexture> * resTexture;
  
  CPantin * Pantin;
};    


// Un pantin est une liste de membres où chaque membre peut éventuellement contenir un pantin fils
class CPantin {
public:
  int NbMembres;
  TMembre Membre[MAX_MEMBRE];  
       
public:
  CPantin(void);
  ~CPantin(void); 
  /*pour ajouter la tête, le corps, les bras, les oreilles etc...
    mais aussi une épée au bout d'un bras etc...*/
  /* fichier_image : fichier image par exemple "tete.bmp" (contenant
     les images des vues (face, profilD, dos)
     px, py, pz : position supérieure au milieu
     tx, ty : taille d'une image en pixel
          
     renvoit le numéro du membre*/
  int AjouterMembre(const char * fichier_image, float px, float py, float pz, float tx, float ty, float angle);
                          
  CPantin * GetPantinFils(int i);
       
  /*définit un pantin fils au membre n° i*/
  void SetPantinFils(int i, CPantin * pantin);
  void DetruirePantinFils(int i);
       
  /*définit le pantin fils du dernier membre ajouté*/
  void SetPantinFilsAuDernierMembre(CPantin * pantin);

  /*procédure pour modifier l'angle d'un membre (utile pour animer le pantin)*/
  void SetAngleMembre(int i, float angle);
       
  int GetNbMembres(void) const;
  
};    






/*un bonhomme (le héros, chaque ennemi, des gens du village...)
  est un pantin (car ils ont des membres), et est un objet physique
  (ie ont une position, une vitesse, un parallépipède de choc...)*/
class CBonhomme : public CPhysicalObj, public CPantin {
private:
  float iangle;
  int sens_iangle;
       
  TDirection Direction; // le gars est de profil, de dos??
        
  void TexCoord(int i, float tx, float ty) const;
                
  void AfficherPantin(const CPantin * pantin) const;
       
  enum TEtatBonhomme {ebPretAMarcher, ebFrapper};
  TEtatBonhomme Etat;
  int EtapeEtat;
       
  int invinsible_etape;
  
  CListe<COrdreDeplacement> liste;

public:
  // définit la direction dans lequel le bonhomme va (haut, bas, gauche, droite)
  void SetDirection(TDirection NouvelleDirection);
  TDirection GetDirection(void) const;
  
  /*création du bonhomme ... mais faut ajouter des membres au bonhomme-pantin...*/
  CBonhomme(const char * filename);
  ~CBonhomme(void);
  
  // affiche le bonhomme (en fait, anime le pantin puis affiche le pantin)
  void Render(const CSol * Map);
  
  
  void Frapper(void);
  bool EnTrainDeFrapper(void) const;
  
  
  
  bool EstInvinsible(void) const;
  void DevenirInvinsible(int nbetape);
  
  
  void Avancer(TDirection Direction, const CMap * Map);
  
  void AjouterOrdresDeplacement(TPoint3D pos);
  void AjouterOrdresDeplacement(float x, float y, TMethodePlacement mp);
  void TraiterOrdresDeplacement(const CMap * Map, const bool MoteurPhysiqueActif);
  void ViderOrdresDeplacement(void);
  bool IsSoumisADesOrdres(void);
  
  
  
public:
  const char * const filename;
  
  
};


#endif /* BONHOMME_HPP */