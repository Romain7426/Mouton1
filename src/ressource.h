#ifndef RESSOURCE_HPP
#define RESSOURCE_HPP

/*
  Ce fichier contient la définition d'un alpha-gestionnaire de ressource,
  et de la alpha-ressource associée.
  
  Dans le principe, une ressource est une interface avec l'objet.
  On ne manipule plus directement l'objet.
  Cependant, ce sera transparent au niveau de l'utilisation.
  
  En pratique, il faut demander à accèder à l'objet,
  et une fois l'utilisation terminée, dire qu'on terminer avec lui
  (comme avec un objet que l'on crée et que l'on détruit).
  
  Bien sûr, l'objet interfacé par une ressource est en lecture seule.
*/


/* Un gestionnaire de ressource est une liste d'informations sur un objet :
   - le pointeur vers l'objet ;
   - le nom de l'objet ;
   - son nombre d'utilisateurs ;
   - son id.
   Une ressource est juste une copie de l'id.
   Lors de l'opération de création de ressource, on fait ++.
   Lors de l'opéartion de destruction de ressource, on fait --.
   Entre temps, il faut que la ressource se comporte comme si c'était l'objet.
*/

/* Pas trouvée de jolie méthode pour réaliser une transparence d'utilisation.
   Pour le faire, on va donc utilisé la méthode bourrine.
   Un gestionnaire de ressource concerne pour l'instant les 3DS.
   On verra pour d'autres trucs ensuite.
*/


#include "texture.hpp"
#include "obj3ds.hpp"
#include "pascal.hpp"


#define MAXGESTIONNAIRE 5
#define MAXRESSOURCE 5120

/* Un objet ressource est ce qu'on va envoyer à l'utilisateur
   lors de la demande de chargement d'un objet alpha.
   
   Pour permettre une utilisation plus transparente pour l'utilisateur,
   la ressource de l'objet alpha se comportera comme si c'était l'objet alpha.
   Pour cela, il dérive de la classe alpha.
   
   En fait, ça marche pas, donc plus d'héritage.
*/
template <class alpha> class ressource {
private:
  /* L'id est la clef qui va permettre au gestionnaire 
     de retrouver l'élément dans sa table.
  */
  int id; 
 
  /* objet est un pointeur sur l'objet. */
  alpha * objet;
 
  /* gestion est un pointeur sur le gestionnaire. */
  void * gestion;
 
  /* Ceci est le constructeur.
     En théorie, le constructeur n'est appelé que par le gestionnaire 'gestion'
     désigné plus haut. Il est donc privé.
     Pour être appelé, il a néanmoins besoin d'un ami : prendre. 
    
     Problème : ça ne marche car il faut que gestionnaire soit défini avant.
     Donc public
  */
  //friend ressource<alpha> gestionnaire<alpha>::prendre(char *nom);
 

public:
  ressource(int id, alpha * objet, void * gestion);
  ressource<alpha> * AvoirAutreRessource(void);
 
  /* Par contre le construteur est heureusement public.
     Lors de son appel, le destructeur prévient de sa destruction à gestion.
  */
  ~ressource(void);
 
  /* La fonction d'accès à l'objet. */
  alpha * getObject(void);
};

     

     
/* Un 'element' est une cellule de la table du gestionnaire.
   Une telle cellule contient le nom physque de l'objet pour l'accès 
   par l'utilisateur, un pointeur vers l'objet réel,
   et le nombre d'utilisateur de cet objet réel.
*/
template <class beta> class element {
public:
  char * nom;
  int nbusers;
  beta * objet;
  element(const char * nom, beta * objet);
  ~element(void);
};


 

/* Un gestionnaire est objet qui gére un ensemble de ressource,
   pour économiser la mémoire.
   C'est lui qui gère la correspondance entre ressource et objet réel.
*/
template <class alpha> class gestionnaire {
  //private:
public:
  /* La table des objets. */
  element<alpha> * (elements[MAXRESSOURCE]);
  int nbelts;
 
  /* Ensuite l'organisation de la table.
     Ceci est une permutation de [0..MAXRESSOURCE[
     Contrairement au tableau précédent où on ne savait
     où était mis les objets, les nbelts premiers éléments
     correspondent à des cases occupées.
  */
  int indices[MAXRESSOURCE];
 
  /* La fonction delaisser dit au gestionnaire qu'une ressource se détruit.
     Pour que la ressource en question y ait accès,
     il faut déclarer une fonction amie.
  */
  friend ressource<alpha>::~ressource(void);
  void delaisser(int id);

public:
  /*cette fonction permet de retrouver un objet déjà chargé et rend une ressource*/     
  ressource<alpha> * prendre(int ID);
  
  /* La fonction essentielle d'un gestionnaire et utilisé très souvent:
     c'est un peu comme l'autre prendre sauf que l'on y accède par nom
     si l'objet n'existe pas, ça le crée (ça essaie..) */
  ressource<alpha> * prendre(const char * nom);
  
  
  
 
  /* Le garbage collecting. */
  void collecter(void);
 
  /* Le constructeur avec son metagestionnaire en paramètre. */
  gestionnaire(void);
 
  /* Le destructeur. */
  ~gestionnaire(void);
};




extern void metacollecter(void);


/*******************************************************************************
ressource
*******************************************************************************/


template <class alpha> ressource<alpha>::ressource(int id, alpha * objet, void * gestion) {
  this->id = id;
  this->objet = objet;
  this->gestion = gestion;
}


/*détruire une ressource revient à faire "délaisser" sur le gestionnaire*/
template <class alpha> ressource<alpha>::~ressource(void) {
  ((gestionnaire<alpha> *)(this->gestion))->delaisser(this->id);
}



