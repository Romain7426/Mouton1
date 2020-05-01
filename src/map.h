#ifndef MAP_H
#define MAP_H

#if 0
struct TVoisinage {
  //CListe<CPhysicalObj> Objets;     
  //struct CPhysicalObj * Objets;     
  CPhysicalObj * Objets;     
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TVoisinage);
DEFINE_NEW_OPERATOR_FOR_STRUCT(TVoisinage);
#endif 


struct CZoneTeleportation { 
  TPoint3D   position; 
  TPoint3D   dimension; 
  TDirection depart_direction; 
  char *     destination_carte; 
  TPoint3D   destination_position; 
  TDirection destination_direction; 
}; 
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CZoneTeleportation); 
  
//CZoneTeleportation(void) {}; 
extern CZoneTeleportation * CZoneTeleportation_make(TPoint3D in_position, TPoint3D in_dimension, TDirection in_depart_direction, const char * in_destination_carte, TPoint3D in_destination_position, TDirection in_destination_direction); 
extern CZoneTeleportation * CZoneTeleportation_copy(const CZoneTeleportation * this); 
extern void CZoneTeleportation_delete(CZoneTeleportation * this); 






// RL: A 'CMap' is a big array containing all the items on the ground: 
//      * Fixed objects 
//      * NPCs 
//      * anything 
// 
//     There's nothing really OpenGL here. In the spirit, it's a big array. 
// 
// RL: Inside we have two main structures: 
//      * 'Voisinages', which contains all the objects. 
//      * 'ZonesTeleportation', which contains the gates. 
//      * And that's it! 
// 

//#define VOISINAGE_IS_TAB
enum { VOISINAGE_X_SIZE = 63 }; 
enum { VOISINAGE_Y_SIZE = 63 }; 
enum { VOISINAGE_SIZE = 63 }; 
enum { DicoObjets_SIZE = 2048 }; 
enum { ZonesTeleportation_SIZE = 32 }; 
struct CMap {
  struct CSol parent; 
  
  char * NomCarte; 

  // c un tableau de liste
  //  -> pour chaque case, il y a un voisinage,
  //     le voisinage étant la liste des objets proches
  // RL: Ne devrait-on pas avoir un voisinage pour les objets fixes? Car, 
  //     a priori, ne bougent pas, donc pas de calculs à refaire les concernant. 
  //     Mais le héros peut quand même interagir avec ceux-ci, donc la 
  //     logique du voisinage paraît pertinent. 
#if 0 
  TVoisinage * Voisinages;
  //CPhysicalObj * * Voisinages;
#elif 0
#define VOISINAGE_TAILLE 8192
  //struct CPhysicalObj * (* Voisinages)[VOISINAGE_TAILLE];
  struct CPhysicalObj * (* Voisinages)[VOISINAGE_TAILLE];
#else
  CPhysicalObj * Voisinages_array[VOISINAGE_X_SIZE][VOISINAGE_Y_SIZE][VOISINAGE_SIZE]; 
#endif
  


  //CDico<CPhysicalObj> DicoObjets; 
  /*le dictionnaire répertorie les objets qui ont un nom. (utile pour les scripts) 
     invariant : le dico ne contient que des pointeurs vers des éléments déjà dans Voisinage*/ 
  // Donc on n'alloue pas ces objets ou ne les désalloue pas! 
  // RL: We can't know whether any of these objects have already been deleted. We should be able to track that down. 
  CPhysicalObj * objets_array[DicoObjets_SIZE]; 
  char * objets_noms_array[DicoObjets_SIZE]; 
  int objets_nb; 
  
  
  //CListe<CZoneTeleportation> ZonesTeleportation; 
  CZoneTeleportation * ZonesTeleportation_array[ZonesTeleportation_SIZE]; 
  int ZonesTeleportation_nb; 
  
  
  // Ça c pour la gestion des eveneents. 
  //evenements_t evt_carte; 
  
  
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
  int (* parse)(CMap * this, const char * dir, const char * filename);
  // Fonction de confiance; c'est elle qui réalise effectivement le parsing.
  //friend int yycarteparse(void);
  int (* yycarteparse)(CMap * this);


