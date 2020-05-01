#ifndef BONHOMME_H
#define BONHOMME_H

#define MAX_MEMBRE 10
#define MEMBRE_AVEC_ARME 0
#define MAX_IND_ANGLE 10

//TPoint3D DirectionToVecteur(TDirection d);
extern void DirectionToVecteur(TDirection d, TPoint3D * vec); 


struct TMembre;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TMembre);

struct COrdreDeplacement;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(COrdreDeplacement);

struct CPantin;
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CPantin);

struct COrdreDeplacement {
/*ordre de déplacement vers le point destination (on ne l'atteint pas forcément)
(en fait on ne l'atteint que sur une coordonnée*/
    TDirection direction;
    TPoint3D destination;
};
extern COrdreDeplacement * COrdreDeplacement_make(void); 


struct TMembre { 
  float px, py, pz;
  
  float angle_max, angle;
  float taille_x;
  float taille_y;
  float taille_pixelx, taille_pixely;
  
  //ressource<CTexture> * resTexture;
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
  int (* AjouterMembre)(struct CPantin * this, const char * fichier_image, float px, float py, float pz, float tx, float ty, float angle);
  struct CPantin * (* GetPantinFils)(struct CPantin * this, int i);
  /*définit un pantin fils au membre n° i*/
  void (* SetPantinFils)(struct CPantin * this, int i, struct CPantin * pantin);
  void (* DetruirePantinFils)(struct CPantin * this, int i);
  /*définit le pantin fils du dernier membre ajouté*/
  void (* SetPantinFilsAuDernierMembre)(struct CPantin * this, struct CPantin * pantin);
  /*procédure pour modifier l'angle d'un membre (utile pour animer le pantin)*/
  void (* SetAngleMembre)(struct CPantin * this, int i, float angle);
  int (* GetNbMembres)(const struct CPantin * this);
};    
extern CPantin * CPantin_make(void);
extern CPantin * CPantin_make_aux(CPantin * this); 
extern void CPantin_delete(CPantin * this); 
extern void CPantin_delete_aux(CPantin * this); 
extern int       CPantin__AjouterMembre(struct CPantin * this, const char * fichier_image, float px, float py, float pz, float tx, float ty, float angle);
extern CPantin * CPantin__GetPantinFils(struct CPantin * this, int i);
extern void      CPantin__SetPantinFils(struct CPantin * this, int i, struct CPantin * pantin);
extern void      CPantin__DetruirePantinFils(struct CPantin * this, int i);
extern void      CPantin__SetPantinFilsAuDernierMembre(struct CPantin * this, struct CPantin * pantin);
extern void      CPantin__SetAngleMembre(struct CPantin * this, int i, float angle);
extern int       CPantin__GetNbMembres(const struct CPantin * this);

enum TEtatBonhomme { ebPretAMarcher, ebFrapper }; 


enum { CBonhomme_COrdreDeplacement_Liste_Size = 127 }; 
 
/*un bonhomme (le héros, chaque ennemi, des gens du village...)
  est un pantin (car ils ont des membres), et est un objet physique
  (ie ont une position, une vitesse, un parallépipède de choc...)*/
struct CBonhomme /* : public CPhysicalObj, public CPantin */ { 
  CPhysicalObj parent1; 
  CPantin parent2; 

  char * filename;

  float iangle;
  int sens_iangle;
  TDirection Direction; // le gars est-il de profil, de dos??
        
  enum TEtatBonhomme Etat;
  int EtapeEtat;
       
  int invisible_etape;
  
  //CListe<COrdreDeplacement> liste;
  COrdreDeplacement od_array[CBonhomme_COrdreDeplacement_Liste_Size]; 
  int od_nb; 
  int od_head; 
  int od_tail; 

  void (* TexCoord)(const CBonhomme * this, const int i, const float tx, const float ty);
  void (* AfficherPantin)(const CBonhomme * this, const CPantin * pantin);
  // définit la direction dans lequel le bonhomme va (haut, bas, gauche, droite)
  void (* SetDirection)(CBonhomme * this, const TDirection NouvelleDirection);
  TDirection (* GetDirection)(const CBonhomme * this);
  // affiche le bonhomme (en fait, anime le pantin puis affiche le pantin)
  void (* Life)(CBonhomme * this);
  void (* Render)(const CBonhomme * this, const riemann_t * our_manifold);
  void (* Frapper)(CBonhomme * this);
  bool (* EnTrainDeFrapper)(const CBonhomme * this);
  bool (* EstInvisible)(const CBonhomme * this);
  void (* DevenirInvisible)(CBonhomme * this, const int nbetape);
  void (* Avancer)(CBonhomme * this, const TDirection Direction, const riemann_t * our_manifold); 
  void (* AjouterOrdresDeplacement_vP)(CBonhomme * this, const TPoint3D pos);
  void (* AjouterOrdresDeplacement_vXY)(CBonhomme * this, const float x, const float y, const TMethodePlacement mp);
  void (* TraiterOrdresDeplacement)(CBonhomme * this, const CMap * Map, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
  void (* ViderOrdresDeplacement)(CBonhomme * this);
  bool (* IsSoumisADesOrdres)(const CBonhomme * this);
};

  /*création du bonhomme ... mais faut ajouter des membres au bonhomme-pantin...*/
extern CBonhomme * CBonhomme_make(const char * filename); 
extern void CBonhomme_delete(CBonhomme * this);
extern void CBonhomme__TexCoord(const CBonhomme * this, const int i, const float tx, const float ty);
extern void CBonhomme__AfficherPantin(const CBonhomme * this, const CPantin * pantin);
  // définit la direction dans lequel le bonhomme va (haut, bas, gauche, droite)
extern void CBonhomme__SetDirection(CBonhomme * this, const TDirection NouvelleDirection);
extern TDirection CBonhomme__GetDirection(const CBonhomme * this);
  // affiche le bonhomme (en fait, anime le pantin puis affiche le pantin)
extern void CBonhomme__Life(CBonhomme * this);
extern void CBonhomme__Render(const CBonhomme * this, const riemann_t * our_manifold); 
extern void CBonhomme__Frapper(CBonhomme * this);
extern bool CBonhomme__EnTrainDeFrapper(const CBonhomme * this);
extern bool CBonhomme__EstInvisible(const CBonhomme * this);
extern void CBonhomme__DevenirInvisible(CBonhomme * this, const int nbetape);
extern void CBonhomme__Avancer(CBonhomme * this, const TDirection Direction, const riemann_t * our_manifold); 
extern void CBonhomme__AjouterOrdresDeplacement_vP(CBonhomme * this, const TPoint3D pos);
extern void CBonhomme__AjouterOrdresDeplacement_vXY(CBonhomme * this, const float x, const float y, const TMethodePlacement mp);
extern void CBonhomme__TraiterOrdresDeplacement(CBonhomme * this, const CMap * Map, const riemann_t * our_manifold, const bool MoteurPhysiqueActif);
extern void CBonhomme__ViderOrdresDeplacement(CBonhomme * this);
extern bool CBonhomme__IsSoumisADesOrdres(const CBonhomme * this);



#endif /* BONHOMME_H */
