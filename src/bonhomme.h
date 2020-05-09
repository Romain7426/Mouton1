#ifndef BONHOMME_H
#define BONHOMME_H

enum { MAX_MEMBRE = 10 }; 

enum { MEMBRE_AVEC_ARME = 5 }; // RL: TODO XXX FIXME: Ah hemmm..... 


//TPoint3D DirectionToVecteur(TDirection d);
extern void DirectionToVecteur(TDirection d, TPoint3D * vec); 


struct TMembre;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TMembre);

struct COrdreDeplacement;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(COrdreDeplacement);

struct CPantin;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CPantin);

struct COrdreDeplacement {
  // FS: /*ordre de déplacement vers le point destination (on ne l'atteint pas forcément) (en fait on ne l'atteint que sur une coordonnée*/ 
    TDirection direction;
    TPoint3D destination;
};
//extern COrdreDeplacement * COrdreDeplacement_make(void); 


struct TMembre { 
  float px, py, pz;
  
  float angle_max, angle;
  float taille_x;
  float taille_y;
  float taille_pixelx, taille_pixely;
  
  CTexture * Texture;
  
  struct CPantin * Pantin;
};    



// Un pantin est une liste de membres où chaque membre peut éventuellement contenir un pantin fils
struct CPantin {
  int NbMembres;
  TMembre Membre[MAX_MEMBRE];  
  
  /*pour ajouter la tête, le corps, les bras, les oreilles etc...
    mais aussi une épée au bout d'un bras etc...*/
  /* fichier_image : fichier image par exemple "tete.bmp" (contenant
     les images des vues (face, profilD, dos) px, py, pz : position
     supérieure au milieu tx, ty : taille d'une image en pixel
  */
  
  // renvoit le numéro du membre
  int  (* AjouterMembre)(struct CPantin * this, const char * fichier_image, float px, float py, float pz, float tx, float ty, float angle);
  struct CPantin * (* GetPantinFils)(struct CPantin * this, int i);
  /*définit un pantin fils au membre n° i*/
  void (* SetPantinFils)(struct CPantin * this, int i, struct CPantin * pantin);
  void (* DetruirePantinFils)(struct CPantin * this, int i);
  /*définit le pantin fils du dernier membre ajouté*/
  void (* SetPantinFilsAuDernierMembre)(struct CPantin * this, struct CPantin * pantin);
  /*procédure pour modifier l'angle d'un membre (utile pour animer le pantin)*/
  void (* SetAngleMembre)(struct CPantin * this, int i, float angle);
  int  (* GetNbMembres)(const struct CPantin * this);
};    
extern CPantin * CPantin__make      (void); 
extern CPantin * CPantin__make_aux  (CPantin * this); 
extern void      CPantin__delete    (CPantin * this); 
extern void      CPantin__delete_aux(CPantin * this); 
extern int       CPantin__AjouterMembre(struct CPantin * this, const char * fichier_image, const float px, const float py, const float pz, const float tx, const float ty, const float angle);
extern CPantin * CPantin__GetPantinFils(struct CPantin * this, const int i); 
extern void      CPantin__SetPantinFils(struct CPantin * this, const int i, struct CPantin * pantin); 
extern void      CPantin__DetruirePantinFils          (struct CPantin * this, const int i); 
extern void      CPantin__SetPantinFilsAuDernierMembre(struct CPantin * this, struct CPantin * pantin); 
extern void      CPantin__SetAngleMembre              (struct CPantin * this, const int i, const float angle); 
extern int       CPantin__GetNbMembres          (const struct CPantin * this); 



enum TEtatBonhomme { ebPretAMarcher, ebFrapper }; 

enum { CBonhomme_COrdreDeplacement_Liste_Size = INT8_MAX - 1 }; 
 
struct CBonhomme { 
  CPhysicalObj parent1; 
  CPantin      pantin; 

  char * filename;

  float           iangle;
  int        sens_iangle;
  TDirection   Direction; // le gars est-il de profil, de dos??

  float force_marche; 
  
  enum TEtatBonhomme Etat;
  int EtapeEtat;
       
  int invisible_etape;
  
  // RL: Circular list. 
  COrdreDeplacement od_array[CBonhomme_COrdreDeplacement_Liste_Size]; 
  int8_t od_nb; 
  int8_t od_head; 
  int8_t od_tail; 