template <class alpha> ressource<alpha>* ressource<alpha>::AvoirAutreRessource(void) {
  return ((gestionnaire<alpha> *) this->gestion)->prendre(this->id);
}


template <class alpha> alpha * ressource<alpha>::getObject(void) {
  return objet;
}



/*******************************************************************************
élément
*******************************************************************************/

template <class beta> element<beta>::element(const char * nom, beta * objet) {
  this->nbusers = 0;
  this->objet = objet;
  const int taille = strlen(nom);
  this->nom = new char[taille + 1];
  (void) strcpy(this -> nom, nom);
  /*
    for (int i = 0; i < taille; i++) {
    this->nom[i] = nom[i];
    }
  */
}

template <class beta> element<beta>::~element(void) {
  if (nbusers != 0) printf("Deleting an element whoe nbusers is not null (%d).\n", nbusers);

  delete[] nom;
  
  //delete objet;
  
  
  //((beta *)objet)->~beta();
  //template <class beta> machin<beta>(objet);
  //machin<beta>(objet);
  //free(objet);

  nom = NULL;
  objet = NULL;
  nbusers = 0;
}



/*******************************************************************************
gestionnaire
*******************************************************************************/

template <class alpha> gestionnaire<alpha>::gestionnaire(void) {
  this->nbelts = 0;

  for (int i = 0; i < MAXRESSOURCE; i++) {
    this->indices[i] = i;
  }

  for (int i = 0; i < MAXRESSOURCE; i++) {
    this->elements[i] = NULL;
  }
}

template <class alpha> gestionnaire<alpha>::~gestionnaire(void) {
  for (int i = 0; i < nbelts; i++) {
    //delete (elements[indices[i]])->objet;
    delete elements[indices[i]];
    elements[indices[i]] = NULL;
  }
  nbelts = 0;
}


template <class alpha> ressource<alpha> * gestionnaire<alpha>::prendre(int ID) {
  ressource<alpha> * temp = NULL;
  const int i = ID;
    
  printf("La ressource a été trouvée i = %d\n", i);
  elements[indices[i]] -> nbusers++;

  try {
    temp = new ressource<alpha>(i, elements[indices[i]]->objet, this);
  }
  catch (...) {
    printf("Pas assez de memoire. On collecte.\n");
    metacollecter();
    temp = new ressource<alpha>(i, elements[indices[i]]->objet, this);
  }

  return temp;
}


template <class alpha> ressource<alpha> *gestionnaire<alpha>::prendre(const char * nom) {
  printf("On tente 'prendre' !\n");
  printf("Appel à prendre avec nom = %s, nbelts = %d\n", nom, nbelts);
  printf("On recherche si la ressource existe...\n");
  
  if (nbelts >= MAXRESSOURCE) {
    printf("ERREUR GRAVE: C'est pas bon, la ressource ne sera pas allouée! MAXRESSOURCE = %d\n", MAXRESSOURCE);
    assert(false);
    return NULL;
  }
  
  
  for (int i = 0; i < nbelts; i ++) {
    if (strcmp(elements[indices[i]] -> nom, nom) == 0) {
      printf("La ressource a été trouvée i = %d\n", i);
      elements[indices[i]] -> nbusers ++;
      ressource<alpha> * temp;
      try {
        temp =  new ressource<alpha>(i, elements[indices[i]]->objet, this);
      }
      catch (...) {
        printf("Pas assez de memoire. On collecte.\n");
        metacollecter();
        temp =  new ressource<alpha>(i, elements[indices[i]]->objet, this);
      }
      return temp; 
    }
  }
  

  printf("La ressource n'a pas été trouvée dans la table. On en crée une nouvelle.\n");
  
  try {
    elements[indices[nbelts]] = new element<alpha>(nom, NULL);
  }
  catch(...) {
    printf("Pas assez de memoire 2. On collecte.\n");
    metacollecter();
    elements[indices[nbelts]] = new element<alpha>(nom, NULL);
  }
  
  try {
    elements[indices[nbelts]]->objet = new alpha(nom);
  }  
  catch (...) {
    printf("Pas assez de memoire 3. On collecte.\n");
    metacollecter();
    elements[indices[nbelts]]->objet = new alpha(nom);
  }

  elements[indices[nbelts]] -> nbusers ++;
  
  
  
  ressource<alpha> * temp;
  try {
    temp = new ressource<alpha>(indices[nbelts], elements[indices[nbelts]]->objet, this);
  }
  
  catch (...) {
    metacollecter();
    temp = new ressource<alpha>(indices[nbelts], elements[indices[nbelts]]->objet, this);
  }
  
  nbelts++;
  
  return temp;
}
 


template <class alpha> void gestionnaire<alpha>::delaisser(int id) {
  if (elements[id]->nbusers <= 0) {
    fprintf(stderr, "ERREUR: Erreur dans ressource gestionnaire<alpha>::delaisser : nbusers vaut %d\n", elements[id]->nbusers);
    assert(false);
  }

  --(elements[id]->nbusers);
}

template <class alpha> void gestionnaire<alpha>::collecter(void) {
  for (int i = 0; i < nbelts; i++) {
    assert(elements[indices[i]]->nbusers >= 0);

    if (elements[indices[i]]->nbusers == 0) {
      delete elements[indices[i]];
      elements[indices[i]] = NULL;

      indices[i] = indices[nbelts-1];

      i--;
      nbelts--;
    }
  }
}







extern gestionnaire<C3DS> gestion3DS;
extern gestionnaire<CTexture> gestionTexture;
extern gestionnaire<CPascal> gestionPascal;



#endif /* RESSOURCE_HPP */
