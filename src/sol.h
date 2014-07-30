#ifndef SOL_H
#define SOL_H

//#include "ressource.h"

struct CTexture;
struct TPoint2D;
struct TPoint3D;

struct TPointEcran;

struct TPointEcran {
  TPoint3D pt, normal;       
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TPointEcran);
DEFINE_NEW_OPERATOR_FOR_STRUCT(TPointEcran);

#define marche_compression_defaut 0.0050f

/* précision, nb_phi, nb_theta pour le tore */


#define nb_cases_afficheesX 25
#define nb_cases_afficheesYfond 20
#define nb_cases_afficheesYdevant 10
#define NB_MAX_TEXTURESOL 10


// Cette structe stocke une carte
struct CSol {
  //protected:
  float ybase;
  float R, a;
  int nb_phi, nb_theta;     
  
  float temps;
  
  // texture de sol
  //ressource<CTexture> * TextureSol[NB_MAX_TEXTURESOL];
  CTexture * TextureSol[NB_MAX_TEXTURESOL];
  int nb_texture;
  int indices_dans_bitmap[NB_MAX_TEXTURESOL];
  
  // données de la carte
  float * Z; // tableaud de taille TailleX * TailleY
  
  TPointEcran * PointsEcran;
  int * indices_texture;

  // taille en case de la carte, c'est ChargerZ qui s'occupe de remplir ça
  //public:
  int TailleX, TailleY;
  
  float ZEau;// = 45.8f;




  
  void SETZ(int x, int y, float z);
  /*en privée, un élément de l'extérieur n'a pas le droit de modifier le terrain
    utiliser "ChargerZ" pour cela*/
  
  
  void SETINDTEXTURE(int x, int y, int ind);
  int GETINDTEXTURE(int x, int y) const;
  
  TPoint3D GetPoint3D(float i, float j, float z) const;
  void tore(int i,int j) const;
  void tore0(int i,int j) const;
  
  
  void CalcPoints(int i1, int j1, int i2, int j2) const;

  //public:
  CSol(const bool EnVaisseau);
  ~CSol();
  
  int GetTailleX(void) const;
  int GetTailleY(void) const;
  
  void AfficherCube(float x1, float y1, float z1, float dx, float dy, float dz) const;
  //utiliser pour Debuguer
  
  float FacteurCompression(float j) const;
  float IndiceTemps(float j) const;
  /*ajouter une texture de sol (fichier s)
  indice_dans_bitmap représente la couleur des zones de cette texture dans le fichier
  chargé après dans ChargerIndiceTextureBitmap*/
  void AjouterTextureSol(const char * s, int indice_dans_bitmap);
  
  /*charge le fichier bitmap qui contient les zones pour les textures
    il faut faire appel à ChargerIndiceTextureBitmap après avoir fait les
    AjouterTextureSol
    (à priori fichier_bitmap désigne un fichier dans le répertoire
    "../cartes/")*/
  void ChargerIndiceTextureBitmap(const char * fichier_bitmap);
  
  void LookAt(float i, float j, float z) const; /*place la caméra au dessus du point (i, j)*/
  void LookAt(float i, float j, float z, float dist, float AngleXY, float AngleZ) const; /*place la caméra au dessus du point (i, j)*/
  void Render(int i1, int j1, int i2, int j2) const; /*dessine la partie du tore entre (i1, j1) et (i2, j2)*/
  void RenderEau(int i1, int j1, int i2, int j2) const;
  bool yatilEau(float i, float j, float z) const;
	
  /*affiche une image 2D en (i, j) (position centrale au sol), d'altitude z, de texture tex,
    et de taille définie*/
  void Blit(float i, float j, float z, CTexture* tex, float taillex, float tailleh);
  void Cube(float i, float j, float z, float taillex, float tailleh);
  void PositionModulo(float& i, float& j) const;
  void MatricePourDessiner(float i, float j);
  TPoint2D Differentiel(TPoint3D pos) const;

  
	
  /*donne en fonction de la position en theta le facteur de compression
    il est le plus élevé à l'extérieur du tore, le plus petit à l'intérieur
    et vaut 1 sur le dessus, ou le dessous*/
  void ChargerZ(const char * filename);
  float GETZ(float x, float y) const;
	
  void MatricePour2D(float i, float j, float z) const;
	
  void glVertexTore(float x, float y, float z) const;
	
  void SetTemps(float temps);
  float GetTemps(void) const;
	
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(CSol);
DEFINE_NEW_OPERATOR_FOR_STRUCT(CSol);










#endif /* SOL_HPP */