  // *** METHODS *** 
  
  CBonhomme * (* make)(const char * filename); 
  void (* delete)(CBonhomme * this); 
  void (* TexCoord)(const CBonhomme * this, const int i, const float tx, const float ty, const CCamera * Camera); 
  void (* AfficherPantin)(const CBonhomme * this, const CPantin * pantin, const int lattice_width, const int lattice_height, const CCamera * Camera); 
  // définit la direction dans lequel le bonhomme va (haut, bas, gauche, droite)
  void (* SetDirection)(CBonhomme * this, const TDirection NouvelleDirection); 
  TDirection (* GetDirection)(const CBonhomme * this);
  // affiche le bonhomme (en fait, anime le pantin puis affiche le pantin)
  void (* Life)(CBonhomme * this);
  //void (* Render)(const CBonhomme * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold, const CCamera * Camera); 
  void (* Render)(const CBonhomme * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold, const CCamera * Camera); 
  void (* Frapper)(CBonhomme * this);
  bool (* EnTrainDeFrapper)(const CBonhomme * this);
  bool (* EstInvisible)(const CBonhomme * this);
  void (* DevenirInvisible)(CBonhomme * this, const int nbetape);
  //void (* Avancer)(CBonhomme * this, const TDirection Direction, const riemann_t * our_manifold); 
  void (* Avancer)(CBonhomme * this, const TDirection Direction, const bool slow_walk_huh); 
  void (* AjouterOrdresDeplacement_vP)(CBonhomme * this, const TPoint3D pos);
  void (* AjouterOrdresDeplacement_vXY)(CBonhomme * this, const float x, const float y, const TMethodePlacement mp);
  void (* TraiterOrdresDeplacement)(CBonhomme * this, const CMap * Map, const bool MoteurPhysiqueActif);
  void (* ViderOrdresDeplacement)(CBonhomme * this);
  bool (* IsSoumisADesOrdres)(const CBonhomme * this);
};

// FS: /*création du bonhomme ... mais faut ajouter des membres au bonhomme-pantin...*/
extern CBonhomme * CBonhomme__make(const char * filename); 
extern void CBonhomme__delete(CBonhomme * this);
extern void CBonhomme__TexCoord(const CBonhomme * this, const int i, const float tx, const float ty, const CCamera * Camera);
extern void CBonhomme__AfficherPantin(const CBonhomme * this, const CPantin * pantin, const int lattice_width, const int lattice_height, const CCamera * Camera);
extern void CBonhomme__SetDirection(CBonhomme * this, const TDirection NouvelleDirection);
extern TDirection CBonhomme__GetDirection(const CBonhomme * this);
extern void CBonhomme__Life(CBonhomme * this);
//extern void CBonhomme__Render(const CBonhomme * this, const int lattice_width, const int lattice_height, const riemann_t * our_manifold, const CCamera * Camera); 
extern void CBonhomme__Render(const CBonhomme * this, const float lattice_to_map_scale_factor__x, const float lattice_to_map_scale_factor__y, const float lattice_to_map_scale_factor__z, const riemann_t * our_manifold, const CCamera * Camera); 
extern void CBonhomme__Frapper(CBonhomme * this);
extern bool CBonhomme__EnTrainDeFrapper(const CBonhomme * this);
extern bool CBonhomme__EstInvisible(const CBonhomme * this);
extern void CBonhomme__DevenirInvisible(CBonhomme * this, const int nbetape);
//extern void CBonhomme__Avancer(CBonhomme * this, const TDirection Direction, const riemann_t * our_manifold); 
extern void CBonhomme__Avancer(CBonhomme * this, const TDirection Direction, const bool slow_walk_huh); 
extern void CBonhomme__AjouterOrdresDeplacement_vP(CBonhomme * this, const TPoint3D pos);
extern void CBonhomme__AjouterOrdresDeplacement_vXY(CBonhomme * this, const float x, const float y, const TMethodePlacement mp);
extern void CBonhomme__TraiterOrdresDeplacement(CBonhomme * this, const CMap * Map, const bool MoteurPhysiqueActif);
extern void CBonhomme__ViderOrdresDeplacement(CBonhomme * this);
extern bool CBonhomme__IsSoumisADesOrdres(const CBonhomme * this);



#endif /* BONHOMME_H */
