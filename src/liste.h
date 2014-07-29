#ifndef LISTE_HPP
#define LISTE_HPP

#include <stdlib.h> // NULL
#include <stdio.h> // printf

/*
 * La structure de liste est un peu compliquée.
 *
 * Elle est découpée en trois éléments:
 *  - la liste
 *  - un accesseur
 *  - la boîte
 *
 * Une boîte est la structure qui contient l'élément et le suivant (la structure chaînée de base).
 * Une liste contient la tête de la chaîne (qui est donc une boîte).
 * La liste est donc juste une sur-structure qui ne fait que contenir la tête de la liste.
 * Un accesseur est un objet qui parcours la liste; c le pointeur que l'on déplace sur la liste.
 *
 * 
 * Il reste toujours un grand mystère: à qui appartiennent les éléments qui sont dans la liste?
 * Voilà un grand mystère à résoudre!
 * Personnellement, je préconise que les éléments appartiennent à la liste.
 * Avec le constructeur de base, l'élément est copié avant d'être ajouté.
 * Avec le constructeur 'mp', l'élément est juste ajouté.
 *
 * Néanmoins, pour l'instant (ça évite les bugs même si c memory leak),
 * on ne delete pas les objets.
 *
 */


template <class T> class CListe; 
template <class T> struct Cell;
template <class T> class CAccesseur;



template <class T> class CListe {
public:  
  Cell<T> * debutliste;
  
public:
  //CListe(void) : debutliste(NULL) {printf("CListe::CListe(); Création d'une nouvelle liste...: %p\n", this);}
  CListe(void) : debutliste(NULL) {}
  ~CListe(void) { Vider(); }
  
  void Empiler(const T * e);
  void Empiler_sans_copie(T * e);
  void Depiler(void);

  bool IsVide(void) const {return (debutliste == NULL);};
  void Vider(void);
  
  //const T * PremierElement(void) const;
  T * PremierElement(void);

  CAccesseur<T> ObtenirAcces(void);
};


template <class T> struct Cell {
  T * element;
  Cell * suivant;

  Cell(T * e, Cell * suivant);
  ~Cell(void);
  //void Detruire(void);
  //void FullDelete(void);
};     


template <class T> class CAccesseur {
private:
  Cell<T> * pointeurcourant;
  Cell<T> * pointeurprecedent; // pour détruire un élément au milieu de la liste
  CListe<T> * maliste;
  
public:
  CAccesseur(CListe<T> * l) : pointeurcourant(NULL), pointeurprecedent(NULL), maliste(l) { if (l != NULL) pointeurcourant = l -> debutliste;};
  
  // on va à l'élément suivant
  void AllerSuivant(void);
    
  // est-ce qu'on est à la fin de la liste?
  bool IsFin(void) const;
  
  void DetruireElementCourant(void);
    
  // renvoit l'élément courant
  T * Element(void);
}; 



/*****************************
* liste
******************************/

template <class T> void CListe<T>::Empiler(const T * e) {
  Empiler_sans_copie(new T(e));
}

template <class T> void CListe<T>::Empiler_sans_copie(T * e) {
  Cell<T> * nc;
  nc = new Cell<T>(e, debutliste);
  debutliste = nc;
}

template <class T> void CListe<T>::Depiler(void) {
  if (debutliste == NULL)
    return;
  
  Cell<T> * pointeuratuer = debutliste;
  debutliste = debutliste -> suivant;
  pointeuratuer -> suivant = NULL;
  
  delete pointeuratuer;
}

template <class T> void CListe<T>::Vider(void) {
  if (debutliste == NULL)
    return;

  delete debutliste;
  //debutliste -> FullDelete();
  debutliste = NULL;
}

template <class T> T* CListe<T>::PremierElement(void) {
  if (debutliste == NULL)
    return NULL;

  return debutliste -> element;
}

template <class T> CAccesseur<T> CListe<T>::ObtenirAcces(void) {
  return CAccesseur<T>(this);
}



/*****************************
* cell
******************************/

template <class T> Cell<T>::Cell(T * e, Cell * suivant) {
  this -> element = e;
  this -> suivant = suivant;
}

template <class T> Cell<T>::~Cell(void) {
  if (this == NULL)
    return;
  
  Cell<T> * p;
  p = suivant;
  suivant = NULL;
  
  delete p;
  delete element;
  element = NULL;
}


/*****************************
* accesseur
******************************/

template <class T> bool CAccesseur<T>::IsFin(void) const {
  return (pointeurcourant == NULL);
}

template <class T> void CAccesseur<T>::AllerSuivant(void) {
  if (pointeurcourant == NULL) return;
  pointeurprecedent = pointeurcourant;
  pointeurcourant = pointeurcourant -> suivant;
}

template <class T> T* CAccesseur<T>::Element(void) {
  assert(pointeurcourant != NULL);
  return pointeurcourant -> element;
}

// détruit la cellule courante puis se place sur la cellule suivante
template <class T> void CAccesseur<T>::DetruireElementCourant(void) {
  assert(pointeurcourant != NULL);

  Cell<T> * mypointeurcourantadetruire = pointeurcourant;

  pointeurcourant = pointeurcourant -> suivant;
  mypointeurcourantadetruire -> suivant = NULL;

  if (pointeurprecedent == NULL) {
    maliste -> debutliste = pointeurcourant;
  }
  else {
    pointeurprecedent -> suivant = pointeurcourant;
  }

  delete mypointeurcourantadetruire;
}







#endif /* LISTE_HPP */