  void (* delete)(CMap * this);
  const char * (* GetNomCarte)(const struct CMap * this);

  void (* Life)(struct CMap * this, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau);
  //void (* Render)(const struct CMap * this, const riemann_t * our_manifold, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau); 
  void (* Render)(const CMap * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y, const bool EnVaisseau); 

 
  void (* ChargerZ)(struct CMap * this, const char * filename);
  
  // permet d'ajouter un objet (nonanimé ou animé)
  void (* AjouterObjet)(struct CMap * this, CPhysicalObj * o);  
  void (* AjouterObjet_nom)(struct CMap * this, const char * nom, CPhysicalObj * o);
  
  CPhysicalObj * (* RetrouverObjetViaSonNom)(struct CMap * this, const char * nom);
  
  void (* AjouterZoneTeleportation)(struct CMap * this, TPoint3D position, TPoint3D dimension, TDirection depart_direction, const char * destination_carte, TPoint3D destination_position, TDirection destination_direction);

  void (* AjouterParticules)(struct CMap * this, TPoint3D p, const char * nom, const bool MoteurPhysiqueActif);
  void (* TesterPosition)(struct CMap * this, CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
  CPhysicalObj * (* TesterPositionHero)(struct CMap * this, struct CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
  
  void (* TraiterOrdresDeplacement)(struct CMap * this, struct CBonhomme * aHero, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
  
  const CZoneTeleportation * (* VaTonBouger)(const CMap * this, const CPhysicalObj * aHero);
  
  //struct tab_evt_bool (* tab_evt_carte)(struct CMap * this);
}; 

extern CMap * CMap__make(const char * filename, const bool EnVaisseau);
extern void CMap__delete(CMap * this);

//extern int CMap__parse(CMap * this, const char * dir, const char * filename);
//extern int CMap__yycarteparse(CMap * this);
extern int CMap__ReadDescriptionFile(CMap * this, const char * dir, const char * filename);
extern const char * CMap__GetNomCarte(const struct CMap * this);
extern void CMap__Life(struct CMap * this, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau);
//extern void CMap__Render(const struct CMap * this, const riemann_t * our_manifold, const int i1, const int j1, const int i2, const int j2, const bool EnVaisseau); 
extern void CMap__Render(const CMap * this, const riemann_t * our_manifold, const int nb_cells_displayed_x, const int nb_cells_displayed_y, const int target_map_i, const int target_map_j, const float target_map_x, const float target_map_y, const bool EnVaisseau); 
extern void CMap__ChargerZ(struct CMap * this, const char * filename);
extern void CMap__AjouterObjet(struct CMap * this, CPhysicalObj * o);  
extern void CMap__AjouterObjet_nom(struct CMap * this, const char * nom, CPhysicalObj * o);
extern CPhysicalObj * CMap__RetrouverObjetViaSonNom(CMap * this, const char * nom);
extern void CMap__AjouterZoneTeleportation(struct CMap * this, TPoint3D position, TPoint3D dimension, TDirection depart_direction, const char * destination_carte, TPoint3D destination_position, TDirection destination_direction);
extern void CMap__AjouterParticules(struct CMap * this, TPoint3D p, const char * nom, const bool MoteurPhysiqueActif);
extern void CMap__TesterPosition(struct CMap * this, CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
extern CPhysicalObj * CMap__TesterPositionHero(struct CMap * this, struct CPhysicalObj * o, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
extern void CMap__TraiterOrdresDeplacement(struct CMap * this, struct CBonhomme * aHero, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
extern const CZoneTeleportation * CMap__VaTonBouger(const CMap * this, const CPhysicalObj * aHero);
//extern struct tab_evt_bool CMap__tab_evt_carte(struct CMap * this);





#endif /* MAP_H */



