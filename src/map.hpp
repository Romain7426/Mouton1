#ifndef MAP_HPP
#define MAP_HPP



#include "liste.hpp"
#include "dico.hpp"


//enum TDirection;
struct TPoint2D;
struct TPoint3D;
class CSol;
class CPhysicalObj;
class CBonhomme;
class CEvenement;

#include "vectors.hpp"
#include "sol.hpp"
#include "evenement.hpp"

struct TVoisinage;
class CZoneTeleportation;



struct TVoisinage {
  CListe<CPhysicalObj> Objets;     
};


class CZoneTeleportation {
public:
  TPoint3D position;
  TPoint3D dimension;
  TDirection depart_direction;
  const char * destination_carte;
  TPoint3D destination_position;
  TDirection destination_direction;         
  
  CZoneTeleportation(void) {};
  CZoneTeleportation(TPoint3D in_position, TPoint3D in_dimension, TDirection in_depart_direction, const char * in_destination_carte, TPoint3D in_destination_position, TDirection in_destination_direction);    
};


//#define VOISINAGE_IS_TAB

class CMap : public CSol {
private:
  const char * const NomCarte;

public:
  // c un tableau de liste
  //  -> pour chaque case, il y a un voisinage,
  //     le voisinage étant la liste des objets proches
#ifndef VOISINAGE_IS_TAB
  TVoisinage * Voisinages;
  //CPhysicalObj * * Voisinages;
#else
#define VOISINAGE_TAILLE 8192
    CPhysicalObj * (* Voisinages)[VOISINAGE_TAILLE];
#endif
  
  CDico<CPhysicalObj> DicoObjets;
  CListe<CZoneTeleportation> ZonesTeleportation;
  /*le dictionnaire répertorie les objets qui ont un nom. (utile pour les scripts)
     invariant : le dico ne contient que des pointeurs vers des éléments déjà dans Objets*/
  
  /* Cette fonction lance le parser d'un fichier .carte.
     Elle met toutes les variables à jour.
     Elle est définie dans carte/carte.cpp
     Renvoie un code d'erreur.
     0 : ça c'est bien passé
     < 0 : erreur
     regarde dans les fichers carte/carte.* pour plus de renseignements.
  */
  /* Valeur de retour.
   0 : OK
   < 0 : erreur
   -1 : filename est NULL
   -2 : impossible d'ouvrir en écriture le fichier de sortie.
   -3 : impossible d'ouvrir en lecture le fichier d'entrée.
   < -128 : erreur lors du parsing.
   regarder dans carte/carte.parse.y et chercher l'erreur (res + 128).
  */
  //int parse(const char * filename);
  int parse(const char * dir, const char * filename);
  // Fonction de confiance; c'est elle qui réalise effectivement le parsing.
  friend int yycarteparse(void);


public:
  CMap(const char * filename, const bool EnVaisseau);
  ~CMap(void);

  const char * GetNomCarte(void) const;

  void Render(const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau);
 
  void ChargerZ(const char * filename);
  
  // permet d'ajouter un objet (nonanimé ou animé)
  void AjouterObjet(CPhysicalObj * o);  
  void AjouterObjet(const char * nom, CPhysicalObj * o);
  
  CPhysicalObj * RetrouverObjetViaSonNom(const char * nom);

  void AjouterZoneTeleportation(TPoint3D position, TPoint3D dimension, TDirection depart_direction, const char * destination_carte, TPoint3D destination_position, TDirection destination_direction);

  void AjouterParticules(TPoint3D p, const char * nom, const bool MoteurPhysiqueActif);
  void TesterPosition(CPhysicalObj * o, const bool MoteurPhysiqueActif);
  CPhysicalObj * TesterPositionHero(CPhysicalObj * o, const bool MoteurPhysiqueActif);
  
  void TraiterOrdresDeplacement(CBonhomme * aHero, const bool MoteurPhysiqueActif);
  
  CZoneTeleportation * VaTonBouger(CPhysicalObj * aHero);
  
  // Ça c pour la gestion des eveneents.
  evenements_t evt_carte;
  tab_evt_bool tab_evt_carte(void);
};




#endif /* MAP_HPP */



